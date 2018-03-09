/**
  ******************************************************************************
  * lockdialog
  * 作者：无木成林
  * 版本: V1.0
  * 编写日期: 2017/5/10
  * 功能: 上锁界面
  ******************************************************************************
  * 说明:
  * 覆盖窗口，执行上锁
  ******************************************************************************
**/

#include "lockdialog.h"
#include "ui_lockdialog.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QFile>
#define blur_data 8
#define blur_time 600


extern QString Version ;
LockDialog::LockDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LockDialog)
{
    ui->setupUi(this);
    /*  显示很霸道，切换都切换不了 */
    //this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint|Qt::SubWindow);
    if(Version == "1"){
        this->setWindowFlags(Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint|Qt::SubWindow);
    }
    else{
        this->setWindowFlags(Qt::FramelessWindowHint);
    }
    this->move(0, 0);
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();

    this->setMinimumSize(screenRect.width(),screenRect.height());
    this->setMaximumSize(screenRect.width(),screenRect.height());

    connect(ui->closeBtn,SIGNAL(clicked()),this,SLOT(waitslot()));

    /*  unlockQTimer = new QTimer(this);
    connect(unlockQTimer,SIGNAL(timeout()),this,SLOT(endlock()));
    unlockQTimer->start(20000);
    unlocktime = 0;*/

    /*  ui->BKLabel->move(0, 0);
    QDesktopWidget *desktopWidge = QApplication::desktop();
    QRect screenRec = desktopWidge->screenGeometry();

    ui->BKLabel->setMinimumSize(screenRec.width(),screenRec.height());
    ui->BKLabel->setMaximumSize(screenRec.width(),screenRec.height());


    BKimage = QPixmap("D:/QT_PRO/2017.5.15/project/scource/images/BK1.png");
    ui->BKLabel->setPixmap(BKimage.scaled(QSize(screenRec.width(),screenRec.height())));
*/
}

LockDialog::~LockDialog()
{
    delete ui;
}
void LockDialog::waitslot(){
     emit wait_flag();
}

extern QString SkinPath;

void LockDialog::changeskin(){

    ui->BKLabel->move(0-5, -5);
    QDesktopWidget *desktopWidge = QApplication::desktop();
    QRect screenRec = desktopWidge->screenGeometry();

    ui->BKLabel->setMinimumSize(screenRec.width()+10,screenRec.height()+10);
    ui->BKLabel->setMaximumSize(screenRec.width()+10,screenRec.height()+10);

    if(Version == "1"){
        ui->closeBtn->hide();
        ui->remindLabel->setGeometry((screenRec.width()-360)/2,screenRec.height()/2-20,360,40);
        ui->remindLabel->setText("能解锁的话，记得告诉我");

    }
    else{
        ui->closeBtn->setGeometry(screenRec.width()-35,5,30,25);
        ui->remindLabel->setGeometry((screenRec.width()-360)/2,screenRec.height()/2-20,360,40);
        ui->remindLabel->setText("右上角，这次不等了- -");
    }

    BKimage = QPixmap(SkinPath);
    BKimage.scaled(QSize(screenRec.width(),screenRec.height()));
    ui->BKLabel->setPixmap(BKimage);
    ui->BKLabel->setScaledContents(true);

    unlockQTimer = new QTimer(this);
    connect(unlockQTimer,SIGNAL(timeout()), this, SLOT(show_image()));
    unlockQTimer->start(blur_time);
    blurEffect =new QGraphicsBlurEffect(ui->BKLabel);
    blurEffect->setBlurRadius(blur_data);
    ui->BKLabel->setGraphicsEffect(blurEffect);
}
void LockDialog::show_image()
{
   static int i = blur_data;
   i--;
   if(i>1){
        unlockQTimer->start(blur_time);
        blurEffect->setBlurRadius(i);
        ui->BKLabel->setGraphicsEffect(blurEffect);
   }
   else{
       blurEffect->setBlurRadius(0);
       ui->BKLabel->setGraphicsEffect(blurEffect);
       unlockQTimer->stop();
       i = blur_data;
   }
}

