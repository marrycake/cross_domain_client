
#include "mainwindow.h"

#include <QApplication>
#include "constans.h"
#include <QLocale>
#include <QTranslator>
#include "fileHelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    FileHelper::mkdirIfNotExist(CONF_DIR);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages)
    {
        const QString baseName = "cross_domain_client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName))
        {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
