#include "base64Helper.h"

#include <cryptopp/base64.h>
#include <cryptopp/filters.h>

std::string Base64Helper::encode(const std::string &data) {
  std::string encoded;
  CryptoPP::StringSource ss(
      reinterpret_cast<const unsigned char *>(data.data()), data.size(), true,
      new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded), false));
  return encoded;
}
std::string Base64Helper::decode(const std::string &data) {
  std::string decoded;
  CryptoPP::StringSource ss(
      data, true,
      new CryptoPP::Base64Decoder(new CryptoPP::StringSink(decoded)));
  return decoded;
}
