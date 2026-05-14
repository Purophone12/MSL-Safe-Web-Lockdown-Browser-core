#include "components/lockdown_browser/browser/lockdown_browser_view.h"
#include "components/lockdown_browser/browser/lockdown_manager.h"
#include "ui/base/metadata/metadata_impl_macros.h"

namespace lockdown_browser {

LockdownButton::LockdownButton() : views::LabelButton(base::BindRepeating(&LockdownButton::OnButtonPressed), u"Lockdown") {
}

LockdownButton::~LockdownButton() = default;

void LockdownButton::OnButtonPressed() {
  // Show session code entry UI
}

BEGIN_METADATA(LockdownButton, views::LabelButton)
END_METADATA

}  // namespace lockdown_browser
