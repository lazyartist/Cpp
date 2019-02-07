#include <iostream>

#define NAME_SIZE 8

using namespace std;

struct _tagStudent {
	char strName[NAME_SIZE];
	int iNumber;
	int iKor;
	int iEng;
	int iMath;
	int iTotal;
	float fAvg;
};

int main() {
	_tagStudent std;
	//_tagStudent std = {};

	// 문자열을 배열에 넣어줄 때에는 단순 대입으로는 불가능하다.
	// strcpy_s라는 함수를 이용해서 문자열을 복사해 주어야한다.
	strcpy_s(std.strName, 3, "aa");
	//std.strName[0] = 'a';
	//std.strName[1] = 0;

	// strcat_s 함수는 문자열을 붙여주는 기능
	// strName에 bb를 붙여서 저장한다.
	strcat_s(std.strName, "bb");

	// strcmp 함수는 두 문자열을 비교하여 같을 경우 0을 반환하고 다를 경우 0이 아닌 값을 반환한다.
	cout << strcmp(std.strName, "aabb") << endl;

	cout << std.strName << endl;
	cout << strlen(std.strName) << endl;
	cout << std.iNumber << endl;

	return 0;
}