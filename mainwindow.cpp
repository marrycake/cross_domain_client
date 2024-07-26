
#include "mainwindow.h"

#include <qdebug.h>

#include <QStackedWidget>
#include <QVBoxLayout>

#include "qtmaterialsnackbar.h"
#include "widgets/fileExploreWidget.h"
#include "widgets/loginwidget.h"
#include "widgets/registerWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  initUI();
  connectSignalSlots();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI() {
  setFixedSize(1000, 650);

  stackedWidget = new QStackedWidget(this);
  loginWidget = new LoginWidget(this);
  registerWidget = new RegisterWidget(this);
  fileExploreWidget = new FileExploreWidget(this);
  snackBar = new QtMaterialSnackbar(this);

  stackedWidget->addWidget(loginWidget);
  stackedWidget->addWidget(registerWidget);
  stackedWidget->addWidget(fileExploreWidget);

  stackedWidget->setCurrentIndex(0);
  setCentralWidget(stackedWidget);
}

void MainWindow::connectSignalSlots() {
  connect(loginWidget, &LoginWidget::toRegister, this,
          &MainWindow::switchToRegister);
  connect(loginWidget, &LoginWidget::loginSuccess, this,
          &MainWindow::switchToExplore);
  connect(loginWidget, &LoginWidget::showPrompt, this, &MainWindow::showPrompt);

  connect(registerWidget, &RegisterWidget::registerSuccess, this,
          &MainWindow::reigsterSuccessHandle);
  connect(registerWidget, &RegisterWidget::showPrompt, this,
          &MainWindow::showPrompt);
  connect(registerWidget, &RegisterWidget::switchToLogin, this,
          &MainWindow::switchToLogin);
}

void MainWindow::switchToLogin() { stackedWidget->setCurrentIndex(0); }

void MainWindow::switchToRegister() { stackedWidget->setCurrentIndex(1); }

void MainWindow::switchToExplore() { stackedWidget->setCurrentIndex(2); }

void MainWindow::showPrompt(const QString &msg) { snackBar->addMessage(msg); }

void MainWindow::reigsterSuccessHandle() {
  snackBar->addMessage(tr("register success"));
}