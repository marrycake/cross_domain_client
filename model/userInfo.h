#ifndef USERINFO_H
#define USERINFO_H

#include <cstdint>
#include <string>

class UserInfo {
 public:
  explicit UserInfo(uint64_t userId, uint32_t userPrivilige,
                    const std::string &token)
      : userId(userId), userPrivilige(userPrivilige), token(token){};
  uint64_t getUserId() { return userId; }
  uint32_t getUserPrivilige() { return userPrivilige; }
  const std::string &getToken() { return token; }

  void setUserId(uint64_t userId) { this->userId = userId; }
  void setUserPrivilige(uint32_t userPrivilige) {
    this->userPrivilige = userPrivilige;
  }
  void setToken(const std::string &token) { this->token = token; }

 private:
  uint64_t userId;
  uint32_t userPrivilige;
  std::string token;
};

#endif  // USERINFO_H