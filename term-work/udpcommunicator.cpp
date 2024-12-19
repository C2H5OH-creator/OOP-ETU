#include "udpcommunicator.h"
#include "gamewindow.h"

#include <QDebug>

// Конструктор
UDPCommunicator::UDPCommunicator(quint16 listenPort, quint16 sendPort, const QString& ip, QObject* parent)

    : QObject(parent), remoteAddress_(QHostAddress(ip)), listenPort_(listenPort), sendPort_(sendPort) {
    // Создаем UDP-сокет и привязываем его для прослушивания на порту listenPort_
    udpSocket_.bind(QHostAddress::Any, listenPort_);

    // Подключаем слот для обработки полученных сообщений
    connect(&udpSocket_, &QUdpSocket::readyRead, this, &UDPCommunicator::processReceivedMessage);
}

// Метод для отправки сообщения
void UDPCommunicator::sendMessage(const QJsonObject& message) {
    // Преобразуем QJsonObject в QJsonDocument
    QJsonDocument doc(message);
    QByteArray datagram = doc.toJson();  // Сериализуем в JSON строку (байтовый массив)

    // Отправляем сообщение на порт sendPort_
    udpSocket_.writeDatagram(datagram, remoteAddress_, sendPort_);
    qDebug() << "Message sent:" << QString(doc.toJson(QJsonDocument::Indented));
}

// Метод для начала приема сообщений
void UDPCommunicator::startReceiving() {
    // Слушаем порт для получения сообщений
    udpSocket_.bind(QHostAddress::Any, listenPort_);
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

        // Испускаем сигнал с сообщением
        emit messageReceived(message);
    }
}

// Функция для создания сообщения типа 0 (поле/готовность)
QJsonObject UDPCommunicator::createFieldReadyMessage(CustomGrid* grid) {
    QJsonObject message;
    qDebug() << 1;
    message["type"] = 0;
    qDebug() << 12;
    message["field_size"] = grid->getFieldSize();
    //message["field_size"] =

    qDebug() << 2;
    // Создаем массив для поля
    QJsonArray fieldArray;
        int i = 10;
    QVector buttons = grid->getButtons();
    for (const auto& button : buttons) {
        QJsonObject cell;
        qDebug() << i++;
        cell["row"] = button->getRow();
        cell["col"] = button->getCol();
        cell["value"] = button->getValue();
        fieldArray.append(cell);
    }
    qDebug() << 3;

    message["field"] = fieldArray;
    qDebug() << "Сообщение собрано";
    return message;
}

// Функция для создания сообщения типа 1 (поле)
QJsonObject UDPCommunicator::createFieldMessage(int turn, CustomButton* button) {
    QJsonObject message;
    message["type"] = 1;
    message["turn"] = turn;

    QJsonObject cell;
    cell["row"] = button->getRow();
    cell["col"] = button->getCol();
    cell["value"] = button->getValue();

    message["cell"] = cell;

    auto opponentGrid = gameWindow->getOpponentGrid();

    qDebug() << opponentGrid->getRightButtons() << " " << opponentGrid->getRightFoundedButtons();
    if (opponentGrid->getRightButtons() == opponentGrid->getRightFoundedButtons()) {
        this->sendMessage(this->createWinMessage(gameWindow->windowTitle()));
        QMessageBox::information(gameWindow, "Конец игры!", "Победил " + gameWindow->windowTitle());
        return QJsonObject();
    }
    else if(turn > 50){
        this->sendMessage(this->createGetSummDataMessage());
    }

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


QJsonObject UDPCommunicator::createGetSummDataMessage(){
    QJsonObject message;
    message["type"] = 4;
    message["request"] = "get";
    message["summ"] = 0;
    message["name"] = "";
    return message;

}

QJsonObject UDPCommunicator::createSummDataMessage(int summ, const QString& name){
    QJsonObject message;
    message["type"] = 4;
    message["request"] = "post";
    message["summ"] = summ;
    message["name"] = name;
    return message;
}

QJsonObject UDPCommunicator::createGetGeneralFieldDataMessage(){
    QJsonObject message;
    message["type"] = 3;
    message["request"] = "get";
    message["game_name"] = "";
    message["field_size"] = 0;
    return message;

}

QJsonObject UDPCommunicator::createGeneralFieldDataMessage(const QString& name, int fieldSize){
    QJsonObject message;
    message["type"] = 3;
    message["game_name"] = name;
    message["field_size"] = fieldSize;
    message["request"] = "post";

    return message;

}

void UDPCommunicator::parseGeneralFieldDataMessage(const QJsonObject& message){
    QString gameName = message["game_name"].toString();
    int newFieldSize = message["field_size"].toInt();

    if(message["request"].toString() == "get"){
        QString name = gameWindow->getGameName();
        int fieldSize = gameWindow->getPlayerGrid()->getFieldSize();
        this->sendMessage(this->createGeneralFieldDataMessage(name, fieldSize));
    }
    else {
        gameWindow->setWindowTitle("Игра - " + gameName + " : " + "Игрок - " + gameWindow->getNikname());
        gameWindow->updateGrids(newFieldSize);
    }
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

        if (cellValue != 0) {
            opponentGrid->addToSumm(cellValue);
            opponentGrid->addToRightButtons(1);
        }

        CustomButton* button = opponentGrid->getButtonAt(row, col);
        if (button) {
            button->setValue(cellValue);

            connect(button, &QPushButton::clicked, [this, button,opponentGrid]() {
                // Вызываем метод toggleButtonSelection для текущего объекта CustomGrid
                opponentGrid->toggleButtonSelection(button);
            });
        }
    }

    //qDebug() << "Field size:" << fieldSize;
    //for (CustomButton* button : opponentGrid->getButtons()) {
      //  qDebug() << "Cell (" << button->getRow() << ", " << button->getCol() << "):" << button->getValue();
    //}
}

// Парсер для сообщения типа 1 (поле)
void UDPCommunicator::parseFieldMessage(const QJsonObject& message) {
    int turn = message["turn"].toInt();
    auto opponentGrid = gameWindow->getOpponentGrid();

    if (opponentGrid->getRightButtons() == opponentGrid->getRightFoundedButtons()) {
        this->sendMessage(this->createWinMessage(gameWindow->windowTitle()));
        QMessageBox::information(gameWindow, "Конец игры!", "Победил " + gameWindow->getNikname());
        return;
    }
    gameWindow->setTurn(turn);
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

void UDPCommunicator::parseGetSummMessage(const QJsonObject& message) {
    int summ = message["summ"].toInt();
    QString name = message["name"].toString();

    if(message["request"].toString() == "get"){
        int summ = gameWindow->getOpponentGrid()->getSumm();
        QString nikname = gameWindow->getNikname();
        this->sendMessage(this->createSummDataMessage(summ, nikname));
    }
    else {
        if(summ > gameWindow->getOpponentGrid()->getSumm()){
            QMessageBox::information(gameWindow, "Конец игры!", "Победил " + name);
        }
        else{
           QMessageBox::information(gameWindow, "Конец игры!", "Победил " + gameWindow->getNikname());
        }
    }
}

