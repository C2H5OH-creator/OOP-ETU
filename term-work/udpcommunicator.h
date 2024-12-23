#ifndef UDPCOMMUNICATOR_H
#define UDPCOMMUNICATOR_H

#include <QString>
#include <QUdpSocket>
#include <QHostAddress>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "customgrid.h"
#include "custombutton.h"
//#include "gamewindow.h"

class GameWindow;

class UDPCommunicator : public QObject {
    Q_OBJECT

public:
    // Конструктор
    UDPCommunicator(quint16 listenPort, quint16 sendPort, const QString& ip = "127.0.0.1", QObject* parent = nullptr);

    void setGameWindow(GameWindow* t_gameWindow){ gameWindow = t_gameWindow; }

    // Метод для отправки сообщения
    void sendMessage(const QJsonObject& message);

    // Метод для получения сообщения
    void startReceiving();

    // Функция для создания сообщения типа 0 (поле/готовность)
    QJsonObject createFieldReadyMessage(CustomGrid* grid) ;

    // Функция для создания сообщения типа 1 (поле)
    QJsonObject createFieldMessage(int turn, CustomButton* button);

    // Функция для создания сообщения типа 2 (победа)
    QJsonObject createWinMessage(const QString& name);

    QJsonObject createGetGeneralFieldDataMessage();

    QJsonObject createGeneralFieldDataMessage(const QString& name, int fieldSize);

    QJsonObject createGetSummDataMessage();
    QJsonObject createSummDataMessage(int summ, const QString& name);

    // Функция для обработки сообщения типа 0 (поле/готовность)
    void parseFieldReadyMessage(const QJsonObject& message);

    // Функция для обработки сообщения типа 1 (поле)
    void parseFieldMessage(const QJsonObject& message);

    // Функция для обработки сообщения типа 2 (победа)
    void parseWinMessage(const QJsonObject& message);

    // Функция для обработки сообщения типа 3 (запрос имени)
    void parseGeneralFieldDataMessage(const QJsonObject& message);

    void parseGetSummMessage(const QJsonObject& message);

private slots:
    // Слот для обработки полученного сообщения
    void processReceivedMessage();

signals:
    void messageReceived(const QJsonObject& message);


private:
    GameWindow* gameWindow;
    QUdpSocket udpSocket_;
    QHostAddress remoteAddress_;
    quint16 listenPort_;  // Порт для прослушивания
    quint16 sendPort_;
};

#endif // UDPCOMMUNICATOR_H
