#ifndef FILEITEMWIDGET_H
#define FILEITEMWIDGET_H

#include <qpushbutton.h>
#include <qwidget.h>

#include <QWidget>

#include "fileItemInfo.h"

class FileItemWidget : public QWidget {
 public:
  explicit FileItemWidget(const FileItemInfo &fileInfo,
                          QWidget *parent = nullptr);

 private:
  void initUI();
  void connectSignalSlots();

  FileItemInfo fileInfo;
};

#endif  // FILEITEMWIDGET_H