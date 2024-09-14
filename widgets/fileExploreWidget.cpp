#include "fileExploreWidget.h"

#include <qboxlayout.h>
#include <qchar.h>
#include <qframe.h>
#include <qlabel.h>
#include <qmap.h>
#include <qmessagebox.h>

#include <QVBoxLayout>
#include <memory>
#include <regex>
#include <utility>

#include "../clientconfig.h"
#include "../constans.h"
#include "../http/QHttpmanger.h"
#include "addFolderDialog.h"
#include "aesHelper.h"
#include "base64Helper.h"
#include "dataPacket.h"
#include "exploreBarWidget.h"
#include "fileHelper.h"
#include "filesconstans.h"
#include "hashGenerator.h"
#include "operateBarWidget.h"
#include "rsaHelper.h"
#include "uploadFileDialog.h"

FileExploreWidget::FileExploreWidget(QWidget *parent) : QWidget(parent) {
  initUI();
  connectSignalSlots();
}

FileExploreWidget::~FileExploreWidget() {}

void FileExploreWidget::initUI() {
  addFolderDialog = new AddFolderDialog(this);
  uploadFileDialog = new UploadFileDialog(this);

  operateBar = new OperateBarWidget(this);
  exploreBar = new ExploreBarWidget(this);
  QHBoxLayout *infoDisplayLayout = new QHBoxLayout(this);
  QLabel *currentDirPrompt = new QLabel(tr("current dir: "));
  QLabel *currentDomainPrompt = new QLabel(tr("current domain: "));
  currentDirLabel = new QLabel(this);
  currentDomainLabel = new QLabel(this);
  infoDisplayLayout->addWidget(currentDomainPrompt);
  infoDisplayLayout->addWidget(currentDomainLabel);
  infoDisplayLayout->addWidget(currentDirPrompt);
  infoDisplayLayout->addWidget(currentDirLabel);
  infoDisplayLayout->addStretch(1);
  QFrame *infoDisplayFrame = new QFrame(this);
  infoDisplayFrame->setLayout(infoDisplayLayout);
  infoDisplayFrame->setFrameStyle(QFrame::Box | QFrame::Raised);

  QVBoxLayout *vLayout = new QVBoxLayout(this);
  vLayout->addWidget(operateBar);
  vLayout->addWidget(infoDisplayFrame);
  vLayout->addWidget(exploreBar);
  this->setLayout(vLayout);
}

void FileExploreWidget::connectSignalSlots() {
  connect(operateBar, &OperateBarWidget::backSign, this,
          &FileExploreWidget::goBack);
  connect(operateBar, &OperateBarWidget::homeSign, this,
          &FileExploreWidget::goHome);
  connect(operateBar, &OperateBarWidget::refreshSign, this,
          &FileExploreWidget::refresh);
  connect(operateBar, &OperateBarWidget::uploadSign, this,
          &FileExploreWidget::upload);
  connect(operateBar, &OperateBarWidget::addFolderSign, [this]() {
    const auto &currentModel = modelStack.top();
    addFolderDialog->setParamters(currentModel->getCurrentDomainId(),
                                  currentModel->getCurrentDirId(),
                                  currentModel->getCurrentDirName());
    addFolderDialog->clearFielders();
    addFolderDialog->show();
  });

  connect(exploreBar, &ExploreBarWidget::itemNCLickedSign, this,
          &FileExploreWidget::onItemClickHandle);
  connect(addFolderDialog, &AddFolderDialog::showPrompt, this,
          &FileExploreWidget::showPrompt);
  connect(addFolderDialog, &AddFolderDialog::addFolderSuccess, this,
          &FileExploreWidget::refresh);

  connect(uploadFileDialog, &UploadFileDialog::showPrompt, this,
          &FileExploreWidget::showPrompt);
  connect(uploadFileDialog, &UploadFileDialog::uploadFileSuccess, this,
          &FileExploreWidget::refresh);
  connect(exploreBar, &ExploreBarWidget::downloadFileById, this,
          &FileExploreWidget::downloadFileById);
}

