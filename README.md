# Isle Sound Enhancer — client shell (scaffold)

Windows C++ client that applies the webui's acoustic simulation (echo/muffle)
to the Isle game's audio on the player's PC. See `task_list.md` / `AGENT2-HANDOFF.md`
in the webui repo for the project split; the authoritative design is
helper-1's design doc (piece 1), which gates this shell (piece 2).

## Status: SCAFFOLD ONLY (2026-08-22)
- Design-independent skeleton: no endpoints, payloads, poll rates, or hook
  mechanism are baked in yet — those come from the design doc.
- Audio hook is a **swappable module** (design-direction hold): the app talks
  to `src/audio_hook/audio_hook.h`, and the chosen mechanism (in-process
  inject vs Windows APO vs loopback capture) is a drop-in implementation.
- DSP core slot (`src/dsp/`) is reserved for helper-1's piece 3 port.
- Installer harness (`install/`) is a placeholder; the real setup spec comes
  from the design doc.

## Layout
- `CMakeLists.txt`  — Windows C++17 build (static link, x64)
- `src/main.cpp`    — entry point / shell wiring
- `src/audio_hook/` — abstract hook interface (mechanism-agnostic)
- `src/webui_client/` — abstract data-client slot (contract TBD)
- `src/dsp/`        — DSP engine slot (helper-1, piece 3)
- `install/`        — installer harness placeholder (NSIS template)

## Build (once sources land)
cmake -B build -G "Visual Studio 17 2022" -A x64
cmake --build build --config Release

Nothing here is pushed to origin/main — this scaffold stays local until the
design doc gates piece 2.
