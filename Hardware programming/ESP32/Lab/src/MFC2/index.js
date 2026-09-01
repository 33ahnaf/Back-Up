// server/index.js
//
// A tiny Express API sitting between your ESP32 and Neon Postgres.
//
// POST /api/readings        <- ESP32 pushes a new reading here
// GET  /api/readings/latest <- your web app (Google AI Studio app) polls this
// GET  /api/readings/history?limit=50 <- optional, for charts
//
// Env vars needed (set these in Render/Railway, or a local .env file):
//   DATABASE_URL   -> Neon connection string (Settings > Connection string)
//   DEVICE_API_KEY -> any random secret string you make up, shared with the ESP32
//   PORT           -> optional, defaults to 3000

require('dotenv').config();
const express = require('express');
const cors = require('cors');
const { Pool } = require('pg');

const app = express();
app.use(express.json());
app.use(cors()); // allow the browser-based app to fetch from any origin

const pool = new Pool({
  connectionString: process.env.DATABASE_URL,
  ssl: { rejectUnauthorized: false }, // Neon requires SSL
});

const DEVICE_API_KEY = process.env.DEVICE_API_KEY || 'change-me';

// --- Health check ---
app.get('/', (req, res) => {
  res.json({ status: 'ok', service: 'pmfc-neon-bridge' });
});

// --- ESP32 pushes a reading here ---
app.post('/api/readings', async (req, res) => {
  try {
    const key = req.header('x-api-key');
    if (key !== DEVICE_API_KEY) {
      return res.status(401).json({ error: 'invalid api key' });
    }

    const { cells } = req.body;
    if (!Array.isArray(cells) || cells.length !== 4) {
      return res.status(400).json({ error: 'expected { cells: [ {v,p} x4 ] }' });
    }

    const values = [];
    cells.forEach((c) => {
      values.push(Number(c.v), Number(c.p));
    });

    const result = await pool.query(
      `INSERT INTO readings
         (cell1_v, cell1_p, cell2_v, cell2_p, cell3_v, cell3_p, cell4_v, cell4_p)
       VALUES ($1,$2,$3,$4,$5,$6,$7,$8)
       RETURNING id, created_at`,
      values
    );

    res.json({ ok: true, id: result.rows[0].id, created_at: result.rows[0].created_at });
  } catch (err) {
    console.error('POST /api/readings failed:', err);
    res.status(500).json({ error: 'internal error' });
  }
});

// --- Web app polls this for the most recent reading ---
app.get('/api/readings/latest', async (req, res) => {
  try {
    const result = await pool.query(
      `SELECT * FROM readings ORDER BY created_at DESC LIMIT 1`
    );
    if (result.rows.length === 0) {
      return res.json({ cells: null });
    }
    const r = result.rows[0];
    res.json({
      created_at: r.created_at,
      cells: [
        { v: r.cell1_v, p: r.cell1_p },
        { v: r.cell2_v, p: r.cell2_p },
        { v: r.cell3_v, p: r.cell3_p },
        { v: r.cell4_v, p: r.cell4_p },
      ],
    });
  } catch (err) {
    console.error('GET /api/readings/latest failed:', err);
    res.status(500).json({ error: 'internal error' });
  }
});

// --- Optional: recent history, handy for a chart in the app ---
app.get('/api/readings/history', async (req, res) => {
  try {
    const limit = Math.min(parseInt(req.query.limit) || 50, 500);
    const result = await pool.query(
      `SELECT * FROM readings ORDER BY created_at DESC LIMIT $1`,
      [limit]
    );
    res.json(result.rows.reverse());
  } catch (err) {
    console.error('GET /api/readings/history failed:', err);
    res.status(500).json({ error: 'internal error' });
  }
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => console.log(`pmfc-neon-bridge listening on port ${PORT}`));
