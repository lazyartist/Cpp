#include <iostream>

using namespace std;

// 함수에 템플릿 적용
template<typename T>
void OutputData(T data) {
	cout << typeid(T).name() << endl;
	cout << data << endl;
}

// 클래스에 템플릿 적용
template<typename T>
class A {
public:
	T a;
};

int main() {
	OutputData(1); // OutputData<int> 이렇게 타입을 지정하지 않아도 1을 보고 컴파일러가 타입을 넣어준다.
	OutputData<float>(1.f);
	//OutputData<int>("aaaa"); // 이렇게 실제 인수와 다른 타입을 지정하면 에러난다.
	OutputData<const char*>("aaaa");  // 출력 타입 : char const * 
	OutputData("aaaa");				  // 출력 타입 : char const *
	OutputData<const char[]>("aaaa"); // 출력 타입 : char const [0]

	A<int> a = {};
	cout << a.a << endl;

	return 0;
}