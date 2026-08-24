#pragma once

// Swappable audio-hook slot.
//
// DESIGN.md section 5 (LOCKED, boss 2026-08-24): the hook mechanism is
// **Windows APO on the render endpoint** (primary) — a COM Audio Processing
// Object registered on the output endpoint, running inside `audiodg.exe`
// OUTSIDE the game process: zero EAC surface, few-ms latency, no per-game
// breakage. WASAPI loopback is the zero-risk fallback. Game DLL injection
// is a documented why-not (EAC global-ban risk) — do not build.
//
// The app talks only to this interface, so the mechanism swap (APO <-> 
// loopback) is a drop-in change with no ripple.

struct AudioHook {
  virtual ~AudioHook() = default;

  virtual bool attach() = 0;          // connect to the audio path
  virtual void detach() = 0;          // release cleanly, restore state
  virtual bool active() const = 0;

  // Called on every render quantum. `dst` is the final output buffer;
  // implementations may modify it in place. Must stay real-time safe
  // (no allocation, no locks) to honour the zero-latency requirement.
  virtual void process(float* dst, int frames, int channels) = 0;
};
