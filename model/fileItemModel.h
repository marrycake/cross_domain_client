#ifndef FILEITEMMODEL_H
#define FILEITEMMODEL_H

#include <qjsonobject.h>
#include <qlist.h>

#include <QAbstractListModel>
#include <cstdint>
#include <utility>

#include "fileItemInfo.h"

class FileItemModel {
 public:
  explicit FileItemModel() : currentDomainId(0), currentDirId(1) {}
  explicit FileItemModel(uint64_t currentDomainId, QString currentDomainName,
                         uint64_t currentDirId, QString currentDirName)
      : currentDomainId(currentDomainId),
        currentDirId(currentDirId),
        currentDomainName(std::move(currentDomainName)),
        currentDirName(std::move(currentDirName)) {}
  explicit FileItemModel(const QJsonObject &json);
  QList<FileItemInfo> &getFileItems() { return fileItems; }

  uint64_t getCurrentDomainId() { return this->currentDomainId; }

  uint64_t getCurrentDirId() { return this->currentDirId; }

  const QString &getCurrentDomainName() { return this->currentDomainName; }

  const QString &getCurrentDirName() { return this->currentDirName; }

  void setCurrentDomainId(uint64_t currentDomainId) {
    this->currentDomainId = currentDomainId;
  }

  void setCurrentDirId(uint64_t currentDirId) {
    this->currentDirId = currentDirId;
  }

  void setCurrentDomainName(const QString &currentDomainName) {
    this->currentDomainName = currentDomainName;
  }

  void setCurrentDirName(const QString &currentDirName) {
    this->currentDirName = currentDirName;
  }

 private:
  QList<FileItemInfo> fileItems;
  uint64_t currentDomainId;
  uint64_t currentDirId;

  QString currentDomainName;
  QString currentDirName;
};

#endif  // FILEITEMMODEL_H