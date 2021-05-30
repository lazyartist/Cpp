#include <iostream>

using namespace std;

void _2101_cast() {
	class A {

	public:
		A() {}
		A(int In_v) : v_a(In_v) {}

		int v_a = 0;
		void f() {
			printf("f(): %d\n", v_a);
		}
	};

	class B : public A {
	public:
		//B() {}
		//B(int InV) : v(InV) {} // 생성자에서 상속된 멤버를 초기화 할 수 없다. error: illegal member initialization: 'v' is not a base or member
		B(int In_v) : A(In_v), v_b(In_v) {}

		int v_b = 0;
		void f() {
			printf("f(): %d, %d\n", v_a, v_b);
		}

		virtual void vf() {
			printf("vf(): %d, %d\n", v_a, v_b);
		}
	};

	class C : public B {
	public:
		C(int In_v) : B(In_v) {}
	};

	std::cout << "===== static_cast  =====" << endl;
	{
		A a(1);
		a.f(); // f(): 1

		B b(2);
		b.f(); // f(): 2, 2

		A* pa = static_cast<A*>(&b);
		pa->f(); // f(): 2 => B가 A로 캐스팅 되었고 A::f()가 호출됐다. 정상

		B* pb = static_cast<B*>(&a);
		pb->f(); // f(): 1, -858993460 => A가 B로 캐스팅 되었고 B::f()가 호출됐다. v_b가 없으므로 비정상 행동, 어쨌든 가능은 하다.
	}

	std::cout << "===== dynamic_cast  =====" << endl;
	{
		A a(1);
		a.f(); // f(): 1

		B b(2);
		b.f(); // f(): 2, 2

		std::cout << "===== up casting =====" << endl;

		A* pa = dynamic_cast<A*>(&b);
		pa->f(); // f(): 2 => B가 A로 캐스팅 되었고 A::f()가 호출됐다. 정상

		//B* pb = dynamic_cast<B*>(&a); // A is not a polymorphic type => 컴파일 에러

		std::cout << "===== down casting =====" << endl;

		C* pc = dynamic_cast<C*>(&b); // pc == null => B가 polymorphic type이라서 컴파일 됨.
		//pc->f(); // 런타임 에러 => 다운 캐스팅을 했으므로 pc는 null이다.

		B* pb2 = new C(3);
		pb2->f(); // f(): 3, 3 => C를 생성해서 B에 넣었으므로 정상

		C* pc2 = dynamic_cast<C*>(pb2); // pb는 polymorphic type인 B이므로 컴파일 됨. pb의 타입을 A로 바꾸면 polymorphic 타입이 아니므로 컴파일 안됨.
		pc2->f(); // f(): 3, 3 => dynamic_cast으로 다운 캐스팅을 했지만 pb는 실제로 C타입이므로 정상 작동함. 하지만 위험한 행동임

		// 따라서 런타임 시 다운캐스팅은 dynamic_cast를 사용해서 제대로 형 변환이 이루어졌는지 null 체크를 통해 확인해야한다.

		delete pb2;
	}
}