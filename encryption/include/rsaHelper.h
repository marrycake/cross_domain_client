#ifndef RSAHELPER_H
#define RSAHELPER_H

#include "cryptlib.h"
#include "rsa.h"
#include <cstddef>
#include <cstdint>
#include <utility>
class RsaHelper {
public:
  static std::pair<CryptoPP::RSA::PublicKey, CryptoPP::RSA::PrivateKey>
  genKeyPair(uint32_t keySize);
  static std::string encrypt(CryptoPP::RSA::PublicKey &publicKey,
                             const std::string &data);
  static std::string decrypt(CryptoPP::RSA::PrivateKey &privateKey,
                             const std::string &encryptMsg);
  static std::string sign(CryptoPP::RSA::PrivateKey &privateKey,
                          const std::string &data);
  static bool verify(const std::string &message, const std::string &signature,
                     CryptoPP::RSA::PublicKey &publicKey);
  static CryptoPP::RSA::PublicKey
  loadPublicKeyFromStr(const std::string &publicKeyStr);
  static CryptoPP::RSA::PrivateKey
  loadPrivateKeyFromStr(const std::string &privateKeyStr);
  static CryptoPP::RSA::PublicKey loadPublicKeyFromStr(const char *publicKeyCh,
                                                       size_t len);
  static CryptoPP::RSA::PrivateKey
  loadPrivateKeyFromStr(const char *privateKeyCh, size_t len);
  static std::string
  dumpPublicKeyToStr(const CryptoPP::RSA::PublicKey &publicKey);
  static std::string
  dumpPrivateKeyToStr(const CryptoPP::RSA::PrivateKey &privateKey);
};

#endif // RSAHELPER_H