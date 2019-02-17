#include <iostream>

using namespace std;

void const18() {

	cout << "const 멤버함수, 비 const 멤버함수" << endl;
	{
		/*
		const 멤버함수: 
			함수 내에서 멤버 변수를 변경하지 않는다는 것을 보장
			const 객체는 const 멤버함수만 호출 가능
		*/
		class A {
		public:
			void cf() const /* 이 함수에서 멤버변수를 변경하지 않음을 보장 */ {
				//i++; // 컴파일 에러
				cout << "cf" << endl;
			}

			void f() {
				i = 9;
			}

			int i = 0;
		};

		A a;
		a.cf(); // cf
		a.f();

		const A b;
		b.cf(); // cf
		//b.f(); // 컴파일 에러, const 객체는 const 함수만 호출할 수 있다.
	}
}