void FileExploreWidget::goBack() {
  if (modelStack.size() > 1) {
    modelStack.pop();
    currentDomainLabel->setText(modelStack.top()->getCurrentDomainName());
    currentDirLabel->setText(modelStack.top()->getCurrentDirName());
    exploreBar->updateUI(modelStack.top()->getFileItems());
  }
}

void FileExploreWidget::goHome() {
  loadDomains();
  exploreBar->updateUI(modelStack.top()->getFileItems());
}

void FileExploreWidget::refresh() {
  const auto &currentModel = modelStack.top();
  QMap<QString, QString> headers = {
      {"token", QString::fromStdString(
                    ClientConfig::getInstance().getUserInfo().getToken())}};
  QString url =
      QString::fromStdString(ClientConfig::getInstance().getServerUrl()) +
      FETCH_DIR_ITEMS_ROUTE;
  if (modelStack.top()->getCurrentDomainId() == localDomainId) {
    url +=
        "/" +
        QString::number(ClientConfig::getInstance().getUserInfo().getUserId()) +
        "/" + QString::number(modelStack.top()->getCurrentDirId());
  } else {
    url +=
        "/" +
        QString::number(ClientConfig::getInstance().getUserInfo().getUserId()) +
        "/" + QString::number(modelStack.top()->getCurrentDomainId()) + "/" +
        QString::number(modelStack.top()->getCurrentDirId());
  }
  auto result = QHttpmanger::UrlRequestGet(url, headers);

  QJsonDocument jsonDoc = QJsonDocument::fromJson(result.toUtf8());

  if (jsonDoc.isNull() && jsonDoc.isObject()) {
    emit showPrompt(tr("response parse error"));
    return;
  }

  const auto &json = jsonDoc.object();

  int code = json.value("code").toInt();
  if (code != 1) {
    emit showPrompt(tr("load files error"));
    return;
  }

  auto dataObj = json.value("data").toArray();
  currentModel->getFileItems().clear();
  for (const auto &item : dataObj) {
    auto itemObj = item.toObject();
    auto fileId = itemObj.value("id").toInt();
    auto fileName = itemObj.value("name").toString();
    auto fileCategory = itemObj.value("category").toString() == "file"
                            ? FILE_CATEGORY
                            : DIR_CATEGORY;

    auto filePrivilege = itemObj.value("privilege").toInt();
    FileItemInfo fileInfo(fileId, fileName, fileCategory, filePrivilege);
    currentModel->getFileItems().append(fileInfo);
  }

  exploreBar->updateUI(modelStack.top()->getFileItems());
}

void FileExploreWidget::upload() {
  const auto &currentModel = modelStack.top();
  uploadFileDialog->setParamters(currentModel->getCurrentDomainId(),
                                 currentModel->getCurrentDirId(),
                                 currentModel->getCurrentDirName());
  uploadFileDialog->clearFielders();
  uploadFileDialog->show();
}

void FileExploreWidget::onItemClickHandle(uint32_t n) {
  const auto &currentModel = modelStack.top();
  const auto &fileItem = currentModel->getFileItems().at(n);
  switch (fileItem.getCategory()) {
    case DOMAIN_CATEGORY: {
      loadFIlesUnderDomainFolder(fileItem.getFileId(), 1);
      auto &newModel = modelStack.top();
      newModel->setCurrentDirId(1);
      newModel->setCurrentDirName("/");
      newModel->setCurrentDomainId(fileItem.getFileId());
      newModel->setCurrentDomainName(fileItem.getName());
      currentDomainLabel->setText(newModel->getCurrentDomainName());
      currentDirLabel->setText(newModel->getCurrentDirName());
      exploreBar->updateUI(newModel->getFileItems());
      break;
    }
    case DIR_CATEGORY: {
      loadFIlesUnderDomainFolder(currentModel->getCurrentDomainId(),
                                 fileItem.getFileId());
      auto &newModel = modelStack.top();
      newModel->setCurrentDirId(fileItem.getFileId());
      newModel->setCurrentDomainId(currentModel->getCurrentDomainId());
      newModel->setCurrentDomainName(currentModel->getCurrentDomainName());
      if (currentModel->getCurrentDirName() == "/") {
        newModel->setCurrentDirName(currentModel->getCurrentDirName() +
                                    fileItem.getName());
      } else {
        newModel->setCurrentDirName(currentModel->getCurrentDirName() + "/" +
                                    fileItem.getName());
      }
      currentDomainLabel->setText(newModel->getCurrentDomainName());
      currentDirLabel->setText(newModel->getCurrentDirName());
      exploreBar->updateUI(newModel->getFileItems());
      break;
    }
    default:
      break;
  }
}

