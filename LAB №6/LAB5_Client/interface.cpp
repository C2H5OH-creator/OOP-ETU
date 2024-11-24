#include "interface.h"

#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QMessageBox>



Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{
    communicator = new UDPCommunicator(this, client_port);
    connect(communicator, &UDPCommunicator::messageReceived, this, &Interface::handleMessage);

    // Центральный виджет и главный макет
    centralWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(centralWidget);

    // Создаём левый и правый макеты
    createLeftLayout();
    createRightComplexLayout();
    createRightDoubleLayout();

    // Создание групп боксов для каждого макета
    QGroupBox *leftGroupBox = new QGroupBox("Настройки");
    leftGroupBox->setLayout(leftLayout);

    QGroupBox *rightGroupBox = new QGroupBox("Параметры полинома");
    rightGroupBox->setLayout(rightLayout);

    // Разделитель между левым и правым макетами
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setFrameShadow(QFrame::Sunken);

    // Добавление групп боксов и разделителя в основной макет
    mainLayout->addWidget(leftGroupBox);
    mainLayout->addWidget(line);  // Добавляем вертикальный разделитель
    mainLayout->addWidget(rightGroupBox);

    // Установка центрального виджета и основного макета
    setCentralWidget(centralWidget);
}


void Interface::createLeftLayout()
{
    leftLayout = new QVBoxLayout();
    leftLayout->setContentsMargins(10, 10, 10, 10);
    leftLayout->setSpacing(10);

    // Группа выбора множества
    QGroupBox *numberSetGroup = new QGroupBox("На каком множестве определён полином?");
    QHBoxLayout *numberSetLayout = new QHBoxLayout();
    complexRadio = new QRadioButton("Комплексные числа");
    complexRadio->setChecked(true); // По умолчанию
    realRadio = new QRadioButton("Вещественные числа");

    numberSetLayout->addWidget(complexRadio);
    numberSetLayout->addWidget(realRadio);
    numberSetGroup->setLayout(numberSetLayout);

    leftLayout->addWidget(numberSetGroup);

    // Разделитель
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    leftLayout->addWidget(line);

    // Группа выбора действия
    QGroupBox *actionGroup = new QGroupBox("Действия с полиномом");
    QVBoxLayout *actionLayout = new QVBoxLayout();
    auto createPolynom = new QRadioButton("Ввести корни и An полинома");
    auto changeValue = new QRadioButton("Изменить An или любой другой корень");
    auto calcPolynom = new QRadioButton("Вычислить значение полинома в точке");
    auto printPolynom = new QRadioButton("Вывести полином");

    connect(complexRadio, &QRadioButton::clicked, this, &Interface::onNumberSetChanged);
    connect(realRadio, &QRadioButton::clicked, this, &Interface::onNumberSetChanged);

    // Подключение сигналов
    connect(createPolynom, &QRadioButton::clicked, this, &Interface::OnCreatePolynomClicked);
    connect(changeValue, &QRadioButton::clicked, this, &Interface::OnChangeValueClicked);
    connect(calcPolynom, &QRadioButton::clicked, this, &Interface::OnCalcPolynomClicked);
    connect(printPolynom, &QRadioButton::clicked, this, &Interface::OnPrintPolynomClicked);

    // Добавление радиокнопок в макет группы
    actionLayout->addWidget(createPolynom);
    actionLayout->addWidget(changeValue);
    actionLayout->addWidget(calcPolynom);
    actionLayout->addWidget(printPolynom);
    actionGroup->setLayout(actionLayout);

    leftLayout->addWidget(actionGroup);
}


