#pragma once

#include <iostream>
#include <memory>

#include "Array.h"
#include "Complex.h"

class Polynom {
	Polynom(number constant) {
		roots->GetArray().push_back(constant);
		coefficient->GetArray().push_back(Complex(1,0));
	};
	
	Polynom(number an,unsigned N) {
		coefficient->GetArray().push_back(an);
		for (unsigned i = 0; i < N; i++) {
			number root;
			std::cin >> root;
			roots->GetArray().push_back(root);
		}
	};
	~Polynom() {};



private:
	std::unique_ptr<Array> roots;
	std::unique_ptr<Array> coefficient;
};