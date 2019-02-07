#include "ObjectManager.h"

ObjectManager* ObjectManager::m_pInst = NULL;

ObjectManager::ObjectManager()
{
}


ObjectManager::~ObjectManager()
{
	SAFE_DELETE(m_pPlayer);
}

bool ObjectManager::Init()
{
	m_pPlayer = new Player();
	m_pPlayer->Init();

	return true;
}
