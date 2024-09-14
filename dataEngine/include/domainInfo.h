#ifndef DOMAININFO_H
#define DOMAININFO_H

#include <cstddef>
#include <cstdint>
class DomainInfo {
 public:
  explicit DomainInfo(uint64_t domainId, uint64_t requestDomainId,
                      uint64_t requestFileId);
  explicit DomainInfo(const char *src);
  DomainInfo();

  size_t toSerializeLen();
  void serilizeTo(const char *dst);

  uint64_t getRequestDomainId() const { return this->requestDomainId; }
  uint64_t getRequestFileId() const { return this->requestFileId; }

  void setDomainId(uint64_t domainId) { this->domainId = domainId; }
  void setRequestDomainId(uint64_t requestDomainId) {
    this->requestDomainId = requestDomainId;
  }
  void setRequestFileId(uint64_t requestFileId) {
    this->requestFileId = requestFileId;
  }

  void display();

 private:
  uint64_t domainId;
  uint64_t requestDomainId;
  uint64_t requestFileId;
};

#endif  // DOMAININFO_H