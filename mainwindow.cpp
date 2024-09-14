#include "mainwindow.h"

#include <qboxlayout.h>
#include <qdebug.h>
#include <qnamespace.h>

#include <QStackedWidget>
#include <QVBoxLayout>
#include <utility>

#include "common.h"
#include "qtmaterialsnackbar.h"
#include "util.h"
#include "widgets/fileExploreWidget.h"
#include "widgets/loginwidget.h"
#include "widgets/registerWidget.h"

MainWindow::MainWindow(QWidget *parent) : DropShadowWidget(parent) {
  initUI();
  connectSignalSlots();
}

MainWindow::~MainWindow() {}

void MainWindow::initUI() {
  setWindowFlag(Qt::FramelessWindowHint);

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

  titleWidget = new TitleWidget(this);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);
  mainLayout->addWidget(titleWidget);
  mainLayout->addWidget(stackedWidget);

  this->setLayout(mainLayout);

  skin_name = Util::getSkinName();

  this->changeSkin(DEFAULT_SKIN);
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

  connect(titleWidget, SIGNAL(closeWidget()), this, SLOT(close()));
  connect(titleWidget, SIGNAL(showMin()), this, SLOT(showMinimized()));
  connect(titleWidget, SIGNAL(showMaxWidget()), this, SLOT(showMaxOrNormal()));
}

void MainWindow::switchToLogin() { stackedWidget->setCurrentIndex(0); }

void MainWindow::switchToRegister() { stackedWidget->setCurrentIndex(1); }

void MainWindow::switchToExplore() {
  stackedWidget->setCurrentIndex(2);
  fileExploreWidget->goHome();
}

void MainWindow::showPrompt(const QString &msg) { snackBar->addMessage(msg); }

void MainWindow::reigsterSuccessHandle() {
  snackBar->addMessage(tr("register success"));
}

void MainWindow::changeSkin(QString skin_name) {
  this->skin_name = std::move(skin_name);
  update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
  DropShadowWidget::paintEvent(event);
  QPainter painter(this);
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::white);
  //   painter.drawPixmap(
  //       QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH,
  //             this->height() - 2 * SHADOW_WIDTH),
  //       QPixmap(skin_name));

  painter.drawPixmap(
      QRect(SHADOW_WIDTH, SHADOW_WIDTH, this->width() - 2 * SHADOW_WIDTH, 125),
      QPixmap(skin_name).scaled(this->width() - 2 * SHADOW_WIDTH, 125));
}

void MainWindow::showMaxOrNormal() {
  this->isMaximized() ? showNormal() : showMaximized();
}