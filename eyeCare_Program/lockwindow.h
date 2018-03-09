#ifndef LOCKWINDOW_H
#define LOCKWINDOW_H

#include "basicwidget.h"
#include <QWidget>

namespace Ui {
class LockWindow;
}

class LockWindow : public BasicWidget
{
    Q_OBJECT

public:
    explicit LockWindow(QWidget *parent = 0);
    ~LockWindow();

private:
    Ui::LockWindow *ui;
};

#endif // LOCKWINDOW_H
