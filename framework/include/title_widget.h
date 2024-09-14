
#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QHBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <QMovie>
#include <QPushButton>
#include <QSignalMapper>
#include <QTextCodec>
#include <QVBoxLayout>
#include <QWidget>

#include "push_button.h"
#include "tool_button.h"

class TitleWidget : public QWidget {
  Q_OBJECT
 public:
  explicit TitleWidget(QWidget *parent = 0);
  void translateLanguage();
  void setTitle(QString titleInfo);

 signals:

  void showSkin();
  void showMaxWidget();
  void showMin();
  void showMainMenu();
  void closeWidget();

 private:
  QPoint press_point;  // 鼠标按下去的点
  bool is_move;

  QLabel *version_title;         // 标题
  PushButton *max_button;        // 最大化
  PushButton *skin_button;       // 换肤, 未使用
  PushButton *main_menu_button;  // 主菜单, 未使用
  PushButton *min_button;        // 最小化
  PushButton *feedback_button;   // 反馈意见， 未使用
  PushButton *close_button;      // 关闭

  QLabel *safe_360_label;  //
  QLabel *safe_label;      //

  QList<ToolButton *> button_list;
};

#endif  // TITLEWIDGET_H
