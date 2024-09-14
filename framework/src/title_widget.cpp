#include "title_widget.h"

#include <QMessageBox>

#include "common.h"

TitleWidget::TitleWidget(QWidget* parent) : QWidget(parent) {
  version_title = new QLabel();
  close_button = new PushButton();
  max_button = new PushButton();
  min_button = new PushButton();

  version_title->setObjectName("whiteLabel");

  max_button->setPicName(QString(":/sysButton/max"));
  min_button->setPicName(QString(":/sysButton/min"));
  close_button->setPicName(QString(":/sysButton/close"));

  connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));
  connect(max_button, SIGNAL(clicked()), this, SIGNAL(showMaxWidget()));
  connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));
  QHBoxLayout* title_layout = new QHBoxLayout();
  title_layout->addWidget(version_title, 0, Qt::AlignVCenter);
  title_layout->addStretch();
  title_layout->addWidget(min_button, 0, Qt::AlignTop);
  title_layout->addWidget(max_button, 0, Qt::AlignTop);
  title_layout->addWidget(close_button, 0, Qt::AlignTop);
  title_layout->setSpacing(0);
  title_layout->setContentsMargins(0, 0, 5, 0);
  version_title->setContentsMargins(15, 0, 0, 0);

  QHBoxLayout* button_layout = new QHBoxLayout();

  safe_360_label = new QLabel();
  safe_label = new QLabel();

  QVBoxLayout* safe_layout = new QVBoxLayout();
  safe_layout->addWidget(safe_360_label);
  safe_layout->addWidget(safe_label);
  safe_layout->setSpacing(5);
  safe_layout->setContentsMargins(0, 0, 0, 0);

  QLabel* logo_label = new QLabel();
  QPixmap pixmap(IMG_LOGO);
  logo_label->setPixmap(pixmap);
  logo_label->setFixedSize(pixmap.size());

  safe_360_label->setObjectName("whiteLabel");
  safe_label->setObjectName("whiteLabel");
  QFont safe_360_font = safe_360_label->font();
  safe_360_font.setPointSize(18);
  safe_360_font.setBold(true);
  safe_360_label->setFont(safe_360_font);

  safe_360_label->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
  safe_label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);

  button_layout->addStretch();
  button_layout->addLayout(safe_layout);
  button_layout->addWidget(logo_label);
  button_layout->setSpacing(10);
  button_layout->setContentsMargins(15, 0, 15, 0);

  QVBoxLayout* main_layout = new QVBoxLayout();
  main_layout->addLayout(title_layout);
  main_layout->addLayout(button_layout);
  main_layout->setSpacing(0);
  main_layout->setContentsMargins(0, 0, 0, 0);

  QFont systemFont("Times", 10, QFont::Bold);
  QFont courierNewFont("Microsoft YaHei", 13, QFont::Bold);
  version_title->setFont(courierNewFont);

  courierNewFont.setPointSize(18);
  safe_360_label->setFont(courierNewFont);

  courierNewFont.setPointSize(13);
  safe_label->setFont(courierNewFont);

  this->translateLanguage();

  setLayout(main_layout);
  setFixedHeight(110);
  is_move = false;
}

void TitleWidget::translateLanguage() {
  version_title->setText(tr("sofeware_name") + "-" + APP_VER_STR);
  close_button->setToolTip(tr("close"));

  safe_360_label->setText(tr("sofeware_name"));

  safe_label->setText(tr("software_descrption"));
}

void TitleWidget::setTitle(QString titleInfo) {}
