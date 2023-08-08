#pragma once

#include <iostream>
#include <fstream>
#include <limits>

enum e_type
{
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	UNKNOWN
};

#define MAX_INT 2147483647
#define MIN_INT -2147483648
class ScalarConverter {
private:
	char    _char;
	int     _integer;
	float   _float;
	double  _double;
	e_type	_type;
	std::string _s;
public:
	ScalarConverter();
	ScalarConverter(const ScalarConverter &c);
	~ScalarConverter();
	ScalarConverter &operator=(const ScalarConverter &c);

	char    getChar(void) const;
	int     getInt(void) const;
	float   getFloat( void ) const;
	double  getDouble( void ) const;

	void setStr(std::string s);

	void    convert();
//	bool    isChar() const;
//	bool    isInt() const;
//	bool    isFloat() const;
//	bool    isDouble() const;
//
//	bool    isImpossible();
	//bool    isLiterals() const;
	//void	printConvert();
	void setType();
	void displayType();
	std::string convertType(int e);
	class ImpossibleCharConversion : public std::exception {
		virtual const char* what() const throw() {return "ICC";}
	};
	class NonDisplayableChar : public std::exception {
		virtual const char* what() const throw() { return "NDC"; }
	};
};

std::ostream& operator<<(std::ostream& out, const ScalarConverter &c);