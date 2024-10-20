#include "gamewindow.h"
#include <QLabel>
#include <QHBoxLayout>

GameWindow::GameWindow(const QString &title, int fieldSize, QWidget *parent) : QWidget(parent) {
    setWindowTitle(title);

    // Основной вертикальный лэйаут для всего окна
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Создаем горизонтальный лэйаут для подписей и полей
    QHBoxLayout *fieldsLayout = new QHBoxLayout;

    // Подпись для поля игрока
    QLabel *playerLabel = new QLabel("Ваше поле");
    playerLabel->setAlignment(Qt::AlignCenter); // Центрируем текст
    fieldsLayout->addWidget(playerLabel, 0, Qt::AlignCenter);

    // Подпись для поля противника
    QLabel *opponentLabel = new QLabel("Поле противника");
    opponentLabel->setAlignment(Qt::AlignCenter); // Центрируем текст
    fieldsLayout->addWidget(opponentLabel, 0, Qt::AlignCenter);

    mainLayout->addLayout(fieldsLayout); // Добавляем лэйаут с подписями

    // Создание горизонтального лэйаута для полей
    QHBoxLayout *gridLayout = new QHBoxLayout;

    // Создание полей
    auto playerGrid = new CustomGrid(false,fieldSize, fieldSize);
    auto opponentGrid = new CustomGrid(true,fieldSize, fieldSize);

    // Добавляем сетки в горизонтальный лэйаут
    gridLayout->addWidget(playerGrid);
    gridLayout->addWidget(opponentGrid);

    mainLayout->addLayout(gridLayout); // Добавляем поля в основной лэйаут

    // Добавляем пустое место внизу для будущих кнопок
    QHBoxLayout *bottomLayout = new QHBoxLayout;

    // Здесь можно будет добавить будущие кнопки, например, кнопку "Start" или "Reset"
    // Пример:
    // QPushButton *startButton = new QPushButton("Start");
    // bottomLayout->addWidget(startButton);

    mainLayout->addLayout(bottomLayout); // Добавляем пустой лэйаут для кнопок

    setLayout(mainLayout);
}
