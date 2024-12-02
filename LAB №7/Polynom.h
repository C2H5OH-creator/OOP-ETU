#pragma once

#include <iostream>
#include <memory>
//#include <QLineEdit>
#include <QVector>

#include "Array.h"
#include "Array.cpp"
#include "Complex.h"
#include "number.h"

template <typename T>
class Polynom {
public:
    Polynom(bool trivial = true);
	
    Polynom(T constant);
	
    Polynom(T t_an,unsigned N);

    Polynom(unsigned N);

    ~Polynom() { }

    bool Create(T t_anCoeff, unsigned t_N, const QVector<T>& t_roots);
	
	bool Clear();

    bool SetValue(bool t_type, unsigned t_index, T t_value);

    std::vector<T> multiplyPolynom(const std::vector<T>& poly, T root);

	// Функция для преобразования полинома из множителей в каноническую форму
    std::vector<T> expandPolynomial(T a, const std::vector<T>& roots);

    T evaluateAtPoint(T x);

    QString PrintCanonicalForm();

    QString PrintNonCanonicalForm();

    QString PrintDoubleCanonicalForm();

    QString PrintDoubleNonCanonicalForm();



    Array<T>* GetRoots() { return roots.get(); }
    //Array<T>* GetCoeffs() { return coefficient.get(); }
    Array<T>& GetCoeffs() { return *coefficient; }


private:
    std::unique_ptr<Array<T>> roots;
    std::unique_ptr<Array<T>> coefficient;
    T anCoeff;

};
