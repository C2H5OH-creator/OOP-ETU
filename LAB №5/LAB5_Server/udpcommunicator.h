#ifndef UDPCOMMUNICATOR_H
#define UDPCOMMUNICATOR_H

#include <QCoreApplication>
#include <QUdpSocket>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>
#include <QJsonArray>
#include <QString>
#include <QByteArray>

class UDPCommunicator : public QObject
{
     Q_OBJECT
public:
     UDPCommunicator(QObject *parent, int t_port);
    ~UDPCommunicator();

    void sendData(const QHostAddress &sender, unsigned short senderPort, const QString &receivedMessage);

    QString createJsonMessage(const QString& sender, int action,
                              const QList<QVariant>& roots,
                              const QString& serverResponse,
                              double evaluateReal, double evaluateImag,
                              const QString& canonForm, const QString& nonCanonForm);

signals:
    void messageReceived(const QString &message);

private slots:
    void getData();

private:
    QUdpSocket *udpSocket;

};
#endif // UDPCOMMUNICATOR_H
