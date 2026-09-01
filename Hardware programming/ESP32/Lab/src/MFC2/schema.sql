-- Run this in the Neon SQL Editor (or via psql) once, to create the table
-- that stores every reading pushed up from the ESP32.

CREATE TABLE IF NOT EXISTS readings (
  id          SERIAL PRIMARY KEY,
  cell1_v     REAL NOT NULL,
  cell1_p     REAL NOT NULL,
  cell2_v     REAL NOT NULL,
  cell2_p     REAL NOT NULL,
  cell3_v     REAL NOT NULL,
  cell3_p     REAL NOT NULL,
  cell4_v     REAL NOT NULL,
  cell4_p     REAL NOT NULL,
  created_at  TIMESTAMPTZ NOT NULL DEFAULT now()
);

-- Speeds up "give me the most recent row" queries as the table grows
CREATE INDEX IF NOT EXISTS idx_readings_created_at ON readings (created_at DESC);
