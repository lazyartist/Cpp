#include <iostream>

#define NAME_SIZE 8

using namespace std;

void _0401_char() {
	cout << "char, char[], const char*" << endl;
	{
		char c = 'c'; // char 변수 생성 후 'c' 리터럴 복사
		char cs[] = "Hello"; // "Hello" 길이 + 1 만큼 char 배열 생성 후 배열 요소에 "Hello\0" 문자 복사
		const char* cp = "Hello"; // "Hello" 리터럴 문자열의 포인터를 cp 변수에 저장. 리터럴은 변경 불가이기 때문에 const로 받아야한다.

		// for breakpoint
		int a = 0;


		// 리터럴 관련해서는 1802 literal 참고
	}
}