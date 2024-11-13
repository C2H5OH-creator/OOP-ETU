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

QString UDPCommunicator::createJsonMessage(const bool& dataType,
                                           const QString& sender, int action,
                                           const QList<QVariant>& roots,
                                           const QString& serverResponse,
                                           double evaluateReal, double evaluateImag,
                                           const QString& canonForm, const QString& nonCanonForm) {
    QJsonObject jsonObject;

    // Добавление dataType
    jsonObject["dataType"] = dataType;

    // Добавление sender
    jsonObject["sender"] = sender;

    // Добавление action
    jsonObject["action"] = action;

    // Формирование массива roots
    QJsonArray rootsArray;
    for (const auto& root : roots) {
        if (dataType == 1) {
            // Если dataType == 1, записываем только вещественные числа
            if (root.canConvert<QList<QVariant>>()) {
                // Преобразуем QVariant в QList<QVariant>
                QList<QVariant> list = root.toList();

                if (!list.isEmpty()) {
                    // Извлекаем первый элемент списка
                    QVariant number = list.first();
                    rootsArray.append(number.toDouble());
                }
            }
        } else {
            // Если dataType != 1, записываем комплексные числа в виде объекта
            if (root.canConvert<QVariantMap>()) {
                QVariantMap complexRoot = root.toMap();
                QJsonObject complexObj;
                complexObj["real"] = complexRoot.value("real").toDouble();
                complexObj["imag"] = complexRoot.value("imag").toDouble();
                rootsArray.append(complexObj);
            }
        }
    }
    jsonObject["roots"] = rootsArray;

    // Добавление server_response
    jsonObject["server_response"] = serverResponse;

    // Добавление evaluate_value
    if (dataType == 1) {
        // Если dataType == 1, записываем только вещественное число
        jsonObject["evaluate_value"] = evaluateReal;
    } else {
        // Если dataType != 1, записываем как комплексное число (с реальной и мнимой частью)
        QJsonObject evaluateValue;
        evaluateValue["real"] = evaluateReal;
        evaluateValue["imag"] = evaluateImag;
        jsonObject["evaluate_value"] = evaluateValue;
    }

    // Добавление canon_form и non_canon_form
    jsonObject["canon_form"] = canonForm;
    jsonObject["non_canon_form"] = nonCanonForm;

    // Создание QJsonDocument и его преобразование в строку
    QJsonDocument jsonDoc(jsonObject);
    return jsonDoc.toJson(QJsonDocument::Indented);
}


UDPCommunicator::MessageData UDPCommunicator::parseJsonMessage(const QString& jsonString) {
    // Преобразуем строку в объект QJsonDocument
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());

    MessageData parsedData;

    if (jsonDoc.isObject()) {
        QJsonObject jsonObject = jsonDoc.object();

        // Парсим dataType
        parsedData.dataType = jsonObject["dataType"].toBool();

        // Парсим sender
        parsedData.sender = jsonObject["sender"].toString();

        // Парсим action
        parsedData.action = jsonObject["action"].toInt();

        // Парсим roots
        QJsonArray rootsArray = jsonObject["roots"].toArray();
        for (const auto& rootValue : rootsArray) {
            if (parsedData.dataType == 1) {
                if (rootValue.isObject()) {
                    QJsonObject rootObj = rootValue.toObject();
                    QVariantMap complexRoot;
                    parsedData.roots.append(rootObj["real"].toDouble());
                }

            } else {
                // Если dataType != 1, ожидаем комплексные числа
                if (rootValue.isObject()) {
                    QJsonObject rootObj = rootValue.toObject();
                    QVariantMap complexRoot;
                    complexRoot["real"] = rootObj["real"].toDouble();
                    complexRoot["imag"] = rootObj["imag"].toDouble();
                    parsedData.roots.append(complexRoot);
                }
            }
        }

        // Парсим server_response
        parsedData.serverResponse = jsonObject["server_response"].toString();

        // Парсим evaluate_value
        if (parsedData.dataType == 1) {
            parsedData.evaluateReal = jsonObject["evaluate_value"].toDouble();
            parsedData.evaluateImag = 0.0;  // Для вещественных значений мнимая часть 0
        } else {
            QJsonObject evaluateValue = jsonObject["evaluate_value"].toObject();
            parsedData.evaluateReal = evaluateValue["real"].toDouble();
            parsedData.evaluateImag = evaluateValue["imag"].toDouble();
        }

        // Парсим canon_form и non_canon_form
        parsedData.canonForm = jsonObject["canon_form"].toString();
        parsedData.nonCanonForm = jsonObject["non_canon_form"].toString();
    }

    return parsedData;
}

