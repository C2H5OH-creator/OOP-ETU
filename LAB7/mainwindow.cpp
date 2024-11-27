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
    rootLabel = std::make_unique<QLabel>("Введите корень ниже:");
    leftLayout->addWidget(rootLabel.get());

    // Контейнер для ввода действительной и мнимой части
    complexWidget = std::make_unique<QWidget>();
    complexLayout = std::make_unique<QHBoxLayout>(complexWidget.get());

    realPartEdit = std::make_unique<QLineEdit>();
    realPartEdit->setPlaceholderText("Дейст. часть");

    imaginaryPartEdit = std::make_unique<QLineEdit>();
    imaginaryPartEdit->setPlaceholderText("Мним. часть");

    // Настроим валидаторы для ввода данных
    realPartEdit->setValidator(std::make_unique<QDoubleValidator>().get());
    imaginaryPartEdit->setValidator(std::make_unique<QDoubleValidator>().get());

    // Добавляем поля для ввода в горизонтальный макет
    complexLayout->addWidget(realPartEdit.get());
    complexLayout->addWidget(imaginaryPartEdit.get());
    leftLayout->addWidget(complexWidget.get());

    // Поле для ввода точности
    precisionEdit = std::make_unique<QLineEdit>();
    precisionEdit->setValidator(std::make_unique<QIntValidator>(1, 10).get()); // точность от 1 до 10
    precisionEdit->setPlaceholderText("Точность");
    leftLayout->addWidget(precisionEdit.get());

    // Кнопка "Посчитать"
    calculateButton = std::make_unique<QPushButton>("Посчитать");
    leftLayout->addWidget(calculateButton.get());

    // Поле для вывода результатов
    resultEdit = std::make_unique<QLineEdit>();
    resultEdit->setPlaceholderText("Результаты");
    resultEdit->setReadOnly(true); // Поле для вывода результатов, только для чтения
    leftLayout->addWidget(resultEdit.get());

    leftGroupBox->setLayout(leftLayout.get()); // Устанавливаем макет для левой группы

    // Правая часть (группа для графика)
    rightGroupBox = std::make_unique<QGroupBox>("График");
    rightLayout = std::make_unique<QVBoxLayout>(rightGroupBox.get());

    // Создаем контейнер для центрирования метки
    centerWidget = std::make_unique<QWidget>();
    centerLayout = std::make_unique<QVBoxLayout>(centerWidget.get());
    centerLayout->addStretch(1); // Заполнение сверху
    graphPlaceholder = std::make_unique<QLabel>("Здесь позже будет график функции");
    graphPlaceholder->setAlignment(Qt::AlignCenter); // Центрируем текст
    centerLayout->addWidget(graphPlaceholder.get());
    centerLayout->addStretch(1); // Заполнение снизу

    rightLayout->addWidget(centerWidget.get()); // Добавляем контейнер в правый макет
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

    setWindowTitle("Лабораторная работа №7");
    resize(800, 600); // начальный размер окна

    // Привязываем обработчик к кнопке
    QObject::connect(calculateButton.get(), &QPushButton::clicked, this, &MainWindow::onCalculateButtonClicked);
}

MainWindow::~MainWindow() {}

void MainWindow::onCalculateButtonClicked() {
    // Получаем данные из полей
    bool okReal, okImag;
    double realPart = realPartEdit->text().toDouble(&okReal);  // Чтение действительной части
    double imaginaryPart = imaginaryPartEdit->text().toDouble(&okImag);  // Чтение мнимой части
    int precision = precisionEdit->text().toInt();

    // Проверим, чтобы данные были введены корректно
    if (!okReal || !okImag) {
        resultEdit->setText("Ошибка ввода!");
        return;
    }

    // Получаем выбранную функцию из выпадающего списка
    QString selectedFunction = functionComboBox->currentText();
    Complex result(0,0);

    if (selectedFunction == "sin(x)") {
        // Считаем синус для корня
        complexSinus = std::make_unique<Sinus<Complex>>(3);
        result = complexSinus->evaluate(Complex(realPart, imaginaryPart));  // Пример: считаем только для действительной части
    } else if (selectedFunction == "Si(x)") {
        // Для интеграла (считаем интеграл синуса, как пример)
        // В реальной задаче, тут нужно будет использовать соответствующую функцию для интеграла
        //std::complex<double> root(realPart, imaginaryPart);
        //result = std::cos(root.real());  // Пример: интеграл синуса это косинус
    }

    // Отображаем результат в поле для вывода
    //resultEdit->setText(QString::number(result, 'f', precision));
    resultEdit->setText(result.GetComplexString());
}
