#pragma once

#include "value.h"

//class CMapManager* stage;

class Player
{
public:
	Player();
	~Player();

private:
	POINT m_Point;
	RECT m_MovableArea;

public:
	int m_Jump = 0;
	POINT GetPoint() { return m_Point; }
	void SetPoint(int x, int y) { m_Point.x = x; m_Point.y = y; }
	void SetPoint(POINT point) { m_Point = point; }
	void SetMovableArea(RECT area);
	bool Init();
	bool Update();
};

