#include <iostream>
#include "utils.h"
#include <string>

/*

*/

namespace ns1603 {
	using namespace std;

	/*
	ForEach 함수 템블릿
		배열의 시작 주소, 끝 주소를 받아 끝까지 순회한다.
		클라이언트 측에서 제공한 함수를 매번 호출하며 현재 요소를 인자로 제공한다.
	*/
	template<typename IterT, typename FuncT>
	void ForEach(IterT* begin, IterT* end, FuncT f) {
		if (begin >= end) return;

		while (begin != end)
		{
			cout << "ForEach " << *begin << endl;
			f(*begin);

			++begin;
		}
	}

	/*
	Less 함수 객체 템플릿
	*/
	template<typename T1, typename T2>
	struct Less {
		bool operator()(T1 t1, T2 t2) {
			return t1 < t2;
		}
	};

	/*
	반환타입과 매개변수 타입을 타입으로 받는 템플릿 함수
	*/
	template<typename ReturnT, typename ArgT>
	ReturnT ReturnArgFunction(ArgT arg) {
		cout << arg << endl;
		return ReturnT();
	}

	/*
	pair 클래스 구현
	*/
	template<typename T1, typename T2>
	struct Pair {
		Pair(const T1& t1, const T2& t2) : first(t1), second(t2) {}
		T1 first;
		T2 second;


		void print() {
			cout << first << ", " << second << endl;
		}
	};

	/*
	배열 복사 템플릿 함수
	1번재 인자의 값을 2번째 인자에 복사하기
	*/
	template<typename T1, typename T2>
	void Copy(T1* src, T2*dest, size_t size) {
		for (size_t i = 0; i < size; i++)
		{
			dest[i] = src[i];
		}
	}

	/*
	Stack 템플릿 클래스
	Push(), Pop(), Empty()
	*/
	template<typename T>
	class Stack {
	public:
		Stack() : size(0), capacity(10) {
			arr = new T[capacity];
		}

		~Stack() {
			delete[] arr;
		}

		void Push(const T data) {
			if (size == capacity) return;

			arr[size++] = data;
		}

		T Pop() {
			if (size == 0 || size == capacity) return 0;

			return arr[--size];
		}

		bool Empty() {
			return size == 0;
		}

		void Print() {
			if (size == 0) {
				cout << "Empty" << endl;
			}
			else {
				GPrint(arr, size);
			}
		}

		int size = 0;
		const int capacity;
		T *arr;
	};

	/*
	Queue 템플릿 클래스
	Push(), Pop(), Empty()
	*/
	template<typename T>
	class Queue {
	public:
		Queue() : size(0), capacity(3) {
			arr = new T[capacity];
		}

		~Queue() {
			delete[] arr;
		}

		void Push(const T data) {
			if (size == capacity) {
				cout << "Full" << endl;
				return;
			}

			arr[end] = data;
			++size;

			if (++end == capacity) {
				end = 0;
			}
		}

		T Pop() {
			if (size == 0) return 0;

			int returnFirst = first++;

			if (first == capacity) {
				first = 0;
			}
			--size;

			return arr[returnFirst];
		}

		bool Empty() {
			return size == 0;
		}

		void Print() {
			if (size == 0) {
				cout << "Empty" << endl;
			}
			else {
				GPrint(arr, size);
			}
		}

		int size = 0;
		const int capacity;
		T *arr;
		int first = 0;
		int end = 0;
	};
}

using namespace std;
using namespace ns1603;

