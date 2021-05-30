#include <iostream>

#define STUDENT_MAX 8
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

enum MENU{
	MENU_NONE,
	MENU_INSERT,
	MENU_DELETE,
	MENU_SEARCH,
	MENU_OUTPUT,
	MENU_EXIT,
};

int main() {
	_tagStudent tStudentArr[STUDENT_MAX] = {};
	int iStudentCount = 0;

	while (true)
	{
		system("cls");

		// menu
		cout << "1. 등록" << endl;
		cout << "2. 삭제" << endl;
		cout << "3. 탐색" << endl;
		cout << "4. 출력" << endl;
		cout << "5. 종료" << endl;
		cout << "메뉴를 선택하세요" << endl;

		int iMenu;
		cin >> iMenu;

		// cin은 오른쪽에 int 변수가 오면 정수를 입력해야한다.
		// 오른쪽에 오는 변수 타입에 맞춰서 값을 입력해야 하는데 실수로 정수가 아닌 문자를 입력할 경우 에러가 발생한다.
		// 그렇기 때문에 예외처리로 에러가 발생했는지를 여기에서 체크하여 에러가 발생하면 cin 내부의 에러버퍼를 비워주고
		// cin 내부에 입력버퍼가 있는데 입력버퍼는 입력한 값을 저장해놓고 그 값을 변수에 넣어주는 역할을 한다.
		// 이 입력버퍼에 \n 이 남아있으므로 버퍼를 순회하여 \n을 지워준다.
		// 에러체크 : cin.fail() true 반환 시 에러.
		if (cin.fail()) {
			// 에러버퍼를 비워준다.
			cin.clear();

			// 입력버퍼에 \n이 남아있으므로 입력버퍼를 검색하여 \n을 지워준다.
			// 첫번째는 검색하고자 하는 버퍼 크기를 지정한다. 넉넉하게 1024바이트 정도 지정해주었다.
			// 2번째는 찾고자 하는 문자를 넣어준다. 그래서 입력버퍼 처음부터 \n이 있는 곳까지 찾아서
			// 그 부분을 모두 지워줘서 다시 입력받을 수 있도록 해준다.
			cin.ignore(1024, '\n');
			continue;
		}

		switch (iMenu)
		{
		case MENU_INSERT:
			// cin은 Space도 입력의 끝으로 인식하기 때문에 Space 포함 문자열을 얻어오려면 cin.getline을 사용한다.
			cout << "이름: ";
			cin >> tStudentArr[iStudentCount].strName;

			// cin과 cin.getline을 같이 쓸 경우 cin에 의해 enter가 버퍼에 남아있고 이게 cin.getline 호출 시 입력 종료로 인식해 버린다.
			// 따라서 cin.ignore를 사용해 \n을 제거해준다.
			cin.ignore(1024, '\n');

			cout << "이름2: ";
			cin.getline(tStudentArr[iStudentCount].strName, NAME_SIZE);

			cout << tStudentArr[iStudentCount].strName << endl;
			break;
		case MENU_DELETE:
			break;
		case MENU_SEARCH:
			break;
		case MENU_OUTPUT:
			break;
		case MENU_EXIT:
			break;
		default:
			cout << "메뉴를 잘못 선택했습니다." << endl;
			break;
		}

		system("pause");
	}

	return 0;
}