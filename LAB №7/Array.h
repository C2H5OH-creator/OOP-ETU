#pragma once

#include <vector>
#include <string>
#include <iostream>

#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <type_traits>
#include "number.h"  // Если тип number — это класс комплексных чисел

#ifndef ARRAY_H
#define ARRAY_H

#include <vector>
#include <iostream>
#include <cmath>
#include <stdexcept>
#include <type_traits>
#include "number.h"  // Для работы с типом number (комплексные числа)

template <typename T>
class Array {
private:
    std::vector<T> array;

public:
    bool Create();
    bool Sort(bool ascending);
    bool SetValue(unsigned t_index, T value);
    bool ChangeSize(unsigned t_size);
    bool Print();

    // Общая версия Mean и StandardDeviation
    T Mean();
    T StandardDeviation();

    std::vector<T>& GetArray() { return array; };
};

#endif // ARRAY_H