void _1603_template_exercise() {
	cout << "ForEach 함수 템플릿" << endl;
	{
		// int, 람다
		auto intLd = [](int&i) -> int {
			cout << "f() " << i << endl;
			return i;
		};

		int iarr[] = { 1, 2, 3, 4, 5 };
		ForEach(iarr, iarr + 5, intLd); // 암시적 호출, 컴파일러가 템플릿 타입을 유추하고 람다 함수도 받을 수 있다.
		ForEach<int, int(*)(int&)>(iarr, iarr + 5, intLd); // 명시적 호출

		// char*, 람다
		auto strLd = [](const char* &str) { // & : 포인터의 참조를 받는 것도 가능함
			cout << str << endl;
		};
		const char* str[] = { "a", "b", "c", "d", "e" };
		ForEach<>(str, str + 5, strLd); // 암시적 호출
		ForEach<const char*, void(*)(const char*&)>(str, str + 5, strLd); // 명시적 호출

		// double, 함수 객체
		struct doubleFtr {
			void operator()(double d) {
				cout << d << endl;
			}
		};
		double ds[] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
		ForEach<>(ds, ds + 5, doubleFtr()); // 암시적 호출
		ForEach<double, doubleFtr>(ds, ds + 5, doubleFtr()); // 명시적 호출
	}

	cout << "Less 함수 객체 템플릿" << endl;
	{
		cout << Less<int, int>()(1, 2) << endl; // 명시적 호출
//		cout << Less<>()(1, 2) << endl; // 암시적 호출 에러
	}

	cout << "반환타입과 매개변수 타입을 타입으로 받는 템플릿 함수" << endl;
	{
		cout << ReturnArgFunction<int, int>(1) << endl; // 1, 0
	}

	cout << "pair 클래스 구현" << endl;
	{
		Pair<int, int> pair(1, 1);
		pair.print(); // 1, 1

		int i;
		Pair<int, int> pair2(i, i);
	}

	cout << "pair 클래스 구현" << endl;
	{
		Pair<int, int> pair(1, 1);
		pair.print(); // 1, 1

		int i;
		Pair<int, int> pair2(i, i);
	}

	cout << "배열 복사 템플릿 함수" << endl;
	{
		const size_t len = 5;

		// int array
		int iSrc[] = { 1, 2, 3, 4, 5 };
		int iDest[len];
		GPrint(iDest, len, ',');
		Copy(iSrc, iDest, len);
		GPrint(iDest, len);

		// char array
		char cSrc[] = { 'a','b','c','d','e' };
		char cDest[len] = { 0 };
		GPrint(cDest, len);
		Copy(cSrc, cDest, len);
		GPrint(cDest, len);

		// char * array
		/*
		const char * arr[] : const char의 포인터 배열
			배열은 const가 아니므로 요소값(포인터) 변경 가능
			요소값(포인터)를 역참조간 문자값은 변경 불가
			따라서 아래처럼 strDest의 타입이 const char라도 배열은 const가 아니기 때문에 요소값(포인터)는 변경 가능하다.
		*/
		const char *strSrc[] = { "abc", "def", "ghi", "jkl", "mno" };
		const char *strDest[len] = {nullptr};
		GPrint(strDest, len);
		Copy<const char *const, const char *>(strSrc, strDest, len);
		GPrint(strDest, len);

	}

	cout << "Stack 클래스" << endl;
	{
		Stack<int> intStack;

		intStack.Push(1);
		intStack.Push(3);
		intStack.Print(); // 1, 3

		cout << intStack.Pop() << endl; // 3, 뒤에서부터 출력 확인
		cout << intStack.Pop() << endl; // 1

		cout << "Empty? " << intStack.Empty() << endl; // 1(true)

		cout << "---" << endl;

		Stack<const char*> strStack;

		strStack.Push("a");
		strStack.Push("b");
		strStack.Print(); // a, b

		cout << strStack.Pop() << endl; // b, 뒤에서부터 출력 확인
		cout << strStack.Pop() << endl; // a

		cout << "Empty? " << strStack.Empty() << endl; // 1(true)
	}

	cout << "Queue 클래스" << endl;
	{
		Queue<int> intQueue;

		intQueue.Push(1);
		intQueue.Push(2);
		intQueue.Push(3);
		intQueue.Print(); // 1, 2, 3

		cout << intQueue.Pop() << endl; // 1, 앞에서 부터 출력 확인
		cout << intQueue.Pop() << endl; // 2
		cout << intQueue.Pop() << endl; // 3

		intQueue.Push(4);
		intQueue.Push(5);
		cout << intQueue.Pop() << endl; // 4

		cout << "Empty? " << intQueue.Empty() << endl; // 0(false)

		intQueue.Print(); // 4, 원래 5가 나와야하지만 GPrint가 처음부터 size만큼 출력하기 때문에 4를 출력한다.(버그)

		cout << "---" << endl;

		Queue<const char*> strQueue;

		strQueue.Push("a");
		strQueue.Push("b");
		strQueue.Print(); // a, b

		cout << strQueue.Pop() << endl; // a // 앞에서부터 출력 확인
		cout << strQueue.Pop() << endl; // b

		cout << "Empty? " << strQueue.Empty() << endl; // 1(true)
	}
}