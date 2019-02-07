#include <iostream>

using namespace std;

int main() {
	/*
	레퍼런스 : 다른 대상을 참조하게 만들어주는 기능
	참조를 하게 되면 그 대상에 접근하여 값을 변경할 수 있다.
	단, 레퍼런스는 처음 레퍼런스 변수 생성시 참조하는 대상을 지정해 주어야 한다.
	변수타입 &레퍼런스명 = 참조할 변수명;
	int &num = num;
	*/
	int iNumber = 100;
	int &rNumber = iNumber;
	rNumber = 101;
	cout << rNumber << endl;
	cout << rNumber << endl;

	return 0;
}