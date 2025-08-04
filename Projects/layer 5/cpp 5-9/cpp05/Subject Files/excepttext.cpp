#include <stdexcept>
#include <iostream>

int main(void)
{
	try
	{
		if (1 != 2)
		{
			throw std::exception();
		}
		else
		{
			std::cout << "else" << std::endl;
		}
	}
	catch (std::exception e)
	{
		std::cout << "called it" << std::endl;
	}
}