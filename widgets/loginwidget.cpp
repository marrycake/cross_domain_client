
#include "loginwidget.h"
#include "QVBoxLayout"
#include <QString>
#include <QDebug>
#include "../http/QHttpmanger.h"
#include "filesconstans.h"

LoginWidget::LoginWidget(QWidget *parent)
    : QWidget{parent}
{
    initUI();
}

LoginWidget::~LoginWidget()
{
}

void LoginWidget::initUI()
{
    userNameField = new QtMaterialTextField(this);
    userNameField->setLabel(tr("userName"));
    userNameField->setMinimumWidth(500);
    passwdField = new QtMaterialTextField(this);
    passwdField->setLabel(tr("password"));
    passwdField->setMinimumWidth(500);
    confirmButton = new QtMaterialFlatButton();
    confirmButton->setText(tr("login"));
    confirmButton->setMinimumWidth(500);

    QVBoxLayout *vlayout = new QVBoxLayout(this);
    vlayout->addStretch();
    vlayout->addWidget(userNameField, 0, Qt::AlignHCenter);
    vlayout->addWidget(passwdField, 0, Qt::AlignHCenter);
    vlayout->addWidget(confirmButton, 0, Qt::AlignHCenter);
    vlayout->addStretch();
    this->setLayout(vlayout);
}

void LoginWidget::connectSignalSlots()
{
    connect(confirmButton, &QtMaterialFlatButton::click, this, &LoginWidget::login);
}

bool LoginWidget::checkUserNameIsValid()
{
    return !userNameField->text().isEmpty();
}

bool LoginWidget::checkPasswordIsValid()
{
    return !passwdField->text().isEmpty();
}

void LoginWidget::requestServer()
{
    QJsonObject json;
    json["userName"] = userNameField->text();
    json["passWord"] = passwdField->text();
    auto response = QHttpmanger::UrlRequestPost(SERVER_URL + LOGIN_ROUTE, QJsonDocument(json).toJson(QJsonDocument::Compact));
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
    if (jsonDoc.isNull() || !jsonDoc.isObject())
    {
        emit loginFailed();
        return;
    }

    QJsonObject responseJsonObject = jsonDoc.object();
}

void LoginWidget::checkResponse(QJsonObject &json)
{
    int code = json.value("code").toInt();
    if (code != 1)
    {
        emit loginFailed();
        return;
    }
    QString data = json["data"].toString();
}

void LoginWidget::login()
{
    if (!checkUserNameIsValid())
    {
        qDebug() << "user name is unvalid";
        return;
    }

    if (!checkPasswordIsValid())
    {
        qDebug() << "password is unvalid";
        return;
    }

    requestServer();
}
