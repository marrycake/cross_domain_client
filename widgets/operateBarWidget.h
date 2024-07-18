#ifndef OPERATEBARWIDGET_H
#define OPERATEBARWIDGET_H

#include <QWidget>
#include "qtmaterialiconbutton.h"

class OperateBarWidget : public QWidget
{
public:
    explicit OperateBarWidget(QWidget *parent = nullptr);
    ~OperateBarWidget();

private:
    void initUI();

    QtMaterialIconButton *backBtn;
    QtMaterialIconButton *homeBtn;
    QtMaterialIconButton *refreshBtn;
    QtMaterialIconButton *uploadBtn;
};

#endif // OPERATEBARWIDGET_H