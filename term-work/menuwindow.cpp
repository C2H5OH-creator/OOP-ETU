#include "menuwindow.h"

MenuWindow::MenuWindow(QWidget *parent) : QWidget(parent){
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Приветственное сообщение
    QLabel *messageLabel = new QLabel("Добро пожаловать в игру!", this);
    messageLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(messageLabel);

    // Радио-кнопки
    QRadioButton *localGameRadio = new QRadioButton("Играть локально", this);
    QRadioButton *createGameRadio = new QRadioButton("Создать игру", this);
    QRadioButton *joinGameRadio = new QRadioButton("Подключиться к игре", this);

    mainLayout->addWidget(localGameRadio);
    mainLayout->addWidget(createGameRadio);
    mainLayout->addWidget(joinGameRadio);

    // Поле для ввода размера поля (будет использоваться для обоих режимов)
    QLineEdit *fieldSizeInput = new QLineEdit(this);
    fieldSizeInput->setPlaceholderText("Введите размер поля...");
    mainLayout->addWidget(fieldSizeInput);

    // Поле для ввода названия игры (показывается только при создании игры)
    QLineEdit *gameNameInput = new QLineEdit(this);
    gameNameInput->setPlaceholderText("Введите название игры...");
    gameNameInput->setVisible(false);  // Скрываем по умолчанию
    mainLayout->addWidget(gameNameInput);

    // Список доступных хостов (заглушка)
    QListView *hostListView = new QListView(this);
    QStringListModel *model = new QStringListModel(this);
    model->setStringList({"Заглушка: хост 1", "Заглушка: хост 2"});
    hostListView->setModel(model);
    hostListView->setVisible(false); // Скрываем, пока не выбрано "Подключиться к игре"
    mainLayout->addWidget(hostListView);

    // Кнопки внизу
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *startButton = new QPushButton("Начать игру", this);
    QPushButton *exitButton = new QPushButton("Выход", this);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(exitButton);
    mainLayout->addLayout(buttonLayout);

    // Логика: если выбрано "Подключиться к игре", показываем список хостов
    connect(joinGameRadio, &QRadioButton::toggled, [hostListView, fieldSizeInput, gameNameInput](bool checked) {
        hostListView->setVisible(checked);
        fieldSizeInput->setVisible(!checked);  // Поле для размера скрывается, если подключаемся к игре
        gameNameInput->setVisible(false);       // Скрываем поле для названия игры
    });

    // Логика: если выбрано "Создать игру", показываем поле для названия игры и размера
    connect(createGameRadio, &QRadioButton::toggled, [fieldSizeInput, gameNameInput]() {
        fieldSizeInput->setVisible(true);
        gameNameInput->setVisible(true);
    });

    // Логика: если выбрано "Играть локально", показываем оба поля
    connect(localGameRadio, &QRadioButton::toggled, [fieldSizeInput, gameNameInput]() {
        fieldSizeInput->setVisible(true);
        gameNameInput->setVisible(false);  // Поле для названия скрывается
    });

    localGameRadio->setChecked(true); // Устанавливаем начальный выбор

    // Подключение кнопки "Начать игру"
    connect(startButton, &QPushButton::clicked, this, [this, localGameRadio, createGameRadio, joinGameRadio, fieldSizeInput, gameNameInput]() {
        bool isLocalGame = localGameRadio->isChecked();
        bool isCreateGame = createGameRadio->isChecked();

        int fieldSize = fieldSizeInput->text().toInt();
        if (fieldSize <= 0) {
            QMessageBox::warning(this, "Ошибка", "Размер поля должен быть больше 0");
            return;
        }

        QString gameName;
        if (isCreateGame) {
            gameName = gameNameInput->text();
            if (gameName.isEmpty()) {
                QMessageBox::warning(this, "Ошибка", "Название игры не может быть пустым");
                return;
            }
        }

        if (isLocalGame) {
            // Локальная игра, открываем два игровых окна с введённым размером поля
            GameWindow *gameWindow1 = new GameWindow("Локальная игра (Игрок 1)", fieldSize);
            gameWindow1->setWindowTitle("Игрок 1");
            gameWindow1->resize(300, 200);
            gameWindow1->show();

            GameWindow *gameWindow2 = new GameWindow("Локальная игра (Игрок 2)", fieldSize);
            gameWindow2->setWindowTitle("Игрок 2");
            gameWindow2->resize(300, 200);
            gameWindow2->show();
        }
        else if (isCreateGame) {
            // Создание игры с указанным названием
            GameWindow *gameWindow = new GameWindow("Игра: " + gameName, fieldSize);
            gameWindow->resize(300, 200);
            gameWindow->show();
        }
        else if (joinGameRadio->isChecked()) {
            // Подключение к игре (пока заглушка)
            QMessageBox::information(this, "Подключение", "Попытка подключения к хосту (заглушка)");
        }
    });

    // Подключение кнопки "Выход"
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    setLayout(mainLayout);
}
