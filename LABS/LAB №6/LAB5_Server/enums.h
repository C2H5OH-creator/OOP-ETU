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

enum ID {
    CREATE_POLYNOM = 0,
    CHANGE_POLYNOM_COEFFS = 1,
    CALCULATE_VALUE_POLYNOMIAL_AT_POINT = 2,
    PRINT_POLYNOM = 3,
    GET_POLYNOM_FORMS = 4,
    CHANGE_AN = 6,
    CHANGE_ROOT = 7,

};

enum network {
    client_port = 6004,
    server_port = 6005,

};
