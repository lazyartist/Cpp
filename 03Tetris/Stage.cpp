#include "Stage.h"


Stage::Stage()
{
}

Stage::Stage(unsigned int w, unsigned int h)
{
	_sizeWH = { w, h };

	_blocks = new BlockState*[h]; // 포인터 배열 생성
	for (size_t i = 0; i < h; i++)
	{
		_blocks[i] = new BlockState[w](); // 배열 생성, ()에 의해 0으로 초기화된다.
		//m_blocks[i] = new BlockState[w]; // 배열 생성, ()가 없으므로 쓰레기 값이 들어간다.
		memset(_blocks[i], (int)BlockState::None, sizeof(BlockState) * w); // None으로 초기화, 위체서 0으로 초기화하면 쓸모없지만 공부를 위해 코드를 추가했다.
	}
}

Stage::~Stage()
{
}

SizeWH Stage::GetSize()
{
	return _sizeWH;
}

BlockState Stage::GetBlockState(unsigned int x, unsigned int y)
{
	if (x < 0 || x > _sizeWH.w || y < 0 || y > _sizeWH.h) {
		return BlockState::None;
	}

	return _blocks[y][x];
}
