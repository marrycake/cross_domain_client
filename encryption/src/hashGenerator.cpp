#include "hashGenerator.h"
#include "hmac.h"
#include "secblockfwd.h"
#include "sha.h"

std::string HashGenerator::sha256(const char *key, size_t keyLength,
                                  const char *data, size_t dataLength) {
  CryptoPP::SecByteBlock keyBytes((const CryptoPP::byte *)key, keyLength);
  CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

  CryptoPP::HMAC<CryptoPP::SHA256> hmac(keyBytes, keyBytes.size());
  hmac.Update((const CryptoPP::byte *)data, dataLength);
  hmac.Final(digest);

  return {reinterpret_cast<const char *>(digest), CryptoPP::SHA256::DIGESTSIZE};
}

std::string HashGenerator::sha128(const char *key, size_t keyLength,
                                  const char *data, size_t dataLength) {
  return sha256(key, keyLength, data, dataLength).substr(0, 16);
}

std::string HashGenerator::sha256(const std::string &key,
                                  const std::string &data) {
  return sha256(key.data(), key.size(), data.data(), data.size());
}

std::string HashGenerator::sha128(const std::string &key,
                                  const std::string &data) {
  return sha256(key, data).substr(0, 16);
}

std::string HashGenerator::sha256(const std::string &data) {

  CryptoPP::SHA256 hash;

  CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

  hash.CalculateDigest(digest,
                       reinterpret_cast<const CryptoPP::byte *>(data.data()),
                       data.length());
  return {reinterpret_cast<char *>(digest), CryptoPP::SHA256::DIGESTSIZE};
}