// Функция создания правого Layout
void Interface::createRightComplexLayout()
{    
    rightLayout = new QVBoxLayout();
    // Виджет для создания полинома
    createPolynomWidget = new QWidget(this);
    createLayout = new QVBoxLayout(createPolynomWidget);

    createLayout->addWidget(new QLabel("Сколько корней вы хотите?", this));
    rootCountInput = new QLineEdit(this);
    createLayout->addWidget(rootCountInput);

    createLayout->addWidget(new QLabel("Введите коэффициент An (действительная и мнимая части):", this));

    aNInputReal = new QLineEdit(this);
    aNInputReal->setPlaceholderText(QString("Действ. часть An"));

    aNInputImaginary = new QLineEdit(this);
    aNInputImaginary->setPlaceholderText(QString("Мним. часть An"));
    QHBoxLayout *aNLayout = new QHBoxLayout();
    aNLayout->addWidget(aNInputReal);
    aNLayout->addWidget(aNInputImaginary);
    createLayout->addLayout(aNLayout);

    // Заголовок для ввода корней
    rootInputLabel = new QLabel("Введите корни ниже:", this);
    rootInputLabel->hide(); // Скрываем по умолчанию
    createLayout->addWidget(rootInputLabel);

    // Слот для изменения количества корней
    connect(rootCountInput, &QLineEdit::textChanged, this, &Interface::onRootCountChanged);

    // Кнопка подтверждения для создания полинома
    auto confirmCreateButton = new QPushButton("Подтвердить", this);
    connect(confirmCreateButton, &QPushButton::clicked, this, &Interface::onConfirmCreate);
    createLayout->addWidget(confirmCreateButton);

    // Кнопка очистки
    auto clearCreateButton = new QPushButton("Очистить", this);
    connect(clearCreateButton, &QPushButton::clicked, this, &Interface::onClearCreateFields);
    createLayout->addWidget(clearCreateButton);

    //=============================================//

    // Виджет для изменения значения
    changeValueWidget = new QWidget(this);
    QVBoxLayout *changeLayout = new QVBoxLayout(changeValueWidget);

    // Добавление радиокнопок для изменения An или корня
    changeAnButton = new QRadioButton("Изменить An", this);
    changeRootButton = new QRadioButton("Изменить корень по индексу", this);
    changeLayout->addWidget(changeAnButton);
    changeLayout->addWidget(changeRootButton);

    // Поля для ввода
    changeInputAnReal = new QLineEdit(this);
    changeInputAnReal->setPlaceholderText(QString("Действ. часть An"));

    changeInputAnImaginary = new QLineEdit(this);
    changeInputAnImaginary->setPlaceholderText(QString("Мним. часть An"));

    changeInputIndex = new QLineEdit(this);
    changeInputIndex->setPlaceholderText(QString("Индекс"));

    changeInputRootReal = new QLineEdit(this);
    changeInputRootReal->setPlaceholderText(QString("Действ. часть корня"));

    changeInputRootImaginary = new QLineEdit(this);
    changeInputRootImaginary->setPlaceholderText(QString("Мним. часть корня"));


    // Установка валидации для индекса
    changeInputIndex->setValidator(new QIntValidator(0, 100, this)); // Установите пределы по необходимости

    // Подключение сигналов для радиокнопок
    connect(changeAnButton, &QRadioButton::clicked, [this]() {
        changeInputAnReal->show();
        changeInputAnImaginary->show();
        changeInputIndex->hide();
        changeInputRootReal->hide();
        changeInputRootImaginary->hide();
    });
    connect(changeRootButton, &QRadioButton::clicked, [this]() {
        changeInputAnReal->hide();
        changeInputAnImaginary->hide();
        changeInputIndex->show();
        changeInputRootReal->show();
        changeInputRootImaginary->show();
    });

    changeLayout->addWidget(changeInputAnReal);
    changeLayout->addWidget(changeInputAnImaginary);
    changeLayout->addWidget(changeInputIndex);
    changeLayout->addWidget(changeInputRootReal);
    changeLayout->addWidget(changeInputRootImaginary);

    QPushButton *confirmChangeButton = new QPushButton("Подтвердить", this);
    connect(confirmChangeButton, &QPushButton::clicked, this, &Interface::onConfirmChangeButton);
    changeLayout->addWidget(confirmChangeButton);

    // Скрыть поля для ввода
    changeInputAnReal->hide();
    changeInputAnImaginary->hide();
    changeInputIndex->hide();
    changeInputRootReal->hide();
    changeInputRootImaginary->hide();

    //=============================================//

    // Виджет для вычисления значения полинома
    calcPolynomWidget = new QWidget(this);
    QVBoxLayout *calcLayout = new QVBoxLayout(calcPolynomWidget);

    // Заголовок для ввода значения
    calcLayout->addWidget(new QLabel("Введите значение для вычисления:", this));

    // Поле для ввода действительной части x
    calcValueReal = new QLineEdit(this);
    calcValueReal->setPlaceholderText(QString("Действ. часть x"));
    calcLayout->addWidget(calcValueReal);

    // Поле для ввода мнимой части x
    calcValueImaginary = new QLineEdit(this);
    calcValueImaginary->setPlaceholderText(QString("Мним. часть x"));
    calcLayout->addWidget(calcValueImaginary);

    QPushButton *confirmCalcButton = new QPushButton("Подтвердить", this);
    connect(confirmCalcButton, &QPushButton::clicked, [this]() {
        // Данные для создания JSON
        QString sender = "Client";
        int action = CALCULATE_VALUE_POLYNOMIAL_AT_POINT;

        // Пустой массив корней для текущего примера
        QList<QVariant> roots;

        // Значения для поля evaluate_value
        double evaluateReal = calcValueReal->text().toDouble();
        double evaluateImaginary = std::abs(calcValueImaginary->text().toDouble());

        // Пустой ответ сервера
        QString serverResponse = "";

        // Создание JSON строки с использованием новой функции
        QString jsonString = communicator->createJsonMessage(1,sender, action, roots, serverResponse, evaluateReal, evaluateImaginary,"","");

        // Отправка JSON строки
        communicator->sendData(QHostAddress("0.0.0.0"), server_port, jsonString);
    });

    calcLayout->addWidget(confirmCalcButton);

    //=============================================//

    // Виджет для вывода полинома
    printPolynomWidget = new QWidget(this);
    QVBoxLayout *printLayout = new QVBoxLayout(printPolynomWidget);

    printLayout->addWidget(new QLabel("Каноническая форма:", this));
    canonicalFormLabel = new QLabel(this);
    printLayout->addWidget(canonicalFormLabel);

    printLayout->addWidget(new QLabel("Не каноническая форма:", this));
    nonCanonicalFormLabel = new QLabel(this);
    printLayout->addWidget(nonCanonicalFormLabel);

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
}


