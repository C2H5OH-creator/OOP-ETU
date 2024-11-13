#include "Array.h"

template <typename T>
bool Array<T>::Create() {
    array = {};
    return array.empty();
}

template <typename T>
bool Array<T>::Sort(bool ascending) {
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

template <typename T>
bool Array<T>::SetValue(unsigned t_index, T value) {
    if (t_index >= array.size()) {
        return false;
    }
    array[t_index] = value;
    return true;
}

template <typename T>
bool Array<T>::ChangeSize(unsigned t_size) {
    if (t_size > array.size()) {
        array.resize(t_size, T());  // Используем конструктор по умолчанию для T
        return true;
    }
    else if (t_size < array.size()) {
        array.resize(t_size);
        return true;
    }
    return false;
}

template <typename T>
bool Array<T>::Print() {
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

template <typename T>
T Array<T>::Mean() {
    if constexpr (std::is_same<T, Complex>::value) {
        number sum(0, 0);
        for (const number& value : array) {
            sum += value;
        }
        return sum / static_cast<double>(array.size());
    }
    else{

        double sum = 0.0;
        for (const T& value : array) {
            sum += value;
        }
        return sum / static_cast<double>(array.size());
    }
}

template <typename T>
T Array<T>::StandardDeviation() {
    if constexpr (std::is_same<T, Complex>::value) {
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

        return number(stddev, 0); // Для комплексных чисел
    }
    else{
        if (array.empty()) {
            throw std::runtime_error("Array is empty");
        }

        double mean = Mean();
        double sum_of_squares = 0;
        for (const T& value : array) {
            sum_of_squares += std::pow(value - mean, 2); // для обычных чисел
        }

        return std::sqrt(sum_of_squares / static_cast<double>(array.size())); // Для обычных чисел (double)
    }
}


/*
// Специализация для double
template <typename T>
typename std::enable_if<std::is_same<T, double>::value, double>::type
Array<T>::Mean() {
    double sum = 0.0;
    for (const T& value : array) {
        sum += value;
    }
    return sum / static_cast<double>(array.size());
}

// Специализация для Complex
template <typename T>
typename std::enable_if<std::is_same<T, number>::value, number>::type
Array<T>::Mean() {
    number sum(0, 0);
    for (const number& value : array) {
        sum += value;
    }
    return sum / static_cast<double>(array.size());
}

// Для всех типов
template <typename T>
T Array<T>::StandardDeviation() {
    // Реализация для общего типа T
}

// Специализация для double
template <typename T>
typename std::enable_if<std::is_same<T, double>::value, double>::type
Array<T>::StandardDeviation() {
    if (array.empty()) {
        throw std::runtime_error("Array is empty");
    }

    double mean = Mean();
    double sum_of_squares = 0;
    for (const T& value : array) {
        sum_of_squares += std::pow(value - mean, 2); // для обычных чисел
    }

    return std::sqrt(sum_of_squares / static_cast<double>(array.size())); // Для обычных чисел (double)
}

// Специализация для Complex
template <typename T>
typename std::enable_if<std::is_same<T, number>::value, number>::type
Array<T>::StandardDeviation() {
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

    return number(stddev, 0); // Для комплексных чисел
}
*/

// Явная инстанциация шаблонов для типов, которые будут использоваться в проекте
template class Array<double>;
template class Array<number>;  // Для комплексных чисел

