#include "10DoubleLinkedList.h"

void Push_Back(PList pList, PNode pNewNode) {
	if (pList->pBegin == NULL) {
		pList->pBegin = pNewNode;
		pList->pEnd = pNewNode;

		pNewNode->pPrev = NULL;
		pNewNode->pNext = NULL;
	}
	else {
		pNewNode->pPrev = pList->pEnd;
		pNewNode->pNext = NULL;

		pList->pEnd->pNext = pNewNode;

		pList->pEnd = pNewNode;
	}

	pList->iSize++;
}

void Push_Front(PList pList, PNode pNewNode) {
	if (pList->pBegin == NULL) {
		pList->pBegin = pNewNode;
		pList->pEnd = pNewNode;

		pNewNode->pPrev = NULL;
		pNewNode->pNext = NULL;
	}
	else {
		pNewNode->pPrev = NULL;
		pNewNode->pNext = pList->pBegin;

		pList->pBegin->pPrev = pNewNode;

		pList->pBegin = pNewNode;
	}

	pList->iSize++;
}

void PopList(PList pList) {
	if (pList->iSize == 0) {
		return;
	}

	if (pList->iSize == 1) {
		delete pList->pEnd;
	}
	else {
		PNode pNewEnd = pList->pEnd->pPrev;
		delete pList->pEnd;
		pNewEnd->pNext = NULL;
		pList->pEnd = pNewEnd;
	}

	pList->iSize--;

	if (pList->iSize == 0) {
		pList->pBegin = NULL;
		pList->pEnd = NULL;
	}
}

void RemoveList(PList pList, int index) {
	if (pList->iSize <= index || index < 0) {
		return;
	}

	int count = 0;
	PNode it = pList->pBegin;
	while (count != index)
	{
		count++;
		it = it->pNext;
	}

	// 리스트의 시작이면서 끝일 수도 있기 때문에 else if로 묶지 않는다.
	// 리스트 시작
	if (it->pPrev == NULL) {
		pList->pBegin = it->pNext;
		pList->pBegin->pPrev = NULL;
	}
	// 리스트 끝
	if (it->pNext == NULL) {
		pList->pEnd = it->pPrev;
		pList->pEnd->pNext = NULL;
	}
	// 리스트의 시작과 끝이 아니라면
	if (it->pPrev != NULL && it->pNext != NULL) {
		it->pPrev->pNext = it->pNext;
	}

	pList->iSize--;
	delete it;
}

void RemoveAllList(PList pList) {
	if (pList->iSize == 0) {
		return;
	}

	PNode it = pList->pBegin;
	while (it != NULL)
	{
		PNode pNext = it->pNext;
		delete it;
		it = pNext;
	}

	pList->iSize = 0;
	pList->pBegin = NULL;
	pList->pEnd = NULL;
}

PNode SearchNode(PList pList, int keyword)
{
	PNode foundNode = NULL;
	PNode it = pList->pBegin;
	while (it != NULL)
	{
		if (it->Data == keyword) {
			foundNode = it;
			break;
		}

		it = it->pNext;
	}

	if (foundNode == NULL) {
		cout << "========== SearchNode Not Found : " << keyword << endl;
	}
	else {
		cout << "========== SearchNode Found : " << foundNode->Data << endl;
	}

	return foundNode;
}

void SortList_Bubble(PList pList, bool bAsc) {
	// for문 대신 while문을 사용하려면 버플정렬 대신 선택정렬이 더 낫다.
	// 버블정렬을 for문으로 구현하려면 pEnd를 한칸씩 앞으로 옮겨주는게 너무 힘들다.
	for (size_t i = 0; i < pList->iSize; i++)
	{
		PNode pFirst = pList->pBegin;
		PNode pSecond = pFirst ->pNext;

		for (size_t j = 0; j < pList->iSize - i - 1; j++)
		{
			bool bSwap = false;
			if (bAsc) {
				bSwap = pFirst->Data > pSecond->Data;
			}
			else {
				bSwap = pFirst->Data < pSecond->Data;
			}

			// swap
			if (bSwap) {
				bool isEnd = pFirst->pPrev == NULL;

				PNode pFirstPrev = pFirst->pPrev;
				PNode pSecondNext = pSecond->pNext;

				// first, seconde swap
				pFirst->pPrev = pSecond;
				pFirst->pNext = pSecond->pNext;
				pSecond->pPrev = pFirstPrev;
				pSecond->pNext = pFirst;

				// first prev, second next 설정
				if (pFirstPrev != NULL) {
					pFirstPrev->pNext = pSecond;
				}
				if (pSecondNext != NULL) {
					pSecondNext->pPrev = pFirst;
				}

				// begin, end 설정
				if (pSecond->pPrev == NULL) {
					pList->pBegin = pSecond;
				}
				if (pFirst->pNext == NULL) {
					pList->pEnd = pFirst;
				}

				// swap해서 first가 한칸 이동했으므로 first는 그대로 둔다.
			}
			else {
				// swap하지 않았으므로 first를 한칸 이동해준다.
				pFirst = pFirst->pNext;
			}

			pSecond = pFirst->pNext;
		}
	}
}

void PrintList(const char *title, PList pList) {
	cout << "==========" << title << "==========" << endl;

	PNode pNode = pList->pBegin;
	while (pNode != NULL)
	{
		cout << pNode->Data << endl;
		pNode = pNode->pNext;
	}

	cout << "==============================" << endl;
}