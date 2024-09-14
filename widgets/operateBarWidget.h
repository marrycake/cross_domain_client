#ifndef OPERATEBARWIDGET_H
#define OPERATEBARWIDGET_H

#include <qobjectdefs.h>

#include <QWidget>

#include "qtmaterialiconbutton.h"

class OperateBarWidget : public QWidget {
  Q_OBJECT
 public:
  explicit OperateBarWidget(QWidget *parent = nullptr);
  ~OperateBarWidget();

 signals:
  void backSign();
  void homeSign();
  void refreshSign();
  void uploadSign();
  void addFolderSign();

 private:
  void initUI();
  void connnectSignalSlots();

  QtMaterialIconButton *backBtn;
  QtMaterialIconButton *homeBtn;
  QtMaterialIconButton *refreshBtn;
  QtMaterialIconButton *uploadBtn;
  QtMaterialIconButton *addFolderBtn;
};

#endif  // OPERATEBARWIDGET_H