void FileExploreWidget::loadFIlesUnderDomainFolder(uint64_t domainId,
                                                   uint64_t folderId) {
  QMap<QString, QString> headers = {
      {"token", QString::fromStdString(
                    ClientConfig::getInstance().getUserInfo().getToken())}};
  QString url =
      QString::fromStdString(ClientConfig::getInstance().getServerUrl()) +
      FETCH_DIR_ITEMS_ROUTE;
  if (domainId == localDomainId) {
    url +=
        "/" +
        QString::number(ClientConfig::getInstance().getUserInfo().getUserId()) +
        "/" + QString::number(folderId);
  } else {
    url +=
        "/" +
        QString::number(ClientConfig::getInstance().getUserInfo().getUserId()) +
        "/" + QString::number(domainId) + "/" + QString::number(folderId);
  }

  auto result = QHttpmanger::UrlRequestGet(url, headers);

  QJsonDocument jsonDoc = QJsonDocument::fromJson(result.toUtf8());

  if (jsonDoc.isNull() && jsonDoc.isObject()) {
    emit showPrompt(tr("response parse error"));
    return;
  }
  auto newModel = std::make_unique<FileItemModel>();
  analyzeFileItemsJson(jsonDoc.object(), newModel);
  modelStack.push(std::move(newModel));
}

void FileExploreWidget::analyzeFileItemsJson(
    const QJsonObject &json, const std::unique_ptr<FileItemModel> &newModel) {
  int code = json.value("code").toInt();
  if (code != 1) {
    emit showPrompt(tr("load files error"));
    return;
  }

  auto dataObj = json.value("data").toArray();

  for (const auto &item : dataObj) {
    auto itemObj = item.toObject();
    auto fileId = itemObj.value("id").toInt();
    auto fileName = itemObj.value("name").toString();
    auto fileCategory = itemObj.value("category").toString() == "file"
                            ? FILE_CATEGORY
                            : DIR_CATEGORY;

    auto filePrivilege = itemObj.value("privilege").toInt();
    FileItemInfo fileInfo(fileId, fileName, fileCategory, filePrivilege);
    newModel->getFileItems().append(fileInfo);
  }
}

void FileExploreWidget::loadDomains() {
  QMap<QString, QString> headers = {
      {"token", QString::fromStdString(
                    ClientConfig::getInstance().getUserInfo().getToken())}};
  auto result = QHttpmanger::UrlRequestGet(
      QString::fromStdString(ClientConfig::getInstance().getServerUrl()) +
          FETCH_DOMAINS_ROUTE,
      headers);

  QJsonDocument jsonDoc = QJsonDocument::fromJson(result.toUtf8());

  if (jsonDoc.isNull() && jsonDoc.isObject()) {
    emit showPrompt(tr("response parse error"));
    return;
  }

  analyzeJson(jsonDoc.object());
  std::regex pattern("\\(local\\)$");
  for (const auto &fileItem : modelStack.top()->getFileItems()) {
    if (std::regex_search(fileItem.getName().toStdString(), pattern)) {
      localDomainId = fileItem.getFileId();
      break;
    }
  }
}

