#pragma once

// DSP engine slot (helper-1, piece 3).
//
// Port of AcousticSimulationEngine.js + pseudo_rt.py to C++: reverb/echo
// curves, low-pass muffle, occlusion, submersion/underwater state. The
// hook calls this inside its render callback, so it must be real-time safe.

struct DspEngine {
  virtual ~DspEngine() = default;

  // in == out allowed (in place).
  virtual void process(const float* in, float* out,
                       int frames, int channels) = 0;
};
