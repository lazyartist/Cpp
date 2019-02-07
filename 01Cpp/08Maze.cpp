#include <iostream>
#include <conio.h>

using namespace std;

#define MAZE_SIZE 10
#define MaxBombCount 3

typedef struct _tagPoint { int x; int y; } POINT, *PPOINT;

char g_MazeMap[MAZE_SIZE][MAZE_SIZE];
int g_BombCount = 0;

void CreateBomb(PPOINT playerPos);
void FireBomb();
void SetMaze(PPOINT playerPos, PPOINT startPos, PPOINT endPos);
void RenderMaze(PPOINT playerPos);

int main() {
	/*
	char m[1][2] = { { 'a', 'b' } }; // 개별 문자를 구분해서 넣어야하고 문자열은 아래처럼 {} 없이 넣어야한다.
	char a[1][MAZE_SIZE] = { "a" }; // char[]은 문자열 "a"를 넣을 수 있다. 문자열은 캐릭터 배열이다. "aa"는 char[3]이므로 넣을 수 없다.
	//a[1] = "a"; // 초기화 이후 배열에 문자열이 자동으로 들어가지 않는다. 또한 = {}형식으로 값을 할당 할 수 없다.
	
	// a : a[0][] 메모리의 포인터
	// a[0] : a[0][0] 메모리의 포인터
	// a[0][0] : a[0]의 첫번째 값
	// *a : a[0]의 값, 즉 a[0][0]의 포인터
	// **a : a의 값(포인터)의 값, 즉 a[0][0]의 값

	strcpy_s(m[0], "a"); // 문자열은 =대입연산자로 할당되지 않기 때문에 strcpy를 사용해야한다. "aa"는 char[3]이라서 에러난다.
	m[0][1] = 'a'; // [a, \0] 이렇게 들어있는데 [a, a]로 바꾼다.
	cout << m[0] << endl; // \0이 없기 때문에 a다음에 이상한 문자를 계속 출력한다.
	*/

	POINT playerPos;
	POINT startPos;
	POINT endPos;

	SetMaze(&playerPos, &startPos, &endPos);

	bool bPlaying = true;
	bool isClear = false;
	while (bPlaying)
	{
		system("cls");

		RenderMaze(&playerPos);

		if (isClear) {
			cout << "Clear!!" << endl;
			break;
		}

		POINT newPlayerPos = playerPos;

		char input = _getch();
		switch (input)
		{
		case 'w':
			newPlayerPos.y += -1;
			break;
		case 's':
			newPlayerPos.y += 1;
			break;
		case 'a':
			newPlayerPos.x += -1;
			break;
		case 'd':
			newPlayerPos.x += 1;
			break;
		case 'f':
			CreateBomb(&playerPos);
			break;
		case 'r':
			FireBomb();
			break;
		case '0':
			bPlaying = false;
			break;
		default:
			break;
		}

		if (newPlayerPos.x < 0) {
			newPlayerPos.x = 0;
		}
		if (newPlayerPos.y >= MAZE_SIZE) {
			newPlayerPos.y = MAZE_SIZE - 1;
		}

		// check new position
		switch (g_MazeMap[newPlayerPos.y][newPlayerPos.x])
		{
		case '0':
			newPlayerPos = playerPos;
			break;
		case '1':
			playerPos = newPlayerPos;
			break;
		case '2':
			playerPos = newPlayerPos;
			break;
		case '3':
			playerPos = newPlayerPos;
			isClear = true;
			break;
		case '4':
			//CreateBomb(&playerPos);
			break;
		default:
			break;
		}

		if (bPlaying == false) break;
	}

	// todo 길찾는 AI 넣기

	return 0;
}

