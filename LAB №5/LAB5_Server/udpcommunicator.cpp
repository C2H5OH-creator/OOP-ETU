#include "udpcommunicator.h"

UDPCommunicator::UDPCommunicator(QObject *parent) : QObject(parent) {
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(6004);

    connect(udpSocket, &QUdpSocket::readyRead, this, &UDPCommunicator::getData);
}

UDPCommunicator::~UDPCommunicator(){
    udpSocket->close();
};

void UDPCommunicator::getData(){
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray message;
        message.resize(udpSocket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        // Чтение данных из сокета
        udpSocket->readDatagram(message.data(), message.size(), &sender, &senderPort);

        // Преобразуем QByteArray в QString
        QString receivedMessage = QString::fromUtf8(message);

        // Генерируем сигнал с полученным сообщением
        emit messageReceived(receivedMessage);
    }
};

void UDPCommunicator::sendData(const QHostAddress &sender, unsigned short senderPort, const QString &receivedMessage){
    // Создание JSON-ответа
    QJsonObject jsonResponse;
    jsonResponse["response"] = receivedMessage;

    // Преобразование JSON в строку
    QJsonDocument jsonDoc(jsonResponse);
    QByteArray jsonData = jsonDoc.toJson();

    // Отправка JSON-ответа обратно отправителю
    udpSocket->writeDatagram(jsonData, sender, senderPort);
    qDebug() << "Sent response:" << jsonData;
};
