#include "exploreBarWidget.h"

#include <qboxlayout.h>
#include <qlistview.h>
#include <qlistwidget.h>

#include <QMessageBox>
#include <memory>

#include "../model/fileItemInfo.h"
#include "../model/fileItemWidget.h"

ExploreBarWidget::ExploreBarWidget(QWidget *parent) : QWidget(parent) {
  initUI();
  connectSignalSlots();
}

void ExploreBarWidget::initUI() {
  listView = new QListWidget(this);
  FileItemInfo info1(1, "hello", FILE_CATEGORY, 1);
  FileItemInfo info2(2, "dir", DIR_CATEGORY, 0);

  FileItemWidget *fileWidget1 = new FileItemWidget(info1, this);
  FileItemWidget *fileWidget2 = new FileItemWidget(info2, this);

  QListWidgetItem *item1 = new QListWidgetItem();
  item1->setSizeHint(QSize(48, 48));
  listView->addItem(item1);
  listView->setItemWidget(item1, fileWidget1);

  QListWidgetItem *item2 = new QListWidgetItem();
  item2->setSizeHint(QSize(48, 48));
  listView->addItem(item2);
  listView->setItemWidget(item2, fileWidget2);

  QVBoxLayout *vLayout = new QVBoxLayout(this);
  vLayout->addWidget(listView);
  this->setLayout(vLayout);
}

void ExploreBarWidget::connectSignalSlots() {
  connect(listView, &QListWidget::itemDoubleClicked, this,
          &ExploreBarWidget::onItemDoubleClicked);
}

void ExploreBarWidget::onItemDoubleClicked(QListWidgetItem *item) {
  QMessageBox::information(
      this, "Item Clicked",
      "You clicked: " + QString::number(listView->row(item)));
}
