// WebUI client — STUB implementation (piece 2, scaffold stage).
//
// Interface + contract are final per DESIGN.md section 2; the WinHTTP
// polling loop is the next increment of piece 2 (after the design doc
// lands on the branch and the hook mechanism is decided). This stub keeps
// the project linkable so the shell/installer shape is buildable and
// QA-gateable independently.

#include "webui_client/webui_client.h"

WebUIClient::WebUIClient(std::string baseUrl, std::string sessionCookie)
    : baseUrl_(std::move(baseUrl)), sessionCookie_(std::move(sessionCookie)) {}

WebUIClient::~WebUIClient() { stop(); }

bool WebUIClient::start() {
  // TODO(agent-2): spawn thread_ + run() polling loop (WinHTTP).
  return false;
}

void WebUIClient::stop() {
  running_.store(false);
  if (thread_.joinable()) thread_.join();
}

WebUiState WebUIClient::snapshot() const {
  std::lock_guard<std::mutex> lock(mutex_);
  return state_;
}

void WebUIClient::run() {
  // TODO(agent-2): headings @2 Hz, grid meta @30 s, zone-masks on load.
  while (running_.load()) {
    // pollHeadings(); pollGridMeta();
  }
}

void WebUIClient::pollHeadings() {
  // TODO(agent-2): GET /api/headings, store playersJson + myPos.
}

void WebUIClient::pollGridMeta() {
  // TODO(agent-2): GET /api/map/rtgrid; when built_at changes, fetch
  // grid_url + "?v=<built_at>" into rtgrid.bin and hand to ise::Grid.
}

void WebUIClient::loadZoneMasks() {
  // TODO(agent-2): GET /api/admin/zone-masks -> ise::ZoneMask list.
}

std::string WebUIClient::httpGet(const std::string& path) const {
  // TODO(agent-2): WinHTTP GET with Cookie: session=<cookie>; map 302 ->
  // "re-auth needed" per DESIGN.md 2.1.
  return {};
}
