#include "fileExploreWidget.h"
#include <QVBoxLayout>

FileExploreWidget::FileExploreWidget(QWidget *parent) : QWidget(parent)
{
    initUI();
}

FileExploreWidget::~FileExploreWidget()
{
}

void FileExploreWidget::initUI()
{
    OperateBarWidget *operateBar = new OperateBarWidget(this);
    ExploreBarWidget *exploreBar = new ExploreBarWidget(this);
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    vLayout->addWidget(operateBar);
    vLayout->addWidget(exploreBar);
    this->setLayout(vLayout);
}