/**
  ******************************************************************************
  * 程序名称：mainwindow
  * 作者：无木成林
  * 版本: V1.0
  * 编写日期: 2017/5/10
  * 功能: 主功能实现及界面ui
  ******************************************************************************
  * 说明:
  * 实现
  ******************************************************************************
**/

#include "mainwindow.h"
#include "basicwidget.h"
#include "ui_mainwindow.h"
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDebug>
#include <QDialog>
#include "lockdialog.h"
#include <QDesktopServices>
#include <QDesktopWidget>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include "qtextstream.h"
#include <qstyle.h>
#include <qfiledialog.h>
#define TIME_NUM 60
#define USE_LOCK 0

/*  外部变量，保存图片地址的，暂时没有去做类数据传递   */
QString SkinPath;
QString Version ;
MainWindow::MainWindow(QWidget *parent) :
    BasicWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*  取当前显示器的分辨率  */
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    /*  每次初始化软件，都将软件置于显示器正中间   */
    this->move(screenRect.width()/2-this->width()/2, screenRect.height()/2-this->height()/2);

    /*  当前配置下只有任务管理器可以删 */
    //setWindowFlags(Qt::FramelessWindowHint |Qt::SubWindow);

    setWindowFlags(Qt::FramelessWindowHint );

    /*  创建一个系统图标    */
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    QMenu *trayIconMenu = new QMenu(this);
    /*  更改menu样式表，没达到预设效果，暂时不做处理    */
    //trayIconMenu->setStyleSheet(      "border: 1px solid black; background-color: #000000;opacity: 100;"
    //                                  "QMenu::item{color:: #fafafa;}"
    //                                  "QMenu::item:selected{color: #000000; background-color: #ffa02f;}");
    //trayIconMenu->setBaseSize(50,50);
    //trayIconMenu->setMinimumHeight(25);

    /*  添加托盘菜单项     */
    QIcon initIcon(QPixmap(":/images/init.ico"));
    QAction *init = new QAction(QObject::tr("  设置"), trayIconMenu);
    /*  设置设置按钮图片   */
    init->setIcon(initIcon);
    /*  将按钮添加进menu  */
    trayIconMenu->addAction(init); //显示

    /*  设置退出按钮图片   */
    QIcon quitIcon(QPixmap(":/images/esc.ico"));
    QAction *quit = new QAction(QObject::tr("  退出"), trayIconMenu);
    quit->setIcon(quitIcon);

    /*  将菜单添加进系统托盘  */
    trayIcon->setContextMenu(trayIconMenu);
    /*  系统托盘说明信息    */
    trayIcon->setToolTip("带你去看海角天涯");
    /*  系统托盘任务图标    */
    QIcon trayIconPic(QPixmap(":/main.ico"));
    trayIcon->setIcon(trayIconPic);
    trayIcon->show();

    /*  连接退出按钮信号与槽  */
    connect(init,SIGNAL(triggered()),this,SLOT(windowshow()));
    /*  连接设置按钮信号与槽  */
    connect(quit,SIGNAL(triggered()),this,SLOT(close()));

    /*  准备按钮图片  */
    onPixmap = QPixmap(":/images/Widget/on_key.png");
    offPixmap = QPixmap(":/images/Widget/off_key.png");

    /*  获取exe路径下的config.ini的路径*/
    QString filepath=QCoreApplication::applicationDirPath();
    file_path=filepath+"/config.ini";

    QSettings *configIniRead = new QSettings(file_path, QSettings::IniFormat);
    /*  将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型  */
    use_software = configIniRead->value("/use_software").toString();
    start_up = configIniRead->value("/start_up").toString();
    lock_version = configIniRead->value("/lock_version").toString();
    lock_skin = configIniRead->value("/lock_skin").toString();
    lock_time = configIniRead->value("/lock_time").toString();
    lock_rest = configIniRead->value("/lock_rest").toString();
    delete configIniRead;
    /*  保存当前图片地址    */
    SkinPath = lock_skin;
      //打印得到的结果
   /* qDebug() << use_software;
    qDebug() << start_up;
    qDebug() << lock_version;
    qDebug() << lock_skin;
    qDebug() << lock_time;
    qDebug() << lock_rest;*/



    /*  保存当前模式，如果模式切换的话，需要重启软件 */
    last_lock_version = lock_version;

    /*  进行按钮操作  ，如果按钮为开，则配置开的图片 */
    if(use_software == "1"){
         ui->use_softwareBtn->setIcon(onPixmap);
         ui->use_softwareBtn->setIconSize(QSize(onPixmap.physicalDpiX(),onPixmap.height()));
    }
    else{
          ui->use_softwareBtn->setIcon(offPixmap);
          ui->use_softwareBtn->setIconSize(QSize(offPixmap.physicalDpiX(),offPixmap.height()));
    }
    connect(ui->use_softwareBtn,SIGNAL(clicked()),this,SLOT(use_softwareslot()));

    QString application_name = QApplication::applicationName();
    QSettings *reg=new QSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run",
    QSettings::NativeFormat);
    QString strAppPath=QDir::toNativeSeparators(QCoreApplication::applicationFilePath());
    if(start_up == "1"){
         ui->start_upBtn->setIcon(onPixmap);
         ui->start_upBtn->setIconSize(QSize(onPixmap.physicalDpiX(),onPixmap.height()));
         reg->setValue(application_name,strAppPath);
    }
    else{
         ui->start_upBtn->setIcon(offPixmap);
         ui->start_upBtn->setIconSize(QSize(offPixmap.physicalDpiX(),offPixmap.height()));
         reg->remove(application_name);
    }
    connect(ui->start_upBtn,SIGNAL(clicked()),this,SLOT(start_upslot()));
    Version = lock_version;
     qDebug() << lock_version;
     qDebug() << Version;
    if(lock_version == "1"){
         ui->lock_versionBtn->setIcon(onPixmap);
         ui->lock_versionBtn->setIconSize(QSize(onPixmap.physicalDpiX(),onPixmap.height()));
         /*  当前配置下只有任务管理器可以删 */
         setWindowFlags(Qt::FramelessWindowHint |Qt::SubWindow);
         connect(ui->minBtn,SIGNAL(clicked()),this,SLOT(windowhide()));
    }
    else{
         ui->lock_versionBtn->setIcon(offPixmap);
         ui->lock_versionBtn->setIconSize(QSize(offPixmap.physicalDpiX(),offPixmap.height()));
         /* 可以退出    */
         setWindowFlags(Qt::FramelessWindowHint);
         /*  添加退出按钮进menu */
         trayIconMenu->addAction(quit);
         connect(ui->minBtn,SIGNAL(clicked()),this,SLOT(showmin()));
    }
    connect(ui->lock_versionBtn,SIGNAL(clicked()),this,SLOT(lock_versionslot()));

    /* 获取本地图片地址，只能是png格式，然后保存地址 */
    /* 在lockdialog中使用这个图片地址     */
    connect(ui->lockskinBtn,SIGNAL(clicked()),this,SLOT(lock_skinslot()));

    /*  时间间隔获取，时间由定时器1s提供，计算设定值，触发信号   */
    lock_time_ing = lock_time.toInt();
    locktime = new QTimer(this);
    connect(locktime,SIGNAL(timeout()), this, SLOT(lockshow()));
    locktime->start(1000);

    /* 休息时长定时器设置    */
    resttime = new QTimer(this);
    connect(resttime,SIGNAL(timeout()), this, SLOT(restslot()));
    resttime->stop();

    /*  休息时长获取  */
    lock_rest_ing = lock_rest.toInt();

    /*  两个text行的消息获取，一旦发生数据变化，就进行信号与槽的控制    */
    connect(ui->restLine,SIGNAL(textChanged(QString)),this,SLOT(lock_restslot()));
    connect(ui->timeLine,SIGNAL(textChanged(QString)),this,SLOT(lock_timeslot()));

    /*  ui中的两个显示本地数据    */
    ui->restLine->setText(lock_rest);
    ui->timeLine->setText(lock_time);

    /*  缩小和关闭都是隐藏函数     */
    connect(ui->closeBtn,SIGNAL(clicked()),this,SLOT(windowhide()));

    /*  换肤为打开本地文件，去找寻png格式的图片，然后保存  */
    connect(ui->lockskinBtn,SIGNAL(clicked()),this,SLOT(openfile()));
    current_time = 0 ;
    current_resttime = 0;

    /*  上锁屏保界面，又一个dialog全屏显示实现  */
    /*  信号与槽连接的是换图片 */
    dialog = new LockDialog ;
    dialog->hide();
    connect(this,SIGNAL(change()),dialog,SLOT(changeskin()));

    connect(dialog,SIGNAL(wait_flag()),this,SLOT(waitslot()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showmin()
{
    this->showMinimized();
    locktime->start();
}
void MainWindow::waitslot()
{
    current_resttime = lock_rest_ing*TIME_NUM + 1;
    resttime->start(1);
}

void MainWindow::openfile(){
    QString lock_skin = QFileDialog::getOpenFileName(this, tr("Open File..."),
    "", tr("Epub File(*.png)"));

    QSettings *configIniWrite = new QSettings(file_path, QSettings::IniFormat);
    configIniWrite->setValue("//lock_skin", lock_skin);
    //写入完成后删除指针
    delete configIniWrite;
    SkinPath = lock_skin;
    qDebug()<<SkinPath;
}

void MainWindow::restslot(){
    current_resttime++;
    resttime->start();
    if(current_resttime >= lock_rest_ing*TIME_NUM){
        resttime->stop();
        current_time = 0;
        dialog->hide();
        locktime->start(1000);
    }

}

void MainWindow::windowhide()
{

    if(last_lock_version != lock_version)
    {
        qApp->quit();
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
    }
    else{
        locktime->start();
        qDebug()<<"定时器开始";
        this->hide();
    }
}


void MainWindow::lock_restslot(){

    lock_rest_ing = ui->restLine->text().toInt();

    QSettings *configIniWrite = new QSettings(file_path, QSettings::IniFormat);
    configIniWrite->setValue("//lock_rest", QString::number(lock_rest_ing));
    delete configIniWrite;
}

void MainWindow::lock_timeslot(){

    lock_time_ing = ui->timeLine->text().toInt();
    QSettings *configIniWrite = new QSettings(file_path, QSettings::IniFormat);
    configIniWrite->setValue("//lock_time", QString::number(lock_time_ing));
    delete configIniWrite;
}

void MainWindow::lockshow()
{
    if( use_software == "1" )
    {
        current_time++;
        locktime->start();
        qDebug()<<"将要锁屏时间"<<current_time;
        qDebug()<<"计划锁屏时长"<<lock_time_ing;
        if(current_time >= lock_time_ing*TIME_NUM)
        {
             qDebug()<<"时间到了";
             locktime->stop();
             dialog->show();
             resttime->start(1000);
             current_resttime = 0;
             emit change();
        }
    }
}
void MainWindow::windowshow()
{
    /*  取当前显示器的分辨率  */
    QDesktopWidget *desktopWidget = QApplication::desktop();
    QRect screenRect = desktopWidget->screenGeometry();
    /*  每次初始化软件，都将软件置于显示器正中间   */
    this->move(screenRect.width()/2-this->width()/2, screenRect.height()/2-this->height()/2);

    this->raise();
    this->show();
    locktime->stop();
    qDebug()<<"定时器暂停";
}

void MainWindow::lock_skinslot()
{

}

void MainWindow::use_softwareslot()
{
    if(use_software == "1"){
        use_software = "0";
        ui->use_softwareBtn->setIcon(offPixmap);
        ui->use_softwareBtn->setIconSize(QSize(offPixmap.physicalDpiX(),offPixmap.height()));
    }
    else{
         use_software = "1";
         ui->use_softwareBtn->setIcon(onPixmap);
         ui->use_softwareBtn->setIconSize(QSize(onPixmap.physicalDpiX(),onPixmap.height()));
    }
    QSettings *configIniWrite = new QSettings(file_path, QSettings::IniFormat);
    configIniWrite->setValue("//use_software", use_software);
    delete configIniWrite;
}
void MainWindow::start_upslot()
{
    QSettings *reg=new QSettings("HKEY_LOCAL_MACHINE//SOFTWARE//Microsoft""//Windows//CurrentVersion//Run",
    QSettings::NativeFormat);
    QString application_name = QApplication::applicationName();

    if(start_up == "1"){
        start_up = "0";
        ui->start_upBtn->setIcon(offPixmap);
        ui->start_upBtn->setIconSize(QSize(offPixmap.physicalDpiX(),offPixmap.height()));
        reg->remove(application_name);
    }
    else{
         start_up = "1";
         ui->start_upBtn->setIcon(onPixmap);
         ui->start_upBtn->setIconSize(QSize(onPixmap.physicalDpiX(),onPixmap.height()));
         reg->setValue(application_name,QApplication::applicationFilePath());
    }
    QSettings *configIniWrite = new QSettings(file_path, QSettings::IniFormat);
    configIniWrite->setValue("//start_up", start_up);
    delete configIniWrite;
}

void MainWindow::lock_versionslot()
{

    if(lock_version == "1"){
        lock_version = "0";
        ui->lock_versionBtn->setIcon(offPixmap);
        ui->lock_versionBtn->setIconSize(QSize(offPixmap.physicalDpiX(),offPixmap.height()));
    }
    else{
         lock_version = "1";
         ui->lock_versionBtn->setIcon(onPixmap);
         ui->lock_versionBtn->setIconSize(QSize(onPixmap.physicalDpiX(),onPixmap.height()));
    }
    Version = lock_version;
    QSettings *configIniWrite = new QSettings(file_path, QSettings::IniFormat);
    configIniWrite->setValue("//lock_version", lock_version);
    delete configIniWrite;

}

