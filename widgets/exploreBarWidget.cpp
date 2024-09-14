#include "exploreBarWidget.h"

#include <qboxlayout.h>
#include <qlistview.h>
#include <qlistwidget.h>

#include <QMessageBox>

#include "../model/fileItemInfo.h"
#include "../model/fileItemWidget.h"

ExploreBarWidget::ExploreBarWidget(QWidget *parent) : QWidget(parent) {
  initUI();
  connectSignalSlots();
}

void ExploreBarWidget::initUI() {
  listView = new QListWidget(this);
  QVBoxLayout *vLayout = new QVBoxLayout(this);
  vLayout->addWidget(listView);
  this->setLayout(vLayout);
}

void ExploreBarWidget::connectSignalSlots() {
  connect(listView, &QListWidget::itemDoubleClicked, this,
          [this](QListWidgetItem *item) {
            emit this->itemNCLickedSign(listView->row(item));
          });
}

void ExploreBarWidget::updateUI(const QList<FileItemInfo> &fileItems) {
  listView->clear();
  for (auto &fileItem : fileItems) {
    FileItemWidget *fileWidget = new FileItemWidget(fileItem, this);
    connect(fileWidget, &FileItemWidget::downloadFileById, this,
            &ExploreBarWidget::downloadFileById);
    QListWidgetItem *item = new QListWidgetItem();
    item->setSizeHint(QSize(48, 48));
    listView->addItem(item);
    listView->setItemWidget(item, fileWidget);
  }
}
