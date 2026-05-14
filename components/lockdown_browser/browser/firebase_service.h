#ifndef COMPONENTS_LOCKDOWN_BROWSER_BROWSER_FIREBASE_SERVICE_H_
#define COMPONENTS_LOCKDOWN_BROWSER_BROWSER_FIREBASE_SERVICE_H_

#include <string>
#include "base/functional/callback.h"
#include "base/values.h"

namespace lockdown_browser {

class FirebaseService {
 public:
  struct Config {
    std::string api_key;
    std::string auth_domain;
    std::string project_id;
    std::string storage_bucket;
    std::string messaging_sender_id;
    std::string app_id;
    std::string measurement_id;
  };

  static FirebaseService* GetInstance();

  virtual void Initialize(const Config& config) = 0;

  // Auth
  virtual void SignInWithGoogle(base::OnceCallback<void(bool success, const std::string& user_id)> callback) = 0;

  // Firestore
  virtual void GetSessionData(const std::string& session_code,
                              base::OnceCallback<void(base::Value::Dict data)> callback) = 0;

  // Analytics/Reporting
  virtual void ReportViolation(const std::string& session_code,
                               const std::string& user_id,
                               const std::string& violation_type,
                               base::Value::Dict details) = 0;

 protected:
  virtual ~FirebaseService() = default;
};

}  // namespace lockdown_browser

#endif  // COMPONENTS_LOCKDOWN_BROWSER_BROWSER_FIREBASE_SERVICE_H_
