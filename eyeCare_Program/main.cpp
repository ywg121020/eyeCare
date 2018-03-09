/**
  ******************************************************************************
  * 文件名称：main
  * 作者：无木成林
  * 版本: V1.0
  * 编写日期: 2017/5/10
  * 功能: 程序入口
  ******************************************************************************
  * 说明:
  *
  ******************************************************************************
**/


#include "mainwindow.h"
#include <QApplication>
#include "lockdialog.h"
#include <QSettings>
#include <QDebug>
#include <QSharedMemory>

int main(int argc, char *argv[])
{
    /*  只能运行单进程 */
    /*  同时又导致系统不能复位 */
    /*QSharedMemory shared("0");
    if (shared.attach())
    {
       return 0;
    }
    shared.create(1);*/

    QApplication a(argc, argv);
    MainWindow w;
    w.hide();
    return a.exec();
}
