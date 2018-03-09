#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "basicwidget.h"
#include <QWidget>
#include <QTime>
#include "lockdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public BasicWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void change();

private slots:
      void lockshow();
      void windowshow();
      void use_softwareslot();
      void start_upslot();
      void lock_versionslot();
      void lock_skinslot();
      void lock_restslot();
      void lock_timeslot();
      void windowhide();
      void restslot();
      void openfile();
      void showmin();
      void waitslot();
private:
    Ui::MainWindow *ui;
    QTimer *locktime;
    QTimer *resttime;
    QString styleSheet;
    LockDialog *dialog;
    QPixmap onPixmap;
    QPixmap offPixmap;


    int     current_time;
    int     current_resttime;
    int     lock_time_ing;
    int     lock_rest_ing ;
    QString use_software;
    QString start_up;
    QString lock_version;
    QString last_lock_version;
    QString lock_skin;
    QString lock_time;
    QString lock_rest;
    QString file_path;

};

#endif // MAINWINDOW_H
