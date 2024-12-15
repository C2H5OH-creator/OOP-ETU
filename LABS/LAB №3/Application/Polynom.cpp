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
};

Polynom::~Polynom() {};

bool Polynom::Create() {
	std::cout << "Введите значение коэффициента an: ";
	std::cin >> anCoeff;

	unsigned N;
	std::cout << "Введите желаемое количество корней: ";
	std::cin >> N;

	for (unsigned i = 0; i < N; i++) {
		number root;
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
	coefficient->GetArray().clear();
	anCoeff = Complex(1, 0);

	return true;
}


bool Polynom::SetValue() {
	unsigned index;
	bool type = 0;
	number value;
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
		break;
	case 1:
		std::cout << "Введите значение: ";
		std::cin >> value;
		anCoeff = value;
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

void Polynom::PrintNonCanonicalForm() {
	// Проверка, есть ли корни
	if (roots->GetArray().empty()) {
		std::cout << "Полином не имеет корней." << std::endl;
		return;
	}

	// Выводим ведущий коэффициент
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
	// Проверка, есть ли корни
	if (roots->GetArray().empty()) {
		std::cout << "Полином не имеет корней." << std::endl;
		return;
	}

	std::vector<number> rootsArray = roots->GetArray();
	std::vector<number> canonicalPoly = expandPolynomial(anCoeff, rootsArray);

	std::cout << "Каноническая форма полинома: ";

	bool firstTerm = true;

	// Функция для преобразования целого числа в символы суперскрипта
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

	// Обратный проход по коэффициентам для вывода от старшей степени к младшей
	for (int i = canonicalPoly.size() - 1; i >= 0; --i) {
		number coeff = canonicalPoly[i];

		if (coeff == Complex(0, 0)) continue;

		// Выводим знак перед членом (если это не первый член)
		if (!firstTerm) {
			if (coeff.getReal() > 0) std::cout << " + ";
			else std::cout << " - ";
		}

		// Обрабатываем модуль коэффициента (для старших степеней коэффициент 1 или -1 опускаем)
		if (i > 0) {
			if (std::abs(coeff.getReal()) != 1 || std::abs(coeff.getImaginary()) != 0) {
				std::cout << "(" << coeff << ")";
				//std::cout << (firstTerm ? coeff : coeff.Magnitude());
			}

			// Выводим x^степень
			std::cout << "x";
			if (i > 1) {
				std::cout << ToSuperscript(i);
			}
		}
		else {
			// Выводим свободный член
			std::cout << coeff;
		}

		firstTerm = false; // После первого члена переключаем флаг
	}
	std::cout << std::endl;
}