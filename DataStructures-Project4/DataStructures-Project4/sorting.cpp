#include <iostream>
#include <fstream>
#include "quicksort.h"
#include "heapsort.h"
#include "mergesort.h"
#include "insertsort.h"


void reverseOrder(std::vector<int>& fillVec, int& size);

void randomOrder(std::vector<int>& fillVec, int& size);

void standardOrder(std::vector<int>& fillVec, int& size);

int main()
{
	// This will be used for the filename
	std::string fileName = "";
	// This will be for opening the file
	std::ifstream input;

	// Prompt the user for a file and then get the filename
	std::cout << "Enter file of data to process: ";
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

	// Integer used to stor how many numbers the user wants sorted
	int howManyInts = 0;

	// Get how many numbers the user wants sorted
	std::cout << "Enter the number of integers to sort: ";
	std::cin >> howManyInts;

	// Go until the user enters a valid integer
	while (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "Please enter a valid integer: " << std::endl;
		std::cin >> howManyInts;
	}

	// Vector of vectors for sorting 
	std::vector<std::vector<int>> sortingVecs;
	// Create vector frame
	for (int i = 0; i < 4; ++i)
	{
		std::vector<int> insideVec;
		sortingVecs.push_back(insideVec);
	}
	
	// Used for the integer in the file
	int fileInt = 0;

	// Reading the data from the file into the vector
	// This will work if there is one number on each line
	// of the input file
	while (!input.eof())
	{
		input >> fileInt;
		sortingVecs[0].push_back(fileInt);
		sortingVecs[1].push_back(fileInt);
		sortingVecs[2].push_back(fileInt);
		sortingVecs[3].push_back(fileInt);
	}

	input.close();
	
	// This will display the unsorted and sorted vectors
	for (int j = 0; j < 4; ++j)
	{
		if (j == 0)
		{
			std::cout << "vector before heap sort: ";
		}
		else if (j == 1)
		{
			std::cout << "vector before merge sort: ";
		}
		else if (j == 2)
		{
			std::cout << "vector before quick sort (no cutoff): ";
		}
		else
		{
			std::cout << "vector before insertion sort: ";
		}

		// Display the unsorted vector for each sorting type
		for (int i = 0; i < sortingVecs[j].size(); ++i)
		{
			std::cout << sortingVecs[j][i] << " ";
		}
		std::cout << std::endl;

		// Do the sorting 
		if (j == 0)
		{
			std::cout << "vector after heap sort: ";
			heapsort(sortingVecs[j]);
		}
		else if (j == 1)
		{
			std::cout << "vector after merge sort: ";
			mergeSort(sortingVecs[j]);
		}
		else if (j == 2)
		{
			std::cout << "vector after quick sort (no cutoff): ";
			quicksort(sortingVecs[j]);
		}
		else
		{
			std::cout << "vector after insertion sort: ";
			insertionSort(sortingVecs[j].begin(), sortingVecs[j].end());
		}

		// Displaying sorted vector
		for (int i = 0; i < sortingVecs[j].size(); ++i)
		{
			std::cout << sortingVecs[j][i] << " ";
		}
		std::cout << std::endl;

		// Add a space in between each type of sort
		std::cout << std::endl;
	}
}

// Pre: this function will accept in a vector that needs filled 
// and an integer that is the size of the desired vector
// Post: the vector will be filled with random numbers
void randomOrder(std::vector<int>& fillVec, int& size)
{
	// For random number
	int random = 0;

	// Seed the random number
	srand(time(0));

	for (int i = 0; i < size; ++i)
	{
		random = rand() % 0;
		fillVec.push_back(random);
	}
}

void standardOrder(std::vector<int>& fillVec, int& size)
{
	for (int i = 0; i < size; ++i)
	{

	}
}

void reverseOrder(std::vector<int>& fillVec, int& size)
{
	for (int i = )
}