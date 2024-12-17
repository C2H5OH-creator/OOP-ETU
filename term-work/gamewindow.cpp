#include "gamewindow.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

GameWindow::GameWindow(const QString &title, int fieldSize, QWidget *parent)
    : QWidget(parent), playerGrid(nullptr), opponentGrid(nullptr), readyButton(nullptr) {
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
    playerGrid = new CustomGrid(false, fieldSize, fieldSize);
    opponentGrid = new CustomGrid(true, fieldSize, fieldSize);

    // Добавляем сетки в горизонтальный лэйаут
    gridLayout->addWidget(playerGrid);
    gridLayout->addWidget(opponentGrid);

    mainLayout->addLayout(gridLayout); // Добавляем поля в основной лэйаут

    // Добавляем лэйаут для кнопок внизу
    QHBoxLayout *bottomLayout = new QHBoxLayout;

    // Кнопка "Готов"
    readyButton = new QPushButton("Готов");
    readyButton->setEnabled(false); // По умолчанию неактивна
    connect(readyButton, &QPushButton::clicked, this, &GameWindow::onReadyClicked);
    bottomLayout->addWidget(readyButton);

    // Кнопка "Сброс"
    QPushButton *resetButton = new QPushButton("Сброс");
    connect(resetButton, &QPushButton::clicked, this, &GameWindow::onResetClicked);
    bottomLayout->addWidget(resetButton);

    mainLayout->addLayout(bottomLayout); // Добавляем кнопки в основной лэйаут

    setLayout(mainLayout);

    // Связываем сигнал изменения выбора с проверкой состояния кнопки "Готов"
    connect(playerGrid, &CustomGrid::selectionChanged, this, &GameWindow::updateReadyButtonState);
}

void GameWindow::onReadyClicked() {

    // Получаем данные с поля игрока
    QVector<QPair<int, QPoint>> selectedButtons = playerGrid->getSelectedButtonsData();

    // Формируем строку для вывода
    QString result = "Выбранные кнопки:\n";
    for (const auto &buttonData : selectedButtons) {
        result += QString("Число: %1, Координаты: (%2, %3)\n")
                      .arg(buttonData.first)
                      .arg(buttonData.second.x())
                      .arg(buttonData.second.y());
    }

    // Показать данные пользователю (можно заменить на отправку противнику)
    QMessageBox::information(this, "Готово", result);
}

void GameWindow::onResetClicked() {
    // Сбрасываем поле игрока
    playerGrid->resetSelection();
}

void GameWindow::updateReadyButtonState() {
    // Активируем кнопку "Готов", если выбрана хотя бы одна кнопка
    readyButton->setEnabled(playerGrid->hasSelection());
}
