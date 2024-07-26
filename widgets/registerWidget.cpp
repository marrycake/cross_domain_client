#include "registerWidget.h"

#include <qnamespace.h>
#include <qpushbutton.h>

#include <QDebug>
#include <QGridLayout>
#include <QLabel>

#include "../clientconfig.h"
#include "../http/QHttpmanger.h"
#include "filesconstans.h"
#include "qtmaterialflatbutton.h"

RegisterWidget::RegisterWidget(QWidget *parent) : QWidget(parent) {
  initUI();
  connectSignalSlots();
}

RegisterWidget::~RegisterWidget() {}

void RegisterWidget::initUI() {
  QLabel *userNameLabel = new QLabel(tr("userName"), this);
  QLabel *passwordLabel = new QLabel(tr("password"), this);
  QLabel *userLevelLabel = new QLabel(tr("userLevel"), this);

  userNameField = new QtMaterialTextField(this);
  userNameField->setLabel(tr("userName"));
  userNameField->setMinimumWidth(500);
  passwdField = new QtMaterialTextField(this);
  passwdField->setLabel(tr("password"));
  passwdField->setMinimumWidth(500);
  userLevelField = new QComboBox(this);
  QStringList items;
  items << tr("first") << tr("second") << tr("third") << tr("forth");
  userLevelField->addItems(items);
  userLevelField->setMinimumWidth(500);
  toLoginButton = new QPushButton(this);
  toLoginButton->setText(tr("to login"));
  confirmButton = new QtMaterialFlatButton(this);
  confirmButton->setText(tr("register"));
  confirmButton->setMinimumWidth(500);

  QVBoxLayout *hlayout = new QVBoxLayout(this);

  QGridLayout *gridLayout = new QGridLayout(this);
  gridLayout->setSpacing(5);
  gridLayout->setContentsMargins(5, 5, 5, 5);

  gridLayout->addWidget(userNameLabel, 0, 0, Qt::AlignRight);
  gridLayout->addWidget(userNameField, 0, 1, 1, 2, Qt::AlignLeft);
  gridLayout->addWidget(passwordLabel, 1, 0, Qt::AlignRight);
  gridLayout->addWidget(passwdField, 1, 1, 1, 2, Qt::AlignLeft);
  gridLayout->addWidget(userLevelLabel, 2, 0, Qt::AlignRight);
  gridLayout->addWidget(userLevelField, 2, 1, 1, 2, Qt::AlignLeft);
  gridLayout->addWidget(toLoginButton, 3, 1, Qt::AlignLeft);
  gridLayout->addWidget(confirmButton, 4, 0, 1, 3, Qt::AlignHCenter);

  hlayout->addStretch();
  hlayout->addLayout(gridLayout);
  hlayout->addStretch();

  this->setLayout(hlayout);
}

void RegisterWidget::connectSignalSlots() {
  connect(confirmButton, &QtMaterialFlatButton::clicked, this,
          &RegisterWidget::registerFunc);
  connect(toLoginButton, &QPushButton::clicked, this,
          &RegisterWidget::switchToLogin);
}

bool RegisterWidget::checkUserNameIsValid() {
  return !userNameField->text().isEmpty();
}

bool RegisterWidget::checkPasswordIsValid() {
  return !passwdField->text().isEmpty();
}

void RegisterWidget::requestServer() {
  QJsonObject json;
  json["name"] = userNameField->text();
  json["password"] = passwdField->text();
  json["privilege"] = userLevelField->currentIndex() + 1;
  auto response = QHttpmanger::UrlRequestPost(
      QString::fromStdString(ClientConfig::getInstance().getServerUrl()) +
          REGISTER_ROUTE,
      QJsonDocument(json).toJson(QJsonDocument::Compact));
  QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
  if (jsonDoc.isNull() || !jsonDoc.isObject()) {
    emit showPrompt(tr("response parse error"));
    return;
  }

  QJsonObject responseJsonObject = jsonDoc.object();
  checkResponse(responseJsonObject);
}

void RegisterWidget::registerFunc() {
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

void RegisterWidget::checkResponse(QJsonObject &json) {
  int code = json.value("code").toInt();
  if (code != 1) {
    emit showPrompt(tr("register failed"));
    return;
  }
  emit registerSuccess();
}
