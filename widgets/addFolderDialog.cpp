#include "addFolderDialog.h"

#include <qboxlayout.h>
#include <qcombobox.h>
#include <qdialog.h>
#include <qgridlayout.h>
#include <qnamespace.h>
#include <qpushbutton.h>

#include <QJsonObject>
#include <QLabel>

#include "../clientconfig.h"
#include "../http/QHttpmanger.h"
#include "filesconstans.h"

AddFolderDialog::AddFolderDialog(QWidget *parent) : QDialog(parent) {
  initUI();
  connectSignalSlots();
}

void AddFolderDialog::setParamters(uint64_t currentDomainId,
                                   uint64_t currentDirId,
                                   const QString &currentDirName) {
  this->currentDomainId = currentDomainId;
  this->currentDirId = currentDirId;
  this->currentDirName = currentDirName;
}

void AddFolderDialog::initUI() {
  setWindowTitle(tr("Add Folder"));
  QLabel *folderNameLabel = new QLabel(tr("folder name: "), this);
  QLabel *folderPrivilegeLabel = new QLabel(tr("folder privilege: "), this);

  folderNameEdit = new QLineEdit(this);

  folderPrivilegeField = new QComboBox(this);
  QStringList items;
  items << tr("first") << tr("second") << tr("third") << tr("forth");
  folderPrivilegeField->addItems(items);

  okBtn = new QPushButton(tr("ok"), this);
  okBtn->setFixedSize(70, 30);
  cancelBtn = new QPushButton(tr("cancel"), this);
  cancelBtn->setFixedSize(70, 30);

  QGridLayout *gridLayout = new QGridLayout(this);
  gridLayout->addWidget(folderNameLabel, 0, 0, Qt::AlignRight);
  gridLayout->addWidget(folderNameEdit, 0, 1, 1, 2);
  gridLayout->addWidget(folderPrivilegeLabel, 1, 0, Qt::AlignRight);
  gridLayout->addWidget(folderPrivilegeField, 1, 1, 1, 2);
  gridLayout->addWidget(cancelBtn, 3, 1, Qt::AlignRight);
  gridLayout->addWidget(okBtn, 3, 2, Qt::AlignRight);

  this->setLayout(gridLayout);
}

void AddFolderDialog::connectSignalSlots() {
  connect(okBtn, &QPushButton::clicked, this, &AddFolderDialog::doAddFolder);
  connect(cancelBtn, &QPushButton::clicked, [this]() { hide(); });
}

void AddFolderDialog::doAddFolder() {
  QJsonObject json;
  json["name"] = folderNameEdit->text();
  json["absolutePath"] = (currentDirName == "/")
                             ? "/" + folderNameEdit->text()
                             : currentDirName + "/" + folderNameEdit->text();
  json["privilege"] = folderPrivilegeField->currentIndex() + 1;
  json["assignedDirectory"] = QString::number(currentDirId);

  QMap<QString, QString> headers = {
      {"token", QString::fromStdString(
                    ClientConfig::getInstance().getUserInfo().getToken())}};
  auto response = QHttpmanger::UrlRequestPost(
      QString::fromStdString(ClientConfig::getInstance().getServerUrl()) +
          FETCH_DIR_ITEMS_ROUTE + "/" +
          QString::number(
              ClientConfig::getInstance().getUserInfo().getUserId()),
      QJsonDocument(json).toJson(QJsonDocument::Compact), headers);
  QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
  if (jsonDoc.isNull() || !jsonDoc.isObject()) {
    emit showPrompt(tr("response parse error"));
    return;
  }

  parseJson(jsonDoc.object());
}

void AddFolderDialog::parseJson(const QJsonObject &json) {
  int code = json.value("code").toInt();
  if (code != 1) {
    emit showPrompt(json.value("message").toString());
  } else {
    emit addFolderSuccess();
  }
  hide();
}

void AddFolderDialog::clearFielders() {
  folderNameEdit->clear();
  folderPrivilegeField->setCurrentIndex(0);
}