#include "Polynom.h"

Polynom::Polynom() {
    roots = std::make_unique<Array>();
    roots->GetArray().push_back(1.0);
    anCoeff = 1.0;
}

Polynom::Polynom(number constant) {
    roots = std::make_unique<Array>();
    roots->GetArray().push_back(constant);
    anCoeff = 1.0;
}

Polynom::Polynom(number t_an, unsigned N) {
    roots = std::make_unique<Array>();
    anCoeff = t_an;
    for (unsigned i = 0; i < N; i++) {
        number root;
        std::cin >> root;
        roots->GetArray().push_back(root);
    }
}

Polynom::~Polynom() {}

bool Polynom::Create(number t_anCoeff, unsigned t_N, QVBoxLayout *createLayout) {
    anCoeff = t_anCoeff;
    for (unsigned i = 0; i < t_N; i++) {

        std::cout << "Введите " << i + 1 << "-й корень: ";
        std::cin >> root;
        roots->GetArray().push_back(root);
        std::cout << "Добавлен корень: " << root << std::endl;  // Отладочный вывод
    }

    std::cout << "Всего корней: " << roots->GetArray().size() << std::endl;  // Проверка размера массива
    return true;
}

bool Polynom::Clear() {
    roots->GetArray().clear();
    anCoeff = 1.0;
    return true;
}

bool Polynom::SetValue() {
    unsigned index;
    bool type = 0;
    double value;
    std::cout << "Выберите, что вы хотите изменить. Корень - 0 или коэффициент an - 1: ";
    std::cin >> type;
    while (type != 1 && type != 0 || std::cin.fail()) {
        std::cout << "Введите корректное число. Либо 1, либо 0: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> type;
    }
    switch (type) {
    case 0:
        std::cout << "Введите индекс: ";
        std::cin >> index;
        std::cout << "Введите значение: ";
        std::cin >> value;
        roots->GetArray()[index] = value;
        return true;
    case 1:
        std::cout << "Введите значение: ";
        std::cin >> value;
        anCoeff = value;
        return true;
    }
    return false;
}

std::vector<number> Polynom::multiplyPolynom(const std::vector<number>& poly, number root) {
    std::vector<number> result(poly.size() + 1, 0.0);  // Создаем новый полином с на один член больше

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

double Polynom::evaluateAtPoint(double x) {
    double result = anCoeff;

    for (size_t i = 0; i < roots->GetArray().size(); ++i) {
        result *= (x - roots->GetArray()[i]);
    }

    return result;
}

void Polynom::PrintNonCanonicalForm() {
    if (roots->GetArray().empty()) {
        std::cout << "Полином не имеет корней." << std::endl;
        return;
    }

    std::cout << "Не каноническая форма полинома: (" << anCoeff << ") * ";

    for (size_t i = 0; i < roots->GetArray().size(); ++i) {
        std::cout << "(x - (" << roots->GetArray()[i] << "))";
        if (i < roots->GetArray().size() - 1) {
            std::cout << " * ";
        }
    }
    std::cout << std::endl;
}

void Polynom::PrintCanonicalForm() {
    if (roots->GetArray().empty()) {
        std::cout << "Полином не имеет корней." << std::endl;
        return;
    }

    std::vector<number> canonicalPoly = expandPolynomial(anCoeff, roots->GetArray());

    std::cout << "Каноническая форма полинома: ";

    bool firstTerm = true;

    auto ToSuperscript = [](int num) -> std::string {
        std::string superscript = "";
        std::string digits = std::to_string(num);
        for (char digit : digits) {
            switch (digit) {
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

    for (int i = canonicalPoly.size() - 1; i >= 0; --i) {
        double coeff = canonicalPoly[i];

        if (coeff == 0.0) continue;

        if (!firstTerm) {
            if (coeff > 0) std::cout << " + ";
            else std::cout << " - ";
        }

        if (i > 0) {
            if (std::abs(coeff) != 1) {
                std::cout << "(" << coeff << ")";
            }

            std::cout << "x";
            if (i > 1) {
                std::cout << ToSuperscript(i);
            }
        }
        else {
            std::cout << coeff;
        }

        firstTerm = false;
    }
    std::cout << std::endl;
}
