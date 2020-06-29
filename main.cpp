#include "widgetmain.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetMain w;
    w.initialize();
    w.show();

    return a.exec();
}
