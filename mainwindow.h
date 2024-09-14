
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "drop_shadow_widget.h"
#include "framework/include/title_widget.h"
#include "qtmaterialsnackbar.h"

class QStackedWidget;
class LoginWidget;
class RegisterWidget;
class FileExploreWidget;

class MainWindow : public DropShadowWidget

{
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 protected:
  virtual void paintEvent(QPaintEvent *event);

 private slots:
  void switchToRegister();
  void switchToLogin();
  void switchToExplore();
  void reigsterSuccessHandle();
  void changeSkin(QString skin_name);
  void showMaxOrNormal();

 public slots:
  void showPrompt(const QString &msg);

 private:
  void initUI();
  void connectSignalSlots();

  TitleWidget *titleWidget;

  QString skin_name;  // 主窗口背景图片的名称

  QStackedWidget *stackedWidget;
  LoginWidget *loginWidget;
  RegisterWidget *registerWidget;
  FileExploreWidget *fileExploreWidget;

  QtMaterialSnackbar *snackBar;
};

#endif  // MAINWINDOW_H
