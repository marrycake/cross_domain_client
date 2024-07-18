#include "operateBarWidget.h"
#include <QHBoxLayout>
#include "filesconstans.h"

OperateBarWidget::OperateBarWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
}

OperateBarWidget::~OperateBarWidget()
{
}

void OperateBarWidget::initUI()
{
    QtMaterialIconButton *backBtn = new QtMaterialIconButton(QIcon(BACK_IMG), this);
    QtMaterialIconButton *homeBtn = new QtMaterialIconButton(QIcon(HOME_IMG), this);
    QtMaterialIconButton *refreshBtn = new QtMaterialIconButton(QIcon(REFRESH_IMG), this);
    QtMaterialIconButton *uploadBtn = new QtMaterialIconButton(QIcon(UPLOAD_IMG), this);

    QHBoxLayout *hLayout = new QHBoxLayout(this);
    hLayout->addWidget(backBtn);
    hLayout->addWidget(homeBtn);
    hLayout->addWidget(refreshBtn);
    hLayout->addWidget(uploadBtn);
    hLayout->addStretch();
    this->setLayout(hLayout);
}