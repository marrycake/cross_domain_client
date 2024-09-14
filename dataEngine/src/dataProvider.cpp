#include "dataProvider.h"

#include "spdlog/spdlog.h"

DataProvider::DataProvider(const char *src) {
  size_t resultLen = 0;
  memcpy(reinterpret_cast<char *>(&userId), src + resultLen, sizeof(userId));
  resultLen += sizeof(userId);
  uint64_t userNameSize = 0;
  memcpy(reinterpret_cast<char *>(&userNameSize), src + resultLen,
         sizeof(userNameSize));
  resultLen += sizeof(userNameSize);
  userName = std::string(src + resultLen, userNameSize);
  resultLen += userNameSize;
  memcpy(reinterpret_cast<char *>(&userPrivilege), src + resultLen,
         sizeof(userPrivilege));
}

DataProvider::DataProvider() : userId(0), userPrivilege(0) {}

size_t DataProvider::toSerializeLen() {
  return sizeof(userId) + sizeof(userName.size()) + userName.size() +
         sizeof(userPrivilege);
}
void DataProvider::serilizeTo(const char *dst) {
  char *p = const_cast<char *>(dst);
  memcpy(p, reinterpret_cast<char *>(&userId), sizeof(userId));
  p += sizeof(userId);
  uint64_t userNameSize = userName.size();
  memcpy(p, reinterpret_cast<char *>(&userNameSize), sizeof(userNameSize));
  p += sizeof(userNameSize);
  memcpy(p, userName.data(), userName.size());
  p += userName.size();
  memcpy(p, reinterpret_cast<char *>(&userPrivilege), sizeof(userPrivilege));
}

void DataProvider::display() {
  spdlog::debug("userId: {:<10}", userId);
  spdlog::debug("userName: {:<30}", userName);
  spdlog::debug("userPrivilege: {:<5}", userPrivilege);
}