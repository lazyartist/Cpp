#pragma once

#include "value.h"
#include "Player.h"

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
private:
	static ObjectManager* m_pInst;

public:
	static ObjectManager* GetInst() {
		if (m_pInst == NULL) {
			m_pInst = new ObjectManager();
		}

		return m_pInst;
	}

	static void DestroyInst() {
		if (m_pInst == NULL) return;

		SAFE_DELETE(m_pInst);
	}

	bool Init();
	Player* GetPlayer() {
		return m_pPlayer;
	}
	POINT GetPlayerPoint() {
		return m_pPlayer->GetPoint();
	}
	void SetPlayerMovableArea(RECT area) {
		return m_pPlayer->SetMovableArea(area);
	}


private:
	// 가장 위에 하는 것이 아닌 해당 타입을 사용하고자 할 때 전방선언을 해줄 수도 있다.
	class Player* m_pPlayer;
};

