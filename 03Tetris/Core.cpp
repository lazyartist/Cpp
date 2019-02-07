#include "Core.h"
#include "values.h"

DefinitionSingleton(Core)

Core::Core()
{
}


Core::~Core()
{
	SafeDelete(_stage);
}

bool Core::Init()
{
	_stage = new Stage(values::StageW, values::StageH);

	_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (_hConsole == INVALID_HANDLE_VALUE) {
		return false;
	}
}

void Core::Run()
{
	bool isGameEnd = false;
	while (isGameEnd != true)
	{
		// input

		// update

		// render
		Render();

		Sleep(1000); // Windows.h 헤더파일 인클루드 필요
	}
}

void Core::Render()
{
	system("cls");

	/*HANDLE hConsoleOutput = NULL;
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	GetConsoleScreenBufferInfo(hConsoleOutput, &csbiInfo);*/

	SizeWH size = _stage->GetSize();

	// frame
	_SetCursor(0, 0);
	unsigned int frameH = size.h;
	//unsigned int frameH = size.h + values::StageBorder;
	for (size_t i = 0; i <= frameH; i++)
	{
		// 최하단만 모든 라인채우기
		if (i == frameH) {
			_SetCursor(0, i);
			for (size_t j = 0; j < size.w + 2; j++)
			{
				cout << "■";
			}
		}
		// 그외 라인은 양끝만 채우기
		else {
			_SetCursor(0, i);
			cout << "■";
			_SetCursor(values::BlockSize + size.w * values::BlockSize, i);
			cout << "■";
		}

		//cout << endl;
	}

	//return;

	COORD stageStart = {values::BlockSize * 1, 0};
	// stage
	for (size_t i = 0; i < size.h; i++)
	{
		_SetCursor(stageStart.X, stageStart.Y + i);

		for (size_t j = 0; j < size.w; j++)
		{
			BlockState blockState = _stage->GetBlockState(j, i);
			switch (blockState)
			{
			case BlockState::None:
				cout << "**";
				break;
			case BlockState::Empty:
				cout << "--";
				break;
			case BlockState::Fill:
				cout << "■";
				break;
			default:
				break;
			}
		}

		//cout << endl;
	}

	// Shape


}

void Core::_SetCursor(SHORT x, SHORT y)
{
	COORD cursor = { 1, 1 };
	SetConsoleCursorPosition(_hConsole, {x, y});
}


