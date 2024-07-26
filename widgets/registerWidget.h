#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <qpushbutton.h>

#include <QComboBox>
#include <QJsonObject>
#include <QWidget>

#include "qtmaterialflatbutton.h"
#include "qtmaterialtextfield.h"


class RegisterWidget : public QWidget {
  Q_OBJECT
 public:
  explicit RegisterWidget(QWidget *parent = nullptr);
  ~RegisterWidget();

 private:
  void connectSignalSlots();
  bool checkUserNameIsValid();
  bool checkPasswordIsValid();
  void requestServer();
  void checkResponse(QJsonObject &json);

 private slots:
  void registerFunc();

 signals:
  void registerSuccess();
  void switchToLogin();
  void showPrompt(const QString &msg);

 private:
  void initUI();

  QtMaterialTextField *userNameField;
  QtMaterialTextField *passwdField;
  QComboBox *userLevelField;
  QPushButton *toLoginButton;
  QtMaterialFlatButton *confirmButton;
};

#endif  // REGISTERWIDGET_H