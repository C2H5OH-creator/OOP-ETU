#include "Polynom.h"

template<typename T>
Polynom<T>::Polynom() {
    roots = std::make_unique<Array<T>>();
    coefficient = std::make_unique<Array<T>>();

    if constexpr (std::is_same<T, Complex>::value) {
        roots->GetArray().push_back(Complex(1, 0));
        coefficient->GetArray().push_back(Complex(1, 0));
    } else {
        roots->GetArray().push_back(1);
        coefficient->GetArray().push_back(1);
    }
}

template<typename T>
Polynom<T>::Polynom(T constant) {
    roots = std::make_unique<Array<T>>();
    coefficient = std::make_unique<Array<T>>();
    roots->GetArray().push_back(constant);

    if constexpr (std::is_same<T, Complex>::value) {
        coefficient->GetArray().push_back(Complex(1, 0));
    } else {
        coefficient->GetArray().push_back(1);
    }
}

template<typename T>
Polynom<T>::Polynom(T t_an, unsigned N) {
    roots = std::make_unique<Array<T>>();
    coefficient = std::make_unique<Array<T>>();
    for (unsigned i = 0; i < N; i++) {
        T root;
        std::cin >> root;
        roots->GetArray().push_back(root);
    }
}

template<typename T>
Polynom<T>::Polynom(unsigned N) {
    roots = std::make_unique<Array<T>>();
    coefficient = std::make_unique<Array<T>>();

    for (unsigned i = 0; i < N; ++i) {
        roots->GetArray().push_back(0);
    }

    if constexpr (std::is_same<T, Complex>::value) {
        coefficient->GetArray().push_back(Complex(1, 0));
    } else {
        coefficient->GetArray().push_back(1);
    }
}


template<typename T>
Polynom<T>::~Polynom() { }

template<typename T>
bool Polynom<T>::Create(T t_anCoeff, unsigned t_N, const QVector<T>& t_roots) {
    Clear();
    anCoeff = t_anCoeff;
    for (unsigned i = 0; i < t_N; i++) {
        roots->GetArray().push_back(t_roots[i]);
    }

    std::cout << "Всего корней: " << roots->GetArray().size() << std::endl;
    return true;
}

template<typename T>
bool Polynom<T>::Clear() {
    roots->GetArray().clear();
    coefficient->GetArray().clear();

    if constexpr (std::is_same<T, Complex>::value) {
        anCoeff = Complex(1, 0);
    } else {
        anCoeff = 1;  // Для обычных чисел, например double или int
    }

    return true;
}

template<typename T>
bool Polynom<T>::SetValue(bool t_type, unsigned t_index, T t_value) {
    switch (t_type) {
    case 0:
        roots->GetArray()[t_index] = t_value;
        return true;
    case 1:
        anCoeff = t_value;
        return true;
    default:
        return false;
    }
}

template<typename T>
std::vector<T> Polynom<T>::multiplyPolynom(const std::vector<T>& poly, T root) {
    if constexpr (std::is_same<T, Complex>::value) {
        std::vector<T> result(poly.size() + 1, Complex(0,0));
        // Выполняем умножение
        for (size_t i = 0; i < poly.size(); ++i) {
            result[i] += poly[i];
            result[i + 1] -= poly[i] * root;
        }

        return result;
    }else{
        std::vector<T> result(poly.size() + 1, 0);
        // Выполняем умножение
        for (size_t i = 0; i < poly.size(); ++i) {
            result[i] += poly[i];
            result[i + 1] -= poly[i] * root;
        }

        return result;
    }


}

template<typename T>
std::vector<T> Polynom<T>::expandPolynomial(T a, const std::vector<T>& roots) {
    std::vector<T> poly = { a };

    // Последовательно умножаем полином на (x - r_i)
    for (T root : roots) {
        poly = multiplyPolynom(poly, root);
    }

    return poly;
}

template<typename T>
T Polynom<T>::evaluateAtPoint(T x) {
    T result = anCoeff;

    std::vector<T> rootsArray = roots->GetArray();

    for (size_t i = 0; i < rootsArray.size(); ++i) {
        result = result * (x - rootsArray[i]);
    }

    return result;
}

template<typename T>
QString Polynom<T>::PrintNonCanonicalForm() {
    QString output = "";
    // Проверка, есть ли корни
    if (roots->GetArray().empty()) {
        std::cout << "Полином не имеет корней." << std::endl;
        return "";
    }

    // Выводим ведущий коэффициент
    if constexpr (std::is_same<T, Complex>::value) {
        output += "(" + anCoeff.GetComplexString() + ") * ";
    } else {
        output += "(" + QString::number(anCoeff) + ") * ";
    }

    for (size_t i = 0; i < roots->GetArray().size(); ++i) {
        if constexpr (std::is_same<T, Complex>::value) {
            output += "(x - (" + roots->GetArray()[i].GetComplexString() + "))";
        } else {
            output += "(x - " + QString::number(roots->GetArray()[i]) + ")";
        }
        if (i < roots->GetArray().size() - 1) {
            output += " * ";
        }
    }
    return output;
}

