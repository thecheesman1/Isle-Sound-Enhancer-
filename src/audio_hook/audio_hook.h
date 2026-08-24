#pragma once

// Swappable audio-hook slot.
//
// Design-direction hold (2026-08-22): the hook mechanism is NOT locked.
// Candidate implementations, pending boss's EAC decision:
//   - inject  : in-process, zero latency, EAC surface (only if server
//               EAC is disabled)
//   - apo     : Windows APO on the render endpoint (runs in audiodg,
//               outside the game process, few ms, no EAC surface)
//   - loopback: capture-based fallback
//
// The rest of the app talks only to this interface, so swapping the
// mechanism is a drop-in change with no ripple.

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
