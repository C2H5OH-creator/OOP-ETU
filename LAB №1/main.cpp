#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "Application.h"
#include "enums.h"
#include "Array.h"

void KeyHandler(const int& t_keyInput, Application* t_menu, int menuType = 0) {
    unsigned t_arrowPoss = t_menu->GetArrowPoss();
    if (t_keyInput == KEY_DOWN) t_menu->SetArrowPoss(++t_arrowPoss);   //Организация движения стрелки вверх
    if (t_keyInput == KEY_UP) t_menu->SetArrowPoss(--t_arrowPoss);     //Организация движения стрелки вниз
    if (t_arrowPoss == ((menuType == MAIN_MENU) 
        ? (MAIN_MENU_HIGHT) 
        : (SORT_MENU_HIGHT)) + 1) t_menu->SetArrowPoss(0);    //Организация движения стрелки циклически
    if (t_arrowPoss == -1) t_menu->SetArrowPoss(((menuType == MAIN_MENU) 
        ? (MAIN_MENU_HIGHT) 
        : (SORT_MENU_HIGHT)));        //Организация движения стрелки циклически
}

int main() {
    int keyInput = 0;
    bool vectorExist = false;

    auto mainMenu = new Application();
    auto array = new Array();
    mainMenu->MainMenu();

    do {
        keyInput = _getch();
        system("cls");
        KeyHandler(keyInput, mainMenu, MAIN_MENU);
        mainMenu->MainMenu();
        unsigned arrowPoss = mainMenu->GetArrowPoss();
       
        if (keyInput == ONE || (arrowPoss == CREATE_ARRAY && keyInput == ENTER)) {
            if (array->Create() && vectorExist == false) {
                vectorExist = true;
                std::cout << "Создан пустой массив!";
            }
            else {
                std::cout << "Массив уже создан!";
            }
        }
        else if (keyInput == TWO || (arrowPoss == SKO && keyInput == ENTER)) {
            std::cout << "Среднее значение: " << array->Mean() << std::endl;
            std::cout << "Стандартное отклонение: " << array->StandardDeviation() << std::endl;

        }
        else if (keyInput == THREE || (arrowPoss == SORT && keyInput == ENTER)) {
            system("cls");
            int sortKeyInput = 0;
            auto sortMenu = new Application();
            sortMenu->SortMenu();

            do {
                sortKeyInput = _getch();
                system("cls");
                KeyHandler(sortKeyInput, sortMenu);
                sortMenu->SortMenu();
                unsigned arrowPoss = sortMenu->GetArrowPoss();

                if (sortKeyInput == ONE
                    || (arrowPoss == SORT_ASCENDING && sortKeyInput == ENTER)) { 
                    if (array->Sort()) { std::cout << "Массив отсортирован по возрастанию" << std::endl; }
                    else { std::cout << "Произошла ошибка в сортировке массива" << std::endl;}
                }
                else if (sortKeyInput == TWO
                    || (arrowPoss == SORT_DESCENDING && sortKeyInput == ENTER)) {
                    if (array->Sort(false)) { std::cout << "Массив отсортирован по убыванию" << std::endl; }
                    else { std::cout << "Произошла ошибка в сортировке массива" << std::endl; }
                }
                else if (sortKeyInput == THREE 
                    || (arrowPoss == SORT_EXIT && sortKeyInput == ENTER)) { break; }
            } while (sortKeyInput != ESC);
            system("cls");
            delete sortMenu;
            mainMenu->MainMenu();
        }
        else if (keyInput == FOUR || (arrowPoss == CHANGE_ARRAY_SIZE && keyInput == ENTER)) {
            std::cout << "Нынешний размер массива: " << array->GetArray().size() << std::endl;
            std::cout << "Введите новый размер: ";
            int newArraySize;
            std::cin >> newArraySize;
            if (array->ChangeSize(newArraySize)) {
                std::cout << "Размер изменён. Теперь размер: " + std::to_string(newArraySize);
            }
        }
        else if (keyInput == FIVE || (arrowPoss == CHANGE_ITEM_VALUE && keyInput == ENTER)) {
            number value;
            unsigned index;
            std::cout << "Введите значение: ";
            std::cin >> value;
           
            std::cout << "Введите индекс: ";
            std::cin >> index;
            if (index > array->GetArray().size()) {
                std::cout << "Индекс выходит за границы массива. Введите другой индекс!" << std::endl;
                std::cout << "Введите индекс: ";
                std::cin >> index;
            }
            array->SetValue(index, value);
            system("cls");
            mainMenu->MainMenu();
        }
        else if (keyInput == SIX || (arrowPoss == PRINT_ARRAY && keyInput == ENTER)) {
            array->Print();
        }
        else if (keyInput == SEVEN || (arrowPoss == EXIT && keyInput == ENTER)) {
            break;
        }
    } while (keyInput != ESC);
    delete mainMenu;
}