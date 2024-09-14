#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H

#include <QString>
#include <string>

#include "cryptopp/rsa.h"
#include "model/userInfo.h"

class ClientConfig {
 public:
  static ClientConfig& getInstance() {
    static ClientConfig instance;
    return instance;
  }

  const std::string& getServerUrl() { return serverUrl; }

  UserInfo& getUserInfo() { return userInfo; }

  void setConfPath(const std::string& confPath) { this->confPath = confPath; }

  void load();
  void dump();
  void redump();

 private:
  std::string serverUrl;
  UserInfo userInfo;
  std::string confPath;

  static std::string& getKeyRoot() {
    static std::string keyRoot = "ClientConf";
    return keyRoot;
  }

  static std::string& getKeyServerUrl() {
    static std::string keyServerUrl = "ServerUrl";
    return keyServerUrl;
  }

  static std::string& getKeyUserInfo() {
    static std::string keyUserInfo = "UserInfo";
    return keyUserInfo;
  }

  static std::string& getKeyUserId() {
    static std::string keyUserId = "UserId";
    return keyUserId;
  }

  static std::string& getKeyUserName() {
    static std::string keyUserName = "UserName";
    return keyUserName;
  }

  static std::string& getKeyUserPrivilige() {
    static std::string keyUserPrivilige = "UserPrivilige";
    return keyUserPrivilige;
  }

  static std::string& getKeyToken() {
    static std::string keyToken = "token";
    return keyToken;
  }

  static std::string& getKeyPublicKey() {
    static std::string keyPublicKey = "publicKey";
    return keyPublicKey;
  }

  static std::string& getKeyPrivateKey() {
    static std::string keyPrivateKey = "privateKey";
    return keyPrivateKey;
  }
};

#endif  // CLIENTCONFIG_H