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
    explicit GraphWidget(QWidget *parent = nullptr)
        : QWidget(parent), xMin(-1), xMax(1), yMin(-1), yMax(1) {
        setMinimumSize(300, 200);  // Минимальные размеры для виджета
    }

    // Функции для рисования графиков
    void drawSine() {
        graphFunction = &GraphWidget::drawSineGraph;
        update();  // Перерисовываем виджет
    }

    void drawIntegralSine() {
        graphFunction = &GraphWidget::drawIntegralSineGraph;
        update();  // Перерисовываем виджет
    }

    // Устанавливаем диапазоны осей
    void setRange(double xMin, double xMax, double yMin, double yMax) {
        this->xMin = xMin;
        this->xMax = xMax;
        this->yMin = yMin;
        this->yMax = yMax;
        update();  // Перерисовываем график с новыми диапазонами
    }

protected:
    void paintEvent(QPaintEvent *event) override {
        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание

        // Рисуем оси
        drawAxes(painter);

        // Рисуем график выбранной функции
        if (graphFunction) {
            (this->*graphFunction)(painter);  // Вызываем соответствующую функцию рисования
        }
    }

private:
    // Диапазоны осей
    double xMin, xMax, yMin, yMax;

    // Указатель на функцию отрисовки
    void (GraphWidget::*graphFunction)(QPainter&) = nullptr;

    // Функция рисования синуса
    void drawSineGraph(QPainter &painter) {
        auto sinus = new Sinus<long double>(20);
        QVector<QPointF> points;
        double step = (xMax - xMin) / width();  // Шаг по оси X на один пиксель

        for (double x = xMin; x <= xMax; x += step) {
            long double y = sinus->evaluate(x);  // Математическая функция (синус)
            //double y = std::sin(x);
            points.append(QPointF(
                mapToScreenX(x), mapToScreenY(y-2)
                ));
        }

        painter.setPen(QPen(Qt::blue));  // Цвет для графика синуса
        painter.drawPolyline(points);  // Рисуем график синуса
    }

    // Функция рисования интегрального синуса
    void drawIntegralSineGraph(QPainter &painter) {
        QVector<QPointF> points;
        auto integralSinus = new IntegralSinus<double>(20);
        double step = (xMax - xMin) / width();  // Шаг по оси X на один пиксель
        double integral = 0;

        for (double x = xMin; x <= xMax; x += step) {
            integral +=  integralSinus->evaluate(x);  // Приближенный интеграл (по методу прямоугольников)
            points.append(QPointF(
                mapToScreenX(x), mapToScreenY(integral*0.5)
                ));
        }

        painter.setPen(QPen(Qt::red));  // Цвет для графика интегрального синуса
        painter.drawPolyline(points);  // Рисуем график интегрального синуса
    }

    void drawAxes(QPainter &painter) {
        painter.setPen(QPen(Qt::black));  // Цвет для осей

        // Ось X
        painter.drawLine(mapToScreenX(xMin), height() / 2, mapToScreenX(xMax), height() / 2);

        // Ось Y
        painter.drawLine(width() / 2, mapToScreenY(yMin), width() / 2, mapToScreenY(yMax));

        // Метки оси X
        painter.drawText(width() - 40, height() / 2 + 20, QString::number(xMax));  // Правая метка
        painter.drawText(40, height() / 2 + 20, QString::number(xMin));  // Левая метка

        // Метки оси Y
        painter.drawText(width() / 2 + 10, 40, QString::number(yMax));  // Верхняя метка
        painter.drawText(width() / 2 + 10, height() - 40, QString::number(yMin));  // Нижняя метка
    }


    // Преобразуем значения X в пиксели
    double mapToScreenX(double x) {
        return (x - xMin) / (xMax - xMin) * (width() - 100) + 50;
    }

    // Преобразуем значения Y в пиксели
    double mapToScreenY(double y) {
        return -(y - yMin) / (yMax - yMin) * (height() - 100) + height() / 2;
    }
};

