#pragma once

// WebUI data-client slot.
//
// Endpoint URLs, payloads, auth and poll rates are defined by the design
// doc (piece 1) - nothing contract-shaped is baked in here yet. Known
// candidates named in the split: rtgrid.bin (static), /api/headings,
// /api/prox/state, zone-masks.

struct WebUIClient {
  virtual ~WebUIClient() = default;

  virtual bool start() = 0;   // connect + begin polling per contract
  virtual void stop() = 0;    // flush + disconnect cleanly

  // Design doc will add the data surface the DSP needs:
  // positions, underwater state, zone/occlusion, grid samples.
};
