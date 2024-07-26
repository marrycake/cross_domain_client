#ifndef MESSAGEBOXDIALOG_H
#define MESSAGEBOXDIALOG_H

#include <QLabel>

#include "qtmaterialdialog.h"
#include "qtmaterialflatbutton.h"

class MessageBoxDialog : public QtMaterialDialog {
 public:
  explicit MessageBoxDialog(const QString &title, const QString &message,
                            QWidget *parent = nullptr);

 private:
  QLabel *messageLabel;
  QtMaterialFlatButton *okButton;
};

#endif  // MESSAGEBOXDIALOG_H