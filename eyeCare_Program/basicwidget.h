#ifndef BASICWIDGET_H
#define BASICWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <qmath.h>
#include <QtGui>

#define MOUSE_STATE_PRESS   1
#define MOUSE_STATE_REALESS 2

class BasicWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BasicWidget(QWidget *parent = 0);
    ~BasicWidget();

private:

protected:
    int mousePosition_X;        //鼠标的位置
    int mousePosition_Y;
    int mouseMovePosition_X;        //鼠标的位置
    int mouseMovePosition_Y;
    int mouseState;             //鼠标状态
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    QPoint move_distance; //移动的距离
    bool   mouse_press; //按下鼠标左键
};

#endif // BASICWIDGET_H
