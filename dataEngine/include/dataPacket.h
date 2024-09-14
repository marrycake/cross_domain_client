#ifndef DATAPACKET_H
#define DATAPACKET_H

#include <string>

#include "dataProvider.h"
#include "directoryItemInfo.h"

class DataPacket {
 public:
  void setEncryptContent(const std::string &encryptContent) {
    this->encryptContent = encryptContent;
  }

  void setDataProvider(const DataProvider &dataProvider) {
    this->dataProvider = dataProvider;
  }

  void setDirectoryItemInfo(const DirectoryItemInfo &directoryItemInfo) {
    this->directoryItemInfo = directoryItemInfo;
  }

  void setEncryptKey(const std::string &encryptKey) {
    this->encryptKey = encryptKey;
  }

  void setSignature(const std::string &signature) {
    this->signature = signature;
  }

  std::string &getEncryptContent() { return this->encryptContent; }

  DataProvider &getDataProvider() { return this->dataProvider; }

  DirectoryItemInfo &getDirectoryItemInfo() { return this->directoryItemInfo; }

  std::string &getEncryptKey() { return this->encryptKey; }

  std::string &getSignature() { return this->signature; }

  bool checkPacketValidate();

  void display();

 private:
  DataProvider dataProvider;
  DirectoryItemInfo directoryItemInfo;
  std::string encryptContent;
  std::string encryptKey;
  std::string signature;
};

#endif  // DATAPACKET_H
