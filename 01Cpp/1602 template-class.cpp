#include <iostream>
#include "utils.h"

/*
클래스 템플릿
	클래스를 만들어내는 틀(메타코드)
	템플릿은 메타 코드을 뿐이고 컴파일러가 실제 클래스를 생성한다.

클래스 템플릿 특수화
	함수 템플릿 특수화와 사용법은 같다.
*/

#define ArrSize 3

namespace ns1602 {
	using namespace std;

	/*
	간단한 Array 클래스 요구사항
	- int, double, char[]을 타입으로 받을 수 있다.
	- Array(int cap) : 생성자는 저장 가능한 최대원소의 개수를 인자로 받아 메모리를 생성
	- ~Array() : 소멸자는 생성한 메모리를 해제
	- Add(int data) : 객체에 데이터를 추가
	- operator[](int idx) : 인덱스 원소의 값을 반환
	- GetSize() : 객체의 원소 개수를 반환

	템플릿 매개변수 디폴트 값 지정
	생성자 함수를 명시적 호출로 지정
	*/
	template<typename T = int, int initCapacity = ArrSize>
	class Array {
	public:
		explicit Array(int cap = initCapacity) : capacity(cap), size(0), pArr(nullptr) {
			pArr = new T[capacity];
		}

		~Array() {
			SAFE_DELETE(pArr);
		}

		void Add(T data) {
			if (size >= capacity) return;

			pArr[size++] = data;
		}

		void print() {
			for (size_t i = 0; i < size; i++)
			{
				cout << pArr[i] << endl;
			}
		}

		int& operator[](const unsigned int idx) {
			if (idx >= size) return pArr[0];

			return pArr[idx];
		}

		int GetSize() {
			return size;
		}

	private:
		T* pArr;
		int capacity;
		int size;
	};

	/*
	cout << 에 Array 객체를 전달할 수 있게 << 연산자 오버로딩
		T 타입을 컴파일러가 어떻게 유추했을까?
	*/
	template<typename T>
	ostream& operator<<(ostream& o, Array<T>& arr) {
		o << arr.GetSize();
		return o;
	};

	/*
	클래스 템플릿 일반
	*/
	template<typename T>
	class SpecialPrint {
	public:
		void operator()(T data) {
			cout << "SpecialPrint " << data << endl;
		}
	};

	/*
	클래스 템플릿 string에 대해 특수화
	*/
	template<>
	class SpecialPrint<string> {
	public:
		void operator()(string data) {
			cout << "SpecialPrint " << data.c_str() << endl;
		}
	};
}

using namespace std;
using namespace ns1602;

void _1602_template_class() {
	cout << "" << endl;
	{
		cout << "--- double" << endl;
		{
			Array<double> arr(ArrSize);
			for (size_t i = 0; i < ArrSize; i++)
			{
				arr.Add(i);
			}
			arr.print();

			/*
			위에서 정의한 operator<< 함수 재정의가 잘 작동하는지 확인
			*/
			cout << "size " << arr << endl; // operator<< 연산자 함수 암묵적 호출
			operator<<(cout << "size ", arr) << endl; // operator<< 연산자 함수 명시적 호출
		}

		cout << "--- string" << endl;
		{
			const char* strings[ArrSize] = { "hi", "Hello", "test" };
			Array<char*> arr(ArrSize);
			for (size_t i = 0; i < ArrSize; i++)
			{
				char* str = new char[32];
				strcpy_s(str, 32, strings[i]);
				arr.Add(str);
			}
			arr.print();

			cout << "size " << arr << endl; // operator<< 연산자 함수 암묵적 호출
		}

		cout << "--- int" << endl;
		{
			/*
			타입을 지정하지 않고 템플릿의 디폴트 매개변수를 사용
				타입명을 쓰지 않는다
				<>는 써줘야한다.
			*/
			Array<> arr;
			for (size_t i = 0; i < ArrSize; i++)
			{
				arr.Add(i);
			}
			arr.print();

			cout << "size " << arr << endl; // operator<< 연산자 함수 암묵적 호출
		}

		cout << "--- SpecialPrint" << endl;
		{
			SpecialPrint<int>()(1);

			char sz[] = "char *";
			SpecialPrint<char *>()(sz);

			string str = "string";
			SpecialPrint<string>()(str); // 클래스 함수 특수화 객체가 생성된다.
		}
	}
}