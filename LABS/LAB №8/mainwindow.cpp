#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    // Создаем главный макет для окна
    mainLayout = std::make_unique<QHBoxLayout>(this);

    // Создаем разделитель (QSplitter) для горизонтального разделения
    splitter = std::make_unique<QSplitter>(Qt::Horizontal);

    // Левый контейнер (группа настроек)
    leftGroupBox = std::make_unique<QGroupBox>("Настройки");
    leftLayout = std::make_unique<QVBoxLayout>(leftGroupBox.get());

    // Выпадающий список для выбора функции
    functionComboBox = std::make_unique<QComboBox>();
    functionComboBox->addItem("sin(x)");
    functionComboBox->addItem("Si(x)");
    leftLayout->addWidget(functionComboBox.get());

    // Добавление заголовка для ввода корня
    rootLabel = std::make_unique<QLabel>("Введите границы ниже:");
    leftLayout->addWidget(rootLabel.get());

    // Создаем контейнеры для ввода minX/maxX и minY/maxY
    xLayout = std::make_unique<QHBoxLayout>();
    yLayout = std::make_unique<QHBoxLayout>();

    minXEdit = std::make_unique<QLineEdit>();
    minXEdit->setPlaceholderText("Min X");
    minXEdit->setText("-15");

    maxXEdit = std::make_unique<QLineEdit>();
    maxXEdit->setPlaceholderText("Max X");
    maxXEdit->setText("15");

    minYEdit = std::make_unique<QLineEdit>();
    minYEdit->setPlaceholderText("Min Y");
    minYEdit->setText("-2");

    maxYEdit = std::make_unique<QLineEdit>();
    maxYEdit->setPlaceholderText("Max Y");
    maxYEdit->setText("2");

    // Настроим валидаторы для ввода данных
    minXEdit->setValidator(std::make_unique<QDoubleValidator>().get());
    maxXEdit->setValidator(std::make_unique<QDoubleValidator>().get());
    minYEdit->setValidator(std::make_unique<QDoubleValidator>().get());
    maxYEdit->setValidator(std::make_unique<QDoubleValidator>().get());

    // Добавляем поля в соответствующие макеты
    xLayout->addWidget(minXEdit.get());
    xLayout->addWidget(maxXEdit.get());
    yLayout->addWidget(minYEdit.get());
    yLayout->addWidget(maxYEdit.get());

    // Добавляем эти макеты в основной вертикальный макет
    leftLayout->addLayout(xLayout.get());
    leftLayout->addLayout(yLayout.get());

    // Поле для ввода точности
    precisionEdit = std::make_unique<QLineEdit>();
    precisionEdit->setValidator(std::make_unique<QIntValidator>(1, 100).get()); // точность от 1 до 10
    precisionEdit->setPlaceholderText("Точность");
    precisionEdit->setText("100");
    leftLayout->addWidget(precisionEdit.get());

    // Кнопка "Посчитать"
    calculateButton = std::make_unique<QPushButton>("Начертить график");
    leftLayout->addWidget(calculateButton.get());
    leftGroupBox->setLayout(leftLayout.get()); // Устанавливаем макет для левой группы

    // Правая часть (группа для графика)
    rightGroupBox = std::make_unique<QGroupBox>("График");
    rightLayout = std::make_unique<QVBoxLayout>(rightGroupBox.get());

    graphWidget = std::make_unique<GraphWidget>();  // Используем класс, который рисует график
    rightLayout->addWidget(graphWidget.get());

    rightGroupBox->setLayout(rightLayout.get()); // Устанавливаем макет для правой группы

    // Разделитель между левой и правой частью
    line = std::make_unique<QFrame>();
    line->setFrameShape(QFrame::VLine);  // Вертикальная линия
    line->setFrameShadow(QFrame::Sunken);  // Тень для линии

    // Добавляем все в разделитель (QSplitter)
    splitter->addWidget(leftGroupBox.get());
    splitter->addWidget(rightGroupBox.get());

    // Устанавливаем размеры для левой и правой части (левая - 1/3, правая - 2/3)
    splitter->setSizes({width() / 3, width() * 2 / 3});

    // Добавляем splitter в главный макет
    mainLayout->addWidget(splitter.get());

    setLayout(mainLayout.get());  // Устанавливаем главный макет

    setWindowTitle("Лабораторная работа №8");
    resize(800, 600); // начальный размер окна

    // Привязываем обработчик к кнопке
    QObject::connect(calculateButton.get(), &QPushButton::clicked, this, &MainWindow::onCalculateButtonClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onCalculateButtonClicked() {
    // Получаем данные из полей
    double maxX = maxXEdit->text().toDouble();
    double minX = minXEdit->text().toDouble();

    double maxY = maxYEdit->text().toDouble();
    double minY = minYEdit->text().toDouble();

    unsigned precision = precisionEdit->text().toUInt();

    // Получаем выбранную функцию из выпадающего списка
    QString selectedFunction = functionComboBox->currentText();
    Complex result(0,0);

    if (selectedFunction == "sin(x)") {
        graphWidget->setPrecision(precision);
        graphWidget->drawSine();
        graphWidget->setRange(minX, maxX, minY, maxY);
    } else if (selectedFunction == "Si(x)") {
        graphWidget->setPrecision(precision);
        graphWidget->drawIntegralSine();
        graphWidget->setRange(minX, maxX, minY, maxY);
    }
}
