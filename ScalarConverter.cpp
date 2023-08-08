#include "ScalarConverter.hpp"

ScalarConverter::~ScalarConverter() {
	std::cout << "destructor called\n";
}
ScalarConverter::ScalarConverter(const ScalarConverter &c) {
	*this = c;
}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter &c) {
	_char = c.getChar();
	_double = c.getDouble();
	_float = c.getFloat();
	_integer = c.getInt();
	return *this;
}

ScalarConverter::ScalarConverter(): _char('\0'), _integer(0), _float(0.0f),_double(0.0), _s(""){
	std::cout << "constructor called\n";
}

void ScalarConverter::setStr(std::string s) {
	_s = s;
}
char ScalarConverter::getChar() const {
	return _char;
}

double ScalarConverter::getDouble() const {
	return _double;
}

int ScalarConverter::getInt() const {
	return _integer;
}

float ScalarConverter::getFloat() const {
	return _float;
}

std::string ScalarConverter::convertType(int e) {
	std::string res;
	bool b = _s.length() == 1 && isprint(_s.at(0)) && !isdigit(_s.at(0));
	try {
		if (b)
		{
			switch (e) {

				case INT: _integer = (int)toascii(_s.at(0));break;
				case FLOAT:_double = (float)toascii(_s.at(0));break;
				case DOUBLE:_integer = (double)toascii(_s.at(0));break;
				case CHAR:_integer = (char)toascii(_s.at(0));break;
				default: std::cout << "unknown type\n";
			}
		}
		if (e == INT)
		{
			(_s.length() != 1 && (_integer = std::stoi(_s)));
			res = std::to_string(_integer);
		}
		else if (e == FLOAT) {
			(_s.length() != 1 && (_float = std::stof(_s)));
			res = std::to_string(_float);
		}
		else if (e == DOUBLE) {
			(_s.length() != 1 && (_double = std::stod(_s)));
			res = std::to_string(_double);
		}
		else if (e == CHAR && !b) {
			res = convertType(INT);
			if (res.compare("nan") && res.compare("impossible"))
			{
				if (stoi(res) > 256 || stoi(res) < 0)
					throw (ScalarConverter::ImpossibleCharConversion());
				if (!isprint(stoi(res)))
					throw (ScalarConverter::NonDisplayableChar());
				_char = std::stoi(_s);
				res = "'";
				char str[2];
				str[0] = _char;
				str[1] = 0;
				res += str;
				res += "'";
			}
		}
		else if (e == CHAR)
		{
			res = "'";
			char str[2];
			str[0] = _char;
			str[1] = 0;
			res += str;
			res += "'";
		}
	}
	catch (std::exception &ex)
	{
		res = ex.what();
		switch (e) {
			case INT:
				res = !res.compare("stoi: no conversion") ? "nan": !res.compare("stoi: out of range") ? "impossible" : "";
				break;
			case FLOAT:
				res = !res.compare("stof: no conversion") ? "nan": !res.compare("stof: out of range") ? "impossible" : "";
				break;
			case DOUBLE:
				res = !res.compare("stod: no conversion") ? "nan": !res.compare("stod: out of range") ? "impossible" : "";
				break;
			case CHAR:
				res = !res.compare("ICC") ? "impossible": !res.compare("NDC") ? "Non displayable" : "";
				break;
			default: std::cout << "unknown type\n";
		}
	}
	return res;
}

void ScalarConverter::setType() {
	_type = UNKNOWN;
	if (_s.length() == 1 && isprint(toascii(_s.at(0))))
	{
		_type = CHAR;
	}
	else if (toascii(_s.at(_s.length() - 1)) == 'f')
	{
		for (unsigned long i = 0; i < _s.length() - 1; ++i) {
			if (!isdigit(_s.at(i)) && toascii(_s.at(i)) != '.')
				return;
		}
		_type = FLOAT;
	}
	else if (_s.find(".") != std::string::npos)
	{
		for (unsigned long i = 0; i < _s.length() - 1; ++i) {
			if (!isdigit(_s.at(i)) && toascii(_s.at(i)) != '.')
				return;
		}
		_type = DOUBLE;
	}
	else
	{
		for (unsigned long i = 0; i < _s.length(); ++i) {
			if (!isdigit(_s.at(i)))
				return;
			_type = INT;
		}
	}

}

void ScalarConverter::displayType() {
	switch (_type) {
		case INT: std::cout << "INT !\n";
			break;
		case CHAR:std::cout << "CHAR !\n";
			break;
		case DOUBLE:std::cout << "DOUBLE !\n";
			break;
		case FLOAT:std::cout << "FLOAT !\n";
			break;
		default: std::cout << "UNKNOWN !\n";
	}
}

void ScalarConverter::convert() {
	std::cout \
	<< "int: " << convertType(INT) << std::endl \
	<< "float: " <<convertType(FLOAT) << "f" << std::endl \
	<< "double: " <<convertType(DOUBLE) << std::endl \
	<< "char: " <<convertType(CHAR) << std::endl;
}
