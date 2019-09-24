#include <iostream>

using namespace std;

/*
상속 접근 지정자	| 기반		|	파생
public			| public	|	public
public			| private	|	접근불가
public			| protected	|	protected

private			| public	|	private
private			| private	|	접근불가
private			| protected	|	private

protected		| public	|	protected
protected		| private	|	접근불가
protected		| protected	|	protected

상속관계에서 생성자, 소멸자 소출 순서
생성자 : 부모 -> 자식
소멸자 : 자식 -> 부모

다형성 : 상속관계에 있는 클래스간에 서로 형변환이 가능한 성질

가상함수 : 함수를 재정의하는 기능, 함수 오버라이딩 이라고도 부른다.
부모 클래스에서 함수 선업 시 virtual 키워드를 붙여주면 자식클래스에서 재정의할 수 있다.
재정의는 함수의 이름과 인자가 똑같아야한다.

가상함수를 가지고 있는 클래스는 내부적으로 가상함수 테이블이라는 것을 생성한다.
가상 함수테이블은 가상함수의 메모리 주소를 저장하는 테이블이다.
자식 클래스에서 가상함수 재정의하고 객체를 생성하면 그 객체의 가상함수 테이블에는 
자식 클래스에서 재정의한 가상함수의 주소가 올라가게 된다.
부모 클래스의 객체를 생성하면 부모 클래스의 가상 함수 주소가 올라간다.
따라서 재정의된 함수를 호출하면 먼저 가상함수 테이블을 참조해서 해당 클래스에 맞는 함수를 호출하게 된다.

만약 자식 클래스에서 재정의하지 않으면 부모의 가상 함수가 호출된다.
부모 클래스 타입의 변수에 자식객체를 넣었을 경우에도 가상 함수 호출 시 실제 객체인 자식 클래스 객체의 가상 함수가 호출된다.

가상함수 테이블을 참조해야하기 때문에 속도가 아주 약간 느려진다.

부모의 가상함수 호출
자식 객체라도 c->p::vf(); 이렇게 호출하면 부모의 가상 함수를 호출한다.

순수가상함수 : 가상함수 뒤에 =0을 붙여주면 해당 가상함수는 구현 부분이 없고 자식 클래스에서 반드시 구현해야한다.
순수가상함수를 갖고 있는 클래스는 추상 클래스라 부르며 객체 생성이 불가능하다.
하지만 변수형으로 사용할 수 있다.
*/

namespace _1501 {
	class A {
	public:
		A() {
			int a;
			a = 1;
			cout << "A" << endl;
		}
		~A() {
			cout << "~A" << endl;
		}
		void f() {
			cout << "A f" << endl;
		}
		virtual void vf() {
			cout << "A vf" << endl;
		}
	};
	class B : public A {
	public:
		B() {
			cout << "B" << endl;
		}
		~B() {
			cout << "~B" << endl;
		}
		void f() {
			cout << "B f" << endl;
		}
		//보모 클래스에서 가상함수로 지정되면 하위 클래스에서 virtual 키워드가 없어도 가상함수로 취급된다.
		void vf() {
			cout << "B vf" << endl;
		}
	};

	class C : public B {
	public:
		C() {
			cout << "C" << endl;
		}
		~C() {
			cout << "~C" << endl;
		}
		void f() {
			cout << "C f" << endl;
		}
		void vf() {
			cout << "C vf" << endl;
		}
	};
}

using namespace _1501;

void _1501_inheritance() {
	cout << "===== A =====" << endl;
	{
		A a;//A ~A
		a.f();//A f
		a.vf();//A vf
	}
	cout << "===== B =====" << endl;
	{
		B b;//A B ~B ~A
		//생성자는 부모 클래스 생성자부터 호출, 소멸자는 자식 클래스 소멸자부터 호출된다.
		b.f();//B f
		b.vf();//B vf
	}
	cout << "===== C =====" << endl;
	{
		C c;//A B C ~C ~B ~A
		//생성자는 부모 클래스 생성자부터 호출, 소멸자는 자식 클래스 소멸자부터 호출된다.
		c.f();//C f
		c.vf();//C vf
		//일반 함수의 호출은 부모 함수가 호출되지 않는다.
	}
	cout << "===== A* = new C() =====" << endl;
	{
		A *a = new C();
		delete a;
		// 가상소멸자 X : A B C ~A
		// 가상소멸자 O : A B C ~C ~B ~A
		// 생성자는 실제객체의 생성자를 호출하지만
		// 소멸자는 가상소멸자가 아닌경우 객체 타입의 소멸자가 호출되고 부모의 소멸자까지 호출된다.
		// 가상 소멸자로 정의한 경우는 실제 객체의 소멸자가 호출되며 부모의 소멸자까지 호출된다.
	}
	cout << "===== B* = new C() =====" << endl;
	{
		B *a = new C();
		delete a;
		// 가상소멸자 X : A B C ~B ~A
		// 가상소멸자 O : A B C ~C ~B ~A
	}
	cout << "===== C* = new C() =====" << endl;
	{
		C *a = new C();
		delete a;
		// 가상소멸자 X : A B C ~C ~B ~A
		// 가상소멸자 O : A B C ~C ~B ~A
	}
	cout << "===== A* = new C() .vf =====" << endl;
	{
		A *a = new C();
		a->f();//A f
		//일반 함수 호출 : 객체의 변수타입의 함수가 호출
		a->vf();//C vf
		//가상 함수 호출 : 실제 객체의 함수가 호출
		//일반 함수는 객체의 타입을 따라가며 가상 함수는 실제 객체의 함수가 호출된다.
		delete a;
	}

	//A* aa = new B(); // 힙에 생성했기 때문에 명시적으로 delete하지 않으면 소멸자가 호출되지 않는다.
	//				 // B가 A를 private 상속받았다면 넣을 수 없다.

	//aa->vf(); // "B vf"
	//delete aa; // aa의 타입이 A*이기 때문에 ~A만 호출되고 ~B는 호출되지 않는다.
}