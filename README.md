# Isle Sound Enhancer — client shell (scaffold)

Windows C++ client that applies the webui's acoustic simulation (echo/muffle)
to the Isle game's audio on the player's PC. See `task_list.md` / `AGENT2-HANDOFF.md`
in the webui repo for the project split; the authoritative design is
helper-1's design doc (piece 1), which gates this shell (piece 2).

## Status: SCAFFOLD — aligned to DESIGN.md v0.1 (helper-1, piece 1, 7ccfec3)
- API contract (endpoints, auth, poll rates), DSP interface and install
  layout now follow DESIGN.md sections 2 / 4 / 6. Hook mechanism remains a
  **swappable module** (section 5 — boss decision pending); `AudioHook` is
  the slot.
- `src/webui_client/` has the full contract + a linkable STUB (WinHTTP
  polling loop is the next piece-2 increment).
- DSP core slot = `src/dsp/dsp_engine.h` (ise::Grid / SubmergeTracker /
  AcousticEngine) — helper-1's piece 3.
- Installer (`install/installer.nsi`) implements the section-4 layout;
  game-side hook placement is commented out until section 5 resolves.

## Layout
- `CMakeLists.txt`  — Windows C++17 build (MSVC, x64, static runtime)
- `src/main.cpp`    — entry point / shell wiring
- `src/audio_hook/` — swappable hook slot (inject / APO / loopback)
- `src/webui_client/` — data client (contract per DESIGN.md §2; stub impl)
- `src/dsp/`        — DSP core interface (helper-1, piece 3)
- `install/`        — NSIS installer (layout per DESIGN.md §4)
- `settings.json`   — app settings sample

## Build (Windows / Visual Studio)
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release

## Push status
Committed locally, UNPUSHED — scaffold stays local until the design doc
gates piece 2 (TaskSplitter hold).
