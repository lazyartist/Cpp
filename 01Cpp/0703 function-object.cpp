#include <iostream>
#include <functional> // C++11에서 함수포인터를 편하게 사용하기 위해 추가된 기능을 사용하기 위해 include

using namespace std;

/*
함수 객체
	함수처럼 동작하는 객체이고 함수처럼 동작하려면 ()연산자를 정의해야함.
	함수 객체는 functor라고 불림
	함수 객체는 함수처럼 사용할 수 있으면서 상태를 가질 수 있다. 

함수 객체의 장점
	객체이므로 멤버 변수와 멤버 함수를 가질 수 있다.
	함수 객체의 서명(signature)이 같아도 객체 타입이 다르면 전혀 다른 타입으로 인식
	일반 함수보다 속도도 빠름
		함수 주소를 전달하여 콜백하는 경우 인라인될 수 없지만 
		함수 객체는 클래스 내부에 정의되므로 암묵적으로 인라인 함수가 된다.
		컴파일러가 쉽게 최적화 가능.

단점
	서명이 같더라도 타입이 다른 객체는 대입, 복사 불가

*/

void _0703_function_object() {

	cout << "===== 함수 객체 구현 =====" << endl;
	{
		/*
		Less 함수 객체 구현
		*/
		struct Less {
			bool operator()(int a, int b) {
				return a < b;
			}
		};

		cout << Less()(1, 2) << endl; // 1

		/*
		std::less<T> 함수 객체 사용
		*/
		std::less<int> less;
		cout << less(1, 2) << endl; // 1
	}

}