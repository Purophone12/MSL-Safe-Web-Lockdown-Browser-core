#ifndef COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_BROWSER_VIEW_H_
#define COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_BROWSER_VIEW_H_

#include "ui/views/controls/button/label_button.h"
#include "ui/views/view.h"

namespace lockdown_browser {

class LockdownButton : public views::LabelButton {
 public:
  LockdownButton();
  ~LockdownButton() override;

  void OnButtonPressed();
};

}  // namespace lockdown_browser

#endif  // COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_BROWSER_VIEW_H_
