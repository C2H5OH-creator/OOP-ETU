#include "application.h"

Application::Application(int argc, char *argv[])
    : QCoreApplication(argc, argv) {
    communicator = new UDPCommunicator(this, server_port);
    connect(communicator, &UDPCommunicator::messageReceived, this, &Application::handleMessage);
    complexPolynom = new Polynom<number>();
    doublePolynom = new Polynom<double>();
}

void Application::handleMessage(const QString &message){
    qDebug() << "Сервер получил сообщение: " + message;

    UDPCommunicator::MessageData responseStruct = communicator->parseJsonMessage(message);
    //qDebug() << "Тип данных" << responseStruct.dataType;
    //qDebug() << "Сервер получил сообщение: " + responseStruct.action;
    QList<QVariant> emptyList;

    // Разбор JSON строки
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());

    // Проверка валидности JSON
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qDebug() << "Ошибка: Получено некорректное сообщение.";
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();

    // Извлечение значения response (которое является строкой, содержащей JSON)
    QString responseString = jsonObject.value("response").toString();
    qDebug() << "Ответ из вложенного JSON: " << responseString;

    // Теперь нужно распарсить строку response как JSON
    QJsonDocument responseDoc = QJsonDocument::fromJson(responseString.toUtf8());

    // Проверка валидности вложенного JSON
    if (responseDoc.isNull() || !responseDoc.isObject()) {
        qDebug() << "Ошибка: Вложенный JSON некорректен.";
        return;
    }

    QJsonObject responseObject = responseDoc.object();


    if(!responseStruct.dataType){
        //qDebug() << "КОМПЛЕКСНЫЕ ЧИСЛА";
        // Извлечение значений из вложенного JSON
        int action = responseObject.value("action").toInt();
        QString sender = responseObject.value("sender").toString();
        qDebug() << "Сервер будет выполнять такое действие: " << action;
        qDebug() << "Отправитель: " << sender;

        QString serverResponse = responseObject.value("server_response").toString();
        qDebug() << "Ответ сервера: " << serverResponse;

        // Извлечение массива корней
        //QJsonArray rootsArray = responseStruct.roots; //responseObject.value("roots").toArray();
        QJsonArray rootsArray = responseObject.value("roots").toArray();
        QVector<number> roots;
        for (const QJsonValue &rootValue : rootsArray) {
            QJsonObject rootObject = rootValue.toObject();
            double real = rootObject.value("real").toDouble();
            double imag = rootObject.value("imag").toDouble();
            roots.append(number(real, imag));  // Создаем число и добавляем в массив корней
            qDebug() << "Добавлен корень: " << "real:" << real << "imag:" << imag;
        }

        // Извлечение коэффициента an из первого элемента массива корней
        number anCoeff(0, 0);
        if (!roots.isEmpty()) {
            anCoeff = roots.first();
            roots.removeFirst();  // Удаляем первый элемент, если он является коэффициентом an
            qDebug() << "Коэффициент an:" << "real:" << anCoeff.getReal() << "imag:" << anCoeff.getImaginary();
        }

        // Извлечение значения evaluate_value
        QJsonObject evaluateObject = responseObject.value("evaluate_value").toObject();
        //double evaluateReal = evaluateObject.value("real").toDouble();
        //double evaluateImag = evaluateObject.value("imag").toDouble();
        //number evaluateValue(evaluateReal, evaluateImag);
        number evaluateValue(responseStruct.evaluateReal, responseStruct.evaluateImag);
        qDebug() << "Значение для evaluate_value:" << "real:" << responseStruct.evaluateReal << "imag:" << responseStruct.evaluateImag;


        QString polynomForms = communicator->createJsonMessage(0,"server",
                                                               action, emptyList,"" ,
                                                               0,0,complexPolynom->PrintCanonicalForm(),
                                                               complexPolynom->PrintNonCanonicalForm());

        number result = complexPolynom->evaluateAtPoint(evaluateValue);

        QString value = communicator->createJsonMessage(0,"server",
                                                               action, emptyList, result.GetComplexString(),0,0,"","");




        QString changedRoot = communicator->createJsonMessage(0,"server",
                                                        action, emptyList, result.GetComplexString(),0,0,"","");


        // Обработка action
        switch (action) {
        case CREATE_POLYNOM:
            complexPolynom->Create(anCoeff, roots.size(), roots);
            break;
        case GET_POLYNOM_FORMS:
            qDebug() << complexPolynom->PrintCanonicalForm();
            communicator->sendData(QHostAddress("0.0.0.0"), client_port, polynomForms);

            break;
        case CALCULATE_VALUE_POLYNOMIAL_AT_POINT:
            communicator->sendData(QHostAddress("0.0.0.0"), client_port, value);
            break;
        case CHANGE_AN:
            complexPolynom->SetValue(1,0,anCoeff);
            break;
        case CHANGE_ROOT:
            if (roots.size() > 1) {
                complexPolynom->SetValue(0, roots[0].getReal(), roots[1]);
            } else {
                qDebug() << "Ошибка: Вектор корней имеет недостаточное количество элементов.";
            }

            break;
        default:
            qDebug() << "Неизвестное действие.";
            break;
        }
    } else {
         qDebug() << "ОБЫЧНЫЕ ЧИСЛА";
        QJsonArray rootsArray = responseObject.value("roots").toArray();
        QVector<double> roots;
        for (const QJsonValue &rootValue : rootsArray) {
            QJsonObject rootObject = rootValue.toObject();
            double real = rootObject.value("real").toDouble();
            roots.append(real);  // Создаем число и добавляем в массив корней
            qDebug() << "Добавлен корень: " << real;
        }


        double anCoeff = 0;
        if (!roots.isEmpty()) {
            anCoeff = roots.first();
            roots.removeFirst();  // Удаляем первый элемент, если он является коэффициентом an
            qDebug() << "Коэффициент an:" << "real:" << anCoeff;
        }

        QString polynomForms = communicator->createJsonMessage(1,"server",
                                                               responseStruct.action, emptyList,"" ,
                                                               0,0,doublePolynom->PrintDoubleCanonicalForm(),
                                                               doublePolynom->PrintDoubleNonCanonicalForm());

        double result = doublePolynom->evaluateAtPoint(responseStruct.evaluateReal);

        QString value = communicator->createJsonMessage(0,"server",
                                                        responseStruct.action, emptyList, QString::number(result, 'f', 5),0,0,"","");




        QString changedRoot = communicator->createJsonMessage(0,"server",
                                                           responseStruct.action, emptyList, QString::number(result, 'f', 5), 0,0,"","");


        // Обработка action
        switch (responseStruct.action) {
        case CREATE_POLYNOM:
            doublePolynom->Create(anCoeff, roots.size(), roots);
            break;
        case GET_POLYNOM_FORMS:
            qDebug() << doublePolynom->PrintCanonicalForm();
            communicator->sendData(QHostAddress("0.0.0.0"), client_port, polynomForms);

            break;
        case CALCULATE_VALUE_POLYNOMIAL_AT_POINT:
            communicator->sendData(QHostAddress("0.0.0.0"), client_port, value);
            break;
        case CHANGE_AN:
            doublePolynom->SetValue(1,0,anCoeff);
            break;
        case CHANGE_ROOT:
            if (roots.size() > 1) {
                doublePolynom->SetValue(0, roots[0], roots[1]);
            } else {
                qDebug() << "Ошибка: Вектор корней имеет недостаточное количество элементов.";
            }

            break;
        default:
            qDebug() << "Неизвестное действие.";
            break;
        }
    }

}


