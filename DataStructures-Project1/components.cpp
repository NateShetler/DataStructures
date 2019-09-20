#include "Vector.h"
#include "List.h"
#include <fstream>
#include <string>
#include <iterator>
#include <iomanip>

// This function will accept an ifstream and graph
// This function will create the graph in the correct format
void createGraph(std::ifstream &input, Vector <List<int>>& graph)
{
	// For testing purposes
	std::string inputString = "";
	int numInFile = 0;
	int vecInt = 0;

	bool endLine = false;

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
	createGraph(input, graph);

	// Print the graph
	printGraph(graph);
}