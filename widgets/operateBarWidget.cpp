#include "operateBarWidget.h"

#include <QHBoxLayout>

#include "filesconstans.h"

OperateBarWidget::OperateBarWidget(QWidget *parent) : QWidget(parent) {
  initUI();
  connnectSignalSlots();
}

OperateBarWidget::~OperateBarWidget() {}

void OperateBarWidget::initUI() {
  backBtn = new QtMaterialIconButton(QIcon(BACK_IMG), this);
  homeBtn = new QtMaterialIconButton(QIcon(HOME_IMG), this);
  refreshBtn = new QtMaterialIconButton(QIcon(REFRESH_IMG), this);
  uploadBtn = new QtMaterialIconButton(QIcon(UPLOAD_IMG), this);

  QHBoxLayout *hLayout = new QHBoxLayout(this);
  hLayout->addWidget(backBtn);
  hLayout->addWidget(homeBtn);
  hLayout->addWidget(refreshBtn);
  hLayout->addWidget(uploadBtn);
  hLayout->addStretch();
  this->setLayout(hLayout);
}

void OperateBarWidget::connnectSignalSlots() {
  connect(backBtn, &QtMaterialIconButton::clicked, this,
          &OperateBarWidget::backSign);
  connect(homeBtn, &QtMaterialIconButton::clicked, this,
          &OperateBarWidget::homeSign);
  connect(refreshBtn, &QtMaterialIconButton::clicked, this,
          &OperateBarWidget::refreshSign);
  connect(uploadBtn, &QtMaterialIconButton::clicked, this,
          &OperateBarWidget::uploadSign);
}