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
    fieldSizeInput = new QLineEdit(this);
    fieldSizeInput->setPlaceholderText("Введите размер поля...");
    mainLayout->addWidget(fieldSizeInput);

    // Поле для ввода названия игры (показывается только при создании игры)
    gameNameInput = new QLineEdit(this);
    gameNameInput->setPlaceholderText("Введите название игры...");
    gameNameInput->setVisible(false);  // Скрываем по умолчанию
    mainLayout->addWidget(gameNameInput);

    // Поля для ввода IP и порта (только для "Создать игру")
    ipInput = new QLineEdit(this);
    ipInput->setPlaceholderText("Введите IP-адрес...");
    ipInput->setVisible(false);  // Скрыто по умолчанию
    mainLayout->addWidget(ipInput);

    portInput = new QLineEdit(this);
    portInput->setPlaceholderText("Введите порт...");
    portInput->setVisible(false);  // Скрыто по умолчанию
    mainLayout->addWidget(portInput);

    niknameInput = new QLineEdit(this);
    niknameInput->setPlaceholderText("Введите ваше имя...");
    niknameInput->setVisible(false);  // Скрыто по умолчанию
    mainLayout->addWidget(niknameInput);

    // Кнопки внизу
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    QPushButton *startButton = new QPushButton("Начать игру", this);
    QPushButton *exitButton = new QPushButton("Выход", this);
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(exitButton);
    mainLayout->addLayout(buttonLayout);

    // Логика отображения элементов интерфейса
    connect(joinGameRadio, &QRadioButton::toggled, [this]() {
        this->fieldSizeInput->setVisible(false);
        this->gameNameInput->setVisible(false);
        this->niknameInput->setVisible(true);
        this->ipInput->setVisible(true);  // Показываем IP-адрес
        this->portInput->setVisible(true); // Показываем порт
    });

    connect(createGameRadio, &QRadioButton::toggled, [this]() {
        this->fieldSizeInput->setVisible(true);
        this->gameNameInput->setVisible(true);
        this->niknameInput->setVisible(true);
        this->ipInput->setVisible(true);  // Показываем IP-адрес
        this->portInput->setVisible(true); // Показываем порт
    });

    connect(localGameRadio, &QRadioButton::toggled, [this]() {
        this->fieldSizeInput->setVisible(true);
        this->gameNameInput->setVisible(false);  // Поле для названия игры скрывается
        this->ipInput->setVisible(false);        // IP-адрес скрывается
        this->portInput->setVisible(false);      // Порт скрывается
    });

    // Начальный выбор
    localGameRadio->setChecked(true);

    // Подключение кнопки "Начать игру"
    connect(startButton, &QPushButton::clicked, this, [this, localGameRadio, createGameRadio, joinGameRadio]() {
        bool isLocalGame = localGameRadio->isChecked();
        bool isCreateGame = createGameRadio->isChecked();
        bool isJoinGame = joinGameRadio->isChecked();

        int fieldSize = this->fieldSizeInput->text().toInt();
        if(!isJoinGame){
            if (fieldSize < 3) {
                QMessageBox::warning(this, "Ошибка", "Размер поля должен быть больше 3");
                return;
            }
        }


        QString gameName;
        if (isCreateGame) {
            gameName = this->gameNameInput->text();
            if (gameName.isEmpty()) {
                QMessageBox::warning(this, "Ошибка", "Название игры не может быть пустым");
                return;
            }
        }

        if (isLocalGame) {
            // Локальная игра, открываем два игровых окна с введённым размером поля
            qint16 port = 4000;
            GameWindow *gameWindow1 = new GameWindow(
                                        "Локальная игра",
                                        "Игрок 1",
                                        fieldSize, port, true);

            gameWindow1->setWindowTitle("Игрок 1");
            gameWindow1->resize(300, 200);
            gameWindow1->show();

            GameWindow *gameWindow2 = new GameWindow(
                                        "Локальная",
                                        "Игрок 2",
                                        fieldSize,
                                        port, false);

            gameWindow2->setWindowTitle("Игрок 2");
            gameWindow2->resize(300, 200);
            gameWindow2->show();
        }
        else if (isCreateGame) {
            QString ip = ipInput->text();
            qint16 port = portInput->text().toInt();
            // Создание игры с указанным названием
            GameWindow *gameWindow = new GameWindow(
                                    gameName,
                                    niknameInput->text(),
                                    fieldSize, port,true,nullptr,ip);

            gameWindow->resize(300, 200);
            gameWindow->show();
        }
        else if (isJoinGame) {
            // Подключение к игре
            QString ip = ipInput->text();
            qint16 port = portInput->text().toInt();
            // Создание игры с указанным названием
            GameWindow *gameWindow = new GameWindow(
                                        "Заглушка",
                                        niknameInput->text(),
                                        3, port, false, nullptr,ip);

            gameWindow->getCommunicator()->sendMessage(gameWindow->getCommunicator()->createGetGeneralFieldDataMessage());

            gameWindow->resize(300, 200);
            gameWindow->show();

        }
    });

    // Подключение кнопки "Выход"
    connect(exitButton, &QPushButton::clicked, this, &QWidget::close);

    setLayout(mainLayout);
}

