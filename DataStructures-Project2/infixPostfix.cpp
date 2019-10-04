#include <iostream>
#include <stack>
#include <string>
#include <cctype>

// Pre: This function will not accept any parameters
// Post: This function will evaluate a postfix expression entered by the user
void evalPostfix();

int main()
{
	// For getting user input
	int userInput = 0;
	// For keeping track of the loop
	bool quit = false;

	while (!quit)
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
			evalPostfix();
		}
		else if (userInput == 0)
		{
			quit = true;
		}
		else
		{
			std::cout << "Please enter only 0, 1, or 2." << std::endl;
		}
	}
}

// Pre: This function will not accept any parameters
// Post: This function will evaluate a postfix expression entered by the user
void evalPostfix()
{
	// This is a string for the user entered expression
	std::string userExpression = " ";
	// These will be used for the operands
	double operand1 = 0.0, operand2 = 0.0;
	// This will be the stack used for storing the numbers entered
	std::stack<double> numbers;

	// Clearing the input stream
	std::cin.clear();
	std::cin.ignore(1000, '\n');

	std::cout << "Please enter a valid postfix expression to evaluate: " << std::endl;

	// Go through the user input until a new line is reached. 
	while (std::cin.peek() != '\n')
	{
		// Get the user input one thing at a time
		std::cin >> userExpression;

		// If the thing is a double push onto the stack
		if (std::isdigit(userExpression[0]))
		{
			double inputNum = std::stod(userExpression);
			numbers.push(inputNum);
		}
		else
		{
			// Get the operands and then pop them off the stack
			operand1 = numbers.top();
			numbers.pop();
			operand2 = numbers.top();
			numbers.pop();

			// Checking to see which operator it is and then do the operation
			// and push it onto the stack
			if (userExpression == "*")
			{
				numbers.push(operand2 * operand1);
			}
			else if (userExpression == "/")
			{
				numbers.push(operand2 / operand1);
			}
			else if (userExpression == "+")
			{
				numbers.push(operand2 + operand1);
			}
			else if (userExpression == "-")
			{
				numbers.push(operand2 - operand1);
			}
		}
	}

	// Output the evaluation
	std::cout << "Your expression evaluates to " << numbers.top() << std::endl;
}