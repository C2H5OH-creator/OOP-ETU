#include "gamewindow.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

GameWindow::GameWindow(const QString &title,
                       int fieldSize,
                       quint16 sendPort,
                       quint16 receivePort,
                       QWidget *parent)
    : QWidget(parent), playerGrid(nullptr), opponentGrid(nullptr), readyButton(nullptr) {
    setWindowTitle(title);

    communicator = new UDPCommunicator("127.0.0.1",receivePort,sendPort, this);
    communicator->setGameWindow(this);

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

    //opponentGrid->setUPD(communicator);

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
    connect(playerGrid, &CustomGrid::selectionChanged,
                    this, &GameWindow::updateReadyButtonState);

    // Подключение обработки полученного сообщения
    connect(communicator, SIGNAL(messageReceived(QJsonObject)),
            this, SLOT(onMessageReceived(QJsonObject)));

    connect(opponentGrid, &CustomGrid::messageToSend,
            this, &GameWindow::ButtonChecked);

}

void GameWindow::onReadyClicked() {
    communicator->sendMessage(communicator->createFieldReadyMessage(playerGrid));
}

void GameWindow::ButtonChecked(CustomButton* button) {
    communicator->sendMessage(communicator->createFieldMessage(++turn, button));
}

void GameWindow::onResetClicked() {
    // Сбрасываем поле игрока
    playerGrid->resetSelection();
}

void GameWindow::updateReadyButtonState() {
    // Активируем кнопку "Готов", если выбрана хотя бы одна кнопка
    readyButton->setEnabled(playerGrid->hasSelection());
}

void GameWindow::onMessageReceived(const QJsonObject& message) {
    int type = message.value("type").toInt();

    switch (type) {
    case 0:
        qDebug() << "Field ready message received in" << this->windowTitle();
        communicator->parseFieldReadyMessage(message);
        break;
    case 1:
        qDebug() << "Field message received in" << this->windowTitle();
        communicator->parseFieldMessage(message);
        break;
    case 2:
        qDebug() << "Win message received in" << this->windowTitle();
        communicator->parseWinMessage(message);
        break;
    default:
        qWarning() << "Unknown message type in" << this->windowTitle();
    }
}
