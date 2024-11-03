#include "interface.h"

#include <QHBoxLayout>
#include <QDoubleValidator>
#include <QMessageBox>


Interface::Interface(QWidget *parent)
    : QMainWindow(parent)
{
    connect(communicator, &UDPCommunicator::messageReceived, this, &Interface::handleMessage);

    //=============================================//

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

    //=============================================//

    // Добавление радиокнопок в левый Layout
    leftLayout->addWidget(createPolynom);
    leftLayout->addWidget(changeValue);
    leftLayout->addWidget(calcPolynom);
    leftLayout->addWidget(printPolynom);

    // Правый Layout для отображения элементов в зависимости от выбора
    QVBoxLayout *rightLayout = new QVBoxLayout();

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
        //number result = polynom.evaluateAtPoint(value);

        // Создаем JSON объект
        QJsonObject jsonObject;
        jsonObject["sender"] = "Client";  // Укажите отправителя
        jsonObject["action"] = CALCULATE_VALUE_POLYNOMIAL_AT_POINT;
        jsonObject["roots"] = "[]";
        QJsonArray value;

        QJsonObject rootObject;
        rootObject["real"] = calcValueReal->text().toDouble();
        rootObject["imag"] = std::abs(calcValueImaginary->text().toDouble());
        value.append(rootObject);

        jsonObject["server_response"] = "";
        jsonObject["evaluate_value"] = "";

        // Преобразуем объект в JSON строку
        QJsonDocument jsonDoc(jsonObject);
        QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

        // Здесь вы можете отправить jsonString через ваш класс Communicator
        communicator->sendData(QHostAddress("0.0.0.0"),6004,jsonString);

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

    // Добавление левых и правых Layout в главный
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setCentralWidget(centralWidget);
}

Interface::~Interface() {}

void Interface::OnCreatePolynomClicked() {
    changeValueWidget->hide();
    calcPolynomWidget->hide();
    printPolynomWidget->hide();
    createPolynomWidget->show();
}

void Interface::OnChangeValueClicked() {
    createPolynomWidget->hide();
    calcPolynomWidget->hide();
    printPolynomWidget->hide();
    changeValueWidget->show();
}

void Interface::OnCalcPolynomClicked() {
    createPolynomWidget->hide();
    changeValueWidget->hide();
    printPolynomWidget->hide();
    calcPolynomWidget->show();
}

void Interface::OnPrintPolynomClicked() {
    createPolynomWidget->hide();
    changeValueWidget->hide();
    calcPolynomWidget->hide();
    printPolynomWidget->show();

    QJsonObject jsonObject1;
    jsonObject1["sender"] = "Client";
    jsonObject1["action"] = DEFAULT_CANON_FORM;
    QJsonDocument jsonDoc1(jsonObject1);
    QString jsonString1 = jsonDoc1.toJson(QJsonDocument::Compact);

    communicator->sendData(QHostAddress("0.0.0.0"), port, jsonString1);

    QJsonObject jsonObject;
    jsonObject["sender"] = "Client";
    jsonObject["action"] = DEFAULT_NON_CANON_FORM;
    QJsonDocument jsonDoc(jsonObject);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    communicator->sendData(QHostAddress("0.0.0.0"), port, jsonString);
}

