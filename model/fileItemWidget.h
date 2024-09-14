#ifndef FILEITEMWIDGET_H
#define FILEITEMWIDGET_H

#include <qobjectdefs.h>
#include <qpushbutton.h>
#include <qwidget.h>

#include <QWidget>
#include <cstdint>

#include "fileItemInfo.h"

class FileItemWidget : public QWidget {
  Q_OBJECT
 public:
  explicit FileItemWidget(const FileItemInfo &fileInfo,
                          QWidget *parent = nullptr);

 signals:
  void downloadFileById(uint64_t fileId);

 private:
  void initUI();
  void connectSignalSlots();

  FileItemInfo fileInfo;
};

#endif  // FILEITEMWIDGET_H