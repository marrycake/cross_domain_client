#ifndef EXPLOREBARWIDGET_H
#define EXPLOREBARWIDGET_H

#include <qobjectdefs.h>

#include <QListWidget>
#include <QWidget>
#include <memory>

#include "../model/fileItemModel.h"

class ExploreBarWidget : public QWidget {
  Q_OBJECT
 public:
  explicit ExploreBarWidget(QWidget *parent = nullptr);
  void updateUI(const QList<FileItemInfo> &fileItems);

 signals:
  void itemNCLickedSign(uint32_t n);
  void downloadFileById(uint64_t fileId);

 private:
  void initUI();
  void connectSignalSlots();

  QListWidget *listView;
};

#endif  // EXPLOREBARWIDGET_H