#include <iostream>
#include <time.h>
// 콘솔창에서 입출력하는 기능을 제공하는 헤더파일
#include <conio.h> 

using namespace std;

void printNumbers(int *numbers, int size);

const int ROW = 3, COL = 3;
const int NUMBER_COUNT = ROW * COL;

int main() {
	int numbers[NUMBER_COUNT] = {};
	int maxNumCount = NUMBER_COUNT - 1;
	int cursor = maxNumCount;

	// fill numbers
	for (size_t i = 0; i < maxNumCount; i++)
	{
		numbers[i] = i+1;
	}
	numbers[cursor] = INT_MAX;

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
	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		if (numbers[i] == INT_MAX) {
			cursor = i;
			break;
		}
	}

	printNumbers(numbers, sizeof(numbers) / sizeof(int));

	bool playing = true;
	bool isClear = false;
	while (playing) {
		// render
		system("cls");
		for (size_t i = 0; i < ROW; i++)
		{
			for (size_t j = 0; j < COL; j++)
			{
				int number = numbers[i * COL + j];
				if (number == INT_MAX)
				{
					cout << "[ ]\t";
				}
				else 
				{
					cout << "[" << number << "]\t";
				}
			}
			cout << endl;
		}

		if (isClear)
		{
			cout << "Clear!!" << endl;
			break;
		}

		// input key
		char inputCh = _getch();
		int moveRow = 0, moveCol = 0;
		switch (inputCh)
		{
		case 'w':
			moveRow = -1;
			break;
		case 's':
			moveRow = 1;
			break;
		case 'a':
			moveCol = -1;
			break;
		case 'd':
			moveCol = 1;
			break;
		default:
			playing = false;
			break;
		}

		if (!playing) break;

		int cursorRow = cursor / COL;
		int cursorCol = cursor % COL;

		// move position
		int nextRow = cursorRow + moveRow;
		int nextCol = cursorCol + moveCol;

		if (nextRow < 0 || ROW <= nextRow)
		{
			nextRow = cursorRow;
		}
		if (nextCol < 0 || COL <= nextCol)
		{
			nextCol = cursorCol;
		}

		int nextCursor = nextRow * COL + nextCol;
		cout << nextCursor;

		if (nextCursor != cursor)
		{
			// swap
			int temp = numbers[nextCursor];
			numbers[nextCursor] = numbers[cursor];
			numbers[cursor] = temp;

			cursor = nextCursor;
		}

		// check clear
		isClear = true;
		for (size_t i = 0; i < maxNumCount; i++)
		{
			isClear &= numbers[i] == i + 1;

			if (!isClear) break;
		}
		
		cout << isClear << endl;
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
