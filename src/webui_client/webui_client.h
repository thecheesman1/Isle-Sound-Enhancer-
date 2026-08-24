#pragma once

#include <atomic>
#include <mutex>
#include <string>
#include <thread>

#include "dsp/dsp_engine.h"  // ise::Pos

// WebUI data client — contract from DESIGN.md section 2 (helper-1, piece 1).
//
// Endpoints (session-authenticated via Cookie: session=<cookie>, except the
// static grid binary):
//   /api/map/rtgrid    GET  login  {success, built, meta, grid_url} — 30 s
//   /static/data/rtgrid.bin  static  fetch with ?v=<built_at>
//   /api/headings      GET  login  {success, players:{sid:{heading,x,y,z}}}
//                                   — 2 Hz (this is the position source)
//   /api/admin/zone-masks  GET  login  {success, masks:{zone:{w,h,mask[]}}}
//                                   — on load
//   /api/map/position  GET  login  RCON fallback for a single sid
//   (LIVE payload is NESTED: {success, position:{x,y,z,heading,in_game}, error}
//   — the WinHTTP loop must parse position.*; matches the deployed endpoint.)
//
// Auth: the session cookie is read at RUNTIME from the user's browser store
// (Chrome/Edge cookie db or manual paste) — never embedded in the binary.
// Invalid session -> 302 to /login: surface "re-auth needed" to the user.
//
// Implementation uses WinHTTP on a background thread; the shell reads the
// latest snapshot via snapshot() (mutex-protected). Poll timings follow
// DESIGN.md 2.3: headings 2 Hz, rtgrid meta every 30 s, zone-masks once.

struct WebUiState {
  bool headingsValid = false;
  std::string playersJson;      // raw payload, parsed by the DSP/UI layer
  ise::Pos myPos;               // local player's last known position
  float gridBuiltAt = 0.0f;
  bool gridLoaded = false;
  bool masksLoaded = false;
};

class WebUIClient {
 public:
  explicit WebUIClient(std::string baseUrl, std::string sessionCookie);
  ~WebUIClient();

  WebUIClient(const WebUIClient&) = delete;
  WebUIClient& operator=(const WebUIClient&) = delete;

  bool start();     // spawn the polling thread
  void stop();      // signal + join the thread
  WebUiState snapshot() const;

 private:
  void run();                       // polling loop
  void pollHeadings();
  void pollGridMeta();
  void loadZoneMasks();
  std::string httpGet(const std::string& path) const;

  std::string baseUrl_;
  std::string sessionCookie_;
  std::atomic<bool> running_{false};
  std::thread thread_;
  mutable std::mutex mutex_;
  WebUiState state_;
};
