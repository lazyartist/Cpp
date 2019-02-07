#pragma once

#include "value.h"
#include "Player.h"
#include "CStage.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	static InputManager* GetInst();

	void Udpate(Player* player, CStage* stage);

private:
	static InputManager* m_Inst;

	Player m_Player;
	CStage m_Stage;
};

