#include "AdvancedCalculator.h"

bool isInteger(double n) {
	return std::floor(n) == n;
}

ErrorCode stringToDouble(std::string input, double* output) {
	std::string special_characters = ".";
	std::string signs = "-,+";
	std::string all = special_characters + signs;
	*output = -9999.9999;

	if (!isdigit(input.at(input.size() - 1)))
		return ErrorCode::BadFormat;
	if (std::any_of(begin(all), end(all), [&input](char c) {return std::count(begin(input), end(input), c) > 1; }))
		return ErrorCode::BadFormat;
	if (std::any_of(begin(signs), end(signs), [&input](char c) {return std::count(begin(input) + 1, end(input), c) != 0; }))
		return ErrorCode::BadFormat;
	if (input.at(0) == '.')
		return ErrorCode::BadFormat;

	std::stringstream ss;
	ss << input;
	ss >> *output;

	return ErrorCode::OK;
}

ErrorCode CheckIfStringIsLegal(std::string* input, const std::string& symbols) {
	if (!std::all_of(begin(*input), end(*input), [symbols](char c) {
		return std::any_of(begin(symbols), end(symbols), [c](char aa) {return c == aa || isdigit(c); }); }))
		return ErrorCode::BadCharacter;

	return ErrorCode::OK;
}

ErrorCode SeparateOperands(std::string& input, const std::string& allowedOps, Data* output) {
	std::string temp;

	auto it = std::find_first_of(begin(input) + 1, end(input), begin(allowedOps), end(allowedOps));
	output->operation = *it;
	*it = ' ';

	temp.resize(std::distance(begin(input), it));
	std::copy(begin(input), it, begin(temp));
	if (stringToDouble(temp, &output->frist_value) != ErrorCode::OK)
		return ErrorCode::BadFormat;
	std::transform(begin(input), it, begin(input), [](auto c) {return ' '; });

	if (output->operation != '!')
	{
		temp.resize(std::distance(it + 1, end(input)));
		std::copy(it + 1, end(input), begin(temp));
		if (stringToDouble(temp, &output->second_value) != ErrorCode::OK)
			return ErrorCode::BadFormat;
		std::transform(it + 1, end(input), it + 1, [](auto c) {return ' '; });
	}

	if (!std::all_of(begin(input), end(input), [](char c) {return c == ' '; }))
		return ErrorCode::BadFormat;

	if (output->operation == '%' && !isInteger(output->frist_value))
		return ErrorCode::ModuleOfNonIntegerValue;

	if (output->operation == '/' && output->second_value == 0)
		return ErrorCode::DivideBy0;

	if (output->operation == '$')
		if (output->frist_value < 0 || output->second_value < 0)
			return ErrorCode::SqrtOfNegativeNumber;

	return ErrorCode::OK;
}

ErrorCode process(std::string input, double* out) {
	*out = 0.0;

	std::string allowed_operations = "+-*/%^$!";
	std::string allowed_operands = ".";
	std::string all_allowed_symbols = allowed_operations + allowed_operands;

	input.erase(std::remove(begin(input), end(input), ' '), end(input));

	if (CheckIfStringIsLegal(&input, all_allowed_symbols) != ErrorCode::OK)
		return ErrorCode::BadCharacter;

	Data data;
	ErrorCode error = SeparateOperands(input, allowed_operations, &data);
	if (error != ErrorCode::OK)
		return error;

	*out = operations.find(data.operation)->second(data.frist_value, data.second_value);

	return ErrorCode::OK;
}
