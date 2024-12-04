#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QVector>
#include <cmath>

#include "sinus.h"
#include "integralsinus.h"

class GraphWidget : public QWidget {
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = nullptr);

    void setPrecision(int precision);

    // Функции для рисования графиков
    void drawSine();
    void drawIntegralSine();

    // Устанавливаем диапазоны осей
    void setRange(double xMin, double xMax, double yMin, double yMax);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    // Диапазоны осей
    double xMin, xMax, yMin, yMax;
    int precision;

    // Указатель на функцию отрисовки
    void (GraphWidget::*graphFunction)(QPainter&) = nullptr;

    // Функция рисования синуса
    void drawSineGraph(QPainter &painter);

    // Функция рисования интегрального синуса
    void drawIntegralSineGraph(QPainter &painter);

    // Рисуем оси
    void drawAxes(QPainter &painter);

    // Преобразуем значения X в пиксели
    double mapToScreenX(double x);

    // Преобразуем значения Y в пиксели
    double mapToScreenY(double y);
};

#endif // GRAPHWIDGET_H