void Interface::createRightDoubleLayout(){
    // Виджет для создания полинома
    createDoublePolynomWidget = new QWidget(this);
    createDoubleLayout = new QVBoxLayout(createDoublePolynomWidget);

    createDoubleLayout->addWidget(new QLabel("Сколько корней вы хотите?", this));
    doubleRootCountInput = new QLineEdit(this);
    createDoubleLayout->addWidget(doubleRootCountInput);

    createDoubleLayout->addWidget(new QLabel("Введите коэффициент An:", this));

    aNInput = new QLineEdit(this);
    aNInput->setPlaceholderText(QString("Коэфф. An"));

    QHBoxLayout *aNLayout = new QHBoxLayout();
    aNLayout->addWidget(aNInput);
    createDoubleLayout->addLayout(aNLayout);

    // Заголовок для ввода корней
    rootInputLabel = new QLabel("Введите корни ниже:", this);
    rootInputLabel->hide(); // Скрываем по умолчанию
    createDoubleLayout->addWidget(rootInputLabel);


    // Слот для изменения количества корней
    connect(doubleRootCountInput, &QLineEdit::textChanged, this, &Interface::onRootCountChanged);

    // Кнопка подтверждения для создания полинома
    auto confirmCreateButton = new QPushButton("Подтвердить", this);
    connect(confirmCreateButton, &QPushButton::clicked, this, &Interface::onConfirmCreate);
    createDoubleLayout->addWidget(confirmCreateButton);

    // Кнопка очистки
    auto clearCreateButton = new QPushButton("Очистить", this);
    connect(clearCreateButton, &QPushButton::clicked, this, &Interface::onClearCreateFields);
    createDoubleLayout->addWidget(clearCreateButton);

    //=============================================//

    // Виджет для изменения значения
    changeDoubleValueWidget = new QWidget(this);
    QVBoxLayout *changeLayout = new QVBoxLayout(changeDoubleValueWidget);

    // Добавление радиокнопок для изменения An или корня
    changeAnButton = new QRadioButton("Изменить An", this);
    changeRootButton = new QRadioButton("Изменить корень по индексу", this);
    changeLayout->addWidget(changeAnButton);
    changeLayout->addWidget(changeRootButton);

    // Поля для ввода
    changeInputAn = new QLineEdit(this);
    changeInputAn->setPlaceholderText(QString("Коэфф. An"));

    changeRealInputIndex = new QLineEdit(this);
    changeRealInputIndex->setPlaceholderText(QString("Индекс"));

    changeInputRoot = new QLineEdit(this);
    changeInputRoot->setPlaceholderText(QString("Корень"));

    // Установка валидации для индекса
    changeRealInputIndex->setValidator(new QIntValidator(0, 100, this)); // Установите пределы по необходимости

    // Подключение сигналов для радиокнопок
    connect(changeAnButton, &QRadioButton::clicked, [this]() {
        changeInputAn->show();
        changeRealInputIndex->hide();
        changeInputRoot->hide();
    });
    connect(changeRootButton, &QRadioButton::clicked, [this]() {
        changeInputAn->hide();
        changeRealInputIndex->show();
        changeInputRoot->show();
    });

    changeLayout->addWidget(changeInputAn);
    changeLayout->addWidget(changeRealInputIndex);
    changeLayout->addWidget(changeInputRoot);

    QPushButton *confirmChangeButton = new QPushButton("Подтвердить", this);
    connect(confirmChangeButton, &QPushButton::clicked, this, &Interface::onConfirmChangeButton);
    changeLayout->addWidget(confirmChangeButton);

    // Скрыть поля для ввода
    changeInputAn->hide();
    changeInputAnImaginary->hide();
    changeInputRoot->hide();

    //=============================================//

    // Виджет для вычисления значения полинома
    calcDoublePolynomWidget = new QWidget(this);
    QVBoxLayout *calcLayout = new QVBoxLayout(calcDoublePolynomWidget);

    // Заголовок для ввода значения
    calcLayout->addWidget(new QLabel("Введите значение для вычисления:", this));

    // Поле для ввода действительной части x
    calcDoubleValueReal = new QLineEdit(this);
    calcDoubleValueReal->setPlaceholderText(QString("x"));
    calcLayout->addWidget(calcDoubleValueReal);

    QPushButton *confirmCalcButton = new QPushButton("Подтвердить", this);
    connect(confirmCalcButton, &QPushButton::clicked, [this]() {
        // Данные для создания JSON
        QString sender = "Client";
        int action = CALCULATE_VALUE_POLYNOMIAL_AT_POINT;

        // Пустой массив корней для текущего примера
        QList<QVariant> roots;

        // Значения для поля evaluate_value
        double evaluateReal = calcDoubleValueReal->text().toDouble();
        double evaluateImaginary = 0;

        // Пустой ответ сервера
        QString serverResponse = "";

        // Создание JSON строки с использованием новой функции
        QString jsonString = communicator->createJsonMessage(1,sender, action, roots, serverResponse, evaluateReal, evaluateImaginary,"","");

        // Отправка JSON строки
        communicator->sendData(QHostAddress("0.0.0.0"), server_port, jsonString);
    });

    calcLayout->addWidget(confirmCalcButton);

    //=============================================//

    // Виджет для вывода полинома
    printPolynomWidget = new QWidget(this);
    QVBoxLayout *printLayout = new QVBoxLayout(printPolynomWidget);

    printLayout->addWidget(new QLabel("Каноническая форма:", this));
    canonicalFormLabel = new QLabel(this);
    printLayout->addWidget(canonicalFormLabel);

    printLayout->addWidget(new QLabel("Не каноническая форма:", this));
    nonCanonicalFormLabel = new QLabel(this);
    printLayout->addWidget(nonCanonicalFormLabel);

    // Скрытие всех виджетов по умолчанию
    createDoublePolynomWidget->hide();
    changeDoubleValueWidget->hide();
    calcDoublePolynomWidget->hide();
    printPolynomWidget->hide();

    // Добавление виджетов в правый Layout
    rightLayout->addWidget(createDoublePolynomWidget);
    rightLayout->addWidget(changeDoubleValueWidget);
    rightLayout->addWidget(calcDoublePolynomWidget);
    rightLayout->addWidget(printPolynomWidget);

}

