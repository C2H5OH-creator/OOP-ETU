#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Центральный виджет и главный макет
    centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);

    // Левый Layout для радиокнопок
    leftLayout = new QVBoxLayout();

    auto *createPolynom = new QRadioButton("Ввести корни и An полинома", this);
    auto *changeValue = new QRadioButton("Изменить An или любой другой корень", this);
    auto *calcPolynom = new QRadioButton("Вычислить значение полинома в точке", this);
    auto *printPolynom = new QRadioButton("Вывести полином", this);

    // Подключение сигналов
    connect(createPolynom, &QRadioButton::clicked, this, &MainWindow::OnCreatePolynomClicked);
    connect(changeValue, &QRadioButton::clicked, this, &MainWindow::OnChangeValueClicked);
    connect(calcPolynom, &QRadioButton::clicked, this, &MainWindow::OnCalcPolynomClicked);
    connect(printPolynom, &QRadioButton::clicked, this, &MainWindow::OnPrintPolynomClicked);

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
    createLayout->addWidget(new QLineEdit(this));  // Поле ввода для количества корней
    createLayout->addWidget(new QLabel("Введите первый коэффициент An:", this));
    createLayout->addWidget(new QLineEdit(this));  // Поле ввода для An

    // Виджет для изменения значения
    changeValueWidget = new QWidget(this);
    QVBoxLayout *changeLayout = new QVBoxLayout(changeValueWidget);
    changeLayout->addWidget(new QLabel("Введите новый An или корень:", this));
    changeLayout->addWidget(new QLineEdit(this));  // Поле ввода для изменения

    // Виджет для вычисления значения полинома
    calcPolynomWidget = new QWidget(this);
    QVBoxLayout *calcLayout = new QVBoxLayout(calcPolynomWidget);
    calcLayout->addWidget(new QLabel("Введите значение для вычисления:", this));
    calcLayout->addWidget(new QLineEdit(this));  // Поле ввода для вычисления

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

MainWindow::~MainWindow() {}

void MainWindow::OnCreatePolynomClicked(){
    changeValueWidget->hide();
    calcPolynomWidget->hide();
    printPolynomWidget->hide();

    createPolynomWidget->show();
}

void MainWindow::OnChangeValueClicked(){
    createPolynomWidget->hide();
    calcPolynomWidget->hide();
    printPolynomWidget->hide();

    changeValueWidget->show();
}

void MainWindow::OnCalcPolynomClicked(){
    createPolynomWidget->hide();
    changeValueWidget->hide();
    printPolynomWidget->hide();

    calcPolynomWidget->show();
}

void MainWindow::OnPrintPolynomClicked(){
    createPolynomWidget->hide();
    changeValueWidget->hide();
    calcPolynomWidget->hide();

    printPolynomWidget->show();
}
