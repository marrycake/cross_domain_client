#ifndef USERINFO_H
#define USERINFO_H

#include <cstdint>
#include <string>

#include "cryptopp/rsa.h"

class UserInfo {
 public:
  explicit UserInfo(uint64_t userId, uint32_t userPrivilige,
                    const std::string &token)
      : userId(userId), userPrivilige(userPrivilige), token(token){};
  UserInfo() = default;
  uint64_t getUserId() { return userId; }
  const std::string &getUserName() { return userName; }
  uint32_t getUserPrivilige() { return userPrivilige; }
  const std::string &getToken() { return token; }
  const CryptoPP::RSA::PublicKey &getUserPublicKey() { return userPublicKey; }
  const CryptoPP::RSA::PrivateKey &getUserPrivateKey() {
    return userPrivateKey;
  }

  void setUserId(uint64_t userId) { this->userId = userId; }
  void setUserName(const std::string &userName) { this->userName = userName; }
  void setUserPrivilige(uint32_t userPrivilige) {
    this->userPrivilige = userPrivilige;
  }
  void setToken(const std::string &token) { this->token = token; }
  void setUserPublicKey(const CryptoPP::RSA::PublicKey &userPublicKey) {
    this->userPublicKey = userPublicKey;
  }
  void setUserPrivateKey(const CryptoPP::RSA::PrivateKey &userPrivateKey) {
    this->userPrivateKey = userPrivateKey;
  }

 private:
  uint64_t userId;
  std::string userName;
  uint32_t userPrivilige;
  std::string token;
  CryptoPP::RSA::PublicKey userPublicKey;
  CryptoPP::RSA::PrivateKey userPrivateKey;
};

#endif  // USERINFO_H