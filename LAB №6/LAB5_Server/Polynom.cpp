#include "Polynom.h"

Polynom::Polynom() {
    roots = std::make_unique<Array>();
    coefficient = std::make_unique<Array>();
    roots->GetArray().push_back(Complex(1, 0));
    coefficient->GetArray().push_back(Complex(1, 0));
};

Polynom::Polynom(number constant) {
    roots->GetArray().push_back(constant);
    coefficient->GetArray().push_back(Complex(1, 0));
};

Polynom::Polynom(number t_an, unsigned N) {
    for (unsigned i = 0; i < N; i++) {
        number root;
        std::cin >> root;
        roots->GetArray().push_back(root);
    }
}

Polynom::~Polynom() {};

bool Polynom::Create(number t_anCoeff, unsigned t_N, const QVector<number>& t_roots) {
    Clear();
    anCoeff = t_anCoeff;
    for (unsigned i = 0; i < t_N; i++) {
        roots->GetArray().push_back(t_roots[i]);
    }

    std::cout << "Всего корней: " << roots->GetArray().size() << std::endl;  // Проверка размера массива

    return true;
}

bool Polynom::Clear() {
    roots->GetArray().clear();
    coefficient->GetArray().clear();
    anCoeff = Complex(1, 0);

    return true;
}


bool Polynom::SetValue(bool t_type, unsigned t_index, number t_value) {
    switch (t_type) {
    case 0:
        roots->GetArray()[t_index] = t_value;
        return true;
        break;
    case 1:
        anCoeff = t_value;
        return true;
        break;
    }
    return false;
}

std::vector<number> Polynom::multiplyPolynom(const std::vector<number>& poly, number root) {
    std::vector<number> result(poly.size() + 1, Complex(0, 0)); // Создаем новый полином с на один член больше

    // Выполняем умножение
    for (size_t i = 0; i < poly.size(); ++i) {
        result[i] += poly[i];
        result[i + 1] -= poly[i] * root;
    }

    return result;
}

// Функция для преобразования полинома из множителей в каноническую форму
std::vector<number> Polynom::expandPolynomial(number a, const std::vector<number>& roots) {
    std::vector<number> poly = { a };

    // Последовательно умножаем полином на (x - r_i)
    for (number root : roots) {
        poly = multiplyPolynom(poly, root);
    }

    return poly;
}

number Polynom::evaluateAtPoint(number x) {
    number result = anCoeff;

    std::vector<number> rootsArray = roots->GetArray();

    for (size_t i = 0; i < rootsArray.size(); ++i) {
        result = result * (x - rootsArray[i]);
    }

    return result;
}

QString Polynom::PrintNonCanonicalForm() {
    QString output = "";
    // Проверка, есть ли корни
    if (roots->GetArray().empty()) {
        std::cout << "Полином не имеет корней." << std::endl;
        return "";
    }

    // Выводим ведущий коэффициент
    output += "(" + anCoeff.GetComplexString() + ") * ";

    for (size_t i = 0; i < roots->GetArray().size(); ++i) {
        output += "(x - (" + roots->GetArray()[i].GetComplexString() + "))";
        if (i < roots->GetArray().size() - 1) {
            output += " * ";
        }
    }
    return output;
}

QString Polynom::PrintCanonicalForm() {
    QString output;

    // Проверка, есть ли корни
    if (roots->GetArray().empty()) {
        return "Полином не имеет корней.";
    }

    std::vector<number> rootsArray = roots->GetArray();
    std::vector<number> canonicalPoly = expandPolynomial(anCoeff, rootsArray);

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
        number coeff = canonicalPoly[i];

        // Проверяем, что коэффициент не является нулевым
        if (coeff.getReal() == 0 && coeff.getImaginary() == 0) continue;

        // Добавляем знак перед членом (если это не первый член)
        if (!firstTerm) {
            if (coeff.getReal() >= 0) {
                output += " + "; // Положительный знак
            } else {
                output += " - "; // Отрицательный знак
            }
        }

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
