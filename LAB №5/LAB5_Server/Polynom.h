#pragma once

#include <iostream>
#include <memory>
//#include <QLineEdit>
#include <QVector>

#include "Array.h"
#include "Complex.h"
#include "number.h"

class Polynom {
public:
	Polynom();
	
	Polynom(number constant);
	
	Polynom(number t_an,unsigned N);

	~Polynom();

    bool Create(number t_anCoeff, unsigned t_N, const QVector<number>& t_roots);
	
	bool Clear();

    bool SetValue(bool t_type, unsigned t_index, number t_value);

	std::vector<number> multiplyPolynom(const std::vector<number>& poly, number root);

	// Функция для преобразования полинома из множителей в каноническую форму
	std::vector<number> expandPolynomial(number a, const std::vector<number>& roots);

	number evaluateAtPoint(number x);

    QString PrintCanonicalForm();

    QString PrintNonCanonicalForm();

	Array* GetRoots() { return roots.get(); }
	Array* GetCoeffs() { return coefficient.get(); }

private:
	std::unique_ptr<Array> roots;
	std::unique_ptr<Array> coefficient;
	number anCoeff;

};
