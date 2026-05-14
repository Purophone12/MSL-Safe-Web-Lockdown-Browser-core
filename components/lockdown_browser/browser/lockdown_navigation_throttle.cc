#include "components/lockdown_browser/browser/lockdown_navigation_throttle.h"
#include "components/lockdown_browser/browser/lockdown_manager.h"
#include "content/public/browser/navigation_handle.h"
#include "net/base/url_util.h"
#include "url/gurl.h"

namespace lockdown_browser {

// static
std::unique_ptr<content::NavigationThrottle> LockdownNavigationThrottle::MaybeCreateThrottleFor(
    content::NavigationHandle* navigation_handle) {
  if (LockdownManager::GetInstance()->IsLockdownActive()) {
    return std::make_unique<LockdownNavigationThrottle>(navigation_handle);
  }
  return nullptr;
}

LockdownNavigationThrottle::LockdownNavigationThrottle(content::NavigationHandle* navigation_handle)
    : content::NavigationThrottle(navigation_handle) {}

LockdownNavigationThrottle::~LockdownNavigationThrottle() = default;

content::NavigationThrottle::ThrottleCheckResult LockdownNavigationThrottle::WillStartRequest() {
  return CheckRestriction();
}

content::NavigationThrottle::ThrottleCheckResult LockdownNavigationThrottle::WillRedirectRequest() {
  return CheckRestriction();
}

content::NavigationThrottle::ThrottleCheckResult LockdownNavigationThrottle::CheckRestriction() {
  LockdownManager* manager = LockdownManager::GetInstance();
  if (manager->current_mode() != LockdownMode::kRestrictedBrowsing) {
    return content::NavigationThrottle::PROCEED;
  }

  GURL url = navigation_handle()->GetURL();
  if (manager->IsUrlAllowed(url.spec())) {
    return content::NavigationThrottle::PROCEED;
  }

  // Redirect to block page
  std::string block_url = "https://static.mslacademy.online/default/blockCom.html?site=" +
                          net::EscapeQueryParamValue(url.host(), true) +
                          "&category=MSL LockDown Browser Restricted Browsing Mode";
  return content::NavigationThrottle::ThrottleCheckResult(
      content::NavigationThrottle::REDIRECT,
      net::Error::OK,
      GURL(block_url));
}

}  // namespace lockdown_browser
