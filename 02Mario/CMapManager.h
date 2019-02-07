#pragma once
#include <iostream>
#include "value.h"
#include "CStage.h"

using namespace std;

class CMapManager
{
public:
	static CMapManager* GetInst();
	static void DestroyInst();

	CMapManager();
	~CMapManager();

	bool Init();
	void Run(int iStage);
	RECT GetStageRect(); // todo delete
	CStage* GetStage();

private:
	static CMapManager* m_Inst;
	CStage* m_pStages[STAGE_MAX_COUNT];
};