void FileExploreWidget::analyzeJson(const QJsonObject &json) {
  int code = json.value("code").toInt();
  if (code != 1) {
    emit showPrompt(tr("username or password invalid"));
    return;
  }

  QString dataString = json.value("data").toString();
  QJsonDocument dataDoc = QJsonDocument::fromJson(dataString.toUtf8());
  QJsonObject dataObj = dataDoc.object();
  while (!modelStack.empty()) {
    modelStack.pop();
  }
  modelStack.emplace(std::make_unique<FileItemModel>(dataObj));
}

void FileExploreWidget::downloadFileById(uint64_t fileId) {
  auto &conf = ClientConfig::getInstance();
  QMap<QString, QString> headers = {
      {"token", QString::fromStdString(conf.getUserInfo().getToken())},
      {"publicKey", QString::fromStdString(RsaHelper::dumpPublicKeyToStr(
                        conf.getUserInfo().getUserPublicKey()))}};
  QString entireRoute;
  if (modelStack.top()->getCurrentDomainId() == localDomainId) {
    entireRoute = DOWNLOAD_ROUTE + "/" +
                  QString::number(conf.getUserInfo().getUserId()) + "/" +
                  QString::number(fileId);
  } else {
    // /cross/{userId}/{requestDomainId}/{fileId}
    entireRoute = DOWNLOAD_ROUTE + "/cross" + "/" +
                  QString::number(conf.getUserInfo().getUserId()) + "/" +
                  QString::number(modelStack.top()->getCurrentDomainId()) +
                  "/" + QString::number(fileId);
  }

  auto result = QHttpmanger::UrlRequestGet(
      QString::fromStdString(conf.getServerUrl()) + entireRoute, headers);

  QJsonDocument jsonDoc = QJsonDocument::fromJson(result.toUtf8());

  if (jsonDoc.isNull() && jsonDoc.isObject()) {
    emit showPrompt(tr("response parse error"));
    return;
  }

  const auto &json = jsonDoc.object();
  int code = json.value("code").toInt();
  if (code != 1) {
    emit showPrompt((json.value("msg").toString()));
    return;
  }

  const auto &dataObj = json.value("data").toObject();
  const auto &dataProviderObj = dataObj.value("dataProvider").toObject();
  const auto &directoryItemInfoObj =
      dataObj.value("directoryItemInfo").toObject();

  DataPacket dataPacket;
  auto &dataProvider = dataPacket.getDataProvider();
  dataProvider.setUserId(dataProviderObj.value("userId").toInt());
  dataProvider.setUserName(
      dataProviderObj.value("userName").toString().toStdString());
  dataProvider.setUserPrivilege(dataProviderObj.value("userPrivilege").toInt());

  auto &directoryItemInfo = dataPacket.getDirectoryItemInfo();
  directoryItemInfo.setDirName(
      directoryItemInfoObj.value("name").toString().toStdString());
  directoryItemInfo.setDirPrivilege(
      directoryItemInfoObj.value("privilege").toInt());

  std::string encryptContent = Base64Helper::decode(
      dataObj.value("encryptContent").toString().toStdString());
  std::string encryptKey = Base64Helper::decode(
      dataObj.value("encryptKey").toString().toStdString());
  std::string signature =
      Base64Helper::decode(dataObj.value("signature").toString().toStdString());

  if (HashGenerator::sha256(encryptContent) != signature) {
    emit showPrompt(tr("file invalid"));
    return;
  }

  std::string decryptKey =
      RsaHelper::decrypt(conf.getUserInfo().getUserPrivateKey(), encryptKey);
  std::string decryptContent = AESHelper::decrypt(encryptContent, decryptKey);

  std::string filePath =
      DOWNLOAD_DIR.toStdString() + "/" + directoryItemInfo.getDirName();
  FileHelper::writeToFile(decryptContent, filePath);
}
