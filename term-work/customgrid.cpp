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

            // Создаем кнопку с "?" для противника
            auto button = new CustomButton(0, row, col, "?");
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            button->setMinimumSize(50, 50);

            buttons.push_back(button);
            layout->addWidget(button, row, col);

            connect(button, &QPushButton::clicked, [this, row, col]() {
                buttonClicked(row, col);
            });
        }
    } else {
        // Поле игрока
        std::vector<int> values(rows * cols);

        // Заполняем вектор случайными числами от 1 до 100
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(1, 1000);
        std::generate(values.begin(), values.end(), [&]() { return dist(gen); });

        // Создаём кнопки с числами
        for (unsigned i = 0; i < rows * cols; ++i) {
            unsigned row = i / cols;
            unsigned col = i % cols;

            // Создаём кнопку с числом
            auto button = new CustomButton(values[i], row, col, QString::number(values[i]));
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
    // Получаем строку и столбец кнопки
    int row = button->getRow();
    int col = button->getCol();

    // Если кнопка уже выбрана, снимаем выделение
    if (selectedButtons.contains(button)) {
        button->setStyleSheet(""); // Сбрасываем стиль
        selectedButtons.remove(button);
    } else {
        // Проверяем, не соседствует ли эта кнопка с уже выбранными
        bool canSelect = true;

        // Проверяем соседей по горизонтали и вертикали
        for (auto *selectedButton : selectedButtons) {
            int selectedRow = selectedButton->getRow();
            int selectedCol = selectedButton->getCol();

            // Если сосед по горизонтали или вертикали
            if ((std::abs(selectedRow - row) == 1 && selectedCol == col) ||
                (std::abs(selectedCol - col) == 1 && selectedRow == row)) {
                canSelect = false;
                break; // Если нашли соседей, можно не продолжать проверку
            }
        }

        // Если соседей нет, можно выделить кнопку
        if (canSelect && selectedButtons.size() < 9) {
            button->setStyleSheet("background-color: green;");
            selectedButtons.insert(button);
        }
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
    for (auto *button : selectedButtons) {
        button->setStyleSheet(""); // Убираем цвет
        button->setChecked(false); // Отжимаем кнопку
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


