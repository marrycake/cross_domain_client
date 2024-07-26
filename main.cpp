
#include <QApplication>
#include <QDir>
#include <QLocale>
#include <QTranslator>

#include "clientconfig.h"
#include "constans.h"
#include "fileHelper.h"
#include "mainwindow.h"

// #include "clientconfig.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  FileHelper::mkdirIfNotExist(CONF_DIR);
  QString confPath = CONF_DIR + QDir::separator() + APP_CONF_PATH;
  ClientConfig::getInstance().setConfPath(confPath.toStdString());
  if (!FileHelper::checkFileExistence(confPath)) {
    ClientConfig::getInstance().dump();
  }
  ClientConfig::getInstance().load();

  QTranslator translator;
  const QStringList uiLanguages = QLocale::system().uiLanguages();
  for (const QString &locale : uiLanguages) {
    const QString baseName = "cross_domain_client_" + QLocale(locale).name();
    if (translator.load(":/i18n/" + baseName)) {
      a.installTranslator(&translator);
      break;
    }
  }
  MainWindow w;
  w.show();
  return a.exec();
}
