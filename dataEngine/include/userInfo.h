#ifndef USERINFO_H
#define USERINFO_H

#include <cstddef>
#include <cstdint>
#include <string>

#include "userPrivilige.h"

class UserInfo {
 public:
  explicit UserInfo(uint64_t userId, UserPrivilige userPrivilige,
                    const std::string &publicKey);
  explicit UserInfo(const char *src);
  UserInfo();
  size_t toSerializeLen();
  void serilizeTo(const char *dst);
  const std::string &getPublicKey() { return publicKey; }

  UserPrivilige getUserPrivilige() const { return userPrivilige; }
  uint64_t getUserId() const { return userId; }
  const std::string &getPublicKey() const { return publicKey; }
  void display();

 private:
  uint64_t userId;
  UserPrivilige userPrivilige;
  std::string publicKey;
};

#endif  // USERINFO_H