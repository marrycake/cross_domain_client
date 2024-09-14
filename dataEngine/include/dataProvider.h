#ifndef DATAPROVIDER_H
#define DATAPROVIDER_H

#include <cstdint>
#include <string>
class DataProvider {
 public:
  explicit DataProvider(const char *src);
  DataProvider();

  size_t toSerializeLen();
  void serilizeTo(const char *dst);

  uint64_t getUserId() { return this->userId; }

  const std::string &getUserName() { return this->userName; }

  uint32_t getUserPrivilege() { return this->userPrivilege; }

  void setUserId(uint64_t userId) { this->userId = userId; }

  void setUserName(const std::string userName) { this->userName = userName; }

  void setUserPrivilege(uint32_t userPrivilege) {
    this->userPrivilege = userPrivilege;
  }

  void display();

 private:
  uint64_t userId;
  std::string userName;
  uint32_t userPrivilege;
};

#endif  // DATAPROVIDER_H
