#include "alarmgui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlarmGUI w;
    w.show();
    return a.exec();
}
