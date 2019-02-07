#include "CCore.h"

// 정적변수는 클래스 내부에서 초기화할 수 없고 외부에서 전역변수처럼 초기화해야한다.
CCore* CCore::m_pInst = NULL;

CCore::CCore() {

}

CCore::~CCore() {
	CMapManager::DestroyInst();
	ObjectManager::DestroyInst();
}

CCore* CCore::GetInst() {
	if (m_pInst == NULL) {
		m_pInst = new CCore();
	}
	return m_pInst;
}

void CCore::DestroyInst() {
	SAFE_DELETE(m_pInst);
}

bool CCore::Init() {

	// 오브젝트 관리자 초기화
	if (!ObjectManager::GetInst()->Init()) {
		return false;
	}

	// 맵관리자 초기화
	if (!CMapManager::GetInst()->Init()) {
		return false;
	}

	return true;
}

void CCore::Run() {
	_GameData = { 0, false };

	while (true)
	{
		Player* player = ObjectManager::GetInst()->GetPlayer();
		CStage* stage = CMapManager::GetInst()->GetStage();

		InputManager::GetInst()->Udpate(player, stage);

		// game update
		POINT playerPoint = player->GetPoint();
		char ch = stage->GetStageBlock(playerPoint);
		if (ch == '4') {
			stage->SetStageBlock(playerPoint, '1');
			_GameData.Score++;
		} else if (ch == '9' || ch == '3') {
			_GameData.GameEnd = true;
		}
		
		// render
		stage->Render();

		//CMapManager::GetInst()->Run(0);

		cout << endl;
		cout << "Score : " << _GameData.Score << endl;

		if (_GameData.GameEnd) {
			cout << "GameEnd!";
			break;
		}

		Sleep(100);
	}
}