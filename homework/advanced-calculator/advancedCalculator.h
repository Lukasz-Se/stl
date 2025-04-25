#pragma once
#include <iostream>
#include <map>
#include <functional>
#include <algorithm>
#include <sstream>
#include <cmath>

enum class ErrorCode
{
	OK = 0,
	BadCharacter,
	BadFormat,
	DivideBy0,
	SqrtOfNegativeNumber,
	ModuleOfNonIntegerValue
};

struct Data {
	char operation;
	double frist_value = 0.0;
	double second_value = 0.0;
};

const std::map<const char, std::function<double(double, double)>> operations{
	{'+', std::plus<double>()},
	{'-', std::minus<double>()},
	{'*', std::multiplies<double>()},
	{'/', std::divides<double>()},
	{'%', std::modulus<int>()},
	{'!', [](auto base, auto empty) {if (base >= 0)
	return tgamma(base + 1);
	else return -tgamma(-base + 1); }},
	{'^', [](auto base, auto exponent) {return pow(base, exponent); }},
	{'$', [](auto base, auto exponent) {return pow(base, 1.0 / exponent); }}
};

bool isInteger(double n);
ErrorCode stringToDouble(std::string input, double* output);
ErrorCode CheckIfStringIsLegal(std::string* input, const std::string& symbols);
ErrorCode SeparateOperands(std::string& input, const std::string& allowedOps, Data* output);
ErrorCode process(std::string input, double* out);
