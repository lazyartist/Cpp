#pragma once

#include <iostream>

using namespace std;

template<typename T>
class TDRNode {
public:
	T Data;
	TDRNode<T>* pPrev;
	TDRNode<T>* pNext;

private :
	// private으로 선언해서 외부에서 사용하지 못하게 한다.
	TDRNode(){}
	~TDRNode(){}

	template <typename T>
	friend class TDRList;

	template <typename T>
	friend class TDRIterator;
};

template <typename T>
class TDRIterator {
private:
	TDRNode<T>* pNode;

public:
	TDRIterator(){}
	~TDRIterator(){}

public:
	TDRIterator& operator++() {
		pNode = pNode->pPrev;
		return *this;
	}

	// 후위 연산자, 반환하고 증가시킨다.
	//template <typename T> // 클래스에서 template 선언했기 때문에 여기선 하지 않는다. 선언만하고 외부에서 정의할 경우는 template 선언해야한다.
	TDRIterator<T> operator++(int dummy) {
		TDRIterator<T> pIter;
		pIter = *this; // 현재값 복사

		if (this->pNode->pPrev != NULL) {
			this->pNode = pNode->pPrev;
		}

		return  pIter;
	}

	bool operator !=(const TDRIterator<T>& iter) { // 함수의 반환값과 비교할 경우를 위해 파라미터를 const 참조로 받는다. const를 쓰지 않으려면 &를 쓰지 않는다.
		return pNode != iter.pNode;
	}

	T operator *() {
		return pNode->Data;
	}

	template <typename T>
	friend class TDRList;
};

//template<typename T, int size = 100> // 템플릿 타입변수로 상수를 받을 수 있다. size의 기본값 100, 사용은 TDRList<int, 10>으로 사용한다.
template<typename T>
class TDRList
{
public:
	//template<typename T>
	//typedef TemplateDReverseLinkedList<T> TDRList<T>;

	/*
	템플릿 클래스 내부에 중첩 구조체를 정의하고 TDRList<int> 객체를 생성하니 다음과 같은 에러가 난다.
	"오류	C2460	'TDRList<int>::_TDRNode::pPrev': 정의 중인 'TDRList<int>::_TDRNode'을(를) 사용합니다."
	int 타입 코드 생성 시 에러같은데 잘 모르겠어서 외부 클래스로 생성한다.
	*/

	//typedef struct _TDRNode {
	//	T Data;
	//	TDRList<T>::_TDRNode pPrev;
	//	TDRList<T>::_TDRNode pNext;
	//} TDRNode, *PTDRNode; // 포인터 타입 지정 시 *는 타입명 앞에 와야한다.

	//typedef struct _TDRIterator {
	//	_TDRNode* pNode;

	//	_TDRIterator& operator++() {
	//		pNode = pNode->pPrev;
	//	}
	//} TDRIterator, *PTDRIterator;

	typedef TDRIterator<T> Iterator;

	TDRList();
	~TDRList();

	void push_back(T data);
	//void push_front(T data);
	TDRIterator<T> begin_reverse();
	TDRIterator<T> end_reverse();

	void print();

private:
	TDRIterator<T>* pBeginIter;
	TDRIterator<T>* pEndIter;

	TDRNode<T>* pBegin;
	TDRNode<T>* pEnd;
	int iSize;

};


// Template 정의는 헤더와 구현 파일을 분리하지 말아야한다.
// Template은 각각의 데이터 타입에 맞는 소스코드를 만들어내므로 파일 분리하지 않아야한다.
// IDE를 잘 활용하면 방법이 있다지만 그냥 헤더파일에 정의하는게 좋다.
// 참고 : https://vaert.tistory.com/5
template<typename T>
TDRList<T>::TDRList()
{
	pBeginIter = new TDRIterator<T>;
	pEndIter = new TDRIterator<T>;

	pBegin = new TDRNode<T>;
	pEnd = new TDRNode<T>;

	pBeginIter->pNode = pBegin;
	pEndIter->pNode = pEnd;

	pBegin->pPrev = NULL;
	pBegin->pNext = pEnd;

	pEnd->pPrev = pBegin;
	pEnd->pNext = NULL;

	iSize = 0;
}

