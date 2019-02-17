#include <iostream>
#include "utils.h"

using namespace std;

void _1404_operator_exercise() {

	cout << "===== 컴파일될 수 있게 String 클래스를 작성1 =====" << endl;
	{
		class String {
		public:
			String(const char* str) {
				this->str = str;
			}

			const char* str;

			// const char*() 형 변환 연산자 오버로딩
			operator const char*() {
				return str;
			}
		};

		// 다음이 컴파일 되도록 작성
		String s("Hello");
		const char* sz = s; // 형 변환 연산자 오버로딩에 의해 대입 가능

		cout << sz << endl;
	}

	cout << "===== 컴파일될 수 있게 String 클래스를 작성2 =====" << endl;
	{
		class String{
		public:
			String(const char* str) {
				cout << "String " << str << endl;
				this->str = str;
			}
			~String() {
				cout << "~String " << str << endl;
			}
			const char * str;
			
			// const char*() 형 변환 연산자 오버로딩
			// 이 함수로 인해 cout << 에 인자로 전달할 수 있다.
			operator const char*() {
				return str;
			}
		};

		// 다음이 컴파일 되도록 작성
		const char* sz = "Hello";
		String s("Hi");
		s = sz; // 대입 연산자가 없기 때문에 복사 생성자로 임시 객체를 생성하고 기본 생성자로 값 복사

		/*
		String Hi
		String Hello
		~String Hello
		*/

		cout << s << endl;
	}
}