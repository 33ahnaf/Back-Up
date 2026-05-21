#ifndef _DSP_EFFECTS__H
#define _DSP_EFFECTS__H

#include <stdint.h>

#define REVERB_DELAY 250 // 250ms
#define JUNO_DELAY 50 // 50ms

typedef struct {
    float *buffer;
    int writePos;
    int size;

    void applyReverb(float *sample);
    void allocate(uint32_t sample_rate);
    void release(void);
} ReverbState;

typedef struct {
    float *buffer;
    int writePos;
    int size;
    float phase1;
    float phase2;

    void applyJuno(float *sample);
    void allocate(uint32_t sample_rate);
    void release(void);
} JunoState;

typedef struct {
    float low;
    float high;

    void applyEQ(uint8_t *sample, ReverbState *rs, JunoState *js);
} EQState;

void Reverb_Juno_allocate_all(uint32_t sample_rate, ReverbState *revL, ReverbState *revR, JunoState *junoL, JunoState *junoR);
void Reverb_Juno_release_all(ReverbState *revL, ReverbState *revR, JunoState *junoL, JunoState *junoR);

#endif