#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cstdlib>

// Pre: This function will not accept any parameters
// Post: This function will evaluate a postfix expression entered by the user
void evalPostfix(std::string &entireExpression);

// Pre: This functin will accept in a char
// Post: This function will return an integer
// This function will help determine when to pop things off of the stack,
// returns 2 for multiply or divide and 1 for add or subtract
int setPrecedence(std::string& infixCharacter);

// Pre: This function will accept in an infix expression that is correctly formatted
// Post: This function will convert the infix expression to a postfix expression and then
// it will call evalPostfix to output the evaluation of the converted function
void infixToPostfix(std::string &infixExpression);

int main()
{
	// For getting user input
	int userInput = 0;
	// For keeping track of the loop
	bool quit = false;
	// This will be used for the users expression
	std::string entireExpression = "";

	while (!quit)
	{
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Infix to postfix" << std::endl;
		std::cout << "2. Postfix evaluation" << std::endl;
		std::cout << "Please enter a menu option [0-2]:" << std::endl;
		std::cin >> userInput;

		if (userInput == 1)
		{
			// Clearing the input stream
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			std::cout << "Please enter an infix expression: " << std::endl;
			std::getline(std::cin, entireExpression);
			infixToPostfix(entireExpression);
		}
		else if (userInput == 2)
		{
			// Clearing the input stream
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			std::cout << "Please enter a valid postfix expression to evaluate: " << std::endl;
			std::getline(std::cin, entireExpression);
			evalPostfix(entireExpression);
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
void evalPostfix(std::string &entireExpression)
{
	// This is a string for the user entered expression
	std::string userExpression = " ";
	// These will be used for the operands
	double operand1 = 0.0, operand2 = 0.0;
	// This will be the stack used for storing the numbers entered
	std::stack<double> numbers;


	// Go through the user input until a new line is reached.
	while (entireExpression.length() > 0)
	{
		// Get each thing in the string
		userExpression = entireExpression.substr(0, entireExpression.find(' '));

		// Make a substring if the it's not the last operator or operand
		if (entireExpression.find(' ') != std::string::npos && entireExpression[0] != ' ')
		{
			entireExpression = entireExpression.substr(userExpression.length() + 1, entireExpression.length());
		}
		else
		{
			entireExpression = "";
		}

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

	// To make the program look nice :)
	std::cout << std::endl;

}

// Pre: This functin will accept in a char
// Post: This function will return an integer
// This function will help determine when to pop things off of the stack,
// returns 2 for multiply or divide and 1 for add or subtract, and 0 for neither
int setPrecedence(std::string &infixCharacter)
{

	if (infixCharacter == "/" || infixCharacter == "*")
	{
		return 2;
	}
	else if (infixCharacter == "-" || infixCharacter == "+")
	{
		return 1;
	}

	return 0;
}

// Pre: This function will accept in an infix expression that is correctly formatted
// Post: This function will convert the infix expression to a postfix expression and then
// it will call evalPostfix to output the evaluation of the converted function
void infixToPostfix(std::string &infixExpression)
{
	// Stack for keeping track of operators and parenthesis
	std::stack<std::string> infixCharacters;
	// String for creating the postfix
	std::string postFixExpression = "";
	// String for going through the infix expression
	std::string conversionTool = "";
	// Will be used for putting char on postfix conversion
	std::string postOperator = "";

	while (infixExpression.length() > 0)
	{
		// Get each thing in the string
		conversionTool = infixExpression.substr(0, infixExpression.find(' '));

		// Make a substring if the it's not the last operator or operand
		if (infixExpression.find(' ') != std::string::npos && infixExpression[0] != ' ')
		{
			infixExpression = infixExpression.substr(conversionTool.length() + 1, infixExpression.length());
		}
		else
		{
			infixExpression = "";
		}

		// If the item is a number the add it to the postfix expression
		if (std::isdigit(conversionTool[0]))
		{
			postFixExpression += (conversionTool + " ");
		}
		else
		{
			// If the item is an opening parenthesis then push it onto the stack
			if (conversionTool == "(")
			{
				infixCharacters.push(conversionTool);
			}
			else if (conversionTool == ")")
			{
				// Pop off operators until you get to the second parenthesis
				while (infixCharacters.top() != "(")
				{
					// Add the item to the postfix expression
					postFixExpression += (infixCharacters.top() + " ");

					// Pop the item off
					infixCharacters.pop();
				}

				// Pop the parenthesis off
				infixCharacters.pop();
			}
			else
			{
				// This will pop operators off the stack if they have a higher or equal
				// precedence than the current operator

				bool quitPop = false;

				while (!quitPop)
				{
					if (infixCharacters.empty())
					{
						quitPop = true;

					}
					else if ((setPrecedence(infixCharacters.top())) >= (setPrecedence(conversionTool)))
					{
						// Add teh item to the postfix expression
						postFixExpression += (infixCharacters.top() + " ");

						// Pop the item off
						infixCharacters.pop();
					}
					else
					{
						quitPop = true;
					}
				}

				// Push the operator onto the stack
				infixCharacters.push(conversionTool);
			}
		}

	}

	// Pop off the remaining items
	for (int i = 0; i < infixCharacters.size(); ++i)
	{
		postFixExpression += (infixCharacters.top() + " ");

		// Pop it off the stack
		infixCharacters.pop();
	}

	std::cout << "The postfix expression is: " << std::endl;
	std::cout << postFixExpression << std::endl;

	// Evaluate the converted expression
	evalPostfix(postFixExpression);
}
