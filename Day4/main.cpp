#include <iostream>
#include <string>
#include <fstream>
#include <vector>

enum stages
{
	id,
	winningNumbers,
	ownedNumbers
};

struct stringNumber
{
	std::string number;
	const std::string empty = "...";

	void push(char input)
	{
		for (size_t i = 0; i < number.size(); i++)
		{
			if (number[i] == empty[0])
			{
				number[i] = input;
				break;
			}
		}
	}
};

struct Card
{
	unsigned int ID = 0;
	std::vector<int> winningNumbers;
	std::vector<int> ownedNumbers;
	std::vector<int> matches;
};

bool charIsNumber(char input)
{
	if (input - 48 >= 0 && input - 48 < 10)
	{
		return true;
	}
	else return false;
}

int charsToInt(stringNumber input)
{
	int total = 0;

	for (size_t i = 0; i < 3; i++)
	{
		if (charIsNumber(input.number[i]) && input.number[i] - 48 != 0)
		{
			total += (input.number[i] - 48);
			if (i > 0) total *= 10;
		}
	}

	return total;
}

int main(int argc, char* argv[])
{
	using namespace std;

	if (argc != 2)
	{
		cout << "Please provide a path to the input";
		return 1;
	}

	fstream file(argv[1]);
	string input;
	vector<Card> cards;

	while (getline(file, input))
	{
		cout << input << endl;

		Card currentCard;
		stages currentlyCollecting = id;

		stringNumber charBuffer;
		charBuffer.number = "...";
		int charBufferIndex = 0;

		for (size_t i = 0; i < input.length(); i++)
		{
			switch (currentlyCollecting)
			{
			case id:
				if (charIsNumber(input[i]))
				{
					charBuffer.number[charBufferIndex] = input[i];
					charBufferIndex++;
				}
				else if (input[i] == ':')
				{
					currentCard.ID = charsToInt({ charBuffer });
					currentlyCollecting = winningNumbers;

					charBufferIndex = 0;
					charBuffer.number = charBuffer.empty;
				}
				break;

			case winningNumbers:

				if (!charIsNumber(input[i]))
				{
					if (charBuffer.number != charBuffer.empty)
					{
						currentCard.winningNumbers.push_back(charsToInt(charBuffer));
					}

					charBuffer.number = charBuffer.empty;
				}
				else if (charIsNumber(input[i]))
				{
					charBuffer.push(input[i]);
				}
				break;

			case ownedNumbers:
				break;
			}
		}

		cout << "Card " << currentCard.ID << ":";

		for (size_t i = 0; i < currentCard.winningNumbers.size(); i++)
		{
			cout << " " << currentCard.winningNumbers[i];
		}

		cout << " |";

		for (size_t i = 0; i < currentCard.ownedNumbers.size(); i++)
		{
			cout << " " << currentCard.ownedNumbers[i];
		}

		cout << " |";

		for (size_t i = 0; i < currentCard.matches.size(); i++)
		{
			cout << " " << currentCard.matches[i];
		}

		cout << endl;

		cards.push_back(currentCard);
	}
}
