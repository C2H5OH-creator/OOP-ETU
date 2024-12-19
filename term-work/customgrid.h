#ifndef CUSTOMGRID_H
#define CUSTOMGRID_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSet>
#include <QVector>
#include <QPair>
#include <cmath>

#include "custombutton.h"

class CustomGrid : public QWidget
{
    Q_OBJECT

public:
    explicit CustomGrid(bool isGameCreator, bool enemyGrid, int rows, int cols,int &turn, QWidget *parent = nullptr);

    bool hasSelection() const; // Метод для проверки наличия выделенных кнопок
    QVector<QPair<int, QPoint>> getSelectedButtonsData() const; // Метод для получения данных выбранных кнопок

    QVector<CustomButton*>& getButtons() { return buttons; }

    int getFieldSize() {
        if (buttons.isEmpty()) {
            return 0;  // Возвращаем 0, если кнопок нет
        }
        return static_cast<int>(std::sqrt(buttons.size()));
    }

    void addToRightButtons(int num){ rightButtons += num;}
    void addToSumm(int num){ summ += num;}

    int getSumm(){return summ;}
    int getRightButtons(){return rightButtons;}
    int getRightFoundedButtons(){return rightFoundedButtons;}

    void updateGrid(int newRows, int newCols);

    CustomButton* getButtonAt(int row, int col);
    void updateEnemyGrid(const QVector<QVector<int>>& fieldData);
    void toggleButtonSelection(CustomButton *button); // Метод для переключения состояния кнопки

signals:
    void selectionChanged(); // Сигнал, который будет отправляться при изменении выбора
    //void messageToSend(const QJsonObject& message);
    void messageToSend(CustomButton* button);

public slots:
    void resetSelection(); // Слот для сброса выделения

private:
    void createButtons(); // Метод для создания кнопок
    void buttonClicked(int row, int col);

    int rows; // Количество строк
    int cols; // Количество столбцов
    int &turn;
    bool enemyGrid; // Признак того, что это поле противника
    int rightButtons = 0;
    int rightFoundedButtons = 0;
    int summ = 0;
    bool isGameCreator = false;

    QGridLayout *layout; // Лейаут для размещения кнопок
    QVector<CustomButton*> buttons; // Вектор всех кнопок на поле
    QSet<CustomButton*> selectedButtons; // Множество выбранных кнопок
};

#endif // CUSTOMGRID_H
