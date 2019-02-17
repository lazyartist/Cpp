#include <iostream>
#include <string>

using namespace std;

void _1201_reference() {
	cout << "========== reference ==========" << endl;

	cout << "reference" << endl;
	{
		/*
		레퍼런스 : 다른 대상을 참조하게 만들어주는 기능
		참조를 하게 되면 그 대상에 접근하여 값을 변경할 수 있다.
		단, 레퍼런스는 처음 레퍼런스 변수 생성시 참조하는 대상을 지정해 주어야 한다.
		다른 대상으로 변경할 수 없다.
		변수타입 &레퍼런스명 = 참조할 변수명;
		int &num = num;
		*/
		int iNumber = 100;
		int &rNumber = iNumber;
		rNumber = 101;
		cout << rNumber << endl;
		cout << rNumber << endl;
	}

	{
		// todo : rvalue reference 정리
		// 대입, 할당 시 복사 생성자가 호출된다.
		// lvalue = lvalue; // 임시객체 생성 -> 복사 생성자 호출 -> 깊은 복사
		// lvalue = rvalue; // 기존에는 위와 동일하게 깊은 복사를 하였다.
		// C++11에서 생긴 rvalue reference(&&)로 인해 인자 타입에 &&를 넣으면 rvalue값을 받을 수 있다.
		// 따라서 rvalue로 받은 값을 (깊은)복사하지 않고 포인터 복사만하고 원본값을 nullptr로 만들어준다.
		// 원본 객체가 소멸될때 destructor에 의해 nullptr인 변수의 메모리를 해제하지 않게 된다.
		// 따라서 복사된 객체는 원본 객체의 메모리의 값을 사용할 수 있게 된다.
		// 결론적으로 &&로 인해 rvalue를 구분할 수 있게 됐고 rvalue는 임시객체로 바로 사라질 객체이기 때문에 
		// move라는 방식으로 원본 객체의 값을 이동시켜서 필요없는 부하를 줄여줄 수 있게 됐다.
		// 
		// https://spikez.tistory.com/305

	}
}