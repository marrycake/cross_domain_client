
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "qtmaterialtextfield.h"
#include "qtmaterialflatbutton.h"

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

private:
    void connectSignalSlots();
    bool checkUserNameIsValid();
    bool checkPasswordIsValid();
    void requestServer();
    void checkResponse(QJsonObject &json);

private slots:
    void login();

signals:
    void loginSuccess();
    void loginFailed();

private:
    void initUI();

    QtMaterialTextField *userNameField;
    QtMaterialTextField *passwdField;
    QtMaterialFlatButton *confirmButton;
};

#endif // LOGINWIDGET_H
