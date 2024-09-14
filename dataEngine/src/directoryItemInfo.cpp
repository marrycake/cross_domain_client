#include "directoryItemInfo.h"

#include "spdlog/spdlog.h"

void DirectoryItemInfo::display() {
  spdlog::debug("dirName: {:<30}", dirName);
  spdlog::debug("dirPrivilege: {:<5}", dirPrivilege);
}

DirectoryItemInfo::DirectoryItemInfo(const char* src) {
  size_t index = 0;
  uint64_t dirNameSize = 0;
  memcpy(&dirNameSize, src + index, sizeof(dirNameSize));
  index += sizeof(dirNameSize);
  dirName = std::string(src + index, dirNameSize);
  index += dirNameSize;
  memcpy(&dirPrivilege, src + index, sizeof(dirPrivilege));
}

size_t DirectoryItemInfo::toSerializeLen() {
  return sizeof(dirName.size()) + dirName.size() + sizeof(dirPrivilege);
}

void DirectoryItemInfo::serilizeTo(const char* dst) {
  uint64_t dirNameSize = dirName.size();
  char* p = const_cast<char*>(dst);
  memcpy(p, reinterpret_cast<char*>(&dirNameSize), sizeof(dirNameSize));
  p += sizeof(dirNameSize);
  memcpy(p, dirName.data(), dirName.size());
  p += dirName.size();
  memcpy(p, reinterpret_cast<char*>(&dirPrivilege), sizeof(dirPrivilege));
}