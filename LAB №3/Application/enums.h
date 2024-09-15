#pragma once
enum keys
{
    KEY_UP = 72,
    KEY_DOWN = 80,
    KEY_LEFT = 75,
    KEY_RIGHT = 77,
    ESC = 27,
    ENTER = 13,

    ZERO = 48,
    ONE = 49,
    TWO = 50,
    THREE = 51,
    FOUR = 52,
    FIVE = 53,
    SIX = 54,
    SEVEN = 55,
};

enum menuConst {
    MAIN_MENU_HIGHT = 6,
    SORT_MENU_HIGHT = 2,

    MAIN_MENU = -1,

    CREATE_POLYNOM = 0,
    CHANGE_POLYNOM_COEFFS = 1,
    CALCULATE_VALUE_POLYNOMIAL_AT_POINT = 2,
    CHANGE_POLYNOM_SIZE = 3,
    PRINT_POLYNOM = 4,
    EXIT = 5,

    SORT_ASCENDING = 0,
    SORT_DESCENDING = 1,
    SORT_EXIT = 2,
};