
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "qtmaterialsnackbar.h"

class QStackedWidget;
class LoginWidget;
class RegisterWidget;
class FileExploreWidget;

class MainWindow : public QMainWindow

{
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void switchToRegister();
  void switchToLogin();
  void switchToExplore();
  void reigsterSuccessHandle();

 public slots:
  void showPrompt(const QString &msg);

 private:
  void initUI();
  void connectSignalSlots();

  QStackedWidget *stackedWidget;
  LoginWidget *loginWidget;
  RegisterWidget *registerWidget;
  FileExploreWidget *fileExploreWidget;

  QtMaterialSnackbar *snackBar;
};

#endif  // MAINWINDOW_H
