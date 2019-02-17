#include <iostream>

using namespace std;

// 강의와 다음 블로그를 참고
// https://pacs.tistory.com/entry/C-%EC%97%B0%EC%82%B0%EC%9E%90-%EC%98%A4%EB%B2%84%EB%A1%9C%EB%94%A9-Operator-Overloading%EC%9D%98-%EB%91%90%EA%B0%80%EC%A7%80-%EB%B0%A9%EB%B2%95?category=367869
// https://pacs.tistory.com/entry/C-%EB%8B%A8%ED%95%AD-%EC%97%B0%EC%82%B0%EC%9E%90-%EC%98%A4%EB%B2%84%EB%A1%9C%EB%94%A9

/*
	연산자 오버로딩
	단항, 이항 연산자를 오버로딩할 수 있다.
	멤버 연산자, 전역 연산자 두 가지 방법으로 오버로딩 할 수 있다.
	사용하는데 차이는 없다.

	오버로딩 가능한 단항 연산자: !, &, ~, *, +, -, ++, -- 등
	오버로딩 가능한 이항 연산자: +, -, *, /, ==, !=, <, <= 등
	https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B

	멤버 함수를 이용한 연산자 오버로딩을 할 수 없는 경우
		연산자 왼쪽에 오는 피연산자를 this로 해서 연산자가 호출되는데 
		왼쪽에 다른 객체가 오면 연산자를 호출할 수 없다.(물론 왼쪽의 다른 객체가 연산자를 정의했다면 가능)
		따라서 이럴때는 '전역 함수 연산자 오버로딩'을 이용한다.


*/

typedef struct _tagPoint {
	int x;
	int y;
	// default constructor
	_tagPoint() :x(0), y(0) {}
	// Initializer
	_tagPoint(int x, int y) :x(x), y(y) {}
	// 앝은 복사 생성자
	_tagPoint(const _tagPoint& pt) { 
		// 얕은 복사. this는 자기자신의 포인터이고 *을 붙여서 자기자신을 역참조하여 모든 데이터를 복사하게 한다.
		*this = pt;
	}

	// 외부에서 멤버 연산자 오버로딩할 연산자
	void operator += (int i);

	// +연산자 재정의
	_tagPoint operator +(const _tagPoint& ptr) {
		_tagPoint result = _tagPoint(this->x + ptr.x, this->y + ptr.y);
		return result;
	}

	// +연산자 오버로딩
	_tagPoint operator +(int i) {
		_tagPoint result = _tagPoint(this->x + i, this->y + i);
		return result;
	}

	void operator <<(const _tagPoint& pt) {
		this->x = pt.x;
		this->y = pt.y;
	}

	void operator >>(_tagPoint& pt) {
		pt.x = this->x;
		pt.y = this->y;
	}

	// ++p 연산
	// 참조값을 반환하는 이유 : ++(++p)와 같이 현재 객체가 연속적으로 연산되게 하기 위함이다.
	// 참조값을 반환하지 않으면 객체의 복사본이 반환되기 때문에 바깥쪽 ++연산의 객체와 안쪽 ++연산객체인 p와 다른 객체가 된다.
	// 만약 참조대신 포인터를 반환하면 ++(*(++pt3));와 같이 써야해서 불편하다.
	_tagPoint& operator ++ () {
		this->x += 1;
		this->y += 1;

		// 리턴값이 참조이기 때문에 역참조값을 반환한다.
		return *this;
	}

	// p++ 연산
	// int dummy는 p++ 꼴로 작동하게 하는 역할만 한다.
	_tagPoint operator ++ (int dummy) { // dummy는 int 타입이어야한다. 17TemplateDoubleLinkedList에서 다른 타입 사용해보니 에러남.
		Point temp(x, y); // 증가 연산 이전의 값을 복사
		// 증가연산
		this->x += 1;
		this->y += 1;

		// temp는 지역변수이기 때문에 참조로 반환하지 않는다.
		return temp; // 증가 연산이전의 값을 반환
	}

	// 외부에서 전역 함수로 연산자 오버로딩할 연산자
	// 선언하지 않아도 외부에서 연산자 재정의를 할 수 있지만 
	// 연산자 함수 내부에서 private 멤버에 접근하려면 friend 선언을 해줘야한다.
	friend _tagPoint& operator--(_tagPoint& p);
} Point, *PPoint;

// 클래스 멤버 연산자 오버로딩, 연산자 재정의를 클래스 블럭 외부에서 한다.
// 연산지 이름 앞에 범위지정 연산자를 쓰는 것 말고는 동일한다.
// 아래처럼 typedef로 정의된 이름을 사용하니 IDE에서 함수의 정의를 찾을 수 없다고 뜬다. 컴파일에는 문제 없다.
//_tagPoint& _tagPoint::operator-- () {
void Point::operator += (int i) {
	this->x += i;
	this->y += i;
}

// ===== 전역함수로 연산자 재정의 s ===== 
// 전역함수로 연산자 재정의는 this를 찾을 수 없기 때문에 단항 연산자라도 대상 객체를 받아야한다.
// 호출 형식은 --(Point)
Point& operator-- (Point& p) {
	p.x--;
	p.y--;

	return p;
}

