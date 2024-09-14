
#ifndef CLABEL_H
#define CLABEL_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QPainter>

class CLabel : public QWidget
{
    Q_OBJECT

public:

    explicit CLabel(QWidget *parent = 0);
    ~CLabel();

    void setPixmap(const QPixmap &);
    void setText(const QString &);
    void setMouseEnterFlag(bool);
    void setMousePressFlag(bool);

protected:

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

signals:

    void signalLabelPress(CLabel *);

private:

    void initVariable();
    void initSetupUi();
    void createFrame();
    void createWidget();
    void createLayout();
    void paintWidget(int, QPainter *);
    bool getMouseEnterFlag();
    bool getMousePressFlag();

    bool m_mouseEnterFlag;
    bool m_mousePressFlag;

    QHBoxLayout *m_pHLayout;
    QLabel *m_pLabelIcon;
    QLabel *m_pLabelText;
};

#endif //CLABEL_H
