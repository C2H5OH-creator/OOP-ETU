#include "interface.h"

Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{
    // Центральный виджет и главный макет
    centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Левый Layout для радиокнопок
    leftLayout = new QVBoxLayout();

    auto createPolynom = new QRadioButton("Ввести корни и An полинома", this);
    auto changeValue = new QRadioButton("Изменить An или любой другой корень", this);
    auto calcPolynom = new QRadioButton("Вычислить значение полинома в точке", this);
    auto printPolynom = new QRadioButton("Вывести полином", this);

    // Подключение сигналов
    connect(createPolynom, &QRadioButton::clicked, this, &Interface::OnCreatePolynomClicked);
    connect(changeValue, &QRadioButton::clicked, this, &Interface::OnChangeValueClicked);
    connect(calcPolynom, &QRadioButton::clicked, this, &Interface::OnCalcPolynomClicked);
    connect(printPolynom, &QRadioButton::clicked, this, &Interface::OnPrintPolynomClicked);

    // Добавление радиокнопок в левый Layout
    leftLayout->addWidget(createPolynom);
    leftLayout->addWidget(changeValue);
    leftLayout->addWidget(calcPolynom);
    leftLayout->addWidget(printPolynom);

    // Правый Layout для отображения элементов в зависимости от выбора
    QVBoxLayout *rightLayout = new QVBoxLayout();

    // Виджет для создания полинома
    createPolynomWidget = new QWidget(this);
    QVBoxLayout *createLayout = new QVBoxLayout(createPolynomWidget);
    createLayout->addWidget(new QLabel("Сколько корней вы хотите?", this));
    auto rootCountInput = new QLineEdit(this);  // Поле ввода для количества корней
    createLayout->addWidget(rootCountInput);
    createLayout->addWidget(new QLabel("Введите первый коэффициент An:", this));
    auto aNInput = new QLineEdit(this);  // Поле ввода для An
    createLayout->addWidget(aNInput);

    // Кнопка подтверждения для создания полинома
    QPushButton *confirmCreateButton = new QPushButton("Подтвердить", this);
    connect(confirmCreateButton, &QPushButton::clicked, [this, rootCountInput, aNInput]() {
       createPolynom(rootCount, aN);
    });
    createLayout->addWidget(confirmCreateButton);

    // Виджет для изменения значения
    changeValueWidget = new QWidget(this);
    QVBoxLayout *changeLayout = new QVBoxLayout(changeValueWidget);
    changeLayout->addWidget(new QLabel("Введите новый An или корень:", this));
    auto *changeInput = new QLineEdit(this);  // Поле ввода для изменения
    changeLayout->addWidget(changeInput);

    // Кнопка подтверждения для изменения значения
    QPushButton *confirmChangeButton = new QPushButton("Подтвердить", this);
    connect(confirmChangeButton, &QPushButton::clicked, [this, changeInput]() {
        // Обработка ввода
        double newValue = changeInput->text().toDouble();
        // Вызов функции для изменения значения
        //changePolynomValue(newValue);
    });
    changeLayout->addWidget(confirmChangeButton);

    // Виджет для вычисления значения полинома
    calcPolynomWidget = new QWidget(this);
    QVBoxLayout *calcLayout = new QVBoxLayout(calcPolynomWidget);
    calcLayout->addWidget(new QLabel("Введите значение для вычисления:", this));
    auto *calcInput = new QLineEdit(this);  // Поле ввода для вычисления
    calcLayout->addWidget(calcInput);

    // Кнопка подтверждения для вычисления
    QPushButton *confirmCalcButton = new QPushButton("Подтвердить", this);
    connect(confirmCalcButton, &QPushButton::clicked, [this, calcInput]() {
        // Обработка ввода
        double value = calcInput->text().toDouble();
        // Вызов функции для вычисления полинома
        //double result = calculatePolynom(value);
        // Отображение результата
        //QMessageBox::information(this, "Результат", QString("Значение полинома: %1").arg(result));
    });
    calcLayout->addWidget(confirmCalcButton);

    // Виджет для вывода полинома
    printPolynomWidget = new QWidget(this);
    QVBoxLayout *printLayout = new QVBoxLayout(printPolynomWidget);
    printLayout->addWidget(new QLabel("Здесь будет вывод полинома", this));

    // Скрытие всех виджетов по умолчанию
    createPolynomWidget->hide();
    changeValueWidget->hide();
    calcPolynomWidget->hide();
    printPolynomWidget->hide();

    // Добавление виджетов в правый Layout
    rightLayout->addWidget(createPolynomWidget);
    rightLayout->addWidget(changeValueWidget);
    rightLayout->addWidget(calcPolynomWidget);
    rightLayout->addWidget(printPolynomWidget);

    // Добавление левых и правых Layout в главный
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setCentralWidget(centralWidget);
}

Interface::~Interface() {}

void Interface::OnCreatePolynomClicked(){
    changeValueWidget->hide();
    calcPolynomWidget->hide();
    printPolynomWidget->hide();

    createPolynomWidget->show();
}

void Interface::OnChangeValueClicked(){
    createPolynomWidget->hide();
    calcPolynomWidget->hide();
    printPolynomWidget->hide();

    changeValueWidget->show();
}

void Interface::OnCalcPolynomClicked(){
    createPolynomWidget->hide();
    changeValueWidget->hide();
    printPolynomWidget->hide();

    calcPolynomWidget->show();
}

void Interface::OnPrintPolynomClicked(){
    createPolynomWidget->hide();
    changeValueWidget->hide();
    calcPolynomWidget->hide();

    printPolynomWidget->show();
}
