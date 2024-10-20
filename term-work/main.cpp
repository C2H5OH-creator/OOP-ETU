#include "gamewindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameWindow window(9); // Задайте размер поля
    window.resize(400, 400);
    window.show();
    return a.exec();
}
