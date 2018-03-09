#ifndef LOCKDIALOG_H
#define LOCKDIALOG_H

#include <QDialog>
#include <QTimer>
#include <QGraphicsEffect>
#include <QGraphicsOpacityEffect>
#include <QGraphicsBlurEffect>

namespace Ui {
class LockDialog;
}

class LockDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LockDialog(QWidget *parent = 0);
    ~LockDialog();
signals:
    void wait_flag();

private slots:
    void changeskin();
    void waitslot();
    void show_image();
private:
    QPixmap BKimage;

    Ui::LockDialog *ui;
    QTimer *unlockQTimer;
    int    unlocktime;
    QString lock_skin_;
    QGraphicsBlurEffect *blurEffect;
};

#endif // LOCKDIALOG_H