// 호출 형식은 -(Point, Point)
Point operator- (Point& lp, Point& rp) {
	Point result(lp.x - rp.x, lp.y - rp.y);
	return result;
}
// ===== 전역함수로 연산자 재정의 e ===== 

// ===== () 함수 호출 연산자 재정의(함수객체) s ===== 
/*
f(); 이 호출 문장은 다음과 같이 해석 가능
	1. f라는 이름의 함수를 호출
	2. f라는 이름의 함수 포인터 호출
	3. f라는 이름의 함수 객체의 ()연산자 호출
*/
class FO {
public:
	// () 연산자 오버로딩
	void operator()() {
		cout << "FO operator()" << endl;
	}

	void operator()(int i) {
		cout << "FO operator() " << i << endl;
	}
};
// ===== () 함수 호출 연산자 재정의(함수객체) e ===== 

// ===== [] 배열 접근 연산자 재정의 s ===== 
class Container {
public:
	//int is[]; // 배열 개수를 지정하지 않으면 배열 포인터를 갖는 변수로 생성이 됨. 컴파일 에러 안남.
	int is[2] = {1, 2}; // 개수를 넣지 않으면 "기본 멤버 이니셜라이저에서 배열 범위를 추론할 수 없습니다." 에러남.

	// const 지정한 함수에서 참조를 반환하면 참조로 인해 멤버변수의 값이 변경될 수 있기 때문에 컴파일 에러남
	// "int& 형식에서 const int 형식 이니셜라이저로의 바인딩 참조에서 한정자가 삭제되었습니다."
	// 따라서 반환값에 const를 붙여줘야함
	const int& operator[](const int& idx) const {
		return is[idx];
	}

	// const 지정한 함수에서 반환값으로 포인터를 반환하면 포인터에 의해 멤버변수의 값이 변경될 수 있기 때문에 컴파일 에러남
	// todo 이유는 참조와 같은데 에러 메시지가 다름? 아니면 이유도 다름?
	// "반환값 형식이 함수 형식과 일치하지 않습니다."
	const int* operator()(const int& idx) const {
		return &(is[idx]);

		// 다음과 같이 지역변수에 값을 복사한 후 지역변수의 포인터 반환은 가능함(지역변수는 멤버변수가 아니다.)
		// (물론 외부에서 이 값을 사용하려하면 메모리 해제됐기 때문에 정상 작동하진 않음)
		//auto a = is[idx];
		//return &a;
	}

	// cntr[0] = 9; 형식으로 값을 할당 받기 위해 비 const 함수도 정의해준다.
	int& operator[](const int& idx) {
		return is[idx];
	}
};
// ===== [] 배열 접근 연산자 재정의 e ===== 

//int main() {
void operator14() {

	Point pt1(1, 1), pt2(2, 2);
	// Point 구조체는 +연산자가 operator로 재정의 되어있기 때문에 +연산이 가능하게 되고 pt1의 연산자 함수 +를 호출하며 pt2를 넘겨준다.
	Point pt3 = pt1 + pt2;
	cout << pt3.x << ", " << pt3.y << endl;

	pt1 << pt2;
	cout << pt1.x << ", " << pt1.y << endl;

	pt3 >> pt2;
	cout << "pt2 : " << pt2.x << ", " << pt2.y << endl;

	pt3 = pt2 + 10;
	cout << pt3.x << ", " << pt3.y << endl;

	pt3 += 10;
	cout << pt3.x << ", " << pt3.y << endl;

	++pt3;
	cout << pt3.x << ", " << pt3.y << endl;

	pt3++;
	cout << pt3.x << ", " << pt3.y << endl;

	++(++pt3);
	cout << pt3.x << ", " << pt3.y << endl;

	--pt3;
	cout << "--pt3 : " << pt3.x << ", " << pt3.y << endl;

	Point pt4 = pt3 - pt2;
	cout << "pt4 = pt3 - pt2 : " << pt4.x << ", " << pt4.y << endl;

	cout << "End : " << pt3.x << ", " << pt3.y << endl;

	cout << "() 함수호출 연산자 재정의(함수객체)" << endl;
	{
		FO fo;
		fo(); // void operator()() 함수 호출, FO operator()
		fo(1); // void operator()(int i) 함수 호출, FO operator() 1

		fo(); // 객체 생성 후 호출(암시적)
		fo.operator()(); // 객체 생성 후 호출(명시적)
		FO()(); // 임시 객체 생성 후 호출(암시적)
		FO().operator()(); // 임시 객체 생성 후 호출(명시적)
	}

	cout << "[] 배열 접근 연산자 재정의" << endl;
	{
		const Container ctnr1;
		cout << ctnr1[0] << endl; // 1
		cout << ctnr1[1] << endl; // 2
		cout << ctnr1[2] << endl; // -858993460 쓰레기값
		//ctnr1[0] = 9; // const 객체이므로 값수정을 허용하지 않는다, const int* operator()(const int& idx) const 함수만 호출할 수 있다.

		cout << "-----" << endl;

		Container ctnr2;
		cout << ctnr2[0] << endl; // 1
		ctnr2[0] = 9; // 비 const 객체이므로 값수정 가능, int& operator[](const int& idx) 함수 호출
		cout << ctnr2[0] << endl; // 9
		
	}
}
