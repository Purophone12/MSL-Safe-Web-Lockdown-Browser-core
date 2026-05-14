#ifndef COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_NAVIGATION_THROTTLE_H_
#define COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_NAVIGATION_THROTTLE_H_

#include "content/public/browser/navigation_throttle.h"

namespace lockdown_browser {

class LockdownNavigationThrottle : public content::NavigationThrottle {
 public:
  static std::unique_ptr<content::NavigationThrottle> MaybeCreateThrottleFor(
      content::NavigationHandle* navigation_handle);

  explicit LockdownNavigationThrottle(content::NavigationHandle* navigation_handle);
  ~LockdownNavigationThrottle() override;

  ThrottleCheckResult WillStartRequest() override;
  ThrottleCheckResult WillRedirectRequest() override;

 private:
  ThrottleCheckResult CheckRestriction();
};

}  // namespace lockdown_browser

#endif  // COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_NAVIGATION_THROTTLE_H_
