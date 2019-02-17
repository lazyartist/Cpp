#include <iostream>

using namespace std;

void _1801_const() {
	cout << "===== 상수(constant)란? =====" << endl;
	{
		/*
		상수는 변하지 않는 변수를 뜻한다.
		변수다!!!
		변수의 값과 멤버가 변하면 안된다.

		하지만 const가 아닌 변수의 const 참조 변수일 경우
		이 참조변수가 가리키는 대상을 변경할 수는 없지만 참조변수의 값은 변경이 가능하다.
		*/

		class A {
		public:
			A() {}
			A(int i) {
				this->i = i;
			}
			int i = 0;
			void print() const {
				cout << this << ", " << i << endl;
			}
			//void operator=(A a) const {}
		};

		cout << "--- 일반 변수" << endl;
		{
			/*
			일반(비 const) 변수는 값을 자유롭게 변경 가능
			*/
			A a; // 객체 생성
			a.print(); // 00CFF7F0, 0

			a = A(1); // A(1) 임시객체 생성 -> a 변수에 (얕은)복사, (14 Operator - Type Cast by constructor 참고)
			a.print(); // 00CFF7F0, 1

			a.i = 9; // 객체 멤버 변경
			a.print(); // 00CFF7F0, 9
		}

		cout << "--- const 변수" << endl;
		{
			/*
			const 변수는 값 또는 멤버 변경 불가
			*/
			const A a; // 객체 생성
			a.print(); // print()함수에 const 지정하지 않으면 컴파일 에러.

			//a = A(); // a에 새로운 값 대입 : 컴파일 에러, "이러한 피연산자와 일치하는 '=' 연산자가 없습니다."
			// operator=() const 함수가 있으면 가능, 하지만 컴파일이 가능할뿐 대입연산 기호로 a가 바뀌지 않으니 혼란스럽다.
			
			//a.i = 9; // const객체의 멤버 변경 : 컴파일 에러, const 객체는 멤버 변경 불가

			const A& b = a; // 참조 변수 생성 : const가 아니면 컴파일 에러
			const A* p = &a; // 포인터 변수 생성 : const가 아니면 컴파일 에러
			//p->i = 0; // p 변수의 멤버 변경 : 컴파일 에러, const 객체는 멤버 변경 불가
			p = nullptr; // p 변수에 새로운 주소 할당 : 값은 바꿀수 없지만 포인터는 변경 가능

			const A* const pp = &a; // constant pointer to constant 변수 생성
			//pp = nullptr; // p 변수에 새로운 주소 할당 : 컴파일 에러, 포인터 변경 불가
			//(*pp).i = 0; // p 멤버 변경 : 컴파일 에러, const 객체는 멤버 변경 불가
		}

		cout << "--- 일반 변수의 const 참조" << endl;
		{
			/*
			일반 변수의 const 참조 변수는 값, 멤버 변경 불가
			하지만 원본인 일반 변수는 값 변경 가능
			*/
			A a; // 일반 변수
			const A& b = a; // const 참조 변수 생성
			
			a.i = 0; // 일반 변수 멤버 변경
			//b.i = 0; // const 참조 변수 멤버 변경 : 컴파일 에러, const 참조 변수로 멤버 변경 불가.
		}

		cout << "--- 일반 변수의 포인터 상수(pointer to constant)" << endl;
		{
			/*
			포인터 상수(pointer to constant)는 포인터는 변경 가능, 포인터가 가리키는 값(상수)은 변경 불가
			*/
			A a; // 일반 변수
			const A* p = &a; // pointer to constant 생성, 가리키는 값이 const

			//p->i = 0; // 값(멤버) 변경 : 컴파일 에러, 값이 const
			p = nullptr; // 포인터 변경 : 포인터는 const가 아니다.
		}

		cout << "--- 일반 변수의 상수 포인터 상수(constant pointer to constant)" << endl;
		{
			/*
			상수 포인터 상수(constant pointer to constant)는 포인터, 값 모두 변경 불가
			*/
			A a; // 일반 변수
			const A* const p = &a; // constant pointer to constant 포인터 생성 : 값과 포인터 모두 const

			//p->i = 0; // 멤버 변경 : 컴파일 에러, 값이 const
			//p = nullptr; // 포인터 변경 : 포인터가 const
		}
	}

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

	cout << "상수 포인터(constant pointer), 상수 지시 포인터(pointer to constant), 상수 지시 상수 포인터(constant pointer to constant), 배열 포인터, 상수 배열 포인터" << endl;
	{
		// https://thrillfighter.tistory.com/88
		char ch = 'a';

		// 상수 포인터(constant pointer): 포인터가 상수라서 포인터를 변경할 수 없다.
		char* const cp = &ch;
		//cp = &ch; // 포인터 재할당: 불가
		cp[0] = 'b'; // 값 할당: 가능

		// 상수 지시 포인터(pointer to constant): 포인터가 가리키는 대상이 상수라서 값을 변경할 수 없다. 포인터는 다른값을 할당할 수 있다.
		const char* p2c = &ch; // 할당하는 변수가 const가 아니어도 할당하는 변수와 상관없이 p2c 변수는 값을 변경하지 않겠다는 뜻이므로 할당가능.
		p2c = &ch; // 포인터 재할당: 가능
		//p2c[0] = 'b'; // 값 할당: 불가(식이 수정할 수 있는 lvalue여야 합니다.)

		// 상수 지시 상수 포인터(constant pointer to constant) : 포인터가 상수이고 가리키는 대상도 상수
		const char* const cp2c = &ch;
		//cp2c = &ch; // 포인터 재할당: 불가
		//cp2c[0] = 'b'; // 값 할당: 불가

		// 배열 포인터: 배열은 포인터 주소를 변경할 수 없는 포인터로서 constant pointer와 같은 기능을 한다.
		char ap[] = "a";
		//ap = &ch; // 포인터 재할당: 불가
		ap[0] = 'b'; // 값 할당: 가능

		// 상수 배열 포인터: 상수를 요소로 가지는 배열
		const char cap[] = "a";
		//cap = &ch; // 포인터 재할당: 불가
		//cap[0] = 'b'; // 값 할당: 불가
	}
}