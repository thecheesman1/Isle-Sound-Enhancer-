# Isle Sound Enhancer — client shell (scaffold)

Windows C++ client that applies the webui's acoustic simulation (echo/muffle)
to the Isle game's audio on the player's PC. See `task_list.md` / `AGENT2-HANDOFF.md`
in the webui repo for the project split; the authoritative design is
helper-1's design doc (piece 1), which gates this shell (piece 2).

## Status: SCAFFOLD — aligned to DESIGN.md final (design-sound-enhancer @ 2b1bd83)
- API contract (endpoints, auth, poll rates), DSP interface and install
  layout follow DESIGN.md sections 2 / 4 / 6.
- **Hook = Windows APO on the render endpoint (LOCKED, boss 2026-08-24)**:
  runs inside `audiodg.exe`, outside the game process, zero EAC surface,
  few-ms latency. WASAPI loopback = zero-risk fallback. Game DLL injection
  = documented why-not (EAC global-ban risk). `AudioHook` is the swappable
  slot; the APO implementation is the primary, loopback the fallback.
- **No-Pi-compilation rule (boss)**: nothing compiles on the Pi. Builds run
  on a dev machine or the client PC; release artifacts go to a central
  store (GitHub Releases on this repo / designated path) for a BIG RELEASE
  bundle that ships together. Pi deploy = already-built artifacts + webui
  file syncs only.
- `src/webui_client/` has the full contract + a linkable STUB (WinHTTP
  polling loop is the next piece-2 increment).
- DSP core slot = `src/dsp/dsp_engine.h` (ise::Grid / SubmergeTracker /
  AcousticEngine) — helper-1's piece 3.

## Layout
- `CMakeLists.txt`  — Windows C++17 build (MSVC, x64, static runtime)
- `src/main.cpp`    — entry point / shell wiring
- `src/audio_hook/` — swappable hook slot (APO primary / loopback fallback)
- `src/webui_client/` — data client (contract per DESIGN.md §2; stub impl)
- `src/dsp/`        — DSP core interface (helper-1, piece 3)
- `install/`        — NSIS installer (layout per DESIGN.md §4; APO registers
  the COM effect rather than dropping a game-dir DLL)
- `settings.json`   — app settings sample
- `BUILD.md`        — build + artifact flow (no-Pi-compile rule)

## Build (Windows / Visual Studio — dev machine / client PC only)
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release

Artifacts land in GitHub Releases (this repo) / designated central store;
never built on the Pi.

## Push status
Committed locally, UNPUSHED — piece 2 opens as its own PR once the design
branch (design-sound-enhancer) merges post-QA-gate.
