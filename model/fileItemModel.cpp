#include "fileItemModel.h"

#include <QJsonArray>

#include "fileItemInfo.h"

FileItemModel::FileItemModel(const QJsonObject &json)
    : currentDomainId(0), currentDirId(1) {
  QJsonArray domainsArray = json.value("Domains").toArray();
  int localDomainId = json.value("localDomainId").toInt();

  for (const QJsonValue &domainValue : domainsArray) {
    QJsonObject domainObj = domainValue.toObject();
    auto domainId = domainObj.value("id").toInt();
    auto domainName = domainObj.value("DomainName").toString();
    if (domainId == localDomainId) {
      domainName += "(local)";
    }
    FileItemInfo fileInfo(domainId, domainName, DOMAIN_CATEGORY, 4);
    fileItems.append(fileInfo);
  }
}