#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QUdpSocket>


#include "udpcommunicator.h"
#include "Polynom.h"
#include "Polynom.cpp"
#include "Complex.h"
#include "enums.h"

class Application : public QCoreApplication
{
    Q_OBJECT
public:
    Application(int, char**);

public slots:
    void handleMessage(const QString &message);
private:
    Polynom<number>* complexPolynom;
    Polynom<double>* doublePolynom;
    UDPCommunicator* communicator;
};

#endif // APPLICATION_H
