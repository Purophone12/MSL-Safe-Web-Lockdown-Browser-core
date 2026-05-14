#ifndef COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_MANAGER_H_
#define COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_MANAGER_H_

#include <string>
#include <vector>

#include "base/memory/singleton.h"
#include "base/values.h"

namespace lockdown_browser {

enum class LockdownMode {
  kRegular,
  kExam,
  kRestrictedBrowsing
};

class LockdownManager {
 public:
  static LockdownManager* GetInstance();

  LockdownManager(const LockdownManager&) = delete;
  LockdownManager& operator=(const LockdownManager&) = delete;

  void EnterLockdownMode(const std::string& session_code, LockdownMode mode);
  bool ExitLockdownMode(const std::string& password);

  bool IsLockdownActive() const { return current_mode_ != LockdownMode::kRegular; }
  LockdownMode current_mode() const { return current_mode_; }
  const std::string& session_code() const { return current_session_code_; }
  const std::string& google_id() const { return google_id_; }

  void SetSessionData(base::Value::Dict data);
  const base::Value::Dict& session_data() const { return session_data_; }

  bool IsUrlAllowed(const std::string& url) const;

  std::vector<uint8_t> GetSyncEncryptionKey() const;

 private:
  LockdownManager();
  ~LockdownManager();
  friend struct base::DefaultSingletonTraits<LockdownManager>;

  LockdownMode current_mode_ = LockdownMode::kRegular;
  std::string current_session_code_;
  base::Value::Dict session_data_;
  std::vector<std::string> whitelist_;
};

}  // namespace lockdown_browser

#endif  // COMPONENTS_LOCKDOWN_BROWSER_BROWSER_LOCKDOWN_MANAGER_H_
