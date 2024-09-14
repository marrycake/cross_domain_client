#ifndef ADDFOLDERDIALOG_H
#define ADDFOLDERDIALOG_H
#include <qjsonobject.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>

#include <QComboBox>
#include <QDialog>

class AddFolderDialog : public QDialog {
  Q_OBJECT
 public:
  explicit AddFolderDialog(QWidget *parent = nullptr);
  void setParamters(uint64_t currentDomainId, uint64_t currentDirId,
                    const QString &currentDirName);
  void clearFielders();

 signals:
  void showPrompt(const QString &prompts);
  void addFolderSuccess();

 private slots:
  void doAddFolder();

 private:
  void initUI();
  void connectSignalSlots();
  void parseJson(const QJsonObject &json);

  QLineEdit *folderNameEdit;
  QComboBox *folderPrivilegeField;

  QPushButton *okBtn;
  QPushButton *cancelBtn;

  uint64_t currentDomainId;
  uint64_t currentDirId;
  QString currentDirName;
};

#endif  // ADDFOLDERDIALOG_H