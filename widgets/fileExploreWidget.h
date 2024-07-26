#ifndef FILEEXPLOREWIDGET_H
#define FILEEXPLOREWIDGET_H

#include <QWidget>
#include <cstdint>
#include <memory>

#include "exploreBarWidget.h"
#include "operateBarWidget.h"

class FileExploreWidget : public QWidget {
  Q_OBJECT
 public:
  explicit FileExploreWidget(QWidget *parent = nullptr);
  ~FileExploreWidget();

 private slots:
  void goBack();
  void goHome();
  void refresh();
  void upload();

 private:
  void initUI();
  void connectSignalSlots();

  OperateBarWidget *operateBar;
  ExploreBarWidget *exploreBar;

  std::string currentDir;
  std::string currentDomain;

  uint64_t currentDirId;
  uint64_t currentDomainId;

  std::shared_ptr<FileItemModel> currentModel;
};

#endif  // FILEEXPLOREWIDGET_H