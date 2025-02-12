﻿#include "tool_button.h"

ToolButton::ToolButton(QString pic_name, QColor textColor,
                       QColor backgroundColor, QWidget *parent)
    : QToolButton(parent) {
  //
  _textColor = textColor;
  _backgroundColor = backgroundColor;
  QPalette text_palette = palette();
  text_palette.setColor(QPalette::ButtonText, _textColor);
  setPalette(text_palette);

  QFont &text_font = const_cast<QFont &>(font());
  text_font.setWeight(QFont::Bold);

  setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

  QPixmap pixmap(pic_name);
  setIcon(pixmap);
  setIconSize(pixmap.size());

  setFixedSize(pixmap.width() + 25, pixmap.height() + 28);
  setAutoRaise(true);
  setObjectName("transparentToolButton");

  mouse_over = false;
  mouse_press = false;
}

ToolButton::~ToolButton() {}

void ToolButton::enterEvent(QEvent *) { mouse_over = true; }

void ToolButton::leaveEvent(QEvent *) { mouse_over = false; }

void ToolButton::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::LeftButton) {
    emit clicked();
  }
}

void ToolButton::setMousePress(bool mouse_press) {
  this->mouse_press = mouse_press;
  update();
}

void ToolButton::paintEvent(QPaintEvent *event) {
  if (mouse_over) {
    painterInfo(0, 100, 150);
  } else {
    if (mouse_press) {
      painterInfo(0, 100, 150);
    }
  }

  QToolButton::paintEvent(event);
}

void ToolButton::painterInfo(int top_color, int middle_color,
                             int bottom_color) {
  QPainter painter(this);
  QPen pen(Qt::NoBrush, 1);
  painter.setPen(pen);
  QLinearGradient linear(rect().topLeft(), rect().bottomLeft());
  linear.setColorAt(0, QColor(_backgroundColor.red(), _backgroundColor.green(),
                              _backgroundColor.blue(), top_color));
  linear.setColorAt(0.5,
                    QColor(_backgroundColor.red(), _backgroundColor.green(),
                           _backgroundColor.blue(), middle_color));
  linear.setColorAt(1, QColor(_backgroundColor.red(), _backgroundColor.green(),
                              _backgroundColor.blue(), bottom_color));
  painter.setBrush(linear);
  painter.drawRect(rect());
}
