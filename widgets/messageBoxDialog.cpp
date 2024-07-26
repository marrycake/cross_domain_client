#include "messageBoxDialog.h"

#include <QVBoxLayout>

MessageBoxDialog::MessageBoxDialog(const QString &title, const QString &message,
                                   QWidget *parent)
    : QtMaterialDialog(parent) {
  setWindowTitle(title);

  messageLabel = new QLabel(message, this);
  okButton = new QtMaterialFlatButton(tr("OK"), this);

  QVBoxLayout *layout = new QVBoxLayout(this);
  layout->addWidget(messageLabel);
  layout->addWidget(okButton);

  connect(okButton, &QPushButton::clicked, this, &MessageBoxDialog::hideDialog);

  setLayout(layout);
}