template<typename T>
QString Polynom<T>::PrintCanonicalForm() {
    QString output;

    // Проверка, есть ли корни
    if (roots->GetArray().empty()) {
        return "Полином не имеет корней.";
    }

    std::vector<T> rootsArray = roots->GetArray();
    std::vector<T> canonicalPoly = expandPolynomial(anCoeff, rootsArray);

    bool firstTerm = true;

    // Функция для преобразования целого числа в символы суперскрипта
    auto ToSuperscript = [](int num) -> QString {
        QString superscript;
        QString digits = QString::number(num);
        for (QChar digit : digits) {
            switch (digit.toLatin1()) {
            case '0': superscript += "⁰"; break;
            case '1': superscript += "¹"; break;
            case '2': superscript += "²"; break;
            case '3': superscript += "³"; break;
            case '4': superscript += "⁴"; break;
            case '5': superscript += "⁵"; break;
            case '6': superscript += "⁶"; break;
            case '7': superscript += "⁷"; break;
            case '8': superscript += "⁸"; break;
            case '9': superscript += "⁹"; break;
            }
        }
        return superscript;
    };

    // Обратный проход по коэффициентам для вывода от старшей степени к младшей
    for (int i = canonicalPoly.size() - 1; i >= 0; --i) {
        T coeff = canonicalPoly[i];

        // Проверяем, что коэффициент не является нулевым
        if constexpr (std::is_same<T, Complex>::value) {
            if (coeff.getReal() == 0 && coeff.getImaginary() == 0) continue;
        } else {
            if (coeff == 0) continue;
        }

        // Добавляем знак перед членом (если это не первый член)
        if (!firstTerm) {
            if constexpr (std::is_same<T, Complex>::value) {
                if (coeff.getReal() >= 0) {
                    output += " + "; // Положительный знак
                } else {
                    output += " - "; // Отрицательный знак
                }
            }
        }

        if constexpr (std::is_same<T, Complex>::value) {
            double realPart = coeff.getReal();
            double imaginaryPart = coeff.getImaginary();

            // Обрабатываем случай, когда реальная часть = 0, но мнимая часть ненулевая
            if (realPart == 0 && imaginaryPart != 0) {
                output += (imaginaryPart >= 0 ? "+" : "") + QString::number(imaginaryPart) + "i";
            } else {
                // Обрабатываем модуль коэффициента для реальных частей
                if (std::abs(realPart) != 1 || imaginaryPart != 0) {
                    output += QString::number(realPart) + (imaginaryPart >= 0 ? "+" : "") +
                              QString::number(imaginaryPart) + "i";
                } else {
                    output += (realPart == 0 ? "" : QString::number(realPart)) + (imaginaryPart >= 0 ? "+" : "") +
                              QString::number(imaginaryPart) + "i";
                }
            }
        } else {
            output += QString::number(coeff);
        }

        // Добавляем x^степень
        if (i > 0) {
            output += "x";
            if (i > 1) {
                output += ToSuperscript(i);
            }
        }

        firstTerm = false; // После первого члена переключаем флаг
    }

    return output;
}


template<typename T>
QString Polynom<T>::PrintDoubleNonCanonicalForm() {
    QString output;

    // Проверка, есть ли корни
    if (roots->GetArray().empty()) {
        std::cout << "Полином не имеет корней." << std::endl;
        return "";
    }

    // Выводим ведущий коэффициент
    output += "(" + QString::number(anCoeff) + ") * ";

    for (size_t i = 0; i < roots->GetArray().size(); ++i) {
        output += "(x - " + QString::number(roots->GetArray()[i]) + ")";
        if (i < roots->GetArray().size() - 1) {
            output += " * ";
        }
    }

    return output;
}

template<typename T>
QString Polynom<T>::PrintDoubleCanonicalForm() {
    QString output;

    // Проверка, есть ли корни
    if (roots->GetArray().empty()) {
        return "Полином не имеет корней.";
    }

    std::vector<double> rootsArray = roots->GetArray();
    std::vector<double> canonicalPoly = expandPolynomial(anCoeff, rootsArray);

    bool firstTerm = true;

    // Функция для преобразования целого числа в символы суперскрипта
    auto ToSuperscript = [](int num) -> QString {
        QString superscript;
        QString digits = QString::number(num);
        for (QChar digit : digits) {
            switch (digit.toLatin1()) {
            case '0': superscript += "⁰"; break;
            case '1': superscript += "¹"; break;
            case '2': superscript += "²"; break;
            case '3': superscript += "³"; break;
            case '4': superscript += "⁴"; break;
            case '5': superscript += "⁵"; break;
            case '6': superscript += "⁶"; break;
            case '7': superscript += "⁷"; break;
            case '8': superscript += "⁸"; break;
            case '9': superscript += "⁹"; break;
            }
        }
        return superscript;
    };

    // Обратный проход по коэффициентам для вывода от старшей степени к младшей
    for (int i = canonicalPoly.size() - 1; i >= 0; --i) {
        double coeff = canonicalPoly[i];

        // Пропускаем нулевые коэффициенты
        if (coeff == 0) continue;

        // Добавляем знак перед членом (если это не первый член)
        if (!firstTerm) {
            output += (coeff > 0 ? " + " : " - ");
        }

        // Добавляем модуль коэффициента
        output += QString::number(std::abs(coeff));

        // Добавляем x^степень
        if (i > 0) {
            output += "x";
            if (i > 1) {
                output += ToSuperscript(i);
            }
        }

        firstTerm = false; // После первого члена переключаем флаг
    }

    return output;
}

