
#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QPushButton>
#include <QWidget>

#include "qtmaterialflatbutton.h"
#include "qtmaterialtextfield.h"

class LoginWidget : public QWidget {
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
  void toRegister();
  void showPrompt(const QString &msg);

 private:
  void initUI();

  QtMaterialTextField *userNameField;
  QtMaterialTextField *passwdField;
  QPushButton *registerButton;
  QtMaterialFlatButton *confirmButton;
};

#endif  // LOGINWIDGET_H