Interface::~Interface() {}

void Interface::OnCreatePolynomClicked() {
    if(isComplex){

        changeDoubleValueWidget->hide();
        calcDoublePolynomWidget->hide();
        printPolynomWidget->hide();

        changeValueWidget->hide();
        calcPolynomWidget->hide();
        printPolynomWidget->hide();
        createPolynomWidget->show();
    } else {

        changeValueWidget->hide();
        calcPolynomWidget->hide();
        printPolynomWidget->hide();

        changeDoubleValueWidget->hide();
        calcDoublePolynomWidget->hide();
        printPolynomWidget->hide();
        createDoublePolynomWidget->show();
    }

}

void Interface::OnChangeValueClicked() {   
    if(isComplex){
        calcDoublePolynomWidget->hide();
        printPolynomWidget->hide();
        createDoublePolynomWidget->hide();


        calcPolynomWidget->hide();
        printPolynomWidget->hide();
        createPolynomWidget->hide();
        changeValueWidget->show();
    } else {

        calcPolynomWidget->hide();
        printPolynomWidget->hide();
        createPolynomWidget->hide();

        calcDoublePolynomWidget->hide();
        printPolynomWidget->hide();
        changeDoubleValueWidget->show();
        createDoublePolynomWidget->hide();
    }
}

