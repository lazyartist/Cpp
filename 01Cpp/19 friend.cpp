#include <iostream>

using namespace std;

/*
함수나 클래스를 프렌드로 지정하면 클래스의 모든 멤버(변수, 함수)에 접근할 수 있다.
*/

class A {
private:
	void pf() {
		i = 9;
	}

	int i = 0;

	// friend 지정
	friend class B;
	friend void f();
};

class B {
public:
	void f() {
		A a;
		a.pf(); // A클래스에서 B클레스를 프렌드 지정해서 private 멤버에 접근 가능. 안하면 컴파일 에러.
		a.i; // i도 접근 가능
	}
};

void f() {
	A a;
	a.pf(); // A클래스에서 이 전역함수를 프렌드로 지정해서 private 멤버에 접근 가능. 안하면 컴파일 에러.
	a.i; // i도 접근 가능
}

void _1901_friend() {

	cout << "함수 프렌드, 클래스 프렌드" << endl;
	{
		B b;
		b.f();

		f();
	}
}

