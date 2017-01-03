#include "robot4.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    robot4 w;
    w.setWindowTitle("Robot 4 controller");
    w.show();

    return a.exec();
}
