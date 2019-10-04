#include <iostream>
#include <stack>

int main()
{
	int userInput;

	while (userInput != 0)
	{
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Infix to postfix" << std::endl;
		std::cout << "2. Postfix evaluation" << std::endl;
		std::cout << "Please enter a menu option [0-2]:" << std::endl;
		std::cin >> userInput;

		if (userInput == 1)
		{

		}
		else if (userInput == 2)
		{

		}
		else if (userInput != 0)
		{
			std::cout << "Please enter only 0, 1, or 2." << std::endl;
		}
	}
}