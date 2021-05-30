#pragma once
#include <iostream>

using namespace std;

template<typename T>
class TDNode {
	/*
	생성자와 소멸자를 private하게 되면 외부에서 객체를 생성하고 객체를 해제할 수 없다.
	생성자는 객체를 생성할 때 자동으로 호출이 되는 함수인데 private으로 되면 
	객체를 생성하면서 호출시 접근이 불가능하다.
	*/
private:
	TDNode() :m_pPrev(NULL), m_pNext(NULL) {}
	~TDNode(){}

	/*
	friend : 친구로 만들어준다.
	friend로 지정해준 클래스에서 이 클래스의 private이나 protected에 접근이 가능해진다.
	일반 클래스는 friend 라인만 적으면 되지만 template 클래스는 아래처럼 template을 지정해야한다.
	*/
	template<typename T>
	friend class TDList;

	template<typename T>
	friend class TDListIterator;

private:
	T m_Data;
	TDNode<T>* m_pPrev;
	TDNode<T>* m_pNext;
};

template<typename T>
class TDListIterator {
public:
	TDListIterator(){}
	~TDListIterator(){}

	typedef TDNode<T> Node;
	typedef TDNode<T>* PNode;

public:
	PNode m_pNode;

	TDListIterator<T>& operator++() {
		m_pNode = m_pNode->m_pNext;

		return *this;
	}

	//TDListIterator<T> operator++ (PNode dummy) {
	TDListIterator<T> operator++ (int dummy) { // dummy 타입은 int 이어야 한다. 안그러면 에러남.
		TDListIterator<T> iter;
		iter.m_pNode = m_pNode;

		m_pNode = m_pNode->m_pNext;

		return iter;
	}
	

	bool operator == (PNode node) {
		return m_pNode == node;
	}

	bool operator != (TDListIterator<T> node) {
		return m_pNode != node.m_pNode;
	}

	T operator * () {
		return m_pNode->m_Data;
	}
};

template<typename T>
class TDList
{
public:
	TDList();
	~TDList();

private:
	typedef TDNode<T> Node;
	typedef TDNode<T>* PNode;

public:
	typedef TDListIterator<T> Iterator;

private:
	PNode m_pBegin;
	PNode m_pEnd;
	size_t m_iSize;

public:
	/*
	레퍼런스는 참조 대상의 값을 변경할수 있지만 const를 붙여주면 변경할 수 없다.
	*/
	void push_back(const T& data);
	void push_front(const T& data);
	void print();

	/*
	멤버함수 뒤에 const를 붙여주면 이 함수 내에서 멤버변수의 값을 변경할 수 없다.
	*/
	unsigned int size() const;
	bool empty() const;
	void clear();
	Iterator begin();
	Iterator end();
};

// 클래스 템플릿 생성자/함수를 외부에 정의할 때는 TDList::TDList() 이렇게만 쓰면 안되고
// 아래처럼 template 인수정의와 TDList<T>를 써줘야한다.
template<typename T>
TDList<T>::TDList()
{
	m_pBegin = new Node;
	m_pEnd = new Node;

	m_pBegin->m_pNext = m_pEnd;
	m_pEnd->m_pPrev = m_pBegin;

	m_iSize = 0;
}

template<typename T>
TDList<T>::~TDList()
{
	clear();
	delete m_pBegin;
	delete m_pEnd;
	m_iSize = 0;
}

template<typename T>
inline void TDList<T>::push_back(const T & data)
{
	PNode pNode = new Node;
	pNode->m_Data = data;

	PNode pPrev = m_pEnd->m_pPrev;
	pPrev->m_pNext = pNode;

	pNode->m_pPrev = pPrev;
	pNode->m_pNext = m_pEnd;

	m_pEnd->m_pPrev = pNode;

	++m_iSize;
}

template<typename T>
inline void TDList<T>::push_front(const T & data)
{
	PNode pNode = new Node;
	pNode->m_Data = data;

	PNode pNext = m_pBegin->m_pNext;
	pNext->m_pPrev = pNode;

	pNode->m_pPrev = m_pBegin;
	pNode->m_pNext = pNext;

	m_pBegin->m_pNext = pNode;

	++m_iSize;
}

template<typename T>
inline void TDList<T>::print()
{
	cout << "print" << endl;
	Iterator iter = begin();
	while (iter.m_pNode != m_pEnd)
	{
		cout << iter.m_pNode->m_Data << endl;
		++iter;
	}
}

template<typename T>
inline unsigned int TDList<T>::size() const
{
	return m_iSize;
}

template<typename T>
inline bool TDList<T>::empty() const
{
	return m_iSize == 0;
}

template<typename T>
inline void TDList<T>::clear()
{
	PNode it = m_pBegin->m_pNext;
	while (it != m_pEnd)
	{
		it = it->m_pNext;
		delete it->m_pPrev;
	}

	m_pBegin->m_pNext = m_pEnd;
	m_pEnd->m_pPrev = m_pBegin;
	m_iSize = 0;
}

template<typename T>
//inline TDList<T>::Iterator TDList<T>::begin()// 클래스 내부에서 typedef한 Iterator를 사용 사용할 수 없다. 하지만 함수 내에서는 사용할 수 있다.
inline TDListIterator<T> TDList<T>::begin() 
{
	Iterator iter; // Iterator가 private으로 typedef 됐지만 함수 외부 정의에서도 사용할 수 있다.
	iter.m_pNode = m_pBegin->m_pNext;
	return iter;
}

template<typename T>
inline TDListIterator<T> TDList<T>::end()
{
	Iterator iter;
	iter.m_pNode = m_pEnd;
	return iter;
}
