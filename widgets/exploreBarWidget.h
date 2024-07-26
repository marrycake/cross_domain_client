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

 private slots:
  void onItemDoubleClicked(QListWidgetItem *item);

 private:
  void initUI();
  void connectSignalSlots();

  QListWidget *listView;
};

#endif  // EXPLOREBARWIDGET_H