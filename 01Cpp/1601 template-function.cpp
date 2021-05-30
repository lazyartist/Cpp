#include <iostream>

/*
함수 템플릿
	여러 함수를 만들어내는 함수의 틀

클래스 템플릿
	여러 클래스를 만들어내는 클래스의 틀

함수를 호출하는 곳에서 결정된 타입에 맞는 템플릿 인스턴스 함수를 컴파일러가 각각 생성한다.
컴파일이 완료되면 템플릿은 존재하지 않고 인스턴스화된 함수만 있다.

class, typename
	template<class T> 형식은 C++ 표준화 이전부터 사용하던 형식
	template<typename T> 형식은 표준화 이후 사용
	대부분의 컴파일러는 둘 다 지원

함수 템플릿 특수화
	함수 템플릿 내의 연산을 지원하지 않는 타입을 지정하면 컴파일 에러난다.
	이럴 경우 특수 함수 템플릿을 정의하여 특정한 타입에 대한 함수를 작성한다.
*/

namespace ns1601 {
	using namespace std;

	class A {
	public:
		int i = 1;
	};

	// 함수 템플릿
	template<typename T>
	void tf(T data) {
		cout << typeid(T).name() << ", " << data << endl;
	}

	// 함수 템플릿, 고정타입 지정
	template<typename T, int size>
	void tf(T data) {
		cout << typeid(T).name() << ", " << data << ", " << size << endl;
	}

	// A에 대한 특수 함수 템플릿
	template<>
	void tf(A data) {
		cout << "특수 " << typeid(A).name() << ", " << data.i << endl;
	}

	// 클래스 템플릿
	template<typename T>
	class TA {
	public:
		T a;
	};

}

using namespace std;
using namespace ns1601;

void _1601_template_function() {
	/*
	타입을 지정하지 않으면 컴파일러가 값을 보고 타입을 유추한다.
	*/
	{
		tf(1); // int, 1 : 타입 유추
		tf<int>(1); // int, 1 : 타입 지정
		tf<float>(1.f); // float, 1 : 타입 지정

		tf("a");				// char const *, a
		tf<const char*>("a");	// char const *, a
		tf<const char[]>("a");	// char const [0], a
	}

	/*
	템플릿에도 오버로딩이 적용되어 사인이 일치하는 함수를 호출한다.
	템플릿 매개변수로 타입뿐만 아니라 정수등도 가능
		9라는 정수값을 컴파일러가 유추할 수없기 때문에 명시적으로 넣어야한다.
	*/
	{
		tf<int, 9>(1); // int, 1, 9
	}

	/*
	실제 인수와 다른 타입을 지정하면 에러
	*/
	{
		//tf<int>("a");
	}

	/*
	함수 템플릿 특수화(Function Template Specialization)
	*/
	{
		/*
		tf 함수내에 있는 << 연산자를 A 클래스가 지원하지 않아서 컴파일 에러.
		"이항 '<<': 오른쪽 피연산자로 'T' 형식을 사용하는 연산자가 없거나 허용되는 변환이 없습니다."
		특수 함수 템플릿을 정의하여 해결
		*/

		A a;
		tf<A>(a); // class ns1601::A, 1
	}
}