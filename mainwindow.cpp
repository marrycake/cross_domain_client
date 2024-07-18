
#include "mainwindow.h"
#include "widgets/loginwidget.h"
#include <QVBoxLayout>
#include <QStackedWidget>
#include "widgets/registerWidget.h"
#include "widgets/fileExploreWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(1000, 650);

    QStackedWidget *stackedWidget = new QStackedWidget(this);
    LoginWidget *loginWidget = new LoginWidget(this);
    RegisterWidget *registerWidget = new RegisterWidget(this);
    FileExploreWidget *fileExploreWidget = new FileExploreWidget(this);

    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(registerWidget);
    stackedWidget->addWidget(fileExploreWidget);

    // stackedWidget->setCurrentWidget(registerWidget);
    stackedWidget->setCurrentIndex(0);
    setCentralWidget(stackedWidget);
}

MainWindow::~MainWindow()
{
}
