#ifndef APPLICATION_H
#define APPLICATION_H

#include <QObject>
#include <QCoreApplication>

#include "udpcommunicator.h"
#include "Polynom.h"
#include "Complex.h"

class Application : public QCoreApplication
{
    Q_OBJECT
public:
    Application(int, char**);

public slots:
    void handleMessage(const QString &message);
private:
    UDPCommunicator* communicator;
};

#endif // APPLICATION_H
