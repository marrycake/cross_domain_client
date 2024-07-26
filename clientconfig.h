#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H

#include <QString>
#include <string>

#include "cryptopp/rsa.h"

class ClientConfig {
 public:
  static ClientConfig& getInstance() {
    static ClientConfig instance;
    return instance;
  }

  const std::string& getServerUrl() { return serverUrl; }

  const CryptoPP::RSA::PublicKey& getPublicKey() { return publicKey; }

  const CryptoPP::RSA::PrivateKey& getPrivateKey() { return privateKey; }

  void setConfPath(const std::string& confPath) { this->confPath = confPath; }

  void load();
  void dump();
  void changeToken(const std::string& token);

 private:
  std::string serverUrl;
  CryptoPP::RSA::PublicKey publicKey;
  CryptoPP::RSA::PrivateKey privateKey;
  std::string token;

  std::string confPath;

  static std::string& getKeyRoot() {
    static std::string keyRoot = "ClientConf";
    return keyRoot;
  }

  static std::string& getKeyServerUrl() {
    static std::string keyServerUrl = "ServerUrl";
    return keyServerUrl;
  }

  static std::string& getKeyPublicKey() {
    static std::string keyPublicKey = "publicKey";
    return keyPublicKey;
  }

  static std::string& getKeyPrivateKey() {
    static std::string keyPrivateKey = "privateKey";
    return keyPrivateKey;
  }

  static std::string& getKeyToken() {
    static std::string keyToken = "token";
    return keyToken;
  }
};

#endif  // CLIENTCONFIG_H