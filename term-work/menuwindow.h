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
#include <QMessageBox>

class MenuWindow : public QWidget {
    Q_OBJECT
public:
    MenuWindow(QWidget *parent = nullptr);
private:
    QLineEdit *fieldSizeInput;

    QLineEdit *gameNameInput;

    QLineEdit *ipInput;

    QLineEdit *portInput;

    QLineEdit *niknameInput;


};

#endif // MENUWINDOW_H
