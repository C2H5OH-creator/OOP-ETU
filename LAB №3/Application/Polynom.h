#pragma once

#include <iostream>
#include <memory>

#include "Array.h"
#include "Complex.h"
#include "number.h"

class Polynom {
public:
	Polynom() {
		roots->GetArray().push_back(Complex(1,0));
		coefficient->GetArray().push_back(Complex(1,0));
	};
	
	Polynom(number constant) {
		roots->GetArray().push_back(constant);
		coefficient->GetArray().push_back(Complex(1,0));
	};
	
	Polynom(number t_an,unsigned N) {
		for (unsigned i = 0; i < N; i++) {
			number root;
			std::cin >> root;
			roots->GetArray().push_back(root);
		}
	};

	~Polynom() {};

	bool Create() {
		
		std::cout << "Введите значение коэффициента an	: ";
		std::cin >> anCoeff;

		unsigned N;
		std::cout << "Введите желаемое количество корней";
		std::cin >> N;

		for (unsigned i = 0; i < N; i++) {
			number root;
			std::cout << "Введите " << i << "-й корень";
			std::cin >> root;
			roots->GetArray().push_back(root);
		}
		return true;
	}

	bool SetValue() {
		unsigned index;
		unsigned type = 0;
		number value;
		std::cout << "Выберите, что вы хотите изменить? Корень - 0 или коэффициент an - 1: ";
		std::cin >> type;
		if (type == 0) {
			std::cout << "Введите индекс: ";
			std::cin >> index;
			std::cout << "Введите значение: ";
			std::cin >> value;
			roots->GetArray()[index] = value;
			return true;
		}
		else if (type == 1) {
			std::cout << "Введите значение: ";
			std::cin >> value;
			anCoeff = value;
			return true;
		}
		else {
			std::cout << "Введите корректную цифру для выбора!";
			SetValue();
		}
		return false;
	}

	std::vector<number> multiplyPolynom(const std::vector<number>& poly, number root) {
		std::vector<number> result(poly.size() + 1, Complex(0,0)); // Создаем новый полином с на один член больше

		// Выполняем умножение
		for (size_t i = 0; i < poly.size(); ++i) {
			result[i] += poly[i];
			result[i + 1] -= poly[i] * root;
		}

		return result;
	}

	// Функция для преобразования полинома из множителей в каноническую форму
	std::vector<number> expandPolynomial(number a, const std::vector<number>& roots) {
		// Начинаем с полинома "1", который будет умножаться на a
		std::vector<number> poly = { a };

		// Последовательно умножаем полином на (x - r_i)
		for (number root : roots) {
			poly = multiplyPolynom(poly, root);
		}

		return poly;
	}

	number evaluateAtPoint(number x) {
		number result = anCoeff;

		std::vector<number> rootsArray = roots->GetArray();

		for (size_t i = 0; i < rootsArray.size(); ++i) {
			result = result * (x - rootsArray[i]);
		}

		return result;
	}

	Array* GetRoots() { return roots; }
	Array* GetCoeffs() { return coefficient; }

private:
	Array* roots;
	Array* coefficient;
	number anCoeff;
};