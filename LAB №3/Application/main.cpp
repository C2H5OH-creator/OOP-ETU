#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "Application.h"
#include "Polynom.h"
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
    bool polynomExist = false;

    auto mainMenu = new Application();
    auto polynom = new Polynom();
    mainMenu->MainMenu();

    do {
        keyInput = _getch();
        system("cls");
        KeyHandler(keyInput, mainMenu, MAIN_MENU);
        mainMenu->MainMenu();
        unsigned arrowPoss = mainMenu->GetArrowPoss();
       
        if (keyInput == ONE || (arrowPoss == CREATE_POLYNOM && keyInput == ENTER)) {
            if (polynom->Create() && polynomExist == false) {
                polynomExist = true;
                std::cout << "Создан полином!";
            }
            else {
                polynom->Clear();
                polynomExist = false;
            }
        }
        else if (keyInput == TWO || (arrowPoss == CHANGE_POLYNOM_COEFFS && keyInput == ENTER)) {
            polynom->SetValue();
        }
        else if (keyInput == THREE || (arrowPoss == CALCULATE_VALUE_POLYNOMIAL_AT_POINT && keyInput == ENTER)) {
            number x;
            std::cout << "Введите точку: " << std::endl;
            std::cin >> x;
            std::cout << "Значение полинома в точке: " << polynom->evaluateAtPoint(x);
        }
        else if (keyInput == FOUR || (arrowPoss == CHANGE_POLYNOM_SIZE && keyInput == ENTER)) {
            std::cout << "Нынешний размер полинома: " << polynom->GetRoots()->GetArray().size() << std::endl;
            std::cout << "Введите новый размер: ";
            int newPolynomSize;
            std::cin >> newPolynomSize;
            if (polynom->GetRoots()->ChangeSize(newPolynomSize)) {
                std::cout << "Размер изменён. Теперь размер: " + std::to_string(newPolynomSize);
            }
        }
        else if (keyInput == FIVE || (arrowPoss == PRINT_POLYNOM && keyInput == ENTER)) {
            //polynom->PrintCanonicalForm();
            polynom->PrintNonCanonicalForm();
        } 
        else if (keyInput == SIX || (arrowPoss == EXIT && keyInput == ENTER)) {
            break;
        }
    } while (keyInput != ESC);
    delete mainMenu;
}