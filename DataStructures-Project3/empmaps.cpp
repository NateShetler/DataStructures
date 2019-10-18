#include "empmaps.h"

std::vector<Employee> employees()
{
	// This will be used for the filename
	std::string fileName = "";
	// This will be for opening the file
	std::ifstream input;
	// This is the vector of employees
	std::vector<Employee> empVec;
	// This will count how many employees there are in the file
	int empCount = 0;

	// Prompt the user for a file and then get the filename
	std::cout << "Please enter the graph filename to process:" << std::endl;
	std::cin >> fileName;

	// Try to open the file, if it fails then the user will try again
	input.open(fileName.c_str());

	// Loop until the user enters a valid filename
	while (input.fail())
	{
		input.clear();
		std::cout << "Please enter a valid filename: " << std::endl;
		std::cin >> fileName;
		input.open(fileName.c_str());
	}

	// Used to tell if it is the end of a line in the file
	bool endLine = false;

	// These will be for creating the employee
	int salary = 0;
	std::string lastName = "";
	int identifier = 0;

	// Read the file in
	while (!input.eof())
	{

		while (!endLine)
		{
			// Get the input from the file
			input >> identifier;
			input >> lastName;
			input >> salary;

			// Create the employee
			Employee newEmp = Employee(identifier, lastName, salary);

			// Put the new employee onto the vector
			empVec.push_back(newEmp);

			// If the next character is \n then set bool to true
			if (input.peek() == '\n' || input.eof())
			{
				endLine = true;
			}
		}
		// Add to empCount
		++empCount;

		// Reset endline
		endLine = false;
	}

	// Close the file
	input.close();

	// Output how many employees there are
	std::cout << "Number of employees are: " << empCount << std::endl;

	// Return the vector
	return empVec;
}

/*
std::map<int, vector<Employee>> mapEmpDept(std::vector<Employee>& emp)
{

}
std::map<int, std::vector<Employee>> mapSalRange(std::vector<Employee>& emp)
{

}
void printSalRange(std::map<int, std::vector<Employee>>& salRange)
{

}
std::unordered_map<int, std::vector<Employee>> umapEmpDept(std::vector<Employee>& emp)
{

}
std::unordered_map<int, std::vector<Employee>> umapSalRange(std::vector<Employee>& emp)
{

}
void uprintSalRange(std::unordered_map<int, std::vector<Employee>>& salRange)
{

}
*/