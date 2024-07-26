#include "aesHelper.h"
#include "aes.h"
#include "filters.h"
#include "modes.h"

CryptoPP::byte AESHelper::iv[CryptoPP::AES::BLOCKSIZE] = {
    0xa0, 0x52, 0xf1, 0x1f, 0x55, 0xf0, 0x97, 0x3c,
    0x04, 0x83, 0x4d, 0xcc, 0x0d, 0x29, 0xc0, 0x76};

std::string AESHelper::encrypt(const std::string &key, const std::string &data,
                               CryptoPP::byte *iv) {
  return encrypt(key.data(), key.size(), data.data(), data.size());
}

std::string AESHelper::decrypt(const std::string &key,
                               const std::string &encryptData,
                               CryptoPP::byte *iv) {
  return decrypt(key.data(), key.size(), encryptData.data(),
                 encryptData.size());
}

std::string AESHelper::encrypt(const char *key, size_t keyLen, const char *data,
                               size_t dataLen, CryptoPP::byte *iv) {
  std::string ciphertext;

  CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryption;
  encryption.SetKeyWithIV(reinterpret_cast<const CryptoPP::byte *>(key), keyLen,
                          iv);
  CryptoPP::StringSource(reinterpret_cast<const CryptoPP::byte *>(data),
                         dataLen, true,
                         new CryptoPP::StreamTransformationFilter(
                             encryption, new CryptoPP::StringSink(ciphertext)));
  return ciphertext;
}

std::string AESHelper::decrypt(const char *key, size_t keyLen,
                               const char *encryptData, size_t encryptDataLen,
                               CryptoPP::byte *iv) {
  std::string decryptedtext;

  CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryption;
  decryption.SetKeyWithIV(reinterpret_cast<const CryptoPP::byte *>(key), keyLen,
                          iv);

  CryptoPP::StringSource(
      reinterpret_cast<const CryptoPP::byte *>(encryptData), encryptDataLen,
      true,
      new CryptoPP::StreamTransformationFilter(
          decryption, new CryptoPP::StringSink(decryptedtext)));

  return decryptedtext;
}