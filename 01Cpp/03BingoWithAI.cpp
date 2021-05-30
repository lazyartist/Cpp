#include <iostream>
#include <time.h>
// 콘솔창에서 입출력하는 기능을 제공하는 헤더파일
//#include <conio.h> 

using namespace std;

#define GetIntArrSize(arr) (sizeof(arr) / sizeof(int))

void printNumbers(int *numbers, int size);
void renderNumber(const char * name, int clearCount, int *numbers, int size);
void marking(int number, int *numbers, int size);
int checkClearLine(int *numbers, int size);
int pickNumByEasyAi(int *numbers, int size);
int pickNumByHardAi(int *numbers, int size);

const int COL = 5;
const int NUMBER_COUNT = COL * COL;
const int END_COUNT = 4;

//int POSITION_WEIGHT[NUMBER_COUNT] =
//{
//	3, 2, 3,
//	2, 4, 2,
//	3, 2, 3,
//};

int POSITION_WEIGHT[NUMBER_COUNT] =
{
	3, 2, 2, 2, 3,
	2, 3, 2, 3, 2,
	2, 2, 4, 2, 2, 
	2, 3, 2, 3, 2,
	3, 2, 2, 2, 3,
};

//int POSITION_WEIGHT[NUMBER_COUNT] =
//{
//	3, 2, 2, 2, 2, 2, 3,
//	2, 3, 2, 2, 2, 3, 2,
//	2, 2, 3, 2, 3, 2, 2,
//	2, 2, 2, 4, 2, 2, 2,
//	2, 2, 3, 2, 3, 2, 2,
//	2, 3, 2, 2, 2, 3, 2,
//	3, 2, 2, 2, 2, 2, 3,
//};

int turnCount = 0;


int main() {
	int playerNumbers[NUMBER_COUNT] = {};
	int aiNumbers[NUMBER_COUNT] = {};

	// fill numbers
	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		playerNumbers[i] = i + 1;
		aiNumbers[i] = i + 1;
	}

	// shuffle numbers
	srand(time(0));
	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		int idx1 = rand() % NUMBER_COUNT;
		int idx2 = rand() % NUMBER_COUNT;
		int temp = playerNumbers[idx1];
		playerNumbers[idx1] = playerNumbers[idx2];
		playerNumbers[idx2] = temp;

		idx1 = rand() % NUMBER_COUNT;
		idx2 = rand() % NUMBER_COUNT;
		temp = aiNumbers[idx1];
		aiNumbers[idx1] = aiNumbers[idx2];
		aiNumbers[idx2] = temp;
	}

	printNumbers(playerNumbers, GetIntArrSize(playerNumbers));
	printNumbers(aiNumbers, GetIntArrSize(aiNumbers));

	turnCount = 1;

	bool playing = true;
	bool isPlayerClear = false;
	bool isAiClear = false;
	bool isPlayerTurn = true;
	bool isDuplicatedNumber = false;

	int playerClearCount = 0;
	int aiClearCount = 0;
	int inputNum = 0;

	while (playing) {
		// render
		system("cls");
		renderNumber("Player", playerClearCount, playerNumbers, GetIntArrSize(playerNumbers));
		cout << endl;
		renderNumber("AI", aiClearCount, aiNumbers, GetIntArrSize(aiNumbers));
		cout << endl;
		cout << "Last Input Number : " << inputNum << endl;
		cout << "Turn Count : " << turnCount << " , ";
		cout << (isPlayerTurn ? "Player Turn" : "Ai Turn") << endl;
		if (isDuplicatedNumber) {
			cout << "Retry" << endl;
		}

		if (isPlayerClear || isAiClear)
		{
			if (isPlayerClear && isAiClear) {
				cout << "Draw!!" << endl;
			} else {
				cout << (isPlayerClear ? "Player Win!!" : "Ai Win!!") << endl;
			}
			break;
		}

		// test
		int aaa = pickNumByHardAi(aiNumbers, GetIntArrSize(aiNumbers));

		// input key
		if (isPlayerTurn) {
			cin >> inputNum;
		}
		else {
			//cin >> inputNum;
			inputNum = pickNumByHardAi(aiNumbers, GetIntArrSize(aiNumbers));
			//inputNum = pickNumByEasyAi(aiNumbers, GetIntArrSize(aiNumbers));
		}

		// check duplicate number
		isDuplicatedNumber = true;
		for (size_t i = 0; i < NUMBER_COUNT; i++)
		{
			if (playerNumbers[i] == inputNum) {
				isDuplicatedNumber = false;
				break;
			};
		}
		if (isDuplicatedNumber) continue;

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
		marking(inputNum, playerNumbers, GetIntArrSize(playerNumbers));
		marking(inputNum, aiNumbers, GetIntArrSize(aiNumbers));
		
		// check clear line
		playerClearCount = checkClearLine(playerNumbers, GetIntArrSize(playerNumbers));
		aiClearCount = checkClearLine(aiNumbers, GetIntArrSize(aiNumbers));

		// is clear
		isPlayerClear = playerClearCount >= END_COUNT;
		isAiClear = aiClearCount >= END_COUNT;

		isPlayerTurn = !isPlayerTurn;

		turnCount++;
	}

	return 0;
}

