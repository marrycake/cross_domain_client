
#include "loginwidget.h"

#include <qnamespace.h>

#include <QLabel>
#include <QString>

#include "../clientconfig.h"
#include "../http/QHttpmanger.h"
#include "QVBoxLayout"
#include "filesconstans.h"

LoginWidget::LoginWidget(QWidget *parent) : QWidget{parent} {
  initUI();
  connectSignalSlots();
}

LoginWidget::~LoginWidget() {}

void LoginWidget::initUI() {
  QLabel *userNameLabel = new QLabel(tr("userName"), this);
  QLabel *passwordLabel = new QLabel(tr("password"), this);

  userNameField = new QtMaterialTextField(this);
  userNameField->setLabel(tr("userName"));
  userNameField->setMinimumWidth(500);
  passwdField = new QtMaterialTextField(this);
  passwdField->setLabel(tr("password"));
  passwdField->setMinimumWidth(500);
  registerButton = new QPushButton(this);
  registerButton->setText(tr("no account"));
  confirmButton = new QtMaterialFlatButton();
  confirmButton->setText(tr("login"));
  confirmButton->setMinimumWidth(500);

  QVBoxLayout *hlayout = new QVBoxLayout(this);

  QGridLayout *gridLayout = new QGridLayout(this);
  gridLayout->setSpacing(5);
  gridLayout->setContentsMargins(5, 5, 5, 5);

  gridLayout->addWidget(userNameLabel, 0, 0, Qt::AlignRight);
  gridLayout->addWidget(userNameField, 0, 1, 1, 2, Qt::AlignLeft);
  gridLayout->addWidget(passwordLabel, 1, 0, Qt::AlignRight);
  gridLayout->addWidget(passwdField, 1, 1, 1, 2, Qt::AlignLeft);
  gridLayout->addWidget(registerButton, 2, 1, Qt::AlignLeft);
  gridLayout->addWidget(confirmButton, 3, 0, 1, 3, Qt::AlignHCenter);

  hlayout->addStretch();
  hlayout->addLayout(gridLayout);
  hlayout->addStretch();
  this->setLayout(hlayout);
}

void LoginWidget::connectSignalSlots() {
  connect(confirmButton, &QtMaterialFlatButton::clicked, this,
          &LoginWidget::login);
  connect(registerButton, &QPushButton::clicked, this,
          &LoginWidget::toRegister);
}

bool LoginWidget::checkUserNameIsValid() {
  return !userNameField->text().isEmpty();
}

bool LoginWidget::checkPasswordIsValid() {
  return !passwdField->text().isEmpty();
}

void LoginWidget::requestServer() {
  QJsonObject json;
  json["name"] = userNameField->text();
  json["password"] = passwdField->text();
  auto response = QHttpmanger::UrlRequestPost(
      QString::fromStdString(ClientConfig::getInstance().getServerUrl()) +
          LOGIN_ROUTE,
      QJsonDocument(json).toJson(QJsonDocument::Compact));
  QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
  if (jsonDoc.isNull() || !jsonDoc.isObject()) {
    emit showPrompt(tr("response parse error"));
    return;
  }

  QJsonObject responseJsonObject = jsonDoc.object();
  checkResponse(responseJsonObject);
}

void LoginWidget::checkResponse(QJsonObject &json) {
  int code = json.value("code").toInt();
  if (code != 1) {
    emit showPrompt(tr("username or password invalid"));
    return;
  }
  QJsonObject dataObject = json["data"].toObject();
  ClientConfig::getInstance().getUserInfo().setUserId(dataObject["id"].toInt());
  ClientConfig::getInstance().getUserInfo().setUserName(
      userNameField->text().toStdString());
  ClientConfig::getInstance().getUserInfo().setUserPrivilige(
      dataObject["level"].toInt());
  ClientConfig::getInstance().getUserInfo().setToken(
      dataObject["jwt"].toString().toStdString());
  ClientConfig::getInstance().redump();
  emit loginSuccess();
}

void LoginWidget::login() {
  if (!checkUserNameIsValid()) {
    emit showPrompt(tr("user name is unvalid"));
    return;
  }

  if (!checkPasswordIsValid()) {
    emit showPrompt(tr("password is unvalid"));
    return;
  }

  requestServer();
}
