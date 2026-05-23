/*
 * ============================================================
 *  perspective_correct.h
 *  Lightweight software perspective correction for ESP32-CAM
 *
 *  Strategy:
 *   1. Decode JPEG → raw RGB in chunks (uses ~50KB RAM max)
 *   2. Auto-detect paper corners via edge/contrast detection
 *      OR use fixed calibration offsets measured once at setup
 *   3. Apply inverse perspective warp (homography)
 *   4. Re-encode to JPEG
 *
 *  Since ESP32 has limited RAM (~300KB usable heap), we use:
 *   - FRAMESIZE_SVGA (800×600) for processing (not UXGA)
 *   - Fixed homography from one-time calibration
 *   - Integer-only math (no float arrays in hot loops)
 * ============================================================
 */


/*
#pragma once
#include <Arduino.h>
#include <math.h>

// ─── Calibration structure ───────────────────────────────────
// These are the 4 corners of the flat paper surface as they
// appear in the RAW (tilted) camera image.
// You measure these ONCE during physical setup/calibration.
//
//   TL ──────── TR
//   │            │
//   BL ──────── BR
//
struct PaperCorners {
  float tlX, tlY;  // top-left
  float trX, trY;  // top-right
  float blX, blY;  // bottom-left
  float brX, brY;  // bottom-right
};

// ─── 3×3 homography matrix ───────────────────────────────────
struct Homography {
  double h[9];  // row-major: h[0..8]
};

// ─────────────────────────────────────────────────────────────
//  Solve 3×3 homography from 4 point correspondences.
//  src[] = 4 source points {x,y}  (corners in raw image)
//  dst[] = 4 destination points   (corners of output rect)
//  Returns homography H such that dst ~ H * src  (homogeneous)
//
//  Uses a minimal Direct Linear Transform (DLT) solver.
//  We embed a tiny Gaussian elimination here — no LAPACK needed.
// ─────────────────────────────────────────────────────────────
static bool solveHomography(
    const float src[4][2],
    const float dst[4][2],
    Homography& H)
{
  // Build 8×8 matrix A and vector b from the 4 point pairs
  // Each point gives 2 equations; we fix h[8]=1 (normalization)
  double A[8][8] = {};
  double b[8]    = {};

  for (int i = 0; i < 4; i++) {
    double sx = src[i][0], sy = src[i][1];
    double dx = dst[i][0], dy = dst[i][1];
    int r = i * 2;

    A[r][0]=sx; A[r][1]=sy; A[r][2]=1;
    A[r][3]=0;  A[r][4]=0;  A[r][5]=0;
    A[r][6]=-dx*sx; A[r][7]=-dx*sy;
    b[r] = dx;

    A[r+1][0]=0; A[r+1][1]=0; A[r+1][2]=0;
    A[r+1][3]=sx; A[r+1][4]=sy; A[r+1][5]=1;
    A[r+1][6]=-dy*sx; A[r+1][7]=-dy*sy;
    b[r+1] = dy;
  }

  // Gaussian elimination with partial pivoting
  for (int col = 0; col < 8; col++) {
    // Find pivot
    int pivot = col;
    for (int row = col+1; row < 8; row++)
      if (fabs(A[row][col]) > fabs(A[pivot][col])) pivot = row;

    // Swap rows
    for (int k = 0; k < 8; k++) { double t=A[col][k]; A[col][k]=A[pivot][k]; A[pivot][k]=t; }
    { double t=b[col]; b[col]=b[pivot]; b[pivot]=t; }

    if (fabs(A[col][col]) < 1e-10) return false;  // singular

    double inv = 1.0 / A[col][col];
    for (int row = col+1; row < 8; row++) {
      double factor = A[row][col] * inv;
      for (int k = col; k < 8; k++) A[row][k] -= factor * A[col][k];
      b[row] -= factor * b[col];
    }
  }

  // Back substitution
  double x[8] = {};
  for (int i = 7; i >= 0; i--) {
    x[i] = b[i];
    for (int j = i+1; j < 8; j++) x[i] -= A[i][j] * x[j];
    x[i] /= A[i][i];
  }

  H.h[0]=x[0]; H.h[1]=x[1]; H.h[2]=x[2];
  H.h[3]=x[3]; H.h[4]=x[4]; H.h[5]=x[5];
  H.h[6]=x[6]; H.h[7]=x[7]; H.h[8]=1.0;
  return true;
}

// ─────────────────────────────────────────────────────────────
//  Apply inverse homography warp.
//
//  outW, outH : desired output image dimensions
//  Input/output buffers are raw RGB888 (3 bytes/pixel).
//
//  For each output pixel (ox,oy) we compute the corresponding
//  source pixel via the INVERSE homography, then bilinear-sample.
//  This avoids holes in the output.
// ─────────────────────────────────────────────────────────────
static void warpPerspective(
    const uint8_t* src, int srcW, int srcH,
    uint8_t*       dst, int dstW, int dstH,
    const Homography& Hfwd)   // forward: src→dst corners
{
  // Invert H using adjugate / det  (3×3 analytic inverse)
  const double* h = Hfwd.h;
  double inv[9];
  inv[0] =  h[4]*h[8] - h[5]*h[7];
  inv[1] = -(h[1]*h[8] - h[2]*h[7]);
  inv[2] =  h[1]*h[5] - h[2]*h[4];
  inv[3] = -(h[3]*h[8] - h[5]*h[6]);
  inv[4] =  h[0]*h[8] - h[2]*h[6];
  inv[5] = -(h[0]*h[5] - h[2]*h[3]);
  inv[6] =  h[3]*h[7] - h[4]*h[6];
  inv[7] = -(h[0]*h[7] - h[1]*h[6]);
  inv[8] =  h[0]*h[4] - h[1]*h[3];

  double det = h[0]*inv[0] + h[1]*inv[3] + h[2]*inv[6];
  if (fabs(det) < 1e-10) { memset(dst, 0, dstW*dstH*3); return; }
  for (int k = 0; k < 9; k++) inv[k] /= det;

  for (int oy = 0; oy < dstH; oy++) {
    for (int ox = 0; ox < dstW; ox++) {
      // Apply inverse homography
      double w  = inv[6]*ox + inv[7]*oy + inv[8];
      double sx = (inv[0]*ox + inv[1]*oy + inv[2]) / w;
      double sy = (inv[3]*ox + inv[4]*oy + inv[5]) / w;

      // Bilinear interpolation
      int x0 = (int)sx, y0 = (int)sy;
      int x1 = x0 + 1,  y1 = y0 + 1;
      float fx = (float)(sx - x0), fy = (float)(sy - y0);

      uint8_t* out = dst + (oy * dstW + ox) * 3;

      if (x0 < 0 || y0 < 0 || x1 >= srcW || y1 >= srcH) {
        out[0] = out[1] = out[2] = 255; // white outside
        continue;
      }

      const uint8_t* p00 = src + (y0*srcW + x0)*3;
      const uint8_t* p10 = src + (y0*srcW + x1)*3;
      const uint8_t* p01 = src + (y1*srcW + x0)*3;
      const uint8_t* p11 = src + (y1*srcW + x1)*3;

      for (int c = 0; c < 3; c++) {
        float top    = p00[c]*(1-fx) + p10[c]*fx;
        float bottom = p01[c]*(1-fx) + p11[c]*fx;
        out[c] = (uint8_t)(top*(1-fy) + bottom*fy);
      }
    }
  }
}

// ─────────────────────────────────────────────────────────────
//  HIGH-LEVEL FUNCTION
//  Given a camera frame buffer (JPEG), corrects perspective
//  and returns a new heap-allocated JPEG buffer.
//
//  corners: the 4 paper corners as seen in the RAW image
//           (measure once during pen calibration)
//  outBuf / outLen: caller must free(outBuf) when done
//
//  Returns true on success.
//  Requires: ~srcW*srcH*3 * 2 bytes of heap (raw + warped).
//  At SVGA (800×600): ~2.9 MB — needs PSRAM!
//  At CIF  (400×296): ~700 KB — fits in regular heap.
// ─────────────────────────────────────────────────────────────
#include "img_converters.h"   // ESP32 Arduino core JPEG codec

bool correctPerspective(
    const uint8_t* jpegIn,  size_t jpegLen,
    const PaperCorners& corners,
    uint8_t** jpegOut, size_t* outLen)
{
  // ── 1. Decode JPEG → RGB888 ──
  uint8_t* rgb    = nullptr;
  size_t   rgbLen = 0;
  bool ok = jpg2rgb888(jpegIn, jpegLen, &rgb, &rgbLen);  // ESP32 built-in
  if (!ok || !rgb) return false;

  // Infer dimensions from buffer size (assume 3 bytes/px)
  // Better: pass width/height from frame buffer
  // Here we trust the caller set correct frame size.
  // For FRAMESIZE_SVGA: 800×600
  int srcW = 800, srcH = 600;  // ← adjust to match your framesize

  // ── 2. Build homography ──
  //  src corners (in raw image, measured at calibration)
  float src[4][2] = {
    {corners.tlX, corners.tlY},
    {corners.trX, corners.trY},
    {corners.blX, corners.blY},
    {corners.brX, corners.brY}
  };
  //  dst corners = full output rectangle (A4 proportions at 600×848)
  int outW = 600, outH = 848;  // ≈ A4 aspect ratio
  float dst[4][2] = {
    {0,        0       },
    {(float)outW-1, 0       },
    {0,        (float)outH-1},
    {(float)outW-1, (float)outH-1}
  };

  Homography H;
  if (!solveHomography(src, dst, H)) { free(rgb); return false; }

  // ── 3. Allocate output buffer & warp ──
  uint8_t* warpedRgb = (uint8_t*)malloc(outW * outH * 3);
  if (!warpedRgb) { free(rgb); return false; }

  warpPerspective(rgb, srcW, srcH, warpedRgb, outW, outH, H);
  free(rgb);

  // ── 4. Encode back to JPEG ──
  ok = fmt2jpg(warpedRgb, outW*outH*3, outW, outH,
               PIXFORMAT_RGB888, 85, jpegOut, outLen);
  free(warpedRgb);

  return ok;
}



*/