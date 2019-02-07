#include <iostream>

using namespace std;

typedef struct _tagNode {
	int iData;
	_tagNode* pNextNode = 0;
} Node, *PNode;

typedef struct _tagList {
	PNode pBegin = 0;
	PNode pEnd = 0;
	int iSize = 0;
} List, *PList;

void PushNode(PList list, PNode newNode) {
	if (list->iSize == 0) {
		list->pBegin = newNode;
	}
	else {
		list->pEnd->pNextNode = newNode;
	}

	list->pEnd = newNode;
	list->iSize++;
}

void PopNode(PList list) {
	if (list->iSize == 0) {
		return;
	}
	else {
		PNode it = list->pBegin;
		PNode pEnd = list->pEnd;
		while (it->pNextNode != pEnd)
		{
			it = it->pNextNode;
		}

		delete pEnd;

		it->pNextNode = 0;
		list->pEnd = it;
		list->iSize--;
	}
}

void RemoveNode(PList list, int idx) {
	if (list->iSize == 0 || idx < 0 || list->iSize <= idx) {
		return;
	}
	else {
		int count = 0;
		PNode it = list->pBegin;
		PNode prevNode = it;
		while (it != NULL)
		{
			if (count == idx) {
				break;
			}

			prevNode = it;
			it = it->pNextNode;
			count++;
		}

		if (prevNode == it) { // index : 0
			list->pBegin = it->pNextNode;
		}
		else {
			prevNode->pNextNode = it->pNextNode;
		}

		if (it == list->pEnd) { // 또는 : it.pEnd == NULL
			list->pEnd = prevNode;
		}

		delete it;
		list->iSize--;
	}
}

void RemoveAllNode(const PList list) {
	if (list->iSize == 0) {
		return;
	}
	else {
		int count = 0;
		PNode begin = list->pBegin;
		while (begin != 0)
		{
			PNode pNode = begin->pNextNode;
			delete begin;
			begin = pNode;
		}
	}

	list->pBegin = 0;
	list->pEnd = 0;
	list->iSize = 0;
}

void PrintList(const char name[], const PList list) {
	// const는 이 변수의 값을 바꾸지 않겠다라는 뜻이기 때문에
	// const PList list 하면 list가 가지고 있는 포인터를 바꾸지 않게 제한한다.
	// 따라서 list가 가진 포인터의 주소에있는 값은 변경이 가능하다.
	// list++ : 불가, list->iSize++ : 가능

	cout << "============" << name << "============" << endl;
	PNode it = list->pBegin;
	int count = 0;
	while (it != 0)
	{
		cout << "Count : " << count << ", " << it->iData << endl;
		it = it->pNextNode;
		count++;
	}
	cout << "============" << endl;
}

int main() {
	// 리스트 생성
	List list;

	// 리스트에 요소 추가
	for (size_t i = 0; i < 5; i++)
	{
		PNode newNode = new Node();
		newNode->iData = i;
		PushNode(&list, newNode);
	}
	PrintList("PushNode", &list);
	
	// 리스트에서 끝 요소 제거
	PopNode(&list);
	PrintList("PopNode", &list);

	// 리스트에서 지정한 위치의 요소 제거
	RemoveNode(&list, 1);
	PrintList("RemoveNode", &list);
	RemoveNode(&list, 0);
	PrintList("RemoveNode", &list);

	// 모든 메모리 해제
	RemoveAllNode(&list);
	PrintList("RemoveAllNode", &list);

	return 0;
}