void Interface::OnCalcPolynomClicked() {
    if(isComplex){
        changeDoubleValueWidget->hide();
        printPolynomWidget->hide();
        createDoublePolynomWidget->hide();

        changeValueWidget->hide();
        printPolynomWidget->hide();
        createPolynomWidget->hide();
        calcPolynomWidget->show();
    } else {

        changeValueWidget->hide();
        printPolynomWidget->hide();
        createPolynomWidget->hide();

        changeDoubleValueWidget->hide();
        printPolynomWidget->hide();
        createDoublePolynomWidget->hide();
        calcDoublePolynomWidget->show();
    }
}

void Interface::OnPrintPolynomClicked() {
    if(isComplex){
        changeDoubleValueWidget->hide();
        calcDoublePolynomWidget->hide();
        createDoublePolynomWidget->hide();

        changeValueWidget->hide();
        calcPolynomWidget->hide();
        createPolynomWidget->hide();
        printPolynomWidget->show();
    } else {
        changeValueWidget->hide();
        calcPolynomWidget->hide();
        createPolynomWidget->hide();

        changeDoubleValueWidget->hide();
        calcDoublePolynomWidget->hide();
        createDoublePolynomWidget->hide();
        printPolynomWidget->show();
    }

    QList<QVariant> emptyList;
    QString jsonCanonForm;

    jsonCanonForm = communicator->createJsonMessage(!isComplex,"client",
                                                            GET_POLYNOM_FORMS, emptyList,"" ,
                                                            0,0,"","");

    communicator->sendData(QHostAddress("0.0.0.0"), server_port, jsonCanonForm);

}

void Interface::onNumberSetChanged() {
    // Определяем, какое множество выбрано
    if (realRadio->isChecked()) {
        isComplex = false;
    } else {
        isComplex = true;
    }
}

void Interface::onRootCountChanged(const QString &text) {
    int rootCount = text.toInt();
    if (isComplex){
        // Очистить предыдущие поля корней
        for (auto &rootPair : rootInputs) {
            delete rootPair.first;
            delete rootPair.second;
        }
        rootInputs.clear();

        // Устанавливаем минимальный размер окна при удалении полей
        if (rootCount == 0 || text.isEmpty()) {
            rootInputLabel->hide();
            setMinimumSize(QSize(200, 150)); // Минимальный размер окна
        } else {
            rootInputLabel->show();

        }

        // Добавить поля для корней с подписью
        for (int i = 0; i < rootCount; ++i) {
            QLineEdit *realPart = new QLineEdit(this);
            realPart->setPlaceholderText(QString("Действ. часть %1-го корня").arg(i + 1));
            QLineEdit *imaginaryPart = new QLineEdit(this);
            imaginaryPart->setPlaceholderText(QString("Мним. часть %1-го корня").arg(i + 1));

            QHBoxLayout *rootLayout = new QHBoxLayout();
            rootLayout->addWidget(realPart);
            rootLayout->addWidget(imaginaryPart);

            rootInputLayouts.append(rootLayout);
            rootInputs.push_back(qMakePair(realPart, imaginaryPart));
            createLayout->addLayout(rootLayout);
        }

        // Установка минимального размера окна в зависимости от количества полей
        adjustSize();
    }
    else {
        // Очистить предыдущие поля корней
        for (auto &root: doubleRootInputs) {
            delete root;
        }
        doubleRootInputs.clear();

        // Устанавливаем минимальный размер окна при удалении полей
        if (rootCount == 0 || text.isEmpty()) {
            rootInputLabel->hide();
            setMinimumSize(QSize(200, 150)); // Минимальный размер окна
        } else {
            rootInputLabel->show();

        }

        for (int i = 0; i < rootCount; ++i) {
            QLineEdit *root = new QLineEdit(this);
            root->setPlaceholderText(QString("%1-й корень").arg(i + 1));

            QHBoxLayout *doubleRootLayout = new QHBoxLayout();
            doubleRootLayout->addWidget(root);

            rootInputLayouts.append(doubleRootLayout);
            doubleRootInputs.push_back(root);
            createDoubleLayout->addLayout(doubleRootLayout);
        }
        // Установка минимального размера окна в зависимости от количества полей
        adjustSize();
    }

}

