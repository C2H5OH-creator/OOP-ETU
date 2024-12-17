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
    int getValue() const { return value; }

    void setValue(int val) { value = val; }

    void setCheckedByEnemy() {checked = true;}

signals:
    // Этот сигнал будет использоваться, чтобы передать информацию о клике
    void buttonClicked(int row, int col);

private slots:
    void handleClick() {
        // Логика обработки нажатия на кнопку
        emit buttonClicked(row, col);
    }

private:
    int value = 0;
    int row; // Индекс строки кнопки
    int col; // Индекс столбца кнопки
    bool checked = false;
};

#endif // CUSTOMBUTTON_H
