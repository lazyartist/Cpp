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
자식 객체라도 c->p::vfn(); 이렇게 호출하면 부모의 가상 함수를 호출한다.

순수가상함수 : 가상함수 뒤에 =0을 붙여주면 해당 가상함수는 구현 부분이 없고 자식 클래스에서 반드시 구현해야한다.
순수가상함수를 갖고 있는 클래스는 추상 클래스라 부르며 객체 생성이 불가능하다.
하지만 변수형으로 사용할 수 있다.
*/

class A {
public:
	A() {
		cout << "A" << endl;
	}

	~A() {
		cout << "~A" << endl;
	}

	virtual void vfn() {
		cout << "A vfn" << endl;
	}
};

class B : public A{
public :
	B() {
		cout << "B" << endl;
	}

	~B() {
		cout << "~B" << endl;
	}

	// virtual
	void vfn() {
		cout << "B vfn" << endl;
	}
};

int main() {
	A a; // 지역변수로 선언됐기 때문에 프로그램 종료 시 소멸자가 호출된다.
	B b; // "A" "A" "B" "~B" "~A" "~A" 삭제될 때는 자식 소멸자부터 호출된다. 변수의 순서는 거꾸로 제거된다.

	//A* aa = new B(); // 힙에 생성했기 때문에 명시적으로 delete하지 않으면 소멸자가 호출되지 않는다.
	//				 // B가 A를 private 상속받았다면 넣을 수 없다.

	//aa->vfn(); // "B vfn"
	//delete aa; // aa의 타입이 A*이기 때문에 ~A만 호출되고 ~B는 호출되지 않는다.

	return 0;
}