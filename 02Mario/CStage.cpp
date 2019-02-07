#include "CStage.h"

CStage::CStage()
{

}

CStage::~CStage()
{
}

bool CStage::Init()
{
	for (size_t i = 0; i < MapSize; i++)
	{
		for (size_t j = 0; j < MapSize; j++)
		{
			_map[i][j] = 0;
		}
	}

	return true;
}

bool CStage::Init(const char * pFileName)
{
	Init();

	FileStream fileStream;
	if (fileStream.Open(pFileName, "rt")) {
		//unsigned int iRow = 0;
		//int iCol = 0;

		int iReadSize = 0;
		char strLine[StringCount];
		fileStream.ReadLine(strLine, iReadSize);
		//readCharLine(strLine, pFile);
		_rStage.bottom = atoi(strLine);
		//_iRow = atoi(strLine);

		fileStream.ReadLine(strLine, iReadSize);
		_rStage.right = atoi(strLine);
		//_iCol = atoi(strLine);

		cout << _rStage.bottom << "x" << _rStage.right << endl;

		for (size_t i = 0; i < _rStage.bottom; i++)
		{
			fileStream.ReadLine(_map[i], iReadSize);

			// 플레이어 위치 찾기
			for (size_t j = 0; j < iReadSize; j++)
			{
				if (_map[i][j] == '2') {
					ObjectManager::GetInst()->GetPlayer()->SetPoint(j, i);
				}
			}
		}
	}

	//fileStream.WriteLine(_map[0], sizeof(_map[0]) / sizeof(char));

	return true;
}

void CStage::Render()
{
	/*
	맵은 스크롤 처리해야한다.
	플레이어가 이동한 위치로부터 맵을 출력해줘야한다.

	0: 벽, 1: 길, 2: 시작점, 3: 도착점, 4: 코인
	*/

	// todo display frame 

	POINT playerPoint = ObjectManager::GetInst()->GetPlayerPoint();
	//POINT playerPoint = pPlayer->GetPoint();

	int displayY = playerPoint.y - _ptDisplayPivot.y;
	int displayX = playerPoint.x - _ptDisplayPivot.x;

	system("cls");
	for (int i = displayY; i < displayY + _rDisplay.bottom; i++)
	{
		if(i != displayY) cout << endl;

		for (int j = displayX; j < displayX + _rDisplay.right; j++)
		{
			if (i < 0 || j < 0 || i >= _rStage.bottom || j >= _rStage.right) {
				cout << "++";
				continue;
			}

			if (playerPoint.x == j && playerPoint.y == i) {
				cout << "§";
			}
			else {
				cout << GetBlock(_map[i][j]);
			}
		}
	}
}

void CStage::SetStageBlock(POINT point, char ch)
{
	_map[point.y][point.x] = ch;
}

const char* CStage::GetBlock(char blockData)
{
	return _blocks[blockData - '0'];
}

RECT CStage::GetStageRect()
{
	return _rStage;
}

char CStage::GetStageBlock(int x, int y)
{
	return _map[y][x];
}

char CStage::GetStageBlock(POINT point)
{
	if (point.x < 0 || point.x > _rStage.right || point.y < 0 || point.y > _rStage.bottom)
	{
		return '9';
	}

	return _map[point.y][point.x];
}
