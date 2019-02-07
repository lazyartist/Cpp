#include <iostream>
#include <time.h>
// 콘솔창에서 입출력하는 기능을 제공하는 헤더파일
//#include <conio.h> 

using namespace std;

void printNumbers(int *numbers, int size);

const int COL = 5;
const int NUMBER_COUNT = COL * COL;
const int END_COUNT = 5;

int main() {
	int numbers[NUMBER_COUNT] = {};

	// fill numbers
	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		numbers[i] = i + 1;
	}

	// shuffle numbers
	srand(time(0));
	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		int idx1 = rand() % NUMBER_COUNT;
		int idx2 = rand() % NUMBER_COUNT;
		int temp = numbers[idx1];
		numbers[idx1] = numbers[idx2];
		numbers[idx2] = temp;
	}

	printNumbers(numbers, sizeof(numbers) / sizeof(int));

	bool playing = true;
	bool isClear = false;
	int clearCount = 0;
	while (playing) {
		// render
		system("cls");
		for (size_t i = 0; i < COL; i++)
		{
			for (size_t j = 0; j < COL; j++)
			{
				int number = numbers[i * COL + j];
				if (number == INT_MAX)
				{
					cout << "[*]\t";
				}
				else
				{
					cout << "[" << number << "]\t";
				}
			}
			cout << endl << endl;
		}

		cout << "Clear Count : " << clearCount << endl;

		if (isClear)
		{
			cout << "Clear!!" << endl;
			break;
		}

		// input key
		int inputNum;
		cin >> inputNum;

		int moveRow = 0, moveCol = 0;
		switch (inputNum)
		{
		case 0:
			playing = false;
			break;
		default:
			break;
		}
		if (!playing) break;


		// marking
		for (size_t i = 0; i < NUMBER_COUNT; i++)
		{
			if (numbers[i] == inputNum)
			{
				numbers[i] = INT_MAX;
				break;
			};
		}

		// check clear
		{
			clearCount = 0;

			// row
			for (size_t i = 0; i < COL; i++)
			{
				bool isClearLine = true;
				for (size_t j = 0; j < COL; j++)
				{
					isClearLine &= numbers[i * COL + j] == INT_MAX;
				}
				if (isClearLine) clearCount++;
			}

			// col
			for (size_t i = 0; i < COL; i++)
			{
				bool isClearLine = true;
				for (size_t j = 0; j < COL; j++)
				{
					isClearLine &= numbers[i + j * COL] == INT_MAX;
				}
				if (isClearLine) clearCount++;
			}

			// diagonal
			bool isClearLineToRight = true;
			bool isClearLineToLeft = true;
			for (size_t i = 0; i < COL; i++)
			{
				isClearLineToRight &= numbers[i * COL + i] == INT_MAX;
				isClearLineToLeft &= numbers[i * COL + (COL - 1 - i)] == INT_MAX;
			}
			if (isClearLineToRight) clearCount++;
			if (isClearLineToLeft) clearCount++;
		}

		isClear = clearCount >= END_COUNT;
	}

	return 0;
}

void printNumbers(int *numbers, int size) {
	for (size_t i = 0; i < size; i++)
	{
		cout << *numbers << " ";
		numbers++;
	}
	cout << endl;
}
