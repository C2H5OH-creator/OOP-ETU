#include "udpcommunicator.h"

#include <QDebug>

// Конструктор
UDPCommunicator::UDPCommunicator(const QString& ip, quint16 port, QObject* parent)
    : QObject(parent), remoteAddress_(QHostAddress(ip)), remotePort_(port) {
    // Создаем UDP-сокет
    udpSocket_.bind(QHostAddress::Any, port);

    // Подключаем слот для обработки полученных сообщений
    connect(&udpSocket_, &QUdpSocket::readyRead, this, &UDPCommunicator::processReceivedMessage);
}

// Метод для отправки сообщения
void UDPCommunicator::sendMessage(const QJsonObject& message) {
    // Преобразуем QJsonObject в QJsonDocument
    QJsonDocument doc(message);
    QByteArray datagram = doc.toJson();  // Сериализуем в JSON строку (байтовый массив)

    // Отправляем сообщение
    udpSocket_.writeDatagram(datagram, remoteAddress_, remotePort_);
    qDebug() << "Message sent:" << QString(doc.toJson(QJsonDocument::Indented));
}

// Метод для начала приема сообщений
void UDPCommunicator::startReceiving() {
    // Слушаем порты для получения сообщений
    udpSocket_.bind(QHostAddress::Any, remotePort_);
}

// Слот для обработки полученного сообщения
void UDPCommunicator::processReceivedMessage() {
    while (udpSocket_.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket_.pendingDatagramSize());
        udpSocket_.readDatagram(datagram.data(), datagram.size());

        // Преобразуем полученные данные в QJsonDocument
        QJsonDocument doc = QJsonDocument::fromJson(datagram);
        if (doc.isNull()) {
            qWarning() << "Invalid JSON received";
            return;
        }

        // Преобразуем QJsonDocument в QJsonObject
        QJsonObject message = doc.object();
        qDebug() << "Message received:" << QString(doc.toJson(QJsonDocument::Indented));

        // Обрабатываем сообщение
        int type = message.value("type").toInt();

        switch (type) {
        case 0:
            parseFieldReadyMessage(message);
            break;
        case 1:
            parseFieldMessage(message);
            break;
        case 2:
            parseWinMessage(message);
            break;
        default:
            qWarning() << "Unknown message type";
        }
    }
}


// Функция для создания сообщения типа 0 (поле/готовность)
QJsonObject UDPCommunicator::createFieldReadyMessage(CustomGrid& grid) {
    QJsonObject message;
    message["type"] = 0;
    message["field_size"] = grid.getFieldSize();

    // Создаем массив для поля
    QJsonArray fieldArray;
    QVector buttons = grid.getButtons();
    for (const auto& button : buttons) {
        QJsonObject cell;
        cell["row"] = button->getRow();
        cell["col"] = button->getCol();
        cell["value"] = button->getValue();
        fieldArray.append(cell);
    }

    message["field"] = fieldArray;
    return message;
}

// Функция для создания сообщения типа 1 (поле)
QJsonObject UDPCommunicator::createFieldMessage(int turn, CustomButton& button) {
    QJsonObject message;
    message["type"] = 1;
    message["turn"] = turn;

    QJsonObject cell;
    cell["row"] = button.getRow();
    cell["col"] = button.getCol();
    cell["value"] = button.getValue();

    message["cell"] = cell;

    return message;
}

// Функция для создания сообщения типа 2 (победа)
QJsonObject UDPCommunicator::createWinMessage(const QString& name) {
    QJsonObject message;
    message["type"] = 2;

    QJsonObject winObject;
    winObject["name"] = name;

    message["win"] = winObject;

    return message;
}

// Парсер для сообщения типа 0 (поле/готовность)
void UDPCommunicator::parseFieldReadyMessage(const QJsonObject& message) {
    int fieldSize = message["field_size"].toInt();
    auto opponentGrid = gameWindow->getOpponentGrid();

    QJsonArray fieldArray = message["field"].toArray();
    QVector<CustomButton*> buttons;

    for (const QJsonValue& value : fieldArray) {
        QJsonObject cell = value.toObject();
        int row = cell["row"].toInt();
        int col = cell["col"].toInt();
        int cellValue = cell["value"].toInt();

        CustomButton* button = opponentGrid->getButtonAt(row, col);
        if (button) {
            button->setValue(cellValue);
        }
    }

    qDebug() << "Field size:" << fieldSize;
    for (CustomButton* button : opponentGrid->getButtons()) {
        qDebug() << "Cell (" << button->getRow() << ", " << button->getCol() << "):" << button->getValue();
    }
}

// Парсер для сообщения типа 1 (поле)
void UDPCommunicator::parseFieldMessage(const QJsonObject& message) {
    int turn = message["turn"].toInt();
    QJsonObject cell = message["cell"].toObject();
    int row = cell["row"].toInt();
    int col = cell["col"].toInt();
    int value = cell["value"].toInt();

    auto yourGrid = gameWindow->getPlayerGrid();
    auto button = yourGrid->getButtonAt(row,col);
    button->setCheckedByEnemy();
    qDebug() << "Turn:" << turn << "Cell (" << row << ", " << col << "):" << value;
}

// Парсер для сообщения типа 2 (победа)
void UDPCommunicator::parseWinMessage(const QJsonObject& message) {
    QJsonObject winObject = message["win"].toObject();
    QString winnerName = winObject["name"].toString();

    qDebug() << "Winner is" << winnerName;
}

