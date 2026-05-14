#include "components/lockdown_browser/ui/webui/lockdown_ui.h"

#include "components/lockdown_browser/browser/lockdown_manager.h"
#include "components/lockdown_browser/browser/firebase_service.h"
#include "content/public/browser/web_ui.h"
#include "content/public/browser/web_ui_data_source.h"

namespace lockdown_browser {

LockdownUI::LockdownUI(content::WebUI* web_ui) : content::WebUIController(web_ui) {
  // Set up the WebUI data source
}

LockdownUI::~LockdownUI() = default;

}  // namespace lockdown_browser
