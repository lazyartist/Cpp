#include <iostream>
#include "17TDList.h"
#include "17TDRList.h"

using namespace std;

int main() {
	//template<typename T>
	//typedef TemplateDReverseLinkedList<int> TDRList<int>;

	TDList<int> list;
	TDList<float> list1;

	for (size_t i = 0; i < 10; i++)
	{
		list.push_back(i);
	}

	list.print();
	list.clear();
	list.print();

	// 포인터에 대한 오퍼레이터 재정의는 어짜피 안된다.
	// 포인터 연산은 포인터의 이동이지 객체의 함수를 호출하는 것이 아니기 때문이다.
	// 따라서 Iterator의 연산을 위해서는 역참조를 해줘야한다.
	for (TDList<int>::Iterator iter = list.begin(); iter != list.end(); iter++) {
		cout << "iter" << endl;
	}

	cout << "=== Revers Iterator ===" << endl;
	
	TDRList<int> rList;
	for (size_t i = 0; i < 5; i++)
	{
		rList.push_back(i);
	}

	rList.print();

	for (TDRList<int>::Iterator iter = rList.begin_reverse(); iter != rList.end_reverse(); ++iter)
	{
		cout << "iter " << (*iter) << endl;
	}

	return 0;
}