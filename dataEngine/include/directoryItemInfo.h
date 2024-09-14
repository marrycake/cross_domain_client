#ifndef DIRECTORYITEMINFO_H
#define DIRECTORYITEMINFO_H

#include <string>
class DirectoryItemInfo {
 public:
  explicit DirectoryItemInfo(const char* src);
  DirectoryItemInfo() = default;
  const std::string& getDirName() { return this->dirName; }

  uint32_t getDirPrivilege() { return this->dirPrivilege; }

  void setDirName(const std::string& dirName) { this->dirName = dirName; }

  void setDirPrivilege(uint32_t dirPrivilege) {
    this->dirPrivilege = dirPrivilege;
  }

  size_t toSerializeLen();
  void serilizeTo(const char* dst);

  void display();

 private:
  std::string dirName;
  uint32_t dirPrivilege;
};

#endif  // DIRECTORYITEMINFO_H
