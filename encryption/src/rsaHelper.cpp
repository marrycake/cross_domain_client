#include "rsaHelper.h"
#include "config_int.h"
#include "filters.h"
#include "pssr.h"
#include <cryptopp/base64.h>
#include <cryptopp/files.h>
#include <cryptopp/osrng.h>
#include <cryptopp/rsa.h>

using namespace CryptoPP;

std::pair<CryptoPP::RSA::PublicKey, CryptoPP::RSA::PrivateKey>
RsaHelper::genKeyPair(uint32_t keySize) {
  AutoSeededRandomPool rng;
  InvertibleRSAFunction parameters;
  parameters.GenerateRandomWithKeySize(rng, keySize);

  RSA::PrivateKey privateKey(parameters);
  RSA::PublicKey publicKey(parameters);
  return {publicKey, privateKey};
}
std::string RsaHelper::encrypt(CryptoPP::RSA::PublicKey &publicKey,
                               const std::string &data) {
  AutoSeededRandomPool rng;
  RSAES_OAEP_SHA_Encryptor encryptor(publicKey);

  std::string encryptMsg;

  StringSource(
      data, true,
      new PK_EncryptorFilter(rng, encryptor, new StringSink(encryptMsg)));
  return encryptMsg;
}

std::string RsaHelper::decrypt(CryptoPP::RSA::PrivateKey &privateKey,
                               const std::string &encryptMsg) {
  // Decrypt message
  AutoSeededRandomPool rng;
  RSAES_OAEP_SHA_Decryptor decryptor(privateKey);

  std::string decryptMsg;
  StringSource(
      encryptMsg, true,
      new PK_DecryptorFilter(rng, decryptor,
                             new StringSink(decryptMsg)) // PK_DecryptorFilter
  );                                                     // StringSource
  return decryptMsg;
}

std::string RsaHelper::sign(CryptoPP::RSA::PrivateKey &privateKey,
                            const std::string &data) {
  // Sign message
  AutoSeededRandomPool rng;
  RSASS<PSS, SHA256>::Signer signer(privateKey);

  std::string signature;
  StringSource(data, true,
               new SignerFilter(rng, signer,
                                new StringSink(signature)) // SignerFilter
  );
  return signature;
}

bool RsaHelper::verify(const std::string &message, const std::string &signature,
                       CryptoPP::RSA::PublicKey &publicKey) {
  // Verify signature
  RSASS<PSS, SHA256>::Verifier verifier(publicKey);

  bool result = false;
  StringSource(signature + message, true,
               new SignatureVerificationFilter(
                   verifier,
                   new ArraySink((byte *)&result,
                                 sizeof(result))) // SignatureVerificationFilter
  );                                              // StringSource

  return result;
}

CryptoPP::RSA::PublicKey
RsaHelper::loadPublicKeyFromStr(const std::string &publicKeyStr) {
  return loadPublicKeyFromStr(publicKeyStr.data(), publicKeyStr.size());
}

CryptoPP::RSA::PrivateKey
RsaHelper::loadPrivateKeyFromStr(const std::string &privateKeyStr) {
  return loadPrivateKeyFromStr(privateKeyStr.data(), privateKeyStr.size());
}

CryptoPP::RSA::PublicKey
RsaHelper::loadPublicKeyFromStr(const char *publicKeyCh, size_t len) {
  CryptoPP::RSA::PublicKey publicKey;
  ByteQueue queue;
  Base64Decoder decoder;
  decoder.Attach(new Redirector(queue));
  decoder.Put((CryptoPP::byte *)publicKeyCh, len);
  decoder.MessageEnd();
  publicKey.Load(queue);
  return publicKey;
}

CryptoPP::RSA::PrivateKey
RsaHelper::loadPrivateKeyFromStr(const char *privateKeyCh, size_t len) {
  CryptoPP::RSA::PrivateKey privateKey;
  ByteQueue queue;
  Base64Decoder decoder;
  decoder.Attach(new Redirector(queue));
  decoder.Put((CryptoPP::byte *)privateKeyCh, len);
  decoder.MessageEnd();
  privateKey.Load(queue);
  return privateKey;
}

std::string
RsaHelper::dumpPublicKeyToStr(const CryptoPP::RSA::PublicKey &publicKey) {
  // Save the public key to a string
  std::string publicKeyString;
  CryptoPP::Base64Encoder encoder(new StringSink(publicKeyString));
  publicKey.Save(encoder);
  encoder.MessageEnd();
  return publicKeyString;
}

std::string
RsaHelper::dumpPrivateKeyToStr(const CryptoPP::RSA::PrivateKey &privateKey) {
  // Save the public key to a string
  std::string privateKeyString;
  CryptoPP::Base64Encoder encoder(new StringSink(privateKeyString));
  privateKey.Save(encoder);
  encoder.MessageEnd();
  return privateKeyString;
}