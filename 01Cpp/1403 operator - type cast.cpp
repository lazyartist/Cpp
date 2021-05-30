#include <iostream>
#include "utils.h"

using namespace std;

/*
Type Cast
	1. 생성자를 이용한 타입 변환
	2. 타입 변환 연산자 오버로딩을 이용한 타입 변환
*/

// A 클래스에서 B 클래스의 포인터만 사용하면 선언만으로 사용할 수 있다.
// 하지만 B 클래스 객체를 사용하거나 멤버에 접근하려면 결국 클래스의 크기(정의)를 알아야하므로 
// 이렇게 선언만 해서는 소용없어진다.
// A 클래스에서 B 클래스를 사용하려면 전방 정의하거나 B 클래스의 헤더파일을 만들고 include해서 사용해야한다.
//class B {};

void _1403_operator_type_cast() {
	class B {
	public:
		B() {
			cout << "B " << this << endl;
		}
		~B() {
			cout << "~B " << this << endl;
		}
		int i;
	};

	class A {
	public:
		A() {
			cout << "A " << this << ", " << i << endl;
		}

		A(const A& a) {
			cout << "A, A to A " << this << ", " << i << endl;
		}

		// B 객체로 A 객체 생성
		A(B& b) { // 암시적 생성자 호출 가능
			cout << "A, B to A " << this << ", " << i << endl;
		}

		// int로 A 객체 생성
		explicit A(int i) { // explicit 키워드에 의해 명시적 생성자 호출만 가능
			cout << "A, int to A " << this << ", " << i << endl;
			this->i = i;
		}

		~A() {
			cout << "~A " << this << ", " << i << endl;
		}
		int i = 0;

		// operator=가 재정의 되어있으면 대입 연산 시 A 클래스 임시객체가 생성되지 않고 바로 =연산자가 호출된다.
		/*A& operator=(int i) {
			cout << "A operator= " << this << ", " << i << endl;
			return *this;
		}*/

		// 타입변환 연산자, 반환 타입을 지정하지 않는다.
		operator B() {
			cout << "A B() " << this << ", " << i << endl;
			return B();
		}
		operator int() const{ // const 지정하여 const 객체도 호출할 수 있도록 한다.
			cout << "A int() " << this << ", " << i << endl;
			return 9;
		}
	};

	cout << "===== Type Cast by constructor  =====" << endl;
	{
		A a;
		B b;

		a = b; // 암시적 생성자 호출
		// A 클래스에 B 클래스를 받는 대입 연산자(operator=)가 없으므로 컴파일러는 b를 A로 변경할 수 있는 방법을 찾는다.
		// A 클래스 생성자 중에 B를 받는 생성자(explicit이 없어서 암시적 호출 가능)가 있기 때문에 컴파일러는 암시적으로 b로 A의 임시객체를 생성한다.
		// b를 인자로 생성된 A 임시객체를 컴파일러에 의해 정의된 operator= 함수를 호출하여 a객체에 복사한다.
		// 복사 후 임시객체가 소멸된다.
		cout << "-----" << endl;
		/*
		A 010FFCD0, 0
		B 010FFCC4
		A, B to A 010FFBB0, 0
		~A 010FFBB0, 0
		*/

		//a = 1; // 암시적 생성자 호출 불가
		// 위 a = b;처럼 암시적 생성자 호출을 막기 위해 expicit 키워드를 사용하여 명시적 생성자 호출을 하도록 했다.
		A aa(1); // 명시적 생성자 호출
		// *** 형변환을 의도하지 않는한 인자를 갖는 생성자는 모두 explicit 생성자로 만드는 것이 좋다. ***
		/*
		A, int to A 010FFCB8, 1
		*/

		cout << "----- block end" << endl;
		/*
		~A 010FFCB8, 1
		~B 010FFCC4
		~A 010FFCD0, 0
		*/
	}

	cout << "===== Type Cast by type casting operator  =====" << endl;
	{
		A a; // A 객체 생성
		B b = a; // 암시적으로 A 클래스의 operator B() 연산자 호출하여 B 객체 생성하여 대입
		int i = a; // 암시적으로 A 클래스의 operator int() 연산자 호출하여 int 생성하여 대입
		cout << i << endl; // 9;
		/*
		A 010FFCAC, 0
		A B() 010FFCAC, 0
		B 010FFCA0
		A int() 010FFCAC, 0
		9
		*/

		cout << "-----" << endl;

		const A aa;
		//B bb = aa; // aa는 const 객체인데 B() 함수는 const 함수가 아니라서 컴파일 에러남.
		int ii = aa; // int() 함수는 const라서 const 객체에서 호출 가능.
		/*
		A 010FFC88, 0
		A int() 010FFC88, 0
		*/

		cout << "----- block end" << endl;
		/*
		~A 010FFC88, 0
		~B 010FFCA0
		~A 010FFCAC, 0
		*/
	}
}