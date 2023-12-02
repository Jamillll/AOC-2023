#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int TwoCharToInt(char a, char b)
{
	return ((a - 48) * 10) + (b - 48);
}

int main()
{
	using namespace std;
	fstream file("C:\\Programs\\AOC-2023\\Day1\\input.txt");

	string validNumbers[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

	string input;
	int runningTotal = 0;
	
	while (getline(file, input))
	{
		vector<char> numberVector;
		for (int inputChar = 0; inputChar < input.length(); inputChar++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (input[inputChar] - 48 == j)
				{
					numberVector.push_back(input[inputChar]);
					continue;
				}
			}

			for (int currentValidNumber = 0; currentValidNumber < 10; currentValidNumber++)
			{
				for (int k = 0; k < validNumbers[currentValidNumber].length(); k++)
				{
					if (inputChar + k > input.length())
					{
						break;
					}

					if (input[inputChar + k] != validNumbers[currentValidNumber][k])
					{
						break;
					}

					if (k == validNumbers[currentValidNumber].length() - 1)
					{
						numberVector.push_back(currentValidNumber + 48);
					}
				}
			}
		};

		if (numberVector.size() != 0)
		{
			int currentNumber = TwoCharToInt(numberVector[0], numberVector[numberVector.size() - 1]);
			runningTotal += currentNumber;

			cout << currentNumber << endl;
		}
		else cout << "Empty Line" << endl;
	}

	cout << "Final answer: " << runningTotal << endl;

	file.close();
}