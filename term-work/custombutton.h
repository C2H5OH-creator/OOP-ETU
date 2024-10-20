#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>

class CustomButton: public QPushButton
{
    Q_OBJECT
public:
    CustomButton(unsigned value, unsigned row, unsigned col, const QString &text, QWidget *parent = nullptr)
        :  QPushButton(text, parent), value(value), row(row), col(col) {
        // Настройка кнопки
        connect(this, &QPushButton::clicked, this, &CustomButton::handleClick);
    }

    // Методы для получения индексов кнопки
    int getRow() const { return row; }
    int getCol() const { return col; }

signals:
    // Этот сигнал будет использоваться, чтобы передать информацию о клике
    void buttonClicked(int row, int col);

private slots:
    void handleClick() {
        // Логика обработки нажатия на кнопку
        emit buttonClicked(row, col);
    }

private:
    unsigned value = 0;
    unsigned row; // Индекс строки кнопки
    unsigned col; // Индекс столбца кнопки  CustomButton();
};

#endif // CUSTOMBUTTON_H
