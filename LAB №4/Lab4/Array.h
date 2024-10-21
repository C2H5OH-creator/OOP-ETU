#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "number.h"


class Array {
public:
	Array() {};
	~Array() = default;

	bool Create();
	bool Sort(bool ascending = true);
	bool SetValue(unsigned t_index, number value);
	bool ChangeSize(unsigned t_size);
	bool Print();

	number Mean();
	number StandardDeviation();

	std::vector<number>& GetArray() { return array; };

private:
	std::vector<number> array;
};

