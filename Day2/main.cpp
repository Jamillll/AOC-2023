#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct SubGame
{
	int r = 0;
	int g = 0;
	int b = 0;
};

struct Game 
{
	int ID = 0;
	std::vector<SubGame> values;

	void Display()
	{
		std::cout << "Game " << ID << ": ";
		
		for (size_t i = 0; i < values.size(); i++)
		{
			std::cout << values[i].r << " red, ";
			std::cout << values[i].g << " green, ";
			std::cout << values[i].b << " blue";
			std::cout << "; ";
		}

		std::cout << std::endl;
	}
};

int main(int argc, char* argv[])
{
	using namespace std;

	if (argc != 2)
	{
		cout << "Please open the program with a txt file" << endl;
		return 1;
	}

	fstream file(argv[1]);
	string input;
	vector<Game> games;
	int index = 1;

	while (getline(file, input))
	{
		Game currentGame;
		currentGame.values.push_back({0, 0, 0});
		int currentValueInQuestion = 0;

		for (size_t i = 0; i < input.length(); i++)
		{
			if (input[i] == ':')
			{
				currentGame.ID = index;
			}

			else if (input[i] == ';')
			{
				currentGame.values.push_back({0, 0, 0});
				currentValueInQuestion++;
			}

			else if (input[i] == 'r' && input[i - 1] != 'g')
			{
				if (input[i - 3] != ' ')
				{
					currentGame.values[currentValueInQuestion].r = ((input[i - 3] - 48) * 10) + input[i - 2] - 48;
				}

				else currentGame.values[currentValueInQuestion].r = input[i - 2] - 48;
			}

			else if (input[i] == 'g')
			{
				if (input[i - 3] != ' ')
				{
					currentGame.values[currentValueInQuestion].g = ((input[i - 3] - 48) * 10) + input[i - 2] - 48;
				}

				else currentGame.values[currentValueInQuestion].g = input[i - 2] - 48;
			}

			else if (input[i] == 'b')
			{
				if (input[i - 3] != ' ')
				{
					currentGame.values[currentValueInQuestion].b = ((input[i - 3] - 48) * 10) + input[i - 2] - 48;
				}

				else currentGame.values[currentValueInQuestion].b = input[i - 2] - 48;
			}
		}

		currentGame.Display();
		games.push_back(currentGame);
		index++;

	}file.close();

	SubGame loseCondition = {12, 13, 14};

	int powerSum = 0;
	int finalSum = 0;
	for (size_t i = 0; i < games.size(); i++)
	{
		bool isValidGame = true;
		SubGame minValues = { 0, 0, 0 };

		for (size_t j = 0; j < games[i].values.size(); j++)
		{
			if (games[i].values[j].r > loseCondition.r || games[i].values[j].g > loseCondition.g || games[i].values[j].b > loseCondition.b)
			{
				isValidGame = false;
			}

			if (games[i].values[j].r > minValues.r) minValues.r = games[i].values[j].r;
			if (games[i].values[j].g > minValues.g) minValues.g = games[i].values[j].g;
			if (games[i].values[j].b > minValues.b) minValues.b = games[i].values[j].b;
		}

		powerSum += (minValues.r * minValues.g * minValues.b);

		if (isValidGame) finalSum += games[i].ID;
	}

	cout << "Sum of winning sets: " << finalSum << endl;
	cout << "Sum of min powers: " << powerSum << endl;
}