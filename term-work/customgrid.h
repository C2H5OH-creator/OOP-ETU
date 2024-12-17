#ifndef CUSTOMGRID_H
#define CUSTOMGRID_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QSet>
#include <QVector>
#include <QPair>
#include <cmath>
#include "custombutton.h" // Предполагаем, что CustomButton — это ваш пользовательский класс кнопки

class CustomGrid : public QWidget
{
    Q_OBJECT

public:
    explicit CustomGrid(bool enemyGrid, int rows, int cols, QWidget *parent = nullptr);

    bool hasSelection() const; // Метод для проверки наличия выделенных кнопок
    QVector<QPair<int, QPoint>> getSelectedButtonsData() const; // Метод для получения данных выбранных кнопок

    QVector<CustomButton*>& getButtons() { return buttons; }

    int& getFieldSize() {std::sqrt(buttons.size());}

    CustomButton* getButtonAt(int row, int col);

signals:
    void selectionChanged(); // Сигнал, который будет отправляться при изменении выбора

public slots:
    void resetSelection(); // Слот для сброса выделения

private:
    void createButtons(); // Метод для создания кнопок
    void toggleButtonSelection(CustomButton *button); // Метод для переключения состояния кнопки
    void buttonClicked(int row, int col);

    int rows; // Количество строк
    int cols; // Количество столбцов
    bool enemyGrid; // Признак того, что это поле противника
    QGridLayout *layout; // Лейаут для размещения кнопок
    QVector<CustomButton*> buttons; // Вектор всех кнопок на поле
    QSet<CustomButton*> selectedButtons; // Множество выбранных кнопок
};

#endif // CUSTOMGRID_H
