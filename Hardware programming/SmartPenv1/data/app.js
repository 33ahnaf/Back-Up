// =============================================================================
// app.js — SmartPen browser client
// =============================================================================
// Responsibilities:
//   - Maintain a WebSocket connection to the ESP32 (with auto-reconnect)
//   - Draw incoming (x, y, pen) points onto the main canvas
//   - Track connection status / FPS / latency for the header readouts
//   - Render small debug sparkline graphs (velocity, position trace)
// No external libraries/CDNs — the device is an offline access point, so
// everything here must be self-contained.
// =============================================================================

(() => {
  "use strict";

  // ---------------------------------------------------------------------
  // DOM references
  // ---------------------------------------------------------------------
  const canvas = document.getElementById("pen-canvas");
  const ctx = canvas.getContext("2d");

  const velGraph = document.getElementById("graph-velocity");
  const posGraph = document.getElementById("graph-position");
  const velCtx = velGraph.getContext("2d");
  const posCtx = posGraph.getContext("2d");

  const connValueEl = document.getElementById("conn-value");
  const connStatEl = document.getElementById("stat-conn");
  const fpsValueEl = document.getElementById("fps-value");
  const latencyValueEl = document.getElementById("latency-value");
  const penValueEl = document.getElementById("pen-value");
  const penStatEl = document.getElementById("stat-pen");
  const crosshairEl = document.getElementById("crosshair-readout");
  const reconnectBanner = document.getElementById("reconnect-banner");

  const dbgX = document.getElementById("dbg-x");
  const dbgY = document.getElementById("dbg-y");
  const dbgVx = document.getElementById("dbg-vx");
  const dbgVy = document.getElementById("dbg-vy");
  const dbgStat = document.getElementById("dbg-stat");
  const dbgDt = document.getElementById("dbg-dt");

  const clearBtn = document.getElementById("clear-btn");
  const panel = document.getElementById("debug-panel");
  const panelToggle = document.getElementById("panel-toggle");

  // ---------------------------------------------------------------------
  // Canvas sizing (device-pixel-ratio aware, so strokes stay crisp)
  // ---------------------------------------------------------------------
  let dpr = Math.max(1, window.devicePixelRatio || 1);
  let originX = 0, originY = 0; // canvas-space origin the pen's (0,0) maps to

  function resizeCanvas(cv, context) {
    const rect = cv.getBoundingClientRect();
    cv.width = Math.round(rect.width * dpr);
    cv.height = Math.round(rect.height * dpr);
    context.setTransform(dpr, 0, 0, dpr, 0, 0);
    return rect;
  }

  function resizeAll() {
    const rect = resizeCanvas(canvas, ctx);
    originX = rect.width / 2;
    originY = rect.height / 2;
    resizeCanvas(velGraph, velCtx);
    resizeCanvas(posGraph, posCtx);
    redrawStrokes(); // preserve drawing across resize/orientation change
  }
  window.addEventListener("resize", resizeAll);

  // ---------------------------------------------------------------------
  // Stroke storage — kept as an array of strokes (each an array of
  // {x,y} points) so we can redraw cleanly after a resize and so "pen up"
  // cleanly breaks the line instead of connecting unrelated strokes.
  // ---------------------------------------------------------------------
  let strokes = [];
  let currentStroke = null;
  let wasPenDown = false;

  function beginStroke(x, y) {
    currentStroke = [{ x, y }];
    strokes.push(currentStroke);
  }

  function extendStroke(x, y) {
    if (!currentStroke) { beginStroke(x, y); return; }
    currentStroke.push({ x, y });
  }

  function drawStroke(strokeIdx, stroke) {
    if (stroke.length < 2) return;

    // Phosphor-style persistence: older strokes fade toward the dim ink
    // color instead of disappearing outright — gives the canvas the feel
    // of a plotter/scope trace rather than a flat vector drawing.
    const age = strokes.length - 1 - strokeIdx;
    const alpha = Math.max(0.35, 1 - age * 0.05);

    ctx.beginPath();
    ctx.moveTo(originX + stroke[0].x, originY + stroke[0].y);
    for (let i = 1; i < stroke.length; i++) {
      ctx.lineTo(originX + stroke[i].x, originY + stroke[i].y);
    }
    ctx.strokeStyle = `rgba(255, 162, 60, ${alpha})`;
    ctx.lineWidth = 2;
    ctx.lineJoin = "round";
    ctx.lineCap = "round";
    ctx.shadowColor = "rgba(255, 162, 60, 0.5)";
    ctx.shadowBlur = 4;
    ctx.stroke();
  }

  function redrawStrokes() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    strokes.forEach((s, i) => drawStroke(i, s));
  }

  function clearCanvas() {
    strokes = [];
    currentStroke = null;
    wasPenDown = false;
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    // Ask the firmware to zero its integrator too, so the next incoming
    // point starts fresh instead of jumping from wherever drift had left
    // the on-device position.
    sendCommand("reset");
  }
  clearBtn.addEventListener("click", clearCanvas);

  // ---------------------------------------------------------------------
  // Debug sparkline graphs — small rolling-window line charts, hand
  // rolled (no charting library needed for something this simple).
  // ---------------------------------------------------------------------
  const HISTORY_LEN = 150;
  const velXHistory = [];
  const velYHistory = [];
  const posXHistory = [];
  const posYHistory = [];

  function pushHistory(arr, value) {
    arr.push(value);
    if (arr.length > HISTORY_LEN) arr.shift();
  }

  function drawSparkline(context, cv, seriesA, seriesB, colorA, colorB, symmetric) {
    const w = cv.getBoundingClientRect().width;
    const h = cv.getBoundingClientRect().height;
    context.clearRect(0, 0, w, h);

    const all = seriesA.concat(seriesB);
    if (all.length === 0) return;
    let maxAbs = Math.max(1e-6, ...all.map(Math.abs));

    const midY = h / 2;
    // Zero line
    context.strokeStyle = "rgba(255,255,255,0.08)";
    context.lineWidth = 1;
    context.beginPath();
    context.moveTo(0, symmetric ? midY : h - 1);
    context.lineTo(w, symmetric ? midY : h - 1);
    context.stroke();

    const plot = (series, color) => {
      if (series.length < 2) return;
      context.beginPath();
      series.forEach((v, i) => {
        const x = (i / (HISTORY_LEN - 1)) * w;
        const norm = v / maxAbs; // -1..1
        const y = symmetric ? midY - norm * (h / 2 - 4) : h - 4 - Math.abs(norm) * (h - 8);
        if (i === 0) context.moveTo(x, y); else context.lineTo(x, y);
      });
      context.strokeStyle = color;
      context.lineWidth = 1.5;
      context.stroke();
    };

    plot(seriesA, colorA);
    plot(seriesB, colorB);
  }

  function redrawDebugGraphs() {
    drawSparkline(velCtx, velGraph, velXHistory, velYHistory,
                  "rgba(255,162,60,0.9)", "rgba(111,214,196,0.9)", true);
    drawSparkline(posCtx, posGraph, posXHistory, posYHistory,
                  "rgba(255,162,60,0.9)", "rgba(111,214,196,0.9)", true);
  }

  // ---------------------------------------------------------------------
  // WebSocket connection, with auto-reconnect and a lightweight ping/pong
  // latency measurement.
  // ---------------------------------------------------------------------
  let socket = null;
  let reconnectDelayMs = 500;
  const MAX_RECONNECT_DELAY_MS = 5000;
  let pingSentAt = 0;
  let frameTimestamps = [];

  function setConnected(isConnected) {
    connStatEl.classList.toggle("connected", isConnected);
    connValueEl.textContent = isConnected ? "ONLINE" : "OFFLINE";
    reconnectBanner.classList.toggle("visible", !isConnected);
  }

  function sendCommand(cmd) {
    if (socket && socket.readyState === WebSocket.OPEN) {
      socket.send(cmd);
    }
  }

  function wsUrl() {
    const proto = location.protocol === "https:" ? "wss:" : "ws:";
    return `${proto}//${location.host}/ws`;
  }

  function connect() {
    setConnected(false);
    connValueEl.textContent = "CONNECTING";

    socket = new WebSocket(wsUrl());

    socket.onopen = () => {
      setConnected(true);
      reconnectDelayMs = 500; // reset backoff on success
    };

    socket.onclose = () => {
      setConnected(false);
      scheduleReconnect();
    };

    socket.onerror = () => {
      // onclose will still fire after onerror, so just let that path
      // handle the reconnect scheduling.
    };

    socket.onmessage = (event) => {
      if (event.data === "pong") {
        const rtt = performance.now() - pingSentAt;
        latencyValueEl.textContent = `${rtt.toFixed(0)} ms`;
        return;
      }
      handleFrame(event.data);
    };
  }

  function scheduleReconnect() {
    setTimeout(connect, reconnectDelayMs);
    reconnectDelayMs = Math.min(reconnectDelayMs * 1.5, MAX_RECONNECT_DELAY_MS);
  }

  // Periodic ping for latency — cheap, and doubles as a keepalive so idle
  // NAT/AP timeouts don't silently drop the socket.
  setInterval(() => {
    if (socket && socket.readyState === WebSocket.OPEN) {
      pingSentAt = performance.now();
      sendCommand("ping");
    }
  }, 2000);

  // ---------------------------------------------------------------------
  // Frame handling
  // ---------------------------------------------------------------------
  function handleFrame(raw) {
    let f;
    try {
      f = JSON.parse(raw);
    } catch (e) {
      return; // malformed packet — drop it rather than crash the UI
    }

    // FPS: rolling count of frames received in the last second.
    const now = performance.now();
    frameTimestamps.push(now);
    while (frameTimestamps.length && now - frameTimestamps[0] > 1000) {
      frameTimestamps.shift();
    }
    fpsValueEl.textContent = frameTimestamps.length.toString();

    const penDown = !!f.pen;
    penValueEl.textContent = penDown ? "WRITING" : "IDLE";
    penStatEl.classList.toggle("writing", penDown);

    if (penDown) {
      if (!wasPenDown) {
        beginStroke(f.x, f.y);
      } else {
        extendStroke(f.x, f.y);
      }
      // Incrementally draw just the new segment rather than redrawing the
      // whole canvas every frame — keeps this cheap at 60Hz.
      if (currentStroke && currentStroke.length >= 2) {
        const n = currentStroke.length;
        const p0 = currentStroke[n - 2];
        const p1 = currentStroke[n - 1];
        ctx.beginPath();
        ctx.moveTo(originX + p0.x, originY + p0.y);
        ctx.lineTo(originX + p1.x, originY + p1.y);
        ctx.strokeStyle = "rgba(255, 162, 60, 1)";
        ctx.lineWidth = 2;
        ctx.lineJoin = "round";
        ctx.lineCap = "round";
        ctx.shadowColor = "rgba(255, 162, 60, 0.6)";
        ctx.shadowBlur = 5;
        ctx.stroke();
      }
    } else {
      currentStroke = null;
    }
    wasPenDown = penDown;

    crosshairEl.textContent = `x: ${f.x.toFixed(1)}   y: ${f.y.toFixed(1)}`;

    // Debug readouts + sparklines
    dbgX.textContent = f.x.toFixed(2);
    dbgY.textContent = f.y.toFixed(2);
    dbgVx.textContent = (f.vx ?? 0).toFixed(3);
    dbgVy.textContent = (f.vy ?? 0).toFixed(3);
    dbgStat.textContent = f.stationary ? "yes" : "no";
    dbgDt.textContent = f.dt ? `${(f.dt / 1000).toFixed(1)} ms` : "--";

    pushHistory(velXHistory, f.vx ?? 0);
    pushHistory(velYHistory, f.vy ?? 0);
    pushHistory(posXHistory, f.x ?? 0);
    pushHistory(posYHistory, f.y ?? 0);
  }

  // Debug graphs redraw independently at a modest fixed rate — no need to
  // tie this to every incoming WebSocket message.
  setInterval(() => {
    if (!panel.classList.contains("collapsed")) redrawDebugGraphs();
  }, 100);

  // ---------------------------------------------------------------------
  // Debug panel collapse/expand
  // ---------------------------------------------------------------------
  panelToggle.addEventListener("click", () => {
    const collapsed = panel.classList.toggle("collapsed");
    panelToggle.textContent = collapsed ? "DEBUG \u25BC" : "DEBUG \u25B2";
  });

  // ---------------------------------------------------------------------
  // Boot
  // ---------------------------------------------------------------------
  resizeAll();
  connect();
})();
