#include "advancedCalculator.h"

bool isInteger(double n) {
	return std::floor(n) == n;
}

bool isItCorrectNumber(std::string input)
{
	std::string special_characters = ".";
	std::string signs = "-";
	std::string all = special_characters + signs;

	if (input.at(0) == '.' || input.at(0) == '+')
		return false;
	if (!isdigit(input.at(input.size() - 1)))
		return false;	
	if (std::any_of(begin(input) + 1, end(input), [](char c) {return c == '-';}))
		return false;
	if (std::any_of(begin(all), end(all), [&input](char c) {return std::count(begin(input), end(input), c) > 1; }))
		return false;
	if (std::any_of(begin(input), end(input), [](char c) {return c == ',';}))
		return false;
	if (!std::all_of(begin(input), end(input),
	[all](char c) {
		return std::any_of(begin(all), end(all), [c](char special) {
			return c == special || isdigit(c); }); }))
	return false;
		return true;
}

ErrorCode stringToDouble(std::string input, double* output) {

	std::stringstream ss;
	ss << input;
	ss >> *output;

	return ErrorCode::OK;
}

ErrorCode CheckBadChars(std::string* input, const std::string& symbols) {
	if (!std::all_of(begin(*input), end(*input), [symbols](char c) {
		return std::any_of(begin(symbols), end(symbols), [c](char aa) {return c == aa || isdigit(c); }); }))
		return ErrorCode::BadCharacter;

	return ErrorCode::OK;
}

ErrorCode CheckArithemticErrors(const std::string& raw_input, const Data& input_data_structure)
{
	if (input_data_structure.operation == '%')
		if (!isInteger(input_data_structure.second_value) || input_data_structure.second_value == 0)
			return ErrorCode::ModuleOfNonIntegerValue;

	if (input_data_structure.operation == '/' && input_data_structure.second_value == 0)
		return ErrorCode::DivideBy0;

	if (input_data_structure.operation == '$')
		if (input_data_structure.first_value < 0)
			return ErrorCode::SqrtOfNegativeNumber;

	if (!std::all_of(begin(raw_input), end(raw_input), [](char c) {return c == ' '; }))
		return ErrorCode::BadFormat;

	return ErrorCode::OK;
}

ErrorCode SeparateOperands(std::string& input, const std::string& allowedOps, Data* output) {
	std::string temp;

	auto it = std::find_first_of(begin(input) + 1, end(input), begin(allowedOps), end(allowedOps));
	output->operation = *it;
	*it = ' ';

	temp.resize(std::distance(begin(input), it));
	std::copy(begin(input), it, begin(temp));
	
	if (!isItCorrectNumber(temp))
		return ErrorCode::BadFormat;
	stringToDouble(temp, &output->first_value);

	std::transform(begin(input), it, begin(input), [](char c) {return ' '; });

	if (output->operation != '!')
	{
		temp.clear();
		temp.resize(std::distance(it + 1, end(input)));
		std::copy(it + 1, end(input), begin(temp));
		if(!isItCorrectNumber(temp))
			return ErrorCode::BadFormat;
		stringToDouble(temp, &output->second_value);
		std::transform(it + 1, end(input), it + 1, [](char c) {return ' '; });
	}	

	return ErrorCode::OK;
}

ErrorCode process(std::string input, double* out) {
	*out = 0.0;

	std::string allowed_operations = "+-*/%^$!";
	std::string allowed_operands = ".,";
	std::string all_allowed_symbols = allowed_operations + allowed_operands;

	input.erase(std::remove(begin(input), end(input), ' '), end(input));

	ErrorCode result;
	result = CheckBadChars(&input, all_allowed_symbols);
	if (result != ErrorCode::OK)
		return result;

	Data data;
	result = SeparateOperands(input, allowed_operations, &data);
	if (result != ErrorCode::OK)
		return result;

	result = CheckArithemticErrors(input, data);
	if (result != ErrorCode::OK)
	return result;
	
	*out = operations.find(data.operation)->second(data.first_value, data.second_value);

	return ErrorCode::OK;
}
