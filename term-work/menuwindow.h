#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include "gamewindow.h"

#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QLabel>
#include <QListView>
#include <QStringListModel>

class MenuWindow : public QWidget {
    Q_OBJECT
public:
    MenuWindow(QWidget *parent = nullptr);

};

#endif // MENUWINDOW_H
