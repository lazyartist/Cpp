#pragma once
#include <iostream>
#include "value.h"
#include "ObjectManager.h"
#include "FileStream.h"
//#include "Player.h"

class CStage
{
public:
	CStage();
	~CStage();
	bool Init();
	bool Init(const char* pFileName);
	void Render();
	void SetStageBlock(POINT point, char ch);
	RECT GetStageRect();
	char GetStageBlock(int x, int y);
	char GetStageBlock(POINT point);

private:
	/*enum StageBlockType {
		SBT_NONE = 9,

		SBT_WALL = 0,
		SBT_ROAD = 1,
		SBT_START = 2,
		SBT_END = 3,
		SBT_COIN = 4,

		SBT_MAX,
	};*/

	//StageBlockType _map[MapSize][MapSize];
	char _map[MapSize][MapSize];
	//wchar_t _block[6] = {L'■', L'□', L'☞', L'◈', L'＠'}; // 유니코드로 사용시
	const char* _blocks[6] = {"■", "  ", "☞", "◈", "＠"}; // 멀티바이트로 사용시, 특수문자는 2바이트라서 "" 문자열로 정의한다.
	RECT _rDisplay = { 0, 0, 15, 8 };
	POINT _ptDisplayPivot = { 2, 3 };
	RECT _rStage;

	const char* GetBlock(char blockData);
};
