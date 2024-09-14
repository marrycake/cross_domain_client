#ifndef COMMON_H
#define COMMON_H

#include <QString>

#define APP_VER_STR "1.0.0"
#define APP_VER_NUM 0X010000

#define SHADOW_WIDTH 5
#define WINDOW_WIDTH 680
#define WINDOW_HEIGHT 372
#define WINDOW_START_X 0
#define WINDOW_START_Y 0
#define WINDOW_PAGE_COUNT 4
#define WINDOW_BUTTON_COUNT 4
#define WINDOW_PAGE_MOVE 20
#define WINDOW_ONEBUTTON_WIDTH 170

const QString SOFTWARE_NAME = "文件安全助手";
const QString STR_SOFTWARE_NAME_FAILER = "";
const QString STR_SOFTWARE_LOGO_SHOW = "为文件安全保驾护航";

#define DEFAULT_SKIN ":/skin/default"
#define IMG_LOGO ":/img/logo"

typedef enum { UI_EN, UI_ZH } LANGUAGE;

typedef enum { SAFE, SINA, RENREN } LOGIN;

// 自定义
typedef enum { NORMAL, ENTER, PRESS, NOSTATUS } ButtonStatus;

#endif  // COMMON_H