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
        std::cout << "Массив ещё не инициализирован, либо в нём нет ни одного элемента!" << std::endl;
        return false;
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
        array.resize(t_size, Complex(0, 0));
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
        std::cout << array[i];
        if (i != array.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << " ]" << std::endl;
    return true;
}

number Array::Mean() {
    number sum(0, 0);
    for (const number& value : array) {
        sum += value;
    }
    return sum / static_cast<double>(array.size());
}

number Array::StandardDeviation() {
    if (array.empty()) {
        throw std::runtime_error("Array is empty");
    }

    number mean = Mean();

    double sum_of_squares = 0;
    for (const number& value : array) {
        number diff = value - mean;
        double magnitude = sqrt(diff.getReal() * diff.getReal() + diff.getImaginary() * diff.getImaginary());
        sum_of_squares += magnitude * magnitude;
    }

    double stddev = sqrt(sum_of_squares / static_cast<double>(array.size()));

    return number(stddev, 0);
}
