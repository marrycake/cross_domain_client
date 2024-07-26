#ifndef AESHELPER_H
#define AESHELPER_H

#include "aes.h"
#include "config_int.h"
#include <cstddef>
#include <string>
class AESHelper {
public:
  static std::string encrypt(const std::string &key, const std::string &data,
                             CryptoPP::byte *iv = AESHelper::iv);
  static std::string decrypt(const std::string &key,
                             const std::string &encryptData,
                             CryptoPP::byte *iv = AESHelper::iv);

  static std::string encrypt(const char *key, size_t keyLen, const char *data,
                             size_t dataLen,
                             CryptoPP::byte *iv = AESHelper::iv);
  static std::string decrypt(const char *key, size_t keyLen,
                             const char *encryptData, size_t encryptDataLen,
                             CryptoPP::byte *iv = AESHelper::iv);

  static CryptoPP::byte iv[CryptoPP::AES::BLOCKSIZE];
};

#endif // AESHELPER_H