// Isle Sound Enhancer - entry point (scaffold, aligned to DESIGN.md v0.1).
//
// App shell wiring: loads settings.json (section 4 layout), starts the
// webui client (DESIGN.md 2.2/2.3 poll contract), and attaches the audio
// hook (section 5 - swappable, boss decision pending). The DSP core
// (ise_dsp.h) is helper-1's piece 3; this shell only wires it.

#include "audio_hook/audio_hook.h"
#include "dsp/dsp_engine.h"
#include "webui_client/webui_client.h"

#include <windows.h>
#include <memory>
#include <string>

// settings.json — C:\IsleSoundEnhancer\settings.json
//   { "webui_url": "http://localhost:9385",
//     "session_cookie_ref": "auto|manual",
//     "quality": "medium" }
struct Settings {
  std::string webuiUrl = "http://localhost:9385";
  std::string sessionCookie;   // runtime-only, never embedded
  std::string quality = "medium";  // from settings.json; fed to the DSP/UI layer
};

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
  Settings settings;  // TODO(agent-2): load from settings.json + cookie store

  // WebUI client: polls /api/headings @2 Hz, grid meta @30 s (DESIGN.md 2.3).
  WebUIClient client(settings.webuiUrl, settings.sessionCookie);

  // Audio hook: mechanism swappable (inject vs APO vs WASAPI loopback).
  std::unique_ptr<AudioHook> hook;   // implementation per boss's decision

  // DSP core: helper-1's piece 3, compiled against ise_dsp.h only.
  ise::AcousticEngine engine;

  if (client.start()) {
    if (hook) hook->attach();
    // Shell: each hook render callback reads client.snapshot() ->
    // engine.envAt/pathAudio -> engine.process. Real-time-safe hand-off
    // details land with the hook implementation (piece 2 continuation).

    MSG msg{};
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
      TranslateMessage(&msg);
      DispatchMessageW(&msg);
    }

    if (hook) hook->detach();
    client.stop();
  }
  return 0;
}
