#include "customgrid.h"
#include <random>
#include <vector>
#include <algorithm>

CustomGrid::CustomGrid(bool enemyGrid, int rows, int cols, QWidget *parent)
    : QWidget(parent), rows(rows), cols(cols), enemyGrid(enemyGrid) {
    layout = new QGridLayout(this); // Устанавливаем компоновку
    setLayout(layout);
    createButtons();
}

void CustomGrid::createButtons() {
    for (unsigned i = 0; i < rows + cols; i++) {
        if (enemyGrid){
            for (unsigned i = 0; i < rows * cols; ++i) {
                unsigned row = i / cols;
                unsigned col = i % cols;

                // Создаем кнопку с этим значением
                auto button = new CustomButton(0, row, col, "?");
                button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                 button->setMinimumSize(50, 50);
                buttons.push_back(button);
                layout->addWidget(button, row, col);

                // Подключаем сигнал нажатия на кнопку
                connect(button, &QPushButton::clicked, [this, row, col]() {
                    buttonClicked(row, col);
                });
            }
        }
        else{
            // Сначала создаем вектор, содержащий 9 чисел от 1 до 9 и оставшиеся нули
            std::vector<int> values(rows * cols, 0); // Все кнопки по умолчанию 0
            for (int i = 1; i <= 9; ++i) {
                values[i - 1] = i; // Задаем первые 9 элементов значениями от 1 до 9
            }

            // Перемешиваем значения
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(values.begin(), values.end(), g);

            // Создаем кнопки и размещаем их на сетке
            for (unsigned i = 0; i < rows * cols; ++i) {
                unsigned row = i / cols;
                unsigned col = i % cols;

                // Создаем кнопку с этим значением
                auto button = new CustomButton(values[i], row, col, QString::number(values[i]));
                button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                 button->setMinimumSize(50, 50);

                // Проверяем значение кнопки
                if (button->text() != "0") { // Если значение не 0
                    button->setStyleSheet("background-color: green;"); // Меняем цвет нажатой кнопки
                    button->setDisabled(true); // Отключаем кнопку, чтобы её нельзя было нажать снова
                }

                buttons.push_back(button);
                layout->addWidget(button, row, col);

                // Подключаем сигнал нажатия на кнопку
                connect(button, &QPushButton::clicked, [this, row, col]() {
                    buttonClicked(row, col);
                });
            }
        }

    }
}
