// Isle Sound Enhancer - entry point (scaffold).
//
// Shell wiring only at this stage: the audio hook, webui client and DSP
// engine are abstract slots whose implementations are gated on the design
// doc (piece 1). The hook mechanism in particular is intentionally swappable
// (inject vs APO vs loopback) per the design-direction hold.

#include "audio_hook/audio_hook.h"
#include "dsp/dsp_engine.h"
#include "webui_client/webui_client.h"

#include <windows.h>
#include <memory>

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  // Slot owners wire real implementations here once the design doc lands.
  std::unique_ptr<AudioHook> hook;        // mechanism TBD (swappable)
  std::unique_ptr<WebUIClient> client;    // endpoints TBD
  std::unique_ptr<DspEngine> dsp;         // helper-1, piece 3

  // Zero-latency priority (boss): the hook path must not add buffering;
  // process() below must run on the hook's render callback quantum.
  if (hook) hook->attach();
  if (client) client->start();

  // Message loop placeholder (tray/window shell comes with the real UI).
  MSG msg{};
  while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }
  if (client) client->stop();
  if (hook) hook->detach();
  return 0;
}
