#include "logviewertwo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LogViewerTwo w;
    w.show();
    return a.exec();
}
