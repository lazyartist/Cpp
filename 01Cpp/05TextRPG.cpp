#include <iostream>
#include <time.h>

using namespace std;

enum MAIN_MENU {
	MM_NONE,
	MM_MAP,
	MM_STORE,
	MM_INVENTORY,
	MM_EXIT,
};

enum MAP_TYPE {
	MT_NONE,
	MT_EASY,
	MT_NORMAL,
	MT_HARD,
	MT_BACK,
};

enum JOB {
	JOB_NONE,
	JOB_KNIGHT,
	JOB_ARCHER,
	JOB_WIZARD,
	JOB_END,
};

int main() {
	while (true)
	{
		system("cls");
		cout << "1. map" << endl;
		cout << "2. shop" << endl;
		cout << "3. bag" << endl;
		cout << "4. exit" << endl;
		cout << "select a menu : ";

		int iMenu;
		cin >> iMenu;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}

		if (iMenu == MM_EXIT)
			break;

		switch (iMenu)
		{
		case MM_MAP:
			break;
		case MM_STORE:
			break;
		case MM_INVENTORY:
			break;
		default:
			cout << "wrong selected" << endl;
			break;
		}
	}
}