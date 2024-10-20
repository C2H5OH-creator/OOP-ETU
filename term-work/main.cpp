#include "menuwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MenuWindow menuWindow;
    menuWindow.resize(400, 400);
    menuWindow.show();
    return a.exec();
}
