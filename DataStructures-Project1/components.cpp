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
	// This will be used for the merge loop
	bool quit = false;
	// These will be used for the merging loop
	int firstNum = 0, secondNum = 0;
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

	List<int> list1;
	List<int> list2;

	list1.push_back(1);
	list1.push_back(2);
	list1.push_back(4);
	list1.push_back(5);
	list2.push_back(2);
	list2.push_back(3);
	list2.push_back(4);

	//Need to fix commonElement
	if (list1.commonElement(list2))
	{
		std::cout << "Common element found" << std::endl;
	}
	else
	{
		std::cout << "No common elements" << std::endl;
	}
	
	// Create the graph
	createGraph(input, graph);

	// Print the graph
	printGraph(graph);

	// Looping to see if the user wants to merge any lists
	while (!quit)
	{
		std::cout << "Enter two list ids to potentially merge together or -1 to quit: " << std::endl;
		std::cin >> firstNum;

		// Check to see if the user enters -1 or less
		if (firstNum < 0)
		{
			quit = true;
		}
		else
		{
			std::cin >> secondNum;
		}
		
		// Checking to see if the user enters valid values
		if (std::cin.fail() || (firstNum > graph.size()) || (secondNum > graph.size()))
		{
			std::cout << "Please only enter integers that are in the range of the graph." << std::endl;
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else
		{
			// Double checking to see if the user entered a value less than 0
			if ((firstNum < 0) || (secondNum < 0))
			{
				quit = true;
			}
			else
			{
				// Merging the functions based on size.
				if (firstNum > secondNum)
				{
					graph[secondNum].mergeNoDups(graph[firstNum]);
				}
				else
				{
					graph[firstNum].mergeNoDups(graph[secondNum]);
				}

				// Print the graph
				printGraph(graph);
			}
		}
	}
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
		Vector<int> newVec;
		sorting.push_back(newVec);

		while (!endLine)
		{
			// Get the input and convert to int
			input >> inputString;
			numInFile = std::stoi(inputString);
			sorting[vecInt].push_back(numInFile);

			// If the next character is \n then set bool to true
			if (input.peek() == '\n' || input.eof())
			{
				endLine = true;
			}
		}

		// Add one to the vector integer (what keeps track of the 
		// position in the vector)
		++vecInt;

		// Reset the boolean
		endLine = false;

		//std::cout << fileName << std::endl;
	}

	// Sort the vectors and creating the graph
	for (int i = 0; i < sorting.size(); ++i)
	{
		sort(sorting[i], 0, sorting[i].size() - 1);
		List<int> newList;
		graph.push_back(newList);

		for (int j = 0; j < sorting[i].size(); ++j)
		{
			graph[i].push_back(sorting[i][j]);
		}
	}
}

// This function will output the graph data structure
void printGraph(Vector <List<int>>& graph)
{
	std::cout << "The adjacency list for your graph is: " << std::endl;
	// Output the graph
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