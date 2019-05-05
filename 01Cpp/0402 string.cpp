#include <iostream>

#define NAME_SIZE 8

using namespace std;

void _0402_string() {
	char name[NAME_SIZE];

	// 문자열을 배열에 넣어줄 때에는 단순 대입(name = "aa")으로는 불가능하다.
	// strcpy_s라는 함수를 이용해서 문자열을 복사해 주어야한다.
	strcpy_s(name, 3, "aa");
	cout << name << endl;

	// strcat_s 함수는 문자열을 붙여주는 기능
	// name에 bb를 붙여서 저장한다.
	strcat_s(name, "bb");
	cout << name << endl;

	// strcmp 함수는 두 문자열을 비교하여 같을 경우 0을 반환하고 다를 경우 0이 아닌 값(-1)을 반환한다.
	cout << strcmp(name, "aabbz") << endl;


	// 문자열 리터럴 관련해서는 1802 literal 참고
}