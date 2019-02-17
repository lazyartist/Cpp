#include <iostream>
#include <functional> // C++11에서 함수포인터를 편하게 사용하기 위해 추가된 기능을 사용하기 위해 include

using namespace std;

/*
함수포인터 : 함수의 메모리 주소를 저장하기 위한 포인터 변수
전역함수의 경우 함수명이 곧 함수의 메모리 주소
함수포인터 선언방법 : 반환타입 (*포인터변수명)(인자타입);

this 포인터 : 클래스 안에서 this를 사용할 경우 해당 객체의 메모리 주소가된다. 즉 자기자신의 포인터이다.
멤버함수 내에서 멤버변수 호출 시 this를 생략가능(컴파일시 this를 붙인다)

*/

int Sum(int a, int b) {
	return a + b;
}

class A {
public :
	void FN() {
		cout << "FN" << endl;
	}
};

int main() {
	// todo 함수 포인터 전달 시 왜 &를 사용해 전달하나?

	// ============= 전역 함수포인터 ============= //
	int(*fpSum)(int, int) = &Sum;

	cout << "Sum " << fpSum(1, 2) << endl;

	// 멤버함수포인터 선언시 포인터변수 이름 앞에 클래스명::을 붙여준다
	// ::은 범위지정연산자라 한다.
	void(A::*fn)() = &A::FN;

	A a;
	(a.*fn)();
	//fn(); // 그냥 이렇게 호출하면 this 매핑이 안되어 호출이 안된다.
	// "명백한 호출의 괄호 앞에 오는 식에는 함수(포인터) 형식이 있어야합니다." 에러남
	// 전역 함수 포인터와는 다르게 this가 꼭 필요하다.



	// ============= functional ============== //
	// function 기능은 C++11부터 지원하는 기능이다.
	// 이 기능은 함수포인터를 전역, 멤버 가리지 않고 쉽게 주소를 지정해서 호출할 수 있도록 만들어주는 기능이다.
	// 선언방법 : function<반환타입(인자타입)> 변수명;
	// C++11에서추가된 function 클래스 이용하여 함수포인터 사용하기

	// 전역 함수포인터 바인딩
	function<int(int a, int b)> function01;
	function01 = bind(&Sum, 1, 1); // 바인드 시 구체적인 인자값을 넣으면 인자가 고정되어 아래 라인처럼 인자를 넣어 호출해도 인자값은 변하지 않는다.
	cout << "functional Sum value " << function01(2, 2) << endl;
	function01 = bind(&Sum, placeholders::_1, placeholders::_2); // 바인드 시 인자를 placeholders를 이용해 지정하면 호출 시 인자를 사용할 수 있고 placeholder 순서로 인자의 순서를 바꿔줄 수 있다.
	cout << "functional Sum placeholder " << function01(2, 2) << endl;

	// 객체 함수포인터 바인딩
	A aa;
	function<void()> function02;
	function02 = bind(&A::FN, aa); // bind를 이용해 함수와 객체를 묶어준다.
	function02();

	return 0;
}