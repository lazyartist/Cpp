#include <iostream>
#include "utils.h"

using namespace std;

/*
Smart Pointer
	자동으로 객체를 소멸시켜주는 객체
*/


void _1402_operator_smart_pointer() {

	cout << "===== Smart Pointer =====" << endl;
	{

		class A {
		public:
			A() {
				cout << "A cst " << this << ", " << i << endl;
			}
			~A() {
				cout << "A dst " << this << ", " << i << endl;
			}
			int i;
		};

		class ASmtPtr {
		public:
			ASmtPtr(A* a) {
				cout << "ASmtPtr cst " << a << endl;
				this->a = a;
			}
			~ASmtPtr() {
				cout << "ASmtPtr dst " << a << endl;
				SAFE_DELETE(a);
			}
			A* a;

			// 포인터 변수 처럼 사용할 수 있게 -> 연산자를 오버로딩한다.
			A* operator ->() const {
				//a = new A();
				return a;
				// const 함수인데 반환값에 const를 붙이지 않아도 되는 이유
				// const 함수는 멤버변수 a의 값을 변경하지 않겠다는 뜻인데 *a를 반환하는 것은 
				// a변수의 포인터가 아닌 값을 변경하는 것이기 때문에 가능하다.
			}

			// 포인터 변수의 값을 간접참조하기 위해 * 연산자를 오버로딩한다.
			A& operator *() const {
				return (*a);
			}

			// 포인터 반환을 위해 & 연산자를 오버로딩한다.
			A* operator &() const {
				return a;
			}
		};

		A* a = new A();
		ASmtPtr ap(a);

		//ap-> = new A(); // 함수의 반환값은 rvalue이므로 new A()로 새로운 객체를 할당할 수 없다.

		// ->
		ap->i = 1; // 암시적 호출
		ap.operator->()->i = 2; // 명시적 호출

		// *
		(*ap).i = 3; // 암시적 호출
		ap.operator*().i = 4; // 명시적 호출

		// &
		(&ap)->i = 5; // 암시적 호출
		ap.operator&()->i = 6; // 명시적 호출

		/* Result
		A를 힙에 생성하고 코드 블럭을 빠져나가도 지역변수 ASmtPtr가 소멸하며 A를 소멸시킨다.
		
		A cst 00C18220, -842150451
		ASmtPtr cst 00C18220
		ASmtPtr dst 00C18220
		A dst 00C18220, 6
		*/
	}

	// todo c++ 책보고 스마트 포인터 보강하기
}