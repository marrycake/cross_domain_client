#include "system_tray.h"

SystemTray::SystemTray(QWidget *parent)
	: QSystemTrayIcon(parent)
{
    this->createAction();
	this->translateLanguage();
}

SystemTray::~SystemTray()
{

}

void SystemTray::translateLanguage()
{

    this->setToolTip(tr("open main view when click"));

}

void SystemTray::createAction()
{
    this->setIcon(QIcon(":/img/logo"));

}
