#include "customgrid.h"
#include <random>
#include <vector>
#include <algorithm>

CustomGrid::CustomGrid(bool enemyGrid, int rows, int cols, QWidget *parent)
    : QWidget(parent), rows(rows), cols(cols), enemyGrid(enemyGrid) {
    layout = new QGridLayout(this);
    setLayout(layout);
    createButtons();
}

void CustomGrid::createButtons() {
    if (enemyGrid) {
        // Поле противника
        for (unsigned i = 0; i < rows * cols; ++i) {
            unsigned row = i / cols;
            unsigned col = i % cols;

            // Создаем кнопку с неизвестным значением для противника
            auto button = new CustomButton(0, row, col, "?");
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(50, 50);

            buttons.push_back(button);
            layout->addWidget(button, row, col);


        }
    } else {
        // Поле игрока
        // Поле игрока (по умолчанию нули)
        for (unsigned i = 0; i < rows * cols; ++i) {
            unsigned row = i / cols;
            unsigned col = i % cols;

            // Создаём кнопку с "0"
            auto button = new CustomButton(0, row, col, "0");
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(50, 50);

            buttons.push_back(button);
            layout->addWidget(button, row, col);

            // Подключаем сигнал нажатия для выбора/отмены выбора кнопки
            connect(button, &QPushButton::clicked, [this, button]() {
                toggleButtonSelection(button);
            });
        }
    }
}

void CustomGrid::toggleButtonSelection(CustomButton *button) {
    int row = button->getRow();
    int col = button->getCol();

    if(!enemyGrid){
        if (selectedButtons.contains(button)) {
            // Если кнопка уже выбрана, отменяем выбор
            int removedOrder = button->getValue();
            button->setValue(0);
            button->setText("0");
            button->setStyleSheet(""); // Сброс стиля
            selectedButtons.remove(button);

            // Обновляем порядковые номера оставшихся кнопок
            for (auto *selectedButton : selectedButtons) {
                int currentOrder = selectedButton->getValue();
                if (currentOrder > removedOrder) {
                    selectedButton->setValue(currentOrder - 1);
                    selectedButton->setText(QString::number(currentOrder - 1));
                }
            }
        } else if (selectedButtons.size() < 9) {
            // Проверяем соседство с уже выбранными кнопками
            bool canSelect = true;
            for (auto *selectedButton : selectedButtons) {
                int selectedRow = selectedButton->getRow();
                int selectedCol = selectedButton->getCol();

                // Проверяем, не является ли кнопка смежной по вертикали или горизонтали
                if ((std::abs(selectedRow - row) == 1 && selectedCol == col) ||
                    (std::abs(selectedCol - col) == 1 && selectedRow == row)) {
                    canSelect = false;
                    break; // Нельзя выбирать смежные по вертикали или горизонтали
                }
            }

            // Если можно выбрать кнопку
            if (canSelect) {
                int newOrder = selectedButtons.size() + 1;
                button->setValue(newOrder);
                button->setText(QString::number(newOrder));
                button->setStyleSheet("background-color: green;"); // Зелёный цвет для выбора
                selectedButtons.insert(button);
            }
        }
    } else {
        button->setText(QString::number(button->getValue()));

        (button->getValue() == 0)
            ? (button->setStyleSheet("background-color: red;"))
            : (button->setStyleSheet("background-color: green;"));
        // Эмитируем сигнал
        emit messageToSend(button);
    }

    // Генерируем сигнал о изменении выбора
    emit selectionChanged();
}

bool CustomGrid::hasSelection() const {
    return !selectedButtons.empty(); // Есть ли выбранные кнопки
}

void CustomGrid::buttonClicked(int row, int col) {
    // Здесь можно обрабатывать нажатия, если нужно
}

QVector<QPair<int, QPoint>> CustomGrid::getSelectedButtonsData() const {
    QVector<QPair<int, QPoint>> result;

    // Проходим по всем выбранным кнопкам
    for (auto *button : selectedButtons) {
        int value = button->getValue(); // Предполагается, что CustomButton хранит значение
        QPoint coordinates(button->getRow(), button->getCol());
        result.append(qMakePair(value, coordinates));
    }

    return result;
}

void CustomGrid::resetSelection() {
    // Сбрасываем выбор всех кнопок
    for (auto *button : buttons) {
        button->setStyleSheet("");   // Сбрасываем стиль
        button->setChecked(false);   // Сбрасываем состояние нажатия
        button->setValue(0);         // Возвращаем значение кнопки к 0
        button->setText("0");        // Возвращаем текст кнопки к "0"
    }

    // Очищаем список выбранных кнопок
    selectedButtons.clear();

    // Генерируем сигнал о изменении выбора
    emit selectionChanged();
}


CustomButton* CustomGrid::getButtonAt(int row, int col) {
    for (CustomButton* button : buttons) {
        if (button->getRow() == row && button->getCol() == col) {
            return button;
        }
    }
    return nullptr;  // Если кнопка не найдена
}

void CustomGrid::updateEnemyGrid(const QVector<QVector<int>>& fieldData) {
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            CustomButton *button = getButtonAt(row, col);
            if (button) {
                int value = fieldData[row][col];
                button->setValue(value);
                button->setButtonStyle();  // Обновляем стиль кнопки в зависимости от значения
                button->setText(value == 0 ? "0" : QString::number(value));  // Показываем текст
            }
        }
    }
}

