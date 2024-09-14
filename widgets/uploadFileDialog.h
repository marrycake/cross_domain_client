#ifndef UPLOADFILEDIALOG_H
#define UPLOADFILEDIALOG_H

#include <qlineedit.h>
#include <qpushbutton.h>
#include <qwidget.h>

#include <QComboBox>
#include <QDialog>

class UploadFileDialog : public QDialog {
  Q_OBJECT
 public:
  explicit UploadFileDialog(QWidget *parent = nullptr);
  void setParamters(uint64_t currentDomainId, uint64_t currentDirId,
                    const QString &currentDirName);
  void clearFielders();

 signals:
  void showPrompt(const QString &prompts);
  void uploadFileSuccess();

 private slots:
  void doUpload();
  void selectFileSlot();

 private:
  void initUI();
  void connectSignalSlots();
  void parseJson(const QJsonObject &json);

  QLineEdit *fileToUploadField;
  QComboBox *filePriviligeField;

  QPushButton *okBtn;
  QPushButton *cancelBtn;
  QPushButton *selectFileBtn;

  uint64_t currentDomainId;
  uint64_t currentDirId;
  QString currentDirName;
};

#endif  // UPLOADFILEDIALOG_H