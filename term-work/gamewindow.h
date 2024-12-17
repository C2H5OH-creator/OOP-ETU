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
                        int fieldSize,
                        quint16 sendPort,
                        quint16 receivePort,
                        QWidget *parent = nullptr);

    CustomGrid* getPlayerGrid() {return playerGrid;}
    CustomGrid* getOpponentGrid() {return opponentGrid;}
    void setTurn(int t_turn) {turn = t_turn;}
    int getTurn() {return turn;}

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
    UDPCommunicator* communicator;
    CustomGrid *playerGrid;   // Поле игрока
    CustomGrid *opponentGrid; // Поле противника
    QPushButton *readyButton; // Кнопка "Готов"
};

#endif // GAMEWINDOW_H