void printNumbers(int *numbers, int size) {
	for (size_t i = 0; i < size; i++)
	{
		if (*numbers == -1) {
			cout << "-" << "\t";
		}
		else {
			cout << *numbers << "\t";
		}
		
		numbers++;

		if (i % COL == COL - 1) cout << endl;
	}
	cout << endl;
}

void renderNumber(const char * name, int clearCount, int *numbers, int size) {
	cout << "============== " << name << " ==============" << endl;
	for (size_t i = 0; i < COL; i++)
	{
		for (size_t j = 0; j < COL; j++)
		{
			int number = numbers[i * COL + j];
			if (number == INT_MAX)
			{
				cout << "[--]\t";
			}
			else
			{
				cout << "[" << number << "]\t";
			}
		}
		cout << endl << endl;
	}

	cout << name << " Clear Count : " << clearCount << endl;
}

void marking(int number, int *numbers, int size)
{
	for (size_t i = 0; i < NUMBER_COUNT; i++)
	{
		if (numbers[i] == number)
		{
			numbers[i] = INT_MAX;
			break;
		};
	}
}

int checkClearLine(int *numbers, int size)
{
	int clearCount = 0;

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

	return clearCount;
}

int pickNumByEasyAi(int *numbers, int size)
{
	int selectingNumbers[NUMBER_COUNT] = {};
	int pushIndex = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (numbers[i] != INT_MAX) {
			selectingNumbers[pushIndex++] = numbers[i];
		}
	}

	int selectIndex = rand() % pushIndex;

	return selectingNumbers[selectIndex];
}


int pickNumByHardAi(int *numbers, int size)
{
	// 60% 정도 숫자선택하면 게임이 거의 끝난다.
	// 따라서 40% 선택 이후는 후반이라 봐야한다.
	int timeWeight = (turnCount > NUMBER_COUNT / 3) ? 1 : 0;

	// 게임 후반이다. 한 점만 더 먹으면 승리다. -> 라인완성 우선
	// 게임 초반이다. -> 좋은 자리 우선

	// 라인이 연결될 확률이 가장 높은 곳을 추출
	int scores[NUMBER_COUNT] = {};
	for (size_t i = 0; i < size; i++)
	{
		if (numbers[i] == INT_MAX) {
			scores[i] = -1;
		}
		else {
			int row = i / COL;
			int col = i % COL;
			int score = 0;
			int lineScore = 0;

			// row score
			for (size_t i = 0; i < COL; i++)
			{
				if (numbers[row * COL + i] == INT_MAX) {
					score++;
					lineScore++;
				};
			}
			if (lineScore == COL - 1) {
				score += lineScore * timeWeight;
			}

			// col score
			lineScore = 0;
			for (size_t i = 0; i < COL; i++)
			{
				if (numbers[(i * COL) + col] == INT_MAX) {
					score++;
					lineScore++;
				};
			}
			if (lineScore == COL - 1) {
				score += lineScore * timeWeight;
			}

			// diagonal score : 좌상 -> 우하
			if (row == col) {
				for (size_t j = 0; j < COL; j++)
				{
					if (numbers[(j * COL) + j] == INT_MAX) {
						score++;
						lineScore++;
					};
				}
				if (lineScore == COL - 1) {
					score += lineScore * timeWeight;
				}
			}
			// diagonal score : 우상 -> 좌하
			if (row + col == COL - 1) {
				for (size_t i = 0; i < COL; i++)
				{
					if (numbers[(i * COL) + (COL - 1 - i)] == INT_MAX) {
						score++;
						lineScore++;
					};
				}
				if (lineScore == COL - 1) {
					score += lineScore * timeWeight;
				}
			}

			//scores[i] = score;
			scores[i] = score + POSITION_WEIGHT[i];
		}
	}

	printNumbers(scores, GetIntArrSize(scores));
	cout << "time weight " << timeWeight;

	// 점수가 가장 높은 곳을 선택
	int selectedNumber = 0;
	int selectedPositionScore = 0;

	for (size_t i = 0; i < size; i++)
	{
		if (numbers[i] != INT_MAX) {
			if (selectedPositionScore < scores[i] ||
				(selectedPositionScore == scores[i] && rand() % 2 == 0))
			{
				selectedNumber = numbers[i];
				selectedPositionScore = scores[i];
			}
		}
	}

	return selectedNumber;
}