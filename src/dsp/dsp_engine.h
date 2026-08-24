#pragma once

#include <string>
#include <vector>

// DSP core interface — port of AcousticSimulationEngine.js + PseudoRTAudio.js
// to C++. This is the CONTRACT from DESIGN.md section 6 (helper-1, piece 1);
// the implementation is helper-1's piece 3. The app shell (piece 2) compiles
// against this header only, so the DSP core can land in parallel.
//
// Parity requirement (DESIGN.md section 8): math must match the JS engine —
// incl. the #82 enter-75/exit-40 submersion hysteresis and the
// min(0.6, occ + submerge*0.4) muffle floor. All submersion uses the grid's
// LOCAL water-surface height per node — never a global constant.

namespace ise {

struct EnvParams {
  float lowCut = 80.0f;
  float highCut = 18000.0f;
  float reverb = 0.0f;
  float reverbDecay = 0.4f;
  float preDelay = 0.0f;
  float echo = 0.0f;
  float echoDelay = 0.05f;
  float echoFeedback = 0.0f;
  float occlusionMuffle = 0.0f;
};

struct Pos {
  float x = 0.0f, y = 0.0f, z = 0.0f;  // UE world units
  float heading = 0.0f;                 // yaw, degrees
};

struct ZoneMask {
  std::string name;
  int w = 0, h = 0;
  std::vector<unsigned char> mask;      // wide-space RGBA
};

class Grid {                            // rtgrid.bin + meta
 public:
  bool load(const std::string& binPath, const std::string& metaJson);
  float terrainHeight(float x, float y) const;
  float waterAt(float x, float y) const;
  float surfaceAt(float x, float y) const;  // LOCAL water surface (UE u)
  float builtAt() const;
};

class SubmergeTracker {                 // enter/exit hysteresis, keyed by sid
 public:
  float update(const Pos& p);           // 0..1 submersion
};

class AcousticEngine {
 public:
  void setGrid(const Grid& g);
  void setZoneMasks(const std::vector<ZoneMask>& masks);
  EnvParams envAt(const Pos& p) const;

  struct Path { float occlusion = 0.0f, bounce = 0.0f, submerge = 0.0f; };
  Path pathAudio(const Pos& a, const Pos& b) const;

  struct NodeBundle {
    float dryGain = 1.0f, reverbGain = 0.0f, preDelay = 0.0f;
    float echoGain = 0.0f, echoDelay = 0.05f, echoFeedback = 0.0f;
    double tailSecs = 0.4;
    // DSP primitive handles live in the piece-3 implementation.
  };
  NodeBundle createPeerPipeline(double sampleRate);
  void applyEnvironment(NodeBundle&, const EnvParams&,
                        const Pos& my, const Pos& peer);
  void process(NodeBundle&, const float* in, float* out, size_t frames);
};

}  // namespace ise
