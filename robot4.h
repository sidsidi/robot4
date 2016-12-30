#ifndef ROBOT4_H
#define ROBOT4_H

#include <QMainWindow>

namespace Ui {
class robot4;
}

class robot4 : public QMainWindow
{
    Q_OBJECT

public:
    explicit robot4(QWidget *parent = 0);
    ~robot4();

private:
    Ui::robot4 *ui;
};

#endif // ROBOT4_H
