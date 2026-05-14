#ifndef COMPONENTS_LOCKDOWN_BROWSER_UI_WEBUI_LOCKDOWN_UI_H_
#define COMPONENTS_LOCKDOWN_BROWSER_UI_WEBUI_LOCKDOWN_UI_H_

#include "content/public/browser/web_ui_controller.h"

namespace lockdown_browser {

class LockdownUI : public content::WebUIController {
 public:
  explicit LockdownUI(content::WebUI* web_ui);
  ~LockdownUI() override;
  LockdownUI(const LockdownUI&) = delete;
  LockdownUI& operator=(const LockdownUI&) = delete;
};

}  // namespace lockdown_browser

#endif  // COMPONENTS_LOCKDOWN_BROWSER_UI_WEBUI_LOCKDOWN_UI_H_
