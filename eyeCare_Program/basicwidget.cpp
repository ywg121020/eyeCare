/**
  ******************************************************************************
  * 文件名称：basicwidget
  * 作者：无木成林
  * 版本: V1.0
  * 编写日期: 2017/5/10
  * 功能: 基础窗口桌面
  ******************************************************************************
  * 说明:
  * 生成可移动窗口
  ******************************************************************************
**/
#include "basicwidget.h"
#include <QDebug>

BasicWidget::BasicWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowIcon(QIcon(":/scource/main.ico"));
    this->setMouseTracking(true);


    setAttribute(Qt::WA_TranslucentBackground);
    mouse_press = false;
}

BasicWidget::~BasicWidget()
{

}

void BasicWidget::paintEvent(QPaintEvent *)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    /*  黑影在所键窗口的 最边沿10个像素点  */
    path.addRect(10, 10, this->width()-10, this->height()-10);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QColor color(0, 0, 0, 50);
    for(int i=0; i<10; i++)
    {
        QPainterPath path;
        path.setFillRule(Qt::WindingFill);
        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
        color.setAlpha(150 - qSqrt(i)*50);
        painter.setPen(color);
        painter.drawPath(path);
    }

}

void BasicWidget::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }
    //窗口移动距离
    move_distance = event->globalPos() - pos();


}

void BasicWidget::mouseReleaseEvent(QMouseEvent *)
{
     mouse_press = false;
     mouseState = MOUSE_STATE_REALESS;
     //qDebug()<<"鼠标释放";
}

void BasicWidget::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_distance);
    }
    mouseMovePosition_X = event->x();
    mouseMovePosition_Y = event->y();
    //qDebug()<<"鼠标被按下";
    //qDebug()<<"当前鼠标x = %d"<<mouseMovePosition_X;
    //qDebug()<<"当前鼠标y = %d"<<mousePosition_X;
}
