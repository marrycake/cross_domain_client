#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>
#include "qtmaterialtextfield.h"
#include "qtmaterialflatbutton.h"
#include <QComboBox>

class RegisterWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    ~RegisterWidget();

private:
    void connectSignalSlots();
    bool checkUserNameIsValid();
    bool checkPasswordIsValid();
    void requestServer();

private slots:
    void registerFunc();

signals:
    void registerSuccess();

private:
    void initUI();

    QtMaterialTextField *userNameField;
    QtMaterialTextField *passwdField;
    QComboBox *userLevelField;
    QtMaterialFlatButton *confirmButton;
};

#endif // REGISTERWIDGET_H