void Interface::onRootCountChanged(const QString &text) {
    int rootCount = text.toInt();

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

void Interface::onConfirmCreate() {
    // Создаем JSON объект
    QJsonObject jsonObject;
    jsonObject["sender"] = "Client";  // Укажите отправителя
    jsonObject["action"] = CREATE_POLYNOM;          // Задайте действие, например, 1 для создания полинома

    // Создаем массив для корней
    QJsonArray rootsArray;

    // Добавляем коэффициент ан в массив корней
    QJsonObject anObject;
    anObject["real"] = aNInputReal->text().toDouble(); // Предполагается, что есть метод real()
    anObject["imag"] = aNInputImaginary->text().toDouble();  // Предполагается, что есть метод imag()
    rootsArray.append(anObject);

    // Добавляем корни в массив
    for (const auto &rootPair : rootInputs) {
        QJsonObject rootObject;
        rootObject["real"] = rootPair.first->text().toDouble();
        rootObject["imag"] = rootPair.second->text().toDouble();
        rootsArray.append(rootObject);
    }

    jsonObject["roots"] = rootsArray;
    jsonObject["server_response"] = "";
    jsonObject["evaluate_value"] = "";

    // Преобразуем объект в JSON строку
    QJsonDocument jsonDoc(jsonObject);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);

    // Здесь вы можете отправить jsonString через ваш класс Communicator
    communicator->sendData(QHostAddress("0.0.0.0"),6004,jsonString);

    QMessageBox::information(this, "Подтверждено", "Полином успешно создан!");
}

void Interface::onClearCreateFields() {
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
}


void Interface::onConfirmChangeButton(){
    QJsonObject jsonObject;
    jsonObject["sender"] = "Client";

    if (changeRootButton->isChecked()) {
        jsonObject["action"] = CHANGE_ROOT;
        int index = changeInputIndex->text().toUInt();  // Индекс корня

        QJsonObject evaluateValueObject;
        evaluateValueObject["real"] = changeInputRootReal->text().toDouble();
        evaluateValueObject["imag"] = changeInputRootImaginary->text().toDouble();

        jsonObject["evaluate_value"] = evaluateValueObject;
        jsonObject["root_index"] = index;

            QMessageBox::information(this, "Подтверждено", "Корень успешно изменён!");
    } else {
        jsonObject["action"] = CHANGE_AN;
        QJsonObject evaluateValueObject;
        evaluateValueObject["real"] = changeInputAnReal->text().toDouble();   // Записываем действительную часть
        evaluateValueObject["imag"] = changeInputAnImaginary->text().toDouble();   // Записываем мнимую часть
        jsonObject["evaluate_value"] = evaluateValueObject;

        QMessageBox::information(this, "Подтверждено", "An успешно изменён!");
    }

    // Создание JSON документа
    QJsonDocument jsonDoc(jsonObject);
    QString jsonString = jsonDoc.toJson(QJsonDocument::Compact);
    communicator->sendData(QHostAddress("0.0.0.0"), port,jsonString);

}

void Interface::handleMessage(const QString &message){
    // Разбор JSON строки
    QJsonDocument jsonDoc = QJsonDocument::fromJson(message.toUtf8());

    // Проверяем, валиден ли JSON
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        QMessageBox::warning(this, "Ошибка", "Получено некорректное сообщение.");
        return;
    }

    QJsonObject jsonObject = jsonDoc.object();

    // Извлечение значений
    QString sender = jsonObject.value("sender").toString();
    int action = jsonObject.value("action").toInt();
    QString serverResponse = jsonObject.value("server_response").toString();

    // Обработка action
    switch (action) {
    case CREATE_POLYNOM:  // Например, для действия создания полинома
        canonicalFormLabel->setText(jsonObject.value("canon_form").toString());
        nonCanonicalFormLabel->setText(jsonObject.value("non_canon_form").toString());
        break;
    case DEFAULT_CANON_FORM:  // Например, для действия создания полинома
       canonicalFormLabel->setText(serverResponse);
        break;
    case DEFAULT_NON_CANON_FORM:  // Например, для действия создания полинома
        nonCanonicalFormLabel->setText(serverResponse);
        break;
    case CALCULATE_VALUE_POLYNOMIAL_AT_POINT:  // Например, для действия создания полинома
        QMessageBox::information(this, "Результат", QString("Значение полинома: %1").arg(serverResponse));
        break;
    default:
        QMessageBox::warning(this, "Предупреждение", "Неизвестное действие.");
        break;
    }

}

