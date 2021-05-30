// 사용자가 만든 헤더파일을 포함시킬때는 ""안에 적어준다.
#include "10DoubleLinkedList.h"

int main() {
	
	// 리스트 생성
	PList pList = new List;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
	pList->iSize = 0;

	// 데이터 뒤에 추가
	for (size_t i = 0; i < 9; i++)
	{
		PNode pNode = new Node();
		pNode->Data = i;
		pNode->pPrev = NULL;
		pNode->pNext = NULL;

		Push_Back(pList, pNode);
	}
	PrintList("Push_Back", pList);

	// 데이터 앞에 추가
	PNode addNode = new Node;
	addNode->Data = 99;
	Push_Front(pList, addNode);
	PrintList("Push_Front", pList);

	// 정렬
	SortList_Bubble(pList, true);
	PrintList("SortList", pList);

	// 마지막 데이터 제거
	PopList(pList);
	PrintList("PopList", pList);

	// 특정 위치 데이터 제거
	RemoveList(pList, 1);
	PrintList("RemoveList", pList);
	RemoveList(pList, 6);
	PrintList("RemoveList", pList);

	// 데이터 찾기
	PNode foundNode = SearchNode(pList, 8);
	SearchNode(pList, 55);

	// 모든 데이터 제거
	RemoveAllList(pList);
	PrintList("RemoveAllList", pList);

	// 리스트 메모리 해제
	delete pList;

	return 0;
}