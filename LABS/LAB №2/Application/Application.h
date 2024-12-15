#pragma once
#include <vector>
#include <string>
#include <iostream>

class Application {
public:
    Application();
    ~Application() = default;

    void MainMenu();
    void SortMenu();
    unsigned GetArrowPoss() { return arrowPoss; };
    void SetArrowPoss(unsigned t_arrowPoss) { arrowPoss = t_arrowPoss; };
    
private:
    std::vector<std::string> mainMenuItems = { "Создать массив",
                                    "Расчет среднего и СКО",
                                    "Сортировка",
                                    "Изменить размер массива",
                                    "Изменить значение конкретного элемента",
                                    "Вывести элементы массива",
                                        "Выход" };
    std::vector<std::string> sortMenuItems = { "Сортировать массив по возрастанию",
                                    "Сортировать массив по убыванию",
                                        "Выход" };

    std::string arrow = "   <--";
    unsigned arrowPoss = 0;
};