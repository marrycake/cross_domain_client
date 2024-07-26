#ifndef FILEITEMMODEL_H
#define FILEITEMMODEL_H

#include <qjsonobject.h>
#include <qlist.h>

#include <QAbstractListModel>
#include <memory>

#include "fileItemInfo.h"

class FileItemModel {
  explicit FileItemModel(const QJsonObject &json,
                         std::shared_ptr<FileItemModel> parentModel = nullptr);
  const QList<FileItemInfo> &getFileItems() { return fileItems; }
  std::shared_ptr<FileItemModel> getParentModel() { return parentModel; }

 private:
  QList<FileItemInfo> fileItems;
  std::shared_ptr<FileItemModel> parentModel;
};

#endif  // FILEITEMMODEL_H