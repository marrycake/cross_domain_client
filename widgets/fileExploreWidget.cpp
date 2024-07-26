#include "fileExploreWidget.h"

#include <qmessagebox.h>

#include <QVBoxLayout>

#include "operateBarWidget.h"

FileExploreWidget::FileExploreWidget(QWidget *parent) : QWidget(parent) {
  initUI();
  connectSignalSlots();
}

FileExploreWidget::~FileExploreWidget() {}

void FileExploreWidget::initUI() {
  operateBar = new OperateBarWidget(this);
  exploreBar = new ExploreBarWidget(this);
  QVBoxLayout *vLayout = new QVBoxLayout(this);
  vLayout->addWidget(operateBar);
  vLayout->addWidget(exploreBar);
  this->setLayout(vLayout);
}

void FileExploreWidget::connectSignalSlots() {
  connect(operateBar, &OperateBarWidget::backSign, this,
          &FileExploreWidget::goBack);
  connect(operateBar, &OperateBarWidget::homeSign, this,
          &FileExploreWidget::goHome);
  connect(operateBar, &OperateBarWidget::refreshSign, this,
          &FileExploreWidget::refresh);
  connect(operateBar, &OperateBarWidget::uploadSign, this,
          &FileExploreWidget::upload);
}

void FileExploreWidget::goBack() {
  QMessageBox::information(this, "Item Clicked", "back");
}

void FileExploreWidget::goHome() {
  QMessageBox::information(this, "Item Clicked", "home");
}

void FileExploreWidget::refresh() {
  QMessageBox::information(this, "Item Clicked", "refresh");
}

void FileExploreWidget::upload() {
  QMessageBox::information(this, "Item Clicked", "upload");
}
