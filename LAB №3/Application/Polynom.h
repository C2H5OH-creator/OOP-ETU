#pragma once

#include <iostream>
#include <memory>

#include "Array.h"
#include "Complex.h"
#include "number.h"

class Polynom {
public:
	Polynom();
	
	Polynom(number constant);
	
	Polynom(number t_an,unsigned N);

	~Polynom();

	bool Create();
	
	bool Clear();

	bool SetValue();

	std::vector<number> multiplyPolynom(const std::vector<number>& poly, number root);

	// Функция для преобразования полинома из множителей в каноническую форму
	std::vector<number> expandPolynomial(number a, const std::vector<number>& roots);

	number evaluateAtPoint(number x);

	void PrintCanonicalForm();

	void PrintNonCanonicalForm();

	Array* GetRoots() { return roots.get(); }
	Array* GetCoeffs() { return coefficient.get(); }

private:
	std::unique_ptr<Array> roots;
	std::unique_ptr<Array> coefficient;
	number anCoeff;
};