void Interface::onConfirmCreate() {
    // Данные для создания JSON
    QString sender = "Client";
    int action = CREATE_POLYNOM;

    // Собираем массив корней
    QList<QVariant> roots;

    // Добавляем коэффициент an
    QVariantMap anObject;
    anObject["real"] = (isComplex)?(aNInputReal->text().toDouble()) : (aNInput->text().toDouble());
    anObject["imag"] = (isComplex)?(aNInputImaginary->text().toDouble()) : (0);
    roots.append(anObject);

    if(isComplex){
        // Добавляем корни
        for (const auto &rootPair : rootInputs) {
            QVariantMap rootObject;
            rootObject["real"] = rootPair.first->text().toDouble();
            rootObject["imag"] = rootPair.second->text().toDouble();
            roots.append(rootObject);
        }
    } else if (isComplex == false) {
        // Добавляем корни
        for (const auto &root : doubleRootInputs) {
            QVariantMap rootObject;
            rootObject["real"] = root->text().toDouble();
            rootObject["imag"] = 0;
            roots.append(rootObject);
        }
    }

    // Пустой ответ сервера и значение evaluate_value
    QString serverResponse = "";
    double evaluateReal = 0.0;
    double evaluateImaginary = 0.0;

    // Создание JSON строки с использованием новой функции
    QString jsonString = communicator->createJsonMessage(((isComplex) ? (0) : (1)),sender, action, roots, serverResponse, evaluateReal, evaluateImaginary,"","");

    // Отправка JSON строки через ваш класс Communicator
    communicator->sendData(QHostAddress("0.0.0.0"), server_port, jsonString);

    QMessageBox::information(this, "Подтверждено", "Полином успешно создан!");
}

void Interface::onClearCreateFields() {
    if(isComplex){
        // Очистка полей ввода
        rootCountInput->clear();
        aNInputReal->clear();
        aNInputImaginary->clear();

        for (auto &rootPair : rootInputs) {
            rootPair.first->clear();
            rootPair.second->clear();
        }

        // Скрыть метку для корней и очистить массив
        rootInputLabel->hide();
        for (auto &rootPair : rootInputs) {
            delete rootPair.first;
            delete rootPair.second;
        }
        rootInputs.clear();
    } else {
        // Очистка полей ввода
        doubleRootCountInput->clear();
        aNInput->clear();

        for (auto &root : doubleRootInputs) {
            root->clear();
        }

        // Скрыть метку для корней и очистить массив
        rootInputLabel->hide();
        for (auto &root : doubleRootInputs) {
            delete root;
        }
        doubleRootInputs.clear();

    }

}


