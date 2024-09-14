#ifndef HASHGENERATOR_H
#define HASHGENERATOR_H

#include <cstddef>
#include <string>
class HashGenerator {
 public:
  static std::string sha256(const char *key, size_t keyLength, const char *data,
                            size_t dataLength);
  static std::string sha128(const char *key, size_t keyLength, const char *data,
                            size_t dataLength);
  static std::string sha256(const std::string &key, const std::string &data);
  static std::string sha128(const std::string &key, const std::string &data);
  static std::string sha256(const std::string &data);

 private:
};

#endif  // HASHGENERATOR_H