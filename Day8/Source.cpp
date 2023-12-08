#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Node
{
	std::string id = "";
	std::string left = "";
	std::string right = "";

	void display()
	{
		std::cout << id << " = (" << left << ", " << right << ")" << std::endl;
	}
};

bool isLetterOrDigit(char input)
{
	if (input - 65 >= 0 && input - 65 < 26)
	{
		return true;
	}
	else if (input - 48 >= 0 && input - 48 < 10)
	{
		return true;
	}
	else return false;
}

int main(int argc, char* argv[])
{
	using namespace std;

	if (argc != 2) return 1;

	fstream file(argv[1]);
	string input;
	
	string instructions = "";
	bool gotInstructions = false;

	vector<Node> nodes;

	while (getline(file, input))
	{
		if (!gotInstructions)
		{
			if (input[0] != 'L' && input[0] != 'R')
			{
				gotInstructions = true;
			}

			else for (size_t i = 0; i < input.size(); i++)
			{
				instructions += input[i];
			}
		}

		else
		{
			Node currentNode;

			for (size_t i = 0; i < input.size(); i++)
			{
				if (!isLetterOrDigit(input[i]))
				{
					continue;
				}

				if (currentNode.id.size() != 3)
				{
					currentNode.id += input[i];
				}
				else if (currentNode.left.size() != 3)
				{
					currentNode.left += input[i];
				}
				else
				{
					currentNode.right += input[i];
				}
			}

			nodes.push_back(currentNode);
		}
	}

	cout << instructions << endl;
	for (size_t i = 0; i < nodes.size(); i++) nodes[i].display();

	string startingID = "AAA";
	string endingID = "ZZZ";
	int placeInList = 0;
	int instructionsCount = 1;
	
	for (size_t i = 0; i < nodes.size(); i++)
	{
		if (nodes[i].id == startingID) placeInList = i;
	}

	bool reachedEnd = false;
	while (!reachedEnd)
	{
		for (size_t i = 0; i < instructions.size(); i++)
		{ 
			cout << instructions[i] << endl;

			string lookingFor = "";

			if (instructions[i] == 'L') lookingFor = nodes[placeInList].left;
			if (instructions[i] == 'R') lookingFor = nodes[placeInList].right;

			for (size_t i = 0; i < nodes.size(); i++)
			{
				if (nodes[i].id == lookingFor)
				{
					placeInList = i;
				}
			}

			if (nodes[placeInList].id == endingID)
			{
				reachedEnd = true;
				break;
			}

			instructionsCount++;
		}
	}

	cout << "Finished in " << instructionsCount << " Moves" << endl;
}