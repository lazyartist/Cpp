#include <iostream>
#include "Core.h"

using namespace std;

int main() {

	//Core::m_Inst;
	auto core = Core::GetInst();

	core->Init();
	core->Run();

	Stage s(2, 3);
	//Stage s = Stage(2, 3);

	return 0;
}