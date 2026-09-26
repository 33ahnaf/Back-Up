# PMFC Live Data → Neon.tech → Google AI Studio App

Architecture:

```
ESP32 (ADS1115 readings)
   |  HTTPS POST every 5s
   v
Node/Express API  (hosted free on Render)
   |  SQL insert
   v
Neon.tech Postgres
   ^  SQL select
   |
Node/Express API  (same one, GET endpoint)
   ^  fetch() poll every 2s
   |
Your Google AI Studio web app
```

The ESP32 can't talk directly to Postgres, so the small Node API in
`server/` acts as the bridge: it accepts pushes from the ESP32 and
serves the latest reading as JSON for your app to poll.

---

## Step 1 — Create the Neon database

1. Go to https://neon.tech and sign up / log in.
2. Click **New Project**, give it a name (e.g. `pmfc`), pick a region close to you.
3. Once created, open the **SQL Editor** in the Neon console.
4. Paste in the contents of `server/schema.sql` and run it. This creates the `readings` table.
5. Go to **Connection Details** (or **Dashboard → Connection string**) and copy the full
   connection string. It looks like:
   ```
   postgresql://USER:PASSWORD@ep-xxxx-xxxx.region.aws.neon.tech/neondb?sslmode=require
   ```
   You'll need this in Step 2.

---

## Step 2 — Deploy the backend (Render, free tier)

You need somewhere to run `server/index.js` 24/7 so both the ESP32 and your app can reach it.
Render's free web service tier works well for this.

1. Create a new GitHub repo and push the contents of the `server/` folder to it
   (just `index.js`, `package.json`, `schema.sql` — `.env` is only for local testing, don't commit real secrets).
2. Go to https://render.com, sign up, click **New +** → **Web Service**.
3. Connect your GitHub repo.
4. Configure:
   - **Build command:** `npm install`
   - **Start command:** `npm start`
   - **Instance type:** Free
5. Under **Environment**, add these variables:
   - `DATABASE_URL` = the Neon connection string from Step 1
   - `DEVICE_API_KEY` = make up any long random string, e.g. `pmfc-9f2a7d61c8`
6. Click **Create Web Service**. Wait for the deploy to finish.
7. Render gives you a public URL like `https://pmfc-neon-bridge.onrender.com`.
   Test it in a browser — you should see `{"status":"ok", ...}`.

Note: Render's free tier sleeps after inactivity and takes ~30–60s to wake on
the next request. That's fine for a hobby dashboard; if you need it always-warm,
upgrade the instance or use an uptime pinger.

---

## Step 3 — Configure and flash the ESP32

Open `esp32/pmfc_esp32_neon.ino` in Arduino IDE.

1. Install the extra library via **Library Manager**: **ArduinoJson** (by Benoit Blanchon).
   (You should already have `TFT_eSPI` and `Adafruit_ADS1X15` from your existing project.)
2. Edit these lines near the top:
   ```cpp
   const char* WIFI_SSID     = "YOUR_WIFI_NAME";
   const char* WIFI_PASSWORD = "YOUR_WIFI_PASSWORD";
   const char* SERVER_URL    = "https://pmfc-neon-bridge.onrender.com/api/readings"; // your Render URL + /api/readings
   const char* DEVICE_API_KEY = "pmfc-9f2a7d61c8"; // must match Render's DEVICE_API_KEY exactly
   ```
3. Upload to the ESP32. Open the Serial Monitor at 115200 baud — you should see:
   ```
   WiFi connected, IP: 192.168.x.x
   Push OK, server responded 200
   ```
   printed every ~5 seconds.
4. Check Neon: run `SELECT * FROM readings ORDER BY created_at DESC LIMIT 5;` in the SQL Editor
   to confirm rows are landing.

What changed vs. your original sketch: WiFi connect in `setup()`, a `sendDataToServer()`
function called every 5s from `loop()`, and voltage/power are now recalculated every loop
regardless of which screen is open (previously they only updated while the Power app screen
was on-screen), so the cloud always gets fresh data.

---

## Step 4 — Wire it into your Google AI Studio app

Google AI Studio "Build" apps are editable web apps (HTML/JS, sometimes React). Since the
backend already has CORS enabled, you can fetch it directly from the browser.

**Easiest path:** open your app in AI Studio and give it a prompt like this:

> Add a live dashboard section that polls `https://pmfc-neon-bridge.onrender.com/api/readings/latest`
> every 2 seconds using fetch, and shows 4 cards (Cell 1–4) each with voltage (V) and power (mW),
> updating in place without a full page reload.

**Or paste this snippet directly** into the app's code editor and adapt it to fit the app's structure:

```html
<div id="pmfc-cells" style="display:flex; gap:12px; flex-wrap:wrap;"></div>

<script>
const API_URL = "https://pmfc-neon-bridge.onrender.com/api/readings/latest";

async function refreshReadings() {
  try {
    const res = await fetch(API_URL);
    const data = await res.json();
    if (!data.cells) return;

    const container = document.getElementById("pmfc-cells");
    container.innerHTML = data.cells.map((c, i) => `
      <div style="background:#f2f2f7;border:1px solid #e5e5ea;border-radius:12px;
                  padding:14px;min-width:140px;text-align:center;">
        <h3 style="margin:0 0 8px;color:#34c759;">CELL ${i + 1}</h3>
        <p style="margin:4px 0;font-size:20px;">${c.v.toFixed(3)} V</p>
        <p style="margin:4px 0;font-size:20px;">${c.p.toFixed(2)} mW</p>
      </div>
    `).join("");
  } catch (err) {
    console.error("Failed to fetch readings:", err);
  }
}

refreshReadings();
setInterval(refreshReadings, 2000); // poll every 2 seconds
</script>
```

For a React-style AI Studio app, wrap the same fetch logic in a `useEffect` with
`setInterval`, storing `data.cells` in `useState` and mapping over it in JSX instead
of using `innerHTML`.

---

## Security notes

- `DEVICE_API_KEY` stops randoms from writing fake data to your table — keep it out of
  any public GitHub repo containing the ESP32 sketch, or use a `secrets.h` file that's
  gitignored.
- The ESP32 code uses `client.setInsecure()` to skip TLS certificate validation, which
  is common for hobby projects but doesn't verify the server's identity. If that matters
  for your use case, pin the server's certificate instead.
- The `/api/readings/latest` GET endpoint has no auth, since it's meant to be read by
  your public-facing app. Don't put anything sensitive in that table.
