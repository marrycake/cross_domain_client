
#ifndef SYSYTEMTRAY_H
#define SYSYTEMTRAY_H

#include <QWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QWidgetAction>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

class SystemTray : public QSystemTrayIcon
{
	Q_OBJECT

public:

	explicit SystemTray(QWidget *parent = 0);
	~SystemTray();
	void translateLanguage();


signals:
	void showWidget();

private:
    void createAction();

private:

	QMenu *tray_menu; //托盘菜单


};

#endif //SYSYTEMTRAY_H
