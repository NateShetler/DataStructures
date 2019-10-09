#include <iostream>
#include <stack>
#include <string>
#include <cctype>

// Pre: This function will not accept any parameters
// Post: This function will evaluate a postfix expression entered by the user
void evalPostfix(std::string &entireExpression);

// Pre: This function will accept in a string
// Post: This function will return an integer
// This function will help determine when to pop things off of the stack,
// returns 2 for multiply or divide and 1 for add or subtract, and 0 for something else
int setPrecedence(std::string& infixCharacter);

// Pre: This function will accept in an infix expression that is correctly formatted
// Post: This function will convert the infix expression to a postfix expression and then
// it will call evalPostfix to output the evaluation of the converted function
void infixToPostfix(std::string &infixExpression);

int main()
{
	// For getting user input
	int userInput = -1;
	// For keeping track of the loop
	bool quit = false;
	// This will be used for the users expression
	std::string entireExpression = "";

	while (!quit)
	{
		std::cout << "0. Exit" << std::endl;
		std::cout << "1. Infix to postfix" << std::endl;
		std::cout << "2. Postfix evaluation" << std::endl;

		// Get user input
		std::cout << "Please enter a menu option [0-2]:" << std::endl;
		std::cin >> userInput;

		// Deal with bad input type
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			userInput = -1;
		}

		// The below if statements will determine what the user wants to do and
		// then go through the processess necessary based on what they pick.
		if (userInput == 1)
		{
			// Clearing the input stream
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			// Get the users infix expression
			std::cout << "Please enter an infix expression: " << std::endl;
			std::getline(std::cin, entireExpression);

			// To make output look nicer
			std::cout << std::endl;

			// Call the function to change infix to postfix and then
			// display the postfix evaluation
			infixToPostfix(entireExpression);
		}
		else if (userInput == 2)
		{
			// Clearing the input stream
			std::cin.clear();
			std::cin.ignore(1000, '\n');

			// Get the valid postfix expression, evalPostfix will determine if it is valid
			std::cout << "Please enter a valid postfix expression to evaluate: " << std::endl;
			std::getline(std::cin, entireExpression);

			// To mak output look nicer
			std::cout << std::endl;

			// Call the function to evaluate the postfix expression
			evalPostfix(entireExpression);
		}
		else if (userInput == 0)
		{
			// set quit boolean to true to end the program
			quit = true;
		}
		else
		{
			// Let the user know the values that are valid input
			std::cout << "Please enter only 0, 1, or 2." << std::endl;

			// To make it look better
			std::cout << std::endl;
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

	// For keeping track of how many operators and
	// numbers that you have.
	int operatorCount = 0;
	int numberCount = 0;

	// For keeping track of if there are too many operators
	bool tooMany = false;

	// Go through the user input until a new line is reached.
	while (entireExpression.length() > 0 && !tooMany)
	{
		// Get each thing in the string
		userExpression = entireExpression.substr(0, entireExpression.find(' '));

		// Make a substring if it's not the last operator or operand
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
			// Convert the string to a double
			double inputNum = std::stod(userExpression);
			// Push the double onto the stack
			numbers.push(inputNum);
			// Add to number count
			++numberCount;
		}
		else
		{
			// This block is if the thing from the expressions is not a number

			// Make sure there are enough numbers on the stack to perform an operation
			if (numbers.size() >= 2)
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

					// Add to operator count
					++operatorCount;
				}
				else if (userExpression == "/")
				{
					numbers.push(operand2 / operand1);

					// Add to operator count
					++operatorCount;
				}
				else if (userExpression == "+")
				{
					numbers.push(operand2 + operand1);

					// Add to operator count
					++operatorCount;
				}
				else if (userExpression == "-")
				{
					numbers.push(operand2 - operand1);

					// Add to operator count
					++operatorCount;
				}
			}
			else
			{
				// If there are too many operators then set the boolean to true and let the
				// user know of their mistake

				// Setting too many to true
				tooMany = true;

				// If the user entered an expression with too many operators
				std::cout << "This is not a valid postfix expression: too many operators." << std::endl;
			}

		}
	}

	// Outputting expression evaluation if the postfix expression was valid
	if (((numberCount - operatorCount) == 1) && (!tooMany))
	{
		// Output the evaluation
		std::cout << "Your expression evaluates to " << numbers.top() << std::endl;
	}
	else if ((numberCount - operatorCount) > 1)
	{
		// If the user entered an expression with too few operators
		std::cout << "This is not a valid postfix expression: too few operators." << std::endl;
	}

	// To make the program look nicer :)
	std::cout << std::endl;

}

// Pre: This function will accept in a string
// Post: This function will return an integer
// This function will help determine when to pop things off of the stack,
// returns 2 for multiply or divide and 1 for add or subtract, and 0 for something else
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

	while (infixExpression.length() > 0)
	{
		// Get each thing in the string
		conversionTool = infixExpression.substr(0, infixExpression.find(' '));

		// Make a substring if it's not the last operator or operand
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

				// Boolean used for quitting the loop
				bool quitPop = false;

				while (!quitPop && !infixCharacters.empty())
				{
					if ((setPrecedence(infixCharacters.top())) >= (setPrecedence(conversionTool)))
					{
						// Add the item to the postfix expression
						postFixExpression += (infixCharacters.top() + " ");

						// Pop the item off
						infixCharacters.pop();
					}
					else
					{
						// Set the boolean to true to quit the loop
						quitPop = true;
					}
				}

				// Push the operator onto the stack
				infixCharacters.push(conversionTool);
			}
		}

	}

	// Pop off the remaining items
	for (int i = 0; i < infixCharacters.size() + 1; ++i)
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
