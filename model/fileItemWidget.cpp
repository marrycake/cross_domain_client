#include "fileItemWidget.h"

#include <qboxlayout.h>
#include <qchar.h>
#include <qicon.h>
#include <qlabel.h>
#include <qnamespace.h>
#include <qobjectdefs.h>
#include <qpixmap.h>
#include <qpushbutton.h>
#include <qwidget.h>

#include "fileItemInfo.h"
#include "iconConstants.h"

FileItemWidget::FileItemWidget(const FileItemInfo &fileInfo, QWidget *parent)
    : QWidget(parent), fileInfo(fileInfo) {
  initUI();
  connectSignalSlots();
}

void FileItemWidget::initUI() {
  QPixmap image;
  if (fileInfo.getCategory() == FILE_CATEGORY) {
    image.load(FILE_ICON);
  } else if (fileInfo.getCategory() == DIR_CATEGORY) {
    image.load(FOLDER_ICON);
  } else if (fileInfo.getCategory() == DOMAIN_CATEGORY) {
    image.load(DOMAIN_ICON);
  }

  QLabel *imageLabel = new QLabel(this);
  imageLabel->setPixmap(
      image.scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation));
  QLabel *fileNameLabel = new QLabel(fileInfo.getName(), this);

  QHBoxLayout *hLayout = new QHBoxLayout(this);
  hLayout->addWidget(imageLabel);
  hLayout->addWidget(fileNameLabel);
  hLayout->addStretch(1);

  if (fileInfo.getCategory() == FILE_CATEGORY) {
    QPixmap downImage =
        QPixmap(DOWNLOAD_ICON)
            .scaled(30, 30, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    QIcon downloadIcon(downImage);
    QPushButton *downloadBtn = new QPushButton(downloadIcon, "");
    connect(downloadBtn, &QPushButton::clicked,
            [&, this]() { emit downloadFileById(fileInfo.getFileId()); });
    hLayout->addWidget(downloadBtn);
  }
  this->setLayout(hLayout);
}

void FileItemWidget::connectSignalSlots() {}