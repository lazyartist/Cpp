#include "InputManager.h"

InputManager* InputManager::m_Inst = NULL;

InputManager::InputManager()
{
}

InputManager::~InputManager()
{
}

InputManager * InputManager::GetInst()
{
	if (m_Inst == NULL) {
		m_Inst = new InputManager;
	}
	return m_Inst;
}

void InputManager::Udpate(Player* player, CStage* stage)
{
	POINT playerPoint = player->GetPoint();
	POINT newPlayerPoint = player->GetPoint();
	RECT stageRect = stage->GetStageRect();

	// GetAsyncKeyState 함수는 Win32 API에서 제공되는 키 입력 함수이다.
	// W키를 눌렀을 때 바로 반응하게 하기 위해서 0x8000과 &연산을 하여 
	// 눌렀을 경우 true가 나오게 된다.
	//if (GetAsyncKeyState('A') & 0x8000) {
	if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
		newPlayerPoint.x--;
		char ch = stage->GetStageBlock(newPlayerPoint.x, newPlayerPoint.y);
		if (ch == '0') {
			newPlayerPoint.x = playerPoint.x;
		}
	}

	//if (GetAsyncKeyState('D') & 0x8000) {
	if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
		newPlayerPoint.x++;
		char ch = stage->GetStageBlock(newPlayerPoint.x, newPlayerPoint.y);
		if (ch == '0') {
			newPlayerPoint.x = playerPoint.x;
		}
	}

	if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
		// jump : 땅에 닿았고 점프중이 아니면 점프
		bool onGround = stage->GetStageBlock(playerPoint.x, playerPoint.y + 1) == '0';
		if (onGround && player->m_Jump <= 0) {
			player->m_Jump = 3;
		}
	}

	if (player->m_Jump > 0) {
		// jump
		newPlayerPoint.y--;
		player->m_Jump--;
	}
	else {
		// gravity
		newPlayerPoint.y++;
	}

	char ch = stage->GetStageBlock(newPlayerPoint.x, newPlayerPoint.y);
	if (ch == '0') {
		newPlayerPoint.y = playerPoint.y;
	}

	player->SetPoint(newPlayerPoint);
}
