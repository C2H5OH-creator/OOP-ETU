#ifndef UDPCOMMUNICATOR_H
#define UDPCOMMUNICATOR_H

#include <QCoreApplication>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

class UDPCommunicator : public QObject
{
     Q_OBJECT
public:
     UDPCommunicator(QObject *parent = nullptr);
    ~UDPCommunicator();

    void sendData(const QHostAddress &sender, unsigned short senderPort, const QString &receivedMessage);

signals:
    void messageReceived(const QString &message);

private slots:
    void getData();

private:
    QUdpSocket *udpSocket;

};
#endif // UDPCOMMUNICATOR_H
