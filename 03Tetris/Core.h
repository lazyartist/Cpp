#pragma once

#include "values.h"
#include "Stage.h"

class Core
{
	DeclareSingleton(Core)

private:
	Stage* _stage;
	HANDLE _hConsole;

public:
	Core();
	~Core();

	bool Init();
	void Run();
	void Render();

private:
	void _SetCursor(SHORT x, SHORT y);
};