// 0:벽, 1:길, 2:시작점, 3:도착점, 4:폭탄
void SetMaze(PPOINT playerPos, PPOINT startPos, PPOINT endPos) {
	//maze = {}; // maze가 가지고 있는 메모리 주소를 0x0000000으로 만든다.
	//maze = { 0 }; // 위와 동인한 결과
	// char*를 가진 배열이 아니기 때문에 개별 인덱스에 값을 넣어줘야한다.

	startPos->x = 0;
	startPos->y = 0;
	endPos->x = 8;
	endPos->y = 9;

	*playerPos = *startPos;

	char** pMazeList = NULL;
	int iMazeCount = 0;

	FILE* pFile;
	fopen_s(&pFile, "MazeList.txt", "rt");
	if (pFile != NULL) {
		char cMazeCount;
		fread_s(&cMazeCount, 1, sizeof(char), 1, pFile);

		// atoi : 문자열을 숫자로 바꿀때 사용
		int iMazeCount = atoi(&cMazeCount);

		pMazeList = new char*[iMazeCount];
		//char* pMazeList[9] = {}; // 배열 개수를 동적으로 입력하려면 new로 생성해야한다.

		fread_s(&cMazeCount, 1, sizeof(char), 1, pFile);

		for (size_t i = 0; i < iMazeCount; i++)
		{
			pMazeList[i] = new char[256];
			char cCount;
			char iNameCount = 0;
			while (true)
			{
				// 한 글자씩 읽어서 저장하고 \n을 만나면 다음 변수에 저장하기 위해 while문을 빠져나간다.
				fread_s(&cCount, 1, sizeof(char), 1, pFile);
				if (cCount == '\n') { // 문자 비교에는 비교연산자 사용, 문자열 비교에는 strcmp를 사용
					break;
				}
				pMazeList[i][iNameCount++] = cCount;
			}
			pMazeList[i][iNameCount] = '\0';
		}
		fclose(pFile);
	}

	// MazeMap.txt 읽기
	FILE* fMazeMapFile = NULL;
	fopen_s(&fMazeMapFile, pMazeList[0], "rt");
	if (fMazeMapFile != NULL) {
		for (size_t i = 0; i < MAZE_SIZE; i++)
		{
			fread_s(g_MazeMap[i], MAZE_SIZE, 1, MAZE_SIZE, fMazeMapFile);
			g_MazeMap[i][MAZE_SIZE - 1] = 0;
		}
	}
	fclose(fMazeMapFile);

	// memory delete
	for (size_t i = 0; i < iMazeCount; i++)
	{
		delete[] pMazeList[i];
	}

	//strcpy_s(g_MazeMap[0], "211000000");
	//strcpy_s(g_MazeMap[1], "001000000");
	//strcpy_s(g_MazeMap[2], "011111000");
	//strcpy_s(g_MazeMap[3], "000100010");
	//strcpy_s(g_MazeMap[4], "001100110");
	//strcpy_s(g_MazeMap[5], "000111100");
	//strcpy_s(g_MazeMap[6], "000001000");
	//strcpy_s(g_MazeMap[7], "000011000");
	//strcpy_s(g_MazeMap[8], "001111000");
	//strcpy_s(g_MazeMap[9], "000001113");
}

void RenderMaze(PPOINT playerPos) {
	for (size_t i = 0; i < MAZE_SIZE; i++)
	{
		for (size_t j = 0; j < MAZE_SIZE; j++)
		{
			// player
			if (playerPos->x == j && playerPos->y == i) {
				cout << "☏";
				continue;
			}

			// map
			char ch = g_MazeMap[i][j];
			switch (ch)
			{
			case '0':
				cout << "■";
				break;
			case'1':
				cout << "  ";
				break;
			case '2':
				cout << "☆";
				break;
			case '3':
				cout << "※";
				break;
			case '4':
				cout << "♨";
			default:
				break;
			}
		}
		cout << endl;
	}
}

void CreateBomb(PPOINT playerPos) {
	if (g_BombCount >= MaxBombCount) return;

	if (g_MazeMap[playerPos->y][playerPos->x] == '4') return;

	g_MazeMap[playerPos->y][playerPos->x] = '4';
	g_BombCount++;
}

void FireBomb() {
	for (size_t i = 0; i < MAZE_SIZE; i++)
	{
		for (size_t j = 0; j < MAZE_SIZE; j++)
		{
			if (g_MazeMap[i][j] == '4') {
				//up
				if (i - 1 >= 0) {
					g_MazeMap[i-1][j] = '1';
				}

				// down
				if (i + 1 <= MAZE_SIZE - 1) {
					g_MazeMap[i + 1][j] = '1';
				};

				// left
				if (j - 1 >= 0) {
					g_MazeMap[i][j - 1] = '1';
				}

				// right
				if (j + 1 <= MAZE_SIZE - 1) {
					g_MazeMap[i][j + 1] = '1';
				};

				g_MazeMap[i][j] = '1';

				g_BombCount--;
			}
		}
	}
}