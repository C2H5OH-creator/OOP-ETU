#include "Array.h"

bool Array::Create() {
    array = {};
    return array.empty();
}

bool Array::Sort(bool ascending) {
    if (!array.empty()) {
        for (int i = 0; i < array.size() - 1; i++) {
            for (int j = 0; j < array.size() - i - 1; j++) {
                if (ascending ? (array[j] > array[j + 1]) : (array[j] < array[j + 1])) {
                    std::swap(array[j], array[j + 1]);
                }
            }
        }
    }
    else {
        std::cout << "Массив либо пуст, либо ещё не инициализирован!" << std::endl;
    }
    return true;
}

bool Array::SetValue(unsigned t_index, number value) {
    if (t_index > array.size()) {
        return false;
    }
    array[t_index] = value;
    return true;
}

bool Array::ChangeSize(unsigned t_size) {
    if (t_size > array.size()) {
        array.resize(t_size, 0);
        return true;
    }
    else if (t_size < array.size()) {
        array.resize(t_size);
        return true;
    }
    return false;
}

bool Array::Print() {
    std::cout << "[ ";
    for (int i = 0; i < array.size(); i++) {
        std::cout << std::to_string(array[i]);
        if (i != array.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
    return true;
}

number Array::Mean() {
    number sum = 0.0;
    for (int value : array) {
        sum += value;
    }
    return sum / array.size();
}

number Array::StandardDeviation() {
    number mean = Mean();
    number sum_of_squares = 0.0;

    for (int value : array) {
        sum_of_squares += std::pow(value - mean, 2);
    }

    return std::sqrt(sum_of_squares / array.size());
}