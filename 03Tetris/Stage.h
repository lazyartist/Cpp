#pragma once
#include "values.h"

// 여기서 template은 별 의미 없는듯. 귀찮기만 하다.
//template <int w, int h>
class Stage
{
private:
	BlockState** _blocks;
	SizeWH _sizeWH;

public:
	Stage();
	Stage(unsigned int w, unsigned int h);
	~Stage();

	SizeWH GetSize();
	BlockState GetBlockState(unsigned int x, unsigned int y);

};

