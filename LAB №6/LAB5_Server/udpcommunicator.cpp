#include "udpcommunicator.h"

UDPCommunicator::UDPCommunicator(QObject *parent, int t_port) : QObject(parent) {
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(t_port);

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
    qDebug() << "Отправлено сообщение:" << jsonData;
};


QString UDPCommunicator::createJsonMessage(const QString& sender, int action,
                                           const QList<QVariant>& roots,
                                           const QString& serverResponse,
                                           double evaluateReal, double evaluateImag,
                                           const QString& canonForm, const QString& nonCanonForm) {
    QJsonObject jsonObject;

    // Добавление sender
    jsonObject["sender"] = sender;

    // Добавление action
    jsonObject["action"] = action;

    // Формирование массива roots
    QJsonArray rootsArray;
    for (const auto& root : roots) {
        if (root.canConvert<int>()) {
            // Добавление целого числа
            rootsArray.append(root.toInt());
        } else if (root.canConvert<QVariantMap>()) {
            // Добавление комплексного числа
            QVariantMap complexRoot = root.toMap();
            QJsonObject complexObj;
            complexObj["real"] = complexRoot.value("real").toDouble();
            complexObj["imag"] = complexRoot.value("imag").toDouble();
            rootsArray.append(complexObj);
        }
    }
    jsonObject["roots"] = rootsArray;

    // Добавление server_response
    jsonObject["server_response"] = serverResponse;

    // Добавление evaluate_value
    QJsonObject evaluateValue;
    evaluateValue["real"] = evaluateReal;
    evaluateValue["imag"] = evaluateImag;
    jsonObject["evaluate_value"] = evaluateValue;

    // Добавление canon_form и non_canon_form (новые строки)
    jsonObject["canon_form"] = canonForm;
    jsonObject["non_canon_form"] = nonCanonForm;

    // Создание QJsonDocument и его преобразование в строку
    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Indented);
}

