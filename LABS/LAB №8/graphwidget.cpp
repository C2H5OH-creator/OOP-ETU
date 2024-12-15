#include "graphwidget.h"

GraphWidget::GraphWidget(QWidget *parent)
    : QWidget(parent), xMin(-10), xMax(10), yMin(-2), yMax(2), precision(20) {
    setMinimumSize(300, 200);  // Минимальные размеры для виджета
}

void GraphWidget::setPrecision(int precision) {
    if (precision > 0) {  // Убедимся, что точность положительная
        this->precision = precision;
        update();  // Перерисовываем график с новой точностью
    }
}

// Функции для рисования графиков
void GraphWidget::drawSine() {
    graphFunction = &GraphWidget::drawSineGraph;
    update();  // Перерисовываем виджет
}

void GraphWidget::drawIntegralSine() {
    graphFunction = &GraphWidget::drawIntegralSineGraph;
    update();  // Перерисовываем виджет
}

// Устанавливаем диапазоны осей
void GraphWidget::setRange(double xMin, double xMax, double yMin, double yMax) {
    this->xMin = xMin;
    this->xMax = xMax;
    this->yMin = yMin;
    this->yMax = yMax;
    update();  // Перерисовываем график с новыми диапазонами
}

void GraphWidget::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // Включаем сглаживание

    // Рисуем оси
    drawAxes(painter);

    // Рисуем график выбранной функции
    if (graphFunction) {
        (this->*graphFunction)(painter);  // Вызываем соответствующую функцию рисования
    }
}

// Функция рисования синуса
void GraphWidget::drawSineGraph(QPainter &painter) {
    auto sinus = new Sinus<long double>(precision);
    QVector<QPointF> points;
    double step = (xMax - xMin) / width();

    if (step < 1e-5) {  // Минимальный шаг
        step = 1e-5;
    }

    for (double x = xMin; x <= xMax; x += step) {
        long double y = sinus->evaluate(x);
        //std::cout <<"Y: " <<y <<std::endl;
        if (y < yMin || y > yMax) {
            continue;  // Пропускаем точки вне диапазона
        }
        points.append(QPointF(
            mapToScreenX(x), mapToScreenY(y)
            ));
    }

    painter.setPen(QPen(Qt::blue));  // Цвет для графика синуса
    painter.drawPolyline(points);  // Рисуем график синуса
}

// Функция рисования интегрального синуса
void GraphWidget::drawIntegralSineGraph(QPainter &painter) {
    QVector<QPointF> points;
    auto integralSinus = new IntegralSinus<long double>(precision);
    double step = (xMax - xMin) / width();

    for (double x = xMin; x <= xMax; x += step) {
        long double y = integralSinus->evaluate(x);
        points.append(QPointF(
            mapToScreenX(x), mapToScreenY(y)
            ));
    }

    painter.setPen(QPen(Qt::red));  // Цвет для графика интегрального синуса
    painter.drawPolyline(points);  // Рисуем график интегрального синуса
}

// Рисуем оси
void GraphWidget::drawAxes(QPainter &painter) {
    painter.setPen(QPen(Qt::black));  // Цвет для осей

    // Вычисление отступа для осей
    int axisMargin = 20;  // Отступ от края для осей

    // Ось X
    painter.drawLine(mapToScreenX(xMin), mapToScreenY(0), mapToScreenX(xMax), mapToScreenY(0));

    // Проверяем, нужно ли рисовать ось Y (если 0 попадает в диапазон X)
    if (xMin <= 0 && xMax >= 0) {
        // Находим позицию оси Y (где x = 0)
        double yAxisPos = mapToScreenX(0);
        painter.drawLine(yAxisPos, mapToScreenY(yMax), yAxisPos, mapToScreenY(yMin));  // Рисуем ось Y
    }

    // Метки оси X с отступами
    painter.drawText(mapToScreenX(xMax) - axisMargin - 30, mapToScreenY(0) + 20, QString::number(xMax));  // Правая метка
    painter.drawText(mapToScreenX(xMin) + axisMargin + 10, mapToScreenY(0) + 20, QString::number(xMin));  // Левая метка

    // Метки оси Y с отступами
    if (xMin <= 0 && xMax >= 0) {
        double yAxisPos = mapToScreenX(0);
        painter.drawText(yAxisPos - 30, mapToScreenY(yMax) - 10, QString::number(yMax));  // Верхняя метка
        painter.drawText(yAxisPos - 30, mapToScreenY(yMin) + 10, QString::number(yMin));  // Нижняя метка
    }
}

// Преобразуем значения X в пиксели
double GraphWidget::mapToScreenX(double x) {
    return (x - xMin) / (xMax - xMin) * (width() - 100) + 50;
}

// Преобразуем значения Y в пиксели
double GraphWidget::mapToScreenY(double y) {
    return height() - 50 - (y - yMin) / (yMax - yMin) * (height() - 100);
}


