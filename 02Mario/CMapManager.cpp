#include "CMapManager.h"

// private으로 선언했는데 그냥 접근이 가능하네?
CMapManager* CMapManager::m_Inst = NULL;

CMapManager::CMapManager()
{
	for (size_t i = 0; i < STAGE_MAX_COUNT; i++)
	{
		m_pStages[i] = NULL;
	}
}

CMapManager::~CMapManager()
{
	for (size_t i = 0; i < STAGE_MAX_COUNT; i++)
	{
		SAFE_DELETE(m_pStages[i]);
	}
}

CMapManager * CMapManager::GetInst()
{
	if (m_Inst == NULL) {
		m_Inst = new CMapManager();
	}
	return m_Inst;
}

void CMapManager::DestroyInst()
{
	SAFE_DELETE(m_Inst);
}

bool CMapManager::Init()
{
	for (size_t i = 0; i < STAGE_MAX_COUNT; i++)
	{
		m_pStages[i] = new CStage();

		if (!m_pStages[i]->Init("Stage1.map")) {
			return false;
		}
	}

	return true;
}

void CMapManager::Run(int iStage)
{
	m_pStages[iStage]->Render();
}

RECT CMapManager::GetStageRect()
{
	return m_pStages[CurStage]->GetStageRect();
}

CStage * CMapManager::GetStage()
{
	return m_pStages[CurStage];
}
