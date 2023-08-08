#include "ScalarConverter.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "invalid argument number\n";
		return (1);
	}

	ScalarConverter c;
	c.setStr(av[1]);
	c.setType();
	c.displayType();
	c.convert();
}