#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "customgrid.h"
#include "udpcommunicator.h"
#include <QMessageBox>

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(const QString &title,
                        const QString &nikname,
                        int fieldSize,
                        quint16 sendPort,
                        bool isGameCreator,
                        QWidget *parent = nullptr,
                        const QString& ip = "127.0.0.1");

    CustomGrid* getPlayerGrid() {return playerGrid;}
    CustomGrid* getOpponentGrid() {return opponentGrid;}
    UDPCommunicator* getCommunicator() {return communicator;};

    void setTurn(int t_turn) {turn = t_turn;}

    int getTurn() {return turn;}

    QString getNikname(){return nikname;}

    void setNikname(QString t_nikname) {nikname = t_nikname;}


    QString getGameName(){return gameName;}

    void setGameName(QString t_gameName) {gameName = t_gameName;}

    void updateGrids(int newSize);

    //void setIsGameCreator(bool t_is = false) {isGameCreator = t_is;}

    void onSendMessage();

    //void onMessageReceived(const QString& message);
    //void onMessageReceived(const QJsonObject& message);


private slots:
    void onReadyClicked();           // Обработка нажатия на кнопку "Готов"
    void onResetClicked();           // Обработка нажатия на кнопку "Сброс"
    void updateReadyButtonState();   // Обновление состояния кнопки "Готов"
    void ButtonChecked(CustomButton* button);

    //void onSendMessage();   // Отправка сообщения
    void onMessageReceived(const QJsonObject& message);

private:
    int turn = 0;
    bool isGameCreator;
    qint16 receivePort;
    QString nikname;
    QString gameName;
    UDPCommunicator* communicator;
    CustomGrid *playerGrid;   // Поле игрока
    CustomGrid *opponentGrid; // Поле противника
    QPushButton *readyButton; // Кнопка "Готов"
};

#endif // GAMEWINDOW_H
