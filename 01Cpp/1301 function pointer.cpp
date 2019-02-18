#include <iostream>
#include <functional> // C++11에서 함수포인터를 편하게 사용하기 위해 추가된 기능을 사용하기 위해 include

using namespace std;

/*
함수 호출 방법
	1. 정적함수 호출(전역함수, namespace 내의 전역함수, static 멤버 함수) : f();
	2. 객체로 멤버함수 호출 : a.f();
	3. 객체의 주소로 멤버 함수 호출 : a->f();

함수 호출 규약
	함수 호출 시 전달되는 인자의 순서나 함수가 종료될 때 함수의 스택을 정리하는 시점 등을 약속한것.
	stdcall, cdecl, thiscall, fastcall 등이 있음
		참고 https://ko.wikipedia.org/wiki/X86_%ED%98%B8%EC%B6%9C_%EA%B7%9C%EC%95%BD
	정적 함수의 기본 함수 호출 규약은 cdecl, 멤버함수는 thiscall
	따라서 정적 함수와 멤버 함수 포인터를 다르게 선언함.


함수포인터 : 함수의 메모리 주소를 저장하기 위한 포인터 변수
전역함수의 경우 함수명이 곧 함수의 메모리 주소
함수포인터 선언방법 : 반환타입 (*포인터변수명)(인자타입);

this 포인터 : 클래스 안에서 this를 사용할 경우 해당 객체의 메모리 주소가된다. 즉 자기자신의 포인터이다.
멤버함수 내에서 멤버변수 호출 시 this를 생략가능(컴파일시 this를 붙인다)

*/

void gf() {
	cout << "gf() " << endl;
}

int gfSum(int a, int b) {
	cout << "gfSum() " << a + b << endl;
	return a + b;
}

namespace ns {
	void f() {
		cout << "ns f() " << endl;
	}
}

class A {
public :
	static void sf() {
		cout << "A sf() " << endl;
	}

	void mf() {
		cout << "A mf() " << this << endl;
	}
};