template<typename T>
TDRList<T>::~TDRList()
{
	delete pBegin;
	delete pEnd;
}

template<typename T>
void TDRList<T>::push_back(T data)
{
	TDRNode<T>* pNode = new TDRNode<T>;
	pNode->Data = data;

	pEnd->pPrev->pNext = pNode;

	pNode->pPrev = pEnd->pPrev;
	pNode->pNext = pEnd;

	pEnd->pPrev = pNode;

	iSize++;
}

/*
	inline : 함수호출의 오버헤드(어떤 처리를 하기 위해 들어가는 간접적인 처리 시간, 메모리 등)를 줄이기 위해 크기가 작은 함수를 inlien으로 지정하면
	함수가 사용되는 곳에 코드가 복사되어 컴파일된다.
	헤더에 함수를 정의한 경우 인라인으로 간주된다.
	함수안에 자신을 호출하는 재귀함수나 반복문, switch 문등이 포함되면 컴파일러가 inline 선언이 무시될 수 있다.
*/

template<typename T>
inline TDRIterator<T> TDRList<T>::begin_reverse()
{
	pEndIter->pNode = pEnd->pPrev;
	return *pEndIter;
}

template<typename T>
TDRIterator<T> TDRList<T>::end_reverse()
//inline TDRIterator<T> TDRList<T>::end_reverse()
{
	return *pBeginIter;
}


template<typename T>
void TDRList<T>::print()
{
	TDRIterator<T> iter1;
	TDRIterator<T> iter2 = {};
	iter1 != iter2; // != 참조로 받았을 때 가능

	auto a = end_reverse();

	/*
		!= 참조로 받았을 때 불가, 왜죠?
		참고 : https://kldp.org/node/71134
		설명 :
		++func();
		이라는 구문은 문법적으로 const int를 반환하지 않더라도 
		r-value를 수정하려고 했기때문에 오류가 납니다.
		그러므로 const return값은 레퍼런스 리턴이 아닌 이상 전혀 쓸때가 없습니다.

		end_reverse()의 반환값은 rvalue로써 복사해서 사용만 해야지 변경하면 안된다. 따라서 반환값이 const로 지정하지 않아도 변경불가이다.
		!= 연산자 재정의에서 rvalue를 참조로 받는다면 함수의 반환값을 참조로 받기 때문에 변경이 가능해진다. 
		따라서 이 경우에 != 연산자 재정의에서 const 키워드를 붙여서 변경하지 않겠다고 선언하거나 const가 아닌 변수에 담아서(반환값을 복사해서)
		!= 연산을 해야한다.

		Lvalue, Rvalue
		참고 : https://effort4137.tistory.com/entry/Lvalue-Rvalue
		설명 : 
		Lvalue는 표현식이 끝나도 값이 유지되는 변수등을 나타내고 Rvalue는 표현식이 끝나면 사라지는 상수 및 함수, 연산자의 반환값을 나타낸다.
		int x = 3;			// x: lvalue, 3: rvalue
		const int y = x;	// y: lvalue, x: lvalue
		int z = x + y;		// z: lvalue, x + y: rvalue;
		int *p = &x;		// p: lvalue, &x: rvalue
		cout << string("a");// string("a"): rvalue
		++x;				// ++x: lvalue // 증가된 자신을 리턴
		x++;				// x++: rvalue // 증가되지 않은 복사복을 리턴
	*/
	//for (TDRIterator<T> iter = begin_reverse(); iter != end_reverse(); ++iter)
	for (TDRList<T>::Iterator iter = begin_reverse(); iter != end_reverse(); ++iter)
	{
		cout << (*iter) << endl;
	}
}