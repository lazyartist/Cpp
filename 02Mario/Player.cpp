#include "Player.h"
//#include "CMapManager.h"

Player::Player()
{
}


Player::~Player()
{
}

void Player::SetMovableArea(RECT area)
{
	m_MovableArea = area;
}

bool Player::Init()
{
	m_Point.x = 0;
	m_Point.y = 0;

	return false;
}

bool Player::Update()
{
	//RECT rStage = CMapManager::GetInst()->GetStageRect();
	return false;
}


