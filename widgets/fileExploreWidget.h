#ifndef FILEEXPLOREWIDGET_H
#define FILEEXPLOREWIDGET_H

#include <QWidget>
#include "operateBarWidget.h"
#include "exploreBarWidget.h"

class FileExploreWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileExploreWidget(QWidget *parent = nullptr);
    ~FileExploreWidget();

private:
    void initUI();

    OperateBarWidget *operateBar;
    ExploreBarWidget *exploreBar;
};

#endif // FILEEXPLOREWIDGET_H