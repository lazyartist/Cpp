#pragma once

#include <iostream>
#include "macros.h"
#include <Windows.h>

using namespace std;

static class values {
public:
	static const int StageW = 5;
	static const int StageH = 5;
	static const int BlockSize = 2;
	//static const int StageBorder = 1;
};

enum class BlockState : unsigned char {
	None, Empty, Fill
};

typedef struct _SizeWH{
	unsigned int w;
	unsigned int h;
} SizeWH, *PSizeWH;