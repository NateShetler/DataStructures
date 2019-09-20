#include "Vector.h"
#include "List.h"
#include <fstream>
#include <string>
#include <iterator>
#include <iomanip>

// This will accept two int values
// This will swap the two int values
void swap(int& first, int& second);


// This will be used in the sort function to partition the vector
int partition(Vector <int>& line, int first, int last);


// This is basically an implementation of a quicksort
// This will sort the vector in accending order.
void sort(Vector <int>& line, int first, int last);


// This function will accept an ifstream and graph
// This function will create the graph in the correct format
void createGraph(std::ifstream& input, Vector <List<int>>& graph);

// This function will output the graph data structure
void printGraph(Vector <List<int>>& graph);


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

	// Create the graph
	//createGraph(input, graph);

	// Print the graph
	//printGraph(graph);
}

// This will accept two int values
// This will swap the two int values
void swap(int& first, int& second)
{
	int temp = first;
	first = second;
	second = temp;
}

// This will be used in the sort function to partition the vector
int partition(Vector <int>& line, int first, int last)
{
	// This is the pivot point
	int pivot = line[last];

	// This is the index of the smaller element
	int indexOf = (first - 1);

	for (int i = first; i <= last - 1; i++)
	{
		// This will swap if the current element 
		// is smaller than the pivot point 
		if (line[i] < pivot)
		{
			indexOf++;
			swap(line[indexOf], line[i]);
		}
	}

	// Additional swap
	swap(line[indexOf + 1], line[last]);

	return (indexOf + 1);
}

// This is basically an implementation of a quicksort
// This will sort the vector in accending order.
void sort(Vector <int>& line, int first, int last)
{
	if (first < last)
	{
		// Partition
		int pivot = partition(line, first, last);

		// Recursively sorting the elements
		sort(line, first, pivot - 1);
		sort(line, pivot + 1, last);
	}
}

// This function will accept an ifstream and graph
// This function will create the graph in the correct format
void createGraph(std::ifstream& input, Vector <List<int>>& graph)
{
	// Used for getting input
	std::string inputString = "";
	int numInFile = 0;
	int vecInt = 0;

	// Used to tell if it is the end of a line
	// in the file
	bool endLine = false;

	Vector <Vector<int>> sorting;

	while (!input.eof())
	{
		// Create new list and push back the list onto the graph
		List<int> newList;
		graph.push_back(newList);

		while (!endLine)
		{
			input >> inputString;
			std::cout << inputString << " ";

			numInFile = std::stoi(inputString);
			graph[vecInt].push_back(numInFile);

			if (input.peek() == '\n' || input.eof())
			{
				endLine = true;
			}
		}

		std::cout << std::endl;

		// Add one to the vector integer (what keeps track of the 
		// position in the vector)
		++vecInt;

		// Reset the boolean
		endLine = false;

		//std::cout << fileName << std::endl;
	}
}
// This function will output the graph data structure
void printGraph(Vector <List<int>>& graph)
{
	for (int i = 0; i < graph.size(); ++i)
	{
		std::cout << "list" << i << " ";
		for (List<int>::iterator graphList = graph[i].begin(); graphList != graph[i].end(); ++graphList)
		{
			std::cout << *graphList << " ";
		}
		std::cout << std::endl;
	}
}