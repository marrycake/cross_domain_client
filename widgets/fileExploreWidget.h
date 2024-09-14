#ifndef FILEEXPLOREWIDGET_H
#define FILEEXPLOREWIDGET_H

#include <qjsonobject.h>
#include <qlabel.h>
#include <qobjectdefs.h>

#include <QWidget>
#include <cstdint>
#include <memory>
#include <stack>

#include "addFolderDialog.h"
#include "exploreBarWidget.h"
#include "operateBarWidget.h"
#include "uploadFileDialog.h"

class FileExploreWidget : public QWidget {
  Q_OBJECT
 public:
  explicit FileExploreWidget(QWidget *parent = nullptr);
  ~FileExploreWidget();

 signals:
  void showPrompt(const QString &msg);

 public slots:
  void goHome();

 private slots:
  void goBack();
  void refresh();
  void upload();
  void onItemClickHandle(uint32_t n);
  void downloadFileById(uint64_t fileId);

 private:
  void initUI();
  void connectSignalSlots();
  void loadDomains();
  void analyzeJson(const QJsonObject &json);
  void analyzeFileItemsJson(const QJsonObject &json,
                            const std::unique_ptr<FileItemModel> &newModel);
  void loadFIlesUnderDomainFolder(uint64_t domainId, uint64_t folderId);

  OperateBarWidget *operateBar;
  ExploreBarWidget *exploreBar;

  QLabel *currentDirLabel;
  QLabel *currentDomainLabel;

  AddFolderDialog *addFolderDialog;
  UploadFileDialog *uploadFileDialog;
  std::stack<std::unique_ptr<FileItemModel>> modelStack;

  uint64_t localDomainId;
};

#endif  // FILEEXPLOREWIDGET_H