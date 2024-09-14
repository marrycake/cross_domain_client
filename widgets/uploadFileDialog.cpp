#include "uploadFileDialog.h"

#include <qboxlayout.h>
#include <qcombobox.h>
#include <qdialog.h>
#include <qgridlayout.h>
#include <qnamespace.h>
#include <qpushbutton.h>

#include <QFileDialog>
#include <QJsonObject>
#include <QLabel>

#include "../clientconfig.h"
#include "../http/QHttpmanger.h"
#include "filesconstans.h"

UploadFileDialog::UploadFileDialog(QWidget *parent) : QDialog(parent) {
  initUI();
  connectSignalSlots();
}

void UploadFileDialog::setParamters(uint64_t currentDomainId,
                                    uint64_t currentDirId,
                                    const QString &currentDirName) {
  this->currentDomainId = currentDomainId;
  this->currentDirId = currentDirId;
  this->currentDirName = currentDirName;
}

void UploadFileDialog::initUI() {
  setWindowTitle(tr("upload file"));
  QLabel *folderNameLabel = new QLabel(tr("upload file: "), this);
  QLabel *folderPrivilegeLabel = new QLabel(tr("file privilege: "), this);

  fileToUploadField = new QLineEdit(this);

  filePriviligeField = new QComboBox(this);
  QStringList items;
  items << tr("first") << tr("second") << tr("third") << tr("forth");
  filePriviligeField->addItems(items);

  okBtn = new QPushButton(tr("ok"), this);
  okBtn->setFixedSize(70, 30);
  cancelBtn = new QPushButton(tr("cancel"), this);
  cancelBtn->setFixedSize(70, 30);
  selectFileBtn = new QPushButton(tr("select"), this);

  QGridLayout *gridLayout = new QGridLayout(this);
  gridLayout->addWidget(folderNameLabel, 0, 0, Qt::AlignRight);
  gridLayout->addWidget(fileToUploadField, 0, 1, 1, 2);
  gridLayout->addWidget(selectFileBtn, 0, 4, Qt::AlignRight);
  gridLayout->addWidget(folderPrivilegeLabel, 1, 0, Qt::AlignRight);
  gridLayout->addWidget(filePriviligeField, 1, 1, 1, 2);
  gridLayout->addWidget(cancelBtn, 3, 1, Qt::AlignRight);
  gridLayout->addWidget(okBtn, 3, 2, Qt::AlignRight);

  this->setLayout(gridLayout);
}

void UploadFileDialog::connectSignalSlots() {
  connect(okBtn, &QPushButton::clicked, this, &UploadFileDialog::doUpload);
  connect(cancelBtn, &QPushButton::clicked, [this]() { hide(); });
  connect(selectFileBtn, &QPushButton::clicked, this,
          &UploadFileDialog::selectFileSlot);
}

void UploadFileDialog::doUpload() {
  QMap<QString, QString> headers = {
      {"token", QString::fromStdString(
                    ClientConfig::getInstance().getUserInfo().getToken())}};
  QMap<QString, QString> externalParamters = {
      {"assignedDirectory", QString::number(currentDirId)},
      {"privilege", QString::number(filePriviligeField->currentIndex() + 1)},
      {"category", "file"}};
  auto response = QHttpmanger::UrlRequestPostMultipart(
      QString::fromStdString(ClientConfig::getInstance().getServerUrl()) +
          UPLOAD_ROUTE + "/" +
          QString::number(
              ClientConfig::getInstance().getUserInfo().getUserId()),
      fileToUploadField->text(), externalParamters, headers);
  QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
  if (jsonDoc.isNull() || !jsonDoc.isObject()) {
    emit showPrompt(tr("response parse error"));
    return;
  }

  parseJson(jsonDoc.object());
}

void UploadFileDialog::parseJson(const QJsonObject &json) {
  int code = json.value("code").toInt();
  if (code != 1) {
    emit showPrompt(json.value("message").toString());
  } else {
    emit uploadFileSuccess();
  }
  hide();
}

void UploadFileDialog::clearFielders() {
  fileToUploadField->clear();
  filePriviligeField->setCurrentIndex(0);
}

void UploadFileDialog::selectFileSlot() {
  QString fileName = QFileDialog::getOpenFileName(
      this,
      "Open File",       // Dialog title
      QDir::homePath(),  // Starting directory
      "All Files (*.*);;Text Files (*.txt);;Images (*.png *.jpg)");  // Filter

  if (!fileName.isEmpty()) {
    fileToUploadField->setText(fileName);
  }
}