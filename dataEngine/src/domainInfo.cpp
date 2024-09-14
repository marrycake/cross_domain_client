#include "domainInfo.h"

#include <cstddef>
#include <cstdint>
#include <cstring>

#include "spdlog/spdlog.h"

DomainInfo::DomainInfo(uint64_t domainId, uint64_t requestDomainId,
                       uint64_t requestFileId)
    : domainId(domainId),
      requestDomainId(requestDomainId),
      requestFileId(requestFileId) {}

DomainInfo::DomainInfo(const char *src)
    : domainId(0), requestDomainId(0), requestFileId(0) {
  size_t resultLen = 0;
  memcpy(reinterpret_cast<char *>(&domainId), src + resultLen,
         sizeof(domainId));
  resultLen += sizeof(domainId);
  memcpy(reinterpret_cast<char *>(&requestDomainId), src + resultLen,
         sizeof(requestDomainId));
  resultLen += sizeof(requestDomainId);
  memcpy(reinterpret_cast<char *>(&requestFileId), src + resultLen,
         sizeof(requestFileId));
  resultLen += sizeof(requestFileId);
}

DomainInfo::DomainInfo() : domainId(0), requestDomainId(0), requestFileId(0) {}

size_t DomainInfo::toSerializeLen() {
  return sizeof(domainId) + sizeof(requestDomainId) + sizeof(requestFileId);
}

void DomainInfo::serilizeTo(const char *dst) {
  char *p = const_cast<char *>(dst);
  memcpy(p, reinterpret_cast<char *>(&domainId), sizeof(domainId));
  p += sizeof(domainId);
  memcpy(p, reinterpret_cast<char *>(&requestDomainId),
         sizeof(requestDomainId));
  p += sizeof(requestDomainId);
  memcpy(p, reinterpret_cast<char *>(&requestFileId), sizeof(requestFileId));
  p += sizeof(requestFileId);
}

void DomainInfo::display() {
  spdlog::debug(
      "domainId:{:<10}\n"
      "requestDomainId:{:<5}\n"
      "requestFileId:{:<30}",
      domainId, requestDomainId, requestFileId);
}