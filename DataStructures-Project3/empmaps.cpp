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
	std::cout << "Enter file of employee data to process: ";
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
			Employee newEmp{identifier, lastName, salary};

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


std::map<int, std::vector<Employee>> mapEmpDept(std::vector<Employee>& emp)
{
	// For keeping track of the runtime
	clock_t start, stop;
	start = clock();
	// The department map
	std::map<int, std::vector<Employee>> deptMap;
	// First four digits int
	int firstFour = 0;

	// Create the department map
	for (int i = 0; i < emp.size(); ++i)
	{
		// This will get the first four digits of the 
		// identifier integer
		firstFour = emp[i].id() / 100;

		// Put the new item into the map
		deptMap[firstFour].push_back(emp[i]);
	}

	stop = clock();
	std::cout << "ORDERED Map creation with department as key clock ticks: " << double(stop - start) << std::endl;
	std::cout << "ORDERED Map number of departments: " << deptMap.size() << std::endl;

	// Return the department map
	return deptMap;
}

std::map<int, std::vector<Employee>> mapSalRange(std::vector<Employee>& emp)
{
	// For keeping track of the runtime
	clock_t start, stop;
	start = clock();
	// The department map
	std::map<int, std::vector<Employee>> salMap;
	// First four digits int
	int salaryRange = 0;

	// Create the salary map
	for (int i = 0; i < emp.size(); ++i)
	{
		salaryRange = emp[i].sal();

		// This will create the salary range in the form that
		// it should be (it will get rid of anything before the tens thousands
		// place)
		salaryRange = salaryRange / 10000;
		salaryRange = salaryRange * 10000;

		// Put the new item into the map 
		salMap[salaryRange].push_back(emp[i]);
	}

	stop = clock();
	std::cout << "ORDERED Map creation with salary as key clock ticks: " << double(stop - start) << std::endl;
	std::cout << "ORDERED Map number of salary ranges: " << salMap.size() << std::endl;

	// Return the department map
	return salMap;
}


void printSalRange(std::map<int, std::vector<Employee>>& salRange)
{
	// For keeping track of the largest vector
	int largestNum = 0;
	int largestGroup = 0;

	// This will go through the map
	for (std::map<int, std::vector<Employee>>::iterator salIt = salRange.begin(); salIt != salRange.end(); ++salIt)
	{
		std::cout << "ORDERED Map Salary Range " << salIt->first << " contains " << salIt->second.size() << std::endl;

		// Determine the largest salary group
		if (salIt->second.size() > largestNum)
		{
			largestNum = salIt->second.size();
			largestGroup = salIt->first;
		}
	}

	std::cout << "ORDERED Map Salary Range with most employees: " << largestGroup << " containing " << largestNum << " employees " << std::endl;

	// For formatting
	std::cout << std::endl;
}

std::unordered_map<int, std::vector<Employee>> umapEmpDept(std::vector<Employee>& emp)
{
	// For keeping track of the runtime
	clock_t start, stop;
	start = clock();
	// The department map
	std::unordered_map<int, std::vector<Employee>> deptMap;
	// First four digits int
	int firstFour = 0;

	// Create the department map
	for (int i = 0; i < emp.size(); ++i)
	{
		// This will get the first four digits of the 
		// identifier integer
		firstFour = emp[i].id() / 100;

		// Put the new item into the map
		deptMap[firstFour].push_back(emp[i]);
	}

	stop = clock();
	std::cout << "UNORDERED Map creation with department as key clock ticks: " << double(stop - start) << std::endl;
	std::cout << "UNORDERED Map number of departments: " << deptMap.size() << std::endl;

	// Return the department map
	return deptMap;
}

std::unordered_map<int, std::vector<Employee>> umapSalRange(std::vector<Employee>& emp)
{
	// For keeping track of the runtime
	clock_t start, stop;
	start = clock();
	// The department map
	std::unordered_map<int, std::vector<Employee>> salMap;
	// First four digits int
	int salaryRange = 0;

	// Create the salary map
	for (int i = 0; i < emp.size(); ++i)
	{
		salaryRange = emp[i].sal();

		// This will create the salary range in the form that
		// it should be (it will get rid of anything before the tens thousands
		// place)
		salaryRange = salaryRange / 10000;
		salaryRange = salaryRange * 10000;

		// Put the new item into the map 
		salMap[salaryRange].push_back(emp[i]);
	}

	stop = clock();
	std::cout << "UNORDERED Map creation with salary as key clock ticks: " << double(stop - start) << std::endl;
	std::cout << "UNORDERED Map number of salary ranges: " << salMap.size() << std::endl;

	// Return the department map
	return salMap;
}

void uprintSalRange(std::unordered_map<int, std::vector<Employee>>& salRange)
{
	// For keeping track of the largest vector
	int largestNum = 0;
	int largestGroup = 0;

	// This will go through the map
	for (std::unordered_map<int, std::vector<Employee>>::iterator salIt = salRange.begin(); salIt != salRange.end(); ++salIt)
	{
		std::cout << "UNORDERED Map Salary Range " << salIt->first << " contains " << salIt->second.size() << std::endl;

		// Determine the largest salary group
		if (salIt->second.size() > largestNum)
		{
			largestNum = salIt->second.size();
			largestGroup = salIt->first;
		}
	}

	std::cout << "UNORDERED Map Salary Range with most employees: " << largestGroup << " containing " << largestNum << " employees " << std::endl;

	// For formatting
	std::cout << std::endl;
}