void _1301_function_pointer() {

	cout << "===== 정적 함수 포인터 선언 및 실행 =====" << endl;
	{
		/*
		정적 함수(전역함수, namespace 내의 전역함수, static 멤버 함수)는 함수 포인터 선언이 같다.
		*/

		// 원본 정적 함수 호출
		gf(); // 전역
		ns::f(); // 네임스페이스 전역
		A::sf(); // A 클래스의 정적 멤버 함수

		void (*fp)(); // 정적 함수 포인터 선언

		fp = gf; // 전역 함수 할당
		fp(); // 실행 : gf()

		fp = ns::f; // namespace 내의 전역함수 할당
		fp(); // 실행 : ns f()

		fp = A::sf; // static 멤버 함수
		fp(); // 실행 : A sf()
		
		// 동일한 실행 문법
		(*fp)(); // 실행 : A sf()
	}

	cout << "===== 멤버 함수 포인터 선언 및 실행 =====" << endl;
	{
		/*
		멤버 함수 포인터
			선언 시 포인터 변수 이름 앞에 클래스명::을 붙여준다.
			실행 시는 this가 될 객체에서 다음 연산자를 이용해 호출한다.(연산자 우선 순위로 인해 ()로 감싼다.)
				객체로 호출 : .* 연산자 이용 (a.*f());
				주소로 호출 : ->* 연산자 이용 (a->*f());
				
		*/
		void (A::*mfp) (); // 선언
		mfp = &A::mf; // 멤버 함수 할당
		// todo 함수 포인터 전달 시 왜 &를 사용해 전달하나?

		// mfp(); 이렇게만 호출하면 this 매핑이 안되어 호출이 안된다.
		// "명백한 호출의 괄호 앞에 오는 식에는 함수(포인터) 형식이 있어야합니다." 에러남
		// 전역 함수 포인터와는 다르게 this가 꼭 필요하다.

		// 객체로 호출
		A a; //  this 역할을 할 객체 생성
		cout << &a << endl; // a의 메모리 주소 확인 : 008FFA73
		(a.*mfp)();  // 실행 : f() 008FFA73 <- a에서 실행됨을 확인
		//a.mfp(); // 실행 안됨, 컴파일 에러.

		// 주소로 호출
		A* b = &a;
		cout << b << endl; // b의 메모리 주소 확인 : 008FFA73
		(b->*mfp)();  // 실행 : f() 008FFA73 <- a에서 실행됨을 확인
	}


	cout << "===== function 클래스를 이용한 함수 포인터 바인딩 =====" << endl;
	{
		/*
			function 기능은 C++11부터 지원하는 기능이다.
			이 기능은 함수포인터를 전역, 멤버 가리지 않고 쉽게 주소를 지정해서 호출할 수 있도록 만들어주는 기능이다.
			선언방법 : function<반환타입(인자타입)> 변수명;
			C++11에서추가된 function 클래스 이용하여 함수포인터 사용하기
		*/

		// 전역 함수포인터 바인딩
		function<int(int a, int b)> func1; // function 객체 생성

		// gfSum 함수와 인자를 바인딩 : 
		// 바인드 시 구체적인 인자값을 넣으면 인자가 고정되어 아래 라인처럼 인자를 넣어 호출해도 인자값은 변하지 않는다.
		func1 = bind(&gfSum, 1, 1);
		func1(2, 2); // 실행 : gfSum() 2

		// placeholders를 이용한 함수 바인딩 : 
		// 바인드 시 인자를 placeholders를 이용해 지정하면 호출 시 인자를 사용할 수 있고 placeholder 순서로 인자의 순서를 바꿔줄 수 있다.
		func1 = bind(&gfSum, placeholders::_1, placeholders::_2);
		func1(2, 2); // 실행 : gfSum() 4

		// 객체 함수포인터 바인딩
		A a;
		function<void()> func2;
		// 함수 포인터와 객체를 묶어준다. 
		// 객체 인자 전달 시 객체를 그대로 넘기면 복사 생성된 객체에서 실행된다.
		// 따라서 포인터를 넘겨야한다.
		func2 = bind(&A::mf, &a);
		cout << &a << endl; // 00EFFA37
		func2(); // 실행 : A mf() 00EFFA37 <- a에서 실행됨을 확인, 만약 바인드 시 객체를 넘기면 주소가 서로 다름
	}

	cout << "===== 클라이언트 코드와 서버 코드 =====" << endl;
	{
		/*
		기능이나 서비스를 제공하는 코드 측을 서버 코드라하고 
		기능을 제공받는 코드 측을 클라이언트 코드라한다.
		서버는 하나지만 클라이언트는 여러개이다.

		서버 측 코드에 클라이언트 함수를 전달하는 방법
			함수 포인터, 함수 객체, 대리자, 전략 패턴 등
		*/

		cout << "--- 콜백함수 구현 : 함수 객체" << endl;
		{
			class Client {
			public:
				void operator()() {
					cout << "Client()" << endl;
				}
			};

			class Server {
			public:
				void operator()() {
					cout << "Server()" << endl;
				}
				void operator()(Client* c) {
					cout << "Server() callback" << endl;
					(*c)(); // 콜백 함수 호출
				}
			};

			Server()(); // 서버 함수 호출 : Server()

			Client c; 
			Server()(&c); // 서버 함수 호출 시 클라이언트 콜백 함수 전달 : Server() callback, Client()

			// todo 람다 함수 콜백함수로 전달
			// https://blog.koriel.kr/modern-cpp-lambdayi-teugjinggwa-sayongbeob/
		}

		cout << "--- 콜백함수 구현 : 함수 포인터" << endl;
		{
			struct Server {
			public:
				void operator()(int (*f)(int, int)) {
					cout << "Server() callback" << endl;
					i = (*f)(i, 1); // 콜백 함수 호출
				}
				int i = 0;
			};

			Server sv;
			sv(gfSum); // 서버 함수 호출 시 클라이언트 콜백 함수 전달 : Server() callback, Client()
			sv(&gfSum); // 위와 동일

			// todo 람다 함수 콜백함수로 전달
			// https://blog.koriel.kr/modern-cpp-lambdayi-teugjinggwa-sayongbeob/
		}
	}
}