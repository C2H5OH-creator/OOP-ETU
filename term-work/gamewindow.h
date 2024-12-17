#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include "customgrid.h"

class GameWindow : public QWidget {
    Q_OBJECT

public:
    explicit GameWindow(const QString &title, int fieldSize, QWidget *parent = nullptr);
    CustomGrid* getPlayerGrid() {return playerGrid;}
    CustomGrid* getOpponentGrid() {return opponentGrid;}


private slots:
    void onReadyClicked();           // Обработка нажатия на кнопку "Готов"
    void onResetClicked();           // Обработка нажатия на кнопку "Сброс"
    void updateReadyButtonState();   // Обновление состояния кнопки "Готов"

private:
    CustomGrid *playerGrid;   // Поле игрока
    CustomGrid *opponentGrid; // Поле противника
    QPushButton *readyButton; // Кнопка "Готов"
};

#endif // GAMEWINDOW_H
