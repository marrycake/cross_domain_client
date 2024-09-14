
#ifndef SHADOWWIDGET_H
#define SHADOWWIDGET_H

#include <QDialog>
#include <QPainter>

#include "common.h"

class ShadowWidget : public QDialog {
  Q_OBJECT

 public:
  explicit ShadowWidget(QWidget *parent = 0);
  ~ShadowWidget();

 protected:
  virtual void paintEvent(QPaintEvent *event);

 private:
  void drawWindowShadow(QPainter &painter);
};

#endif  // SHADOWWIDGET_H
