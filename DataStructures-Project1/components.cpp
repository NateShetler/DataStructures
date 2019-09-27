#include "Vector.h"
#include "List.h"
#include <fstream>
#include <string>
#include <iterator>
#include <iomanip>

// Pre: This function will accept an ifstream and graph
// Post: This function will create the graph in the correct format
void createGraph(std::ifstream& input, Vector <List<int>>& graph);

// Pre: This function will accept in a vector of lists of ints (graph) by reference
// Post: This function will output the graph data structure
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
				if (graph[firstNum].size() > graph[secondNum].size())
				{
					graph[firstNum].mergeNoDups(graph[secondNum]);

					// This iterator will be used to remove the smaller element
					Vector<List<int>>::iterator eraseIt= graph.begin() + secondNum;
					graph.erase(eraseIt);
				}
				else
				{
					graph[secondNum].mergeNoDups(graph[firstNum]);

					// This iterator will be used to remove the smaller element
					Vector<List<int>>::iterator eraseIt2 = graph.begin() + firstNum;
					graph.erase(eraseIt2);
				}

				// Print the graph
				printGraph(graph);
			}
		}
	}

}


// Pre: This function will accept an ifstream and graph
// Post: This function will create the graph in the correct format
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

		// Create a new list
		List<int> newList;

		// Push list onto graph
		graph.push_back(newList);

		while (!endLine)
		{
			// Get the input and convert to int
			input >> inputString;
			numInFile = std::stoi(inputString);

			// Get the insertion point
			List<int>::iterator insertPlace = graph[vecInt].find_gt(graph[vecInt].begin(), graph[vecInt].end(), numInFile);

			// Insert the integer
			graph[vecInt].insert(insertPlace, numInFile);

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
	}
}

// Pre: This function will accept in a vector of lists of ints (graph) by reference
// Post: This function will output the graph data structure
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