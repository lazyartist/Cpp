#include <iostream>
#include "CCore.h"

using namespace std;

int main() {

	if (CCore::GetInst()->Init() == NULL) {
		CCore::GetInst()->DestroyInst();

		return 0;
	}

	// 초기화 성공 시 게임을 구동
	CCore::GetInst()->Run();

	// 동작이 끝나면 CCore객체를 메모리에서 해제
	CCore::DestroyInst();

	return 0;
}