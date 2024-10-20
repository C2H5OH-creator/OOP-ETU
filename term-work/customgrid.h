#ifndef CUSTOMGRID_H
#define CUSTOMGRID_H

#include <vector>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>

#include "custombutton.h"

class CustomGrid : public QWidget
{
     Q_OBJECT
public:
     CustomGrid(bool enemyGrid ,int rows, int cols, QWidget *parent = nullptr);

    QString getButtonValue(int t_rows, int t_cols) const {
        if (t_rows <= rows && t_cols <= cols) {
            unsigned index = (rows * (--t_rows)) + (--t_cols);
            return buttons[index]->text();
        }
        return "";
    }

    // Метод для установки значения кнопки
    void setButtonValue(int t_rows, int t_cols, const QString &value) {
        if (t_rows <= rows && t_cols <= cols) {
            unsigned index = (rows * (--t_rows)) + (--t_cols);
            return buttons[index]->setText(value);
        }
    }

    // Метод для получения кнопки по индексу
    QPushButton* getButton(int t_rows, int t_cols) const {
        if (t_rows <= rows && t_cols <= cols) {
            unsigned index = (rows * (--t_rows)) + (--t_cols);
            return buttons[index];
        }
        return nullptr;
    }

private:
    unsigned rows = 0;
    unsigned cols = 0;
    QGridLayout *layout;
    bool enemyGrid = false;
    std::vector<CustomButton*> buttons;
    bool playerButtons[9];

    void createButtons();

private slots:
    void buttonClicked(int row, int col) {
        // Логика обработки нажатия на кнопку
        QMessageBox::information(nullptr, "Button Clicked",
                                 QString("Button at (%1, %2) clicked").arg(row).arg(col));
    }
};


#endif // CUSTOMGRID_H