void Interface::onConfirmChangeButton(){
    if(isComplex){
        if (changeRootButton->isChecked()) {
            // Собираем массив
            QList<QVariant> roots;
            QVariantMap an;
            an["real"] = 0;
            an["imag"] = 0;
            roots.append(an);

            QVariantMap index;
            index["real"] = changeInputIndex->text().toUInt();
            index["imag"] = 0;
            roots.append(index);

            QVariantMap rootObject;
            rootObject["real"] = changeInputRootReal->text().toDouble();
            rootObject["imag"] = changeInputRootImaginary->text().toDouble();
            roots.append(rootObject);

            QString change_root = communicator->createJsonMessage(0,"client",CHANGE_ROOT,roots,"",0,0,"","");
            communicator->sendData(QHostAddress("0.0.0.0"), server_port, change_root);

            QMessageBox::information(this, "Подтверждено", "Корень успешно изменён!");
        } else {
            QList<QVariant> roots;

            // Добавляем коэффициент an
            QVariantMap anObject;
            anObject["real"] = changeInputAnReal->text().toDouble();
            anObject["imag"] = changeInputAnImaginary->text().toDouble();
            roots.append(anObject);

            QString change_root = communicator->createJsonMessage(0,"client",CHANGE_AN,roots,"",0,0,"","");
            communicator->sendData(QHostAddress("0.0.0.0"), server_port, change_root);

            QMessageBox::information(this, "Подтверждено", "An успешно изменён!");
        }
    } else {
        if (changeRootButton->isChecked()) {
            // Собираем массив
            QList<QVariant> roots;
            QVariantMap an;
            an["real"] = 0;
            an["imag"] = 0;
            roots.append(an);

            QVariantMap index;
            index["real"] = changeInputIndex->text().toUInt();
            index["imag"] = 0;
            roots.append(index);

            QVariantMap rootObject;
            rootObject["real"] = changeInputRoot->text().toDouble();
            rootObject["imag"] = 0;
            roots.append(rootObject);

            QString change_root = communicator->createJsonMessage(1,"client",CHANGE_ROOT,roots,"",0,0,"","");
            communicator->sendData(QHostAddress("0.0.0.0"), server_port, change_root);

            QMessageBox::information(this, "Подтверждено", "Корень успешно изменён!");
        } else {
            QList<QVariant> roots;

            // Добавляем коэффициент an
            QVariantMap anObject;
            anObject["real"] = changeInputAn->text().toDouble();
            anObject["imag"] = 0;
            roots.append(anObject);

            QString change_root = communicator->createJsonMessage(1,"client",CHANGE_AN,roots,"",0,0,"","");
            communicator->sendData(QHostAddress("0.0.0.0"), server_port, change_root);

            QMessageBox::information(this, "Подтверждено", "An успешно изменён!");
        }

    }

}

void Interface::handleMessage(const QString &message){
    qDebug() << "Клиент получил сообщение: " + message;

    QList<QVariant> emptyList;
    // Разбор JSON строки
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());

    // Проверка валидности JSON
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        qDebug() << "Ошибка: Получено некорректное сообщение.";
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();

    // Извлечение значения response (которое является строкой, содержащей JSON)
    QString responseString = jsonObject.value("response").toString();
    qDebug() << "Ответ из вложенного JSON: " << responseString;

    // Теперь нужно распарсить строку response как JSON
    QJsonDocument responseDoc = QJsonDocument::fromJson(responseString.toUtf8());

    // Проверка валидности вложенного JSON
    if (responseDoc.isNull() || !responseDoc.isObject()) {
        qDebug() << "Ошибка: Вложенный JSON некорректен.";
        return;
    }

    QJsonObject responseObject = responseDoc.object();

    // Извлечение значений из вложенного JSON
    int action = responseObject.value("action").toInt();
    QString sender = responseObject.value("sender").toString();
    qDebug() << "Сервер будет выполнять такое действие: " << action;
    qDebug() << "Отправитель: " << sender;

    QString serverResponse = responseObject.value("server_response").toString();
    qDebug() << "Ответ сервера: " << serverResponse;

    // Обработка action
    switch (action) {
    case CREATE_POLYNOM:  // Например, для действия создания полинома
        canonicalFormLabel->setText(responseObject.value("canon_form").toString());
        nonCanonicalFormLabel->setText(responseObject.value("non_canon_form").toString());
        break;
    case GET_POLYNOM_FORMS:  // Например, для действия создания полинома
        canonicalFormLabel->setText(responseObject.value("canon_form").toString());
        nonCanonicalFormLabel->setText(responseObject.value("non_canon_form").toString());
        break;
    case CALCULATE_VALUE_POLYNOMIAL_AT_POINT:  // Например, для действия создания полинома
        QMessageBox::information(this, "Результат", QString("Значение полинома: %1").arg(serverResponse));
        break;
    case CHANGE_AN:  // Например, для действия создания полинома
        canonicalFormLabel->setText(responseObject.value("canon_form").toString());
        nonCanonicalFormLabel->setText(responseObject.value("non_canon_form").toString());
        break;
    case CHANGE_ROOT:  // Например, для действия создания полинома
        canonicalFormLabel->setText(responseObject.value("canon_form").toString());
        nonCanonicalFormLabel->setText(responseObject.value("non_canon_form").toString());
        break;
    default:
        QMessageBox::warning(this, "Предупреждение", "Неизвестное действие.");
        break;
    }

}

