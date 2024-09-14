#include "userInfo.h"

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "spdlog/fmt/bin_to_hex.h"
#include "spdlog/spdlog.h"

UserInfo::UserInfo(uint64_t userId, UserPrivilige userPrivilige,
                   const std::string &publicKey)
    : userId(userId), userPrivilige(userPrivilige), publicKey(publicKey) {}

UserInfo::UserInfo(const char *src) : userId(0), userPrivilige(INVALID) {
  size_t index = 0;
  memcpy(reinterpret_cast<char *>(&userId), src + index, sizeof(userId));
  index += sizeof(userId);
  memcpy(reinterpret_cast<char *>(&userPrivilige), src + index,
         sizeof(userPrivilige));
  index += sizeof(userPrivilige);
  uint64_t pubicKeySize = 0;
  memcpy(reinterpret_cast<char *>(&pubicKeySize), src + index,
         sizeof(pubicKeySize));
  index += sizeof(pubicKeySize);
  this->publicKey = std::string(src + index, pubicKeySize);
}

UserInfo::UserInfo() : userId(0), userPrivilige(INVALID) {}

size_t UserInfo::toSerializeLen() {
  return sizeof(userId) + sizeof(userPrivilige) + sizeof(publicKey.size()) +
         publicKey.size();
}

void UserInfo::serilizeTo(const char *dst) {
  char *p = const_cast<char *>(dst);

  memcpy(p, reinterpret_cast<char *>(&userId), sizeof(userId));
  p += sizeof(userId);
  memcpy(p, reinterpret_cast<char *>(&userPrivilige), sizeof(userPrivilige));
  p += sizeof(userPrivilige);
  uint64_t publicKeySize = publicKey.size();
  memcpy(p, reinterpret_cast<char *>(&publicKeySize), sizeof(publicKeySize));
  p += sizeof(publicKeySize);
  memcpy(p, publicKey.data(), publicKey.size());
}

void UserInfo::display() {
  spdlog::debug(
      "userId:{:<10}\n"
      "userPrivilege:{:<5}\n"
      "publicKey:{:<30}",
      userId, static_cast<uint32_t>(userPrivilige), spdlog::to_hex(publicKey));
}