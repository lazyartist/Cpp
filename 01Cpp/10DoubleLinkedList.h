// #pragma once : 이 헤더파일을 딱 1번만 포함시키겠다 라는 의미
#pragma once

#include <iostream>

using namespace std;

// 헤더파일에는 보통 함수 선언 부분을 만들어준다.

typedef struct _Node {
	int Data = 0;
	_Node * pPrev;
	_Node * pNext;
} Node, *PNode;

typedef struct _List {
	PNode pBegin;
	PNode pEnd;
	int iSize;
} List, *PList;

void Push_Back(PList pList, PNode pNewNode);
void Push_Front(PList pList, PNode pNewNode);
void PopList(PList pList);
void RemoveList(PList pList, int index);
void RemoveAllList(PList pList);
PNode SearchNode(PList pList, int keyword);
void SortList_Bubble(PList pList, bool bAsc);
void PrintList(const char * title, PList pList);

// 헤더파일은 함수등을 선언하는 곳이다.
// cpp 파일은 구현하는 곳으로 각 cpp 마다 하나씩 obj 파일이 만들어진다.
// 컴파일 시 첫번째로 소스코드를 obj 파일로 만들고 이 obj 파일을 연결(링크)하여 exe 파일을 만들게 된다.
// 링크과정은 빌드과정인가?

// 헤더파일에서 함수의 구현까지 할 경우 헤더파일을 include하는 파일이 여러개이면 링크에러가 난다.
// include하는 파일이 각각 obj가 생성되고 이 obj에 같은 내용의 함수구현부가 있기 때문에 중복선언(구현?) 문제가 발생한다.
// 이를 해결하기 위해서는 static 키워드를 붙이면 각 obj 마다 독립적으로 처리하게된다.
// 따라서 헤더파일에 함수를 구현할 경우 static을 붙여줘야 안전하다.
// 각각의 obj 파일에 함수가 포함되고 링크 시 양쪽에 있는 함수중 어떤 함수를 연결시켜야할지 몰라서 나는 에러다.


