#include "components/lockdown_browser/browser/lockdown_manager.h"

#include "base/no_destructor.h"
#include "crypto/sha2.h"
#include "url/gurl.h"

namespace lockdown_browser {

// static
LockdownManager* LockdownManager::GetInstance() {
  return base::Singleton<LockdownManager>::get();
}

LockdownManager::LockdownManager() = default;
LockdownManager::~LockdownManager() = default;

void LockdownManager::EnterLockdownMode(const std::string& session_code, LockdownMode mode) {
  current_session_code_ = session_code;
  current_mode_ = mode;
}

bool LockdownManager::ExitLockdownMode(const std::string& password) {
  if (session_data_.FindString("quitPassword") &&
      *session_data_.FindString("quitPassword") == password) {
    current_mode_ = LockdownMode::kRegular;
    current_session_code_.clear();
    session_data_.clear();
    whitelist_.clear();
    return true;
  }
  return false;
}

void LockdownManager::SetSessionData(base::Value::Dict data) {
  session_data_ = std::move(data);
  whitelist_.clear();
  if (base::Value::List* whitelist = session_data_.FindList("whitelist")) {
    for (const auto& item : *whitelist) {
      if (item.is_string()) {
        whitelist_.push_back(item.GetString());
      }
    }
  }
}

std::vector<uint8_t> LockdownManager::GetSyncEncryptionKey() const {
  std::string google_id = "placeholder_google_id"; // Should be fetched from identity manager
  std::string hashed_id = crypto::SHA256HashString(google_id);
  return std::vector<uint8_t>(hashed_id.begin(), hashed_id.end());
}

bool LockdownManager::IsUrlAllowed(const std::string& url) const {
  if (current_mode_ != LockdownMode::kRestrictedBrowsing) {
    return true;
  }

  GURL gurl(url);
  if (!gurl.is_valid()) return false;

  for (const auto& domain : whitelist_) {
    if (gurl.DomainIs(domain)) {
      return true;
    }
  }

  return false;
}

}  // namespace lockdown_browser
