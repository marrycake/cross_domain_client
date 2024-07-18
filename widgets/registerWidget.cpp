#include "registerWidget.h"
#include <QGridLayout>
#include <QLabel>

RegisterWidget::RegisterWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
}

RegisterWidget::~RegisterWidget()
{
}

void RegisterWidget::initUI()
{
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
    gridLayout->addWidget(confirmButton, 3, 0, 1, 3, Qt::AlignHCenter);

    hlayout->addStretch();
    hlayout->addLayout(gridLayout);
    hlayout->addStretch();

    this->setLayout(hlayout);
}

void RegisterWidget::connectSignalSlots() {}

bool RegisterWidget::checkUserNameIsValid()
{
    return true;
}

bool RegisterWidget::checkPasswordIsValid()
{
    return true;
}

void RegisterWidget::requestServer() {}

void RegisterWidget::registerFunc() {}
