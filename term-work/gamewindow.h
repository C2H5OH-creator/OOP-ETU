#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>

#include "customgrid.h"

class GameWindow : public QWidget {
        Q_OBJECT
public:
        GameWindow(int size, QWidget *parent = nullptr);

};

#endif // GAMEWINDOW_H
