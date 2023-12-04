#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int getIndex(int y, int x, int xWidth) 
{ 
	return (y * xWidth) + x; 
}

int main(int argc, char* argv[])
{
	using namespace std;

	if (argc != 2) 
	{
		cout << "Please provide an input file" << endl;
		return 1;
	}

	fstream file(argv[1]);
	string input;

	int fileY = 0;
	while (getline(file, input)) fileY++;
	int fileX = 0; 
	fileX = input.length();

	file.close();

	char* grid = new char[getIndex(fileY - 1, fileX - 1, fileX)];

	int y = 0;
	input = "";

	fstream populateRead(argv[1]);
	while (getline(populateRead, input))
	{
		for (size_t x = 0; x < input.length(); x++)
		{
			if (input[x] == '/n')
			{
				break;
			}

			grid[getIndex(y, x, fileX)] = input[x];
		}

		y++;
	}

	populateRead.close();

	int runningTotal = 0;

	for (size_t y = 0; y < fileY; y++)
	{
		for (size_t x = 0; x < fileX; x++)
		{
			if (grid[getIndex(y, x, fileX)] == '.')
			{
				continue;
			}

			//Checking if is number, if it is skip it cuz we looking for symbols
			if (grid[getIndex(y, x, fileX)] - 48 >= 0 && grid[getIndex(y, x, fileX)] - 48 < 10)
			{
				continue;
			}

			bool breakCheck = false;
			for (int jy = -1; jy < 2; jy++)
			{
				if (breakCheck)
				{
					breakCheck = false;
					break;
				}

				for (int jx = -1; jx < 2; jx++)
				{
					//skip if out of index range
					if (y + jy < 0 || x + jx < 0) continue;

					if (grid[getIndex(y + jy, x + jx, fileX)] == '.')
					{
						continue;
					}

					//skip if is NOT number
					if (grid[getIndex(y + jy, x + jx, fileX)] - 48 < 0 || grid[getIndex(y + jy, x + jx, fileX)] - 48 >= 10)
					{
						continue;
					}

					int storedY = y;
					int storedX = x;

					y += jy;
					x += jx;

					int startOffset = 0;

					//checking if numbers before it
					if (x - 2 >= 0)
					{
						if (grid[getIndex(y, x - 2, fileX)] - 48 >= 0 && grid[getIndex(y, x - 2, fileX)] - 48 < 10)
						{
							startOffset = -2;
						}
					}

					if (x - 1 >= 0 && startOffset == 0)
					{
						if (grid[getIndex(y, x - 1, fileX)] - 48 >= 0 && grid[getIndex(y, x - 1, fileX)] - 48 < 10)
						{
							startOffset = -1;
						}
					}
					
					vector<char> charBuffer;
					while (true)
					{
						if (x + startOffset >= fileX) break;

						charBuffer.push_back(grid[getIndex(y, x + startOffset, fileX)]);
						grid[getIndex(y, x + startOffset, fileX)] = '.';

						if (x + startOffset + 1 >= fileX) break;

						if (grid[getIndex(y, x + startOffset + 1, fileX)] - 48 < 0 || grid[getIndex(y, x + startOffset + 1, fileX)] - 48 >= 10)
						{
							break;
						}

						startOffset++;
					}

					int partNumber = 0;
					for (size_t i = 0; i < charBuffer.size(); i++)
					{
						int currentNumber = charBuffer[i] - 48;

						for (size_t j = 0; j < charBuffer.size() - i - 1; j++)
						{
							currentNumber *= 10;
						}

						partNumber += currentNumber;
					}

					if (storedX < x) x = storedX;
					if (storedY < y) y = storedY;

					runningTotal += partNumber;
					breakCheck = true; //break check if found what checking for
				}
			}
		}
	}

	for (y = 0; y < fileY; y++)
	{
		for (size_t x = 0; x < fileX; x++)
		{
			cout << grid[getIndex(y, x, fileX)];
		}

		cout << endl;
	}

	cout << "Total Parts Number: " << runningTotal;
}