#include "Vector.h"
#include "List.h"
#include <fstream>
#include <string>
#include <iterator>

int main()
{
	// Creating adjacency list to hold graph
	Vector <List<int>> graph;
	// This will be used for the filename
	std::string fileName = "";
	// This will be for opening the file
	std::ifstream input;

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

	// Outputting file (used for testing)
	while (!input.eof())
	{
		getline(input, fileName);
		std::cout << fileName << std::endl;
	}

	// This block of code is for testing the find_gt() function
	{
		List<int> test;

		for (int i = 0; i < 6; ++i)
		{
			test.push_back(i);
		}

		test.find_gt(test.begin(), test.end(), 4);

		std::cout << std::endl;

		List<int>::iterator ptr;
		for (ptr = test.begin(); ptr != test.end(); ++ptr)
		{
			std::cout << *ptr << " ";
		}

		ptr = test.find_gt(test.begin(), test.end(), 3);

		std::cout << *ptr << std::endl;
	}
	

}