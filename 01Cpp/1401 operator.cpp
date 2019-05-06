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

연산자
	오버로딩 가능한 단항 연산자: !, &, ~, *, +, -, ++, -- 등
	오버로딩 가능한 이항 연산자: +, -, *, /, ==, !=, <, <= 등
	https://en.wikipedia.org/wiki/Operators_in_C_and_C%2B%2B

멤버 함수를 이용한 연산자 오버로딩을 할 수 없는 경우
	연산자 왼쪽에 오는 피연산자를 this로 해서 연산자가 호출되는데 
	왼쪽에 다른 객체가 오면 연산자를 호출할 수 없다.(물론 왼쪽의 다른 객체가 연산자를 정의했다면 가능)
	따라서 이럴때는 '전역 함수 연산자 오버로딩'을 이용한다.

복사 생성자
	객체 초기화 시 주어진 객체를 복사하게 하는 생성자
	오버로딩 하지 않으면 얕은 복사를 하는 복사 생성자를 컴파일러가 자동으로 만든다.

복사 생성자가 호출되는 시점
	1. 기존에 생성된 객체를 이용하여 새로운 객체를 초기화하는 경우 
	2. call-by-value 방식으로 함수에 인자를 전달하는 경우
	3. 값 방식으로 객체를 반환하는 경우
*/

typedef struct _tagPoint {
	int x;

	// constructor
	_tagPoint() :x(0) {
		cout << "const " << x << endl;
	}

	// Initializer
	_tagPoint(int x) :x(x) {
		cout << "init const " << x << endl;
	}

	// 복사 생성자
	_tagPoint(const _tagPoint& pt) { 
		cout << "copy const " << pt.x << endl;
		// this는 자기자신의 포인터이고 *을 붙여서 자기자신을 역참조하여 모든 데이터를 복사하게 한다. 얕은 복사이다.
		*this = pt;

		// 이동 생성자를 정의하니 
		// "_tagPoint operator=(const _tagPoint& pt) (암시적으로 선언된)을 참조할 수 없습니다. 삭제된 함수입니다" 에러가 뜬다.
		// 결국 선언해서 해결. 왜그럴까?
	}

	// 이동 생성자
	_tagPoint(_tagPoint&& pt) {
		cout << "move const " << pt.x << endl;
		x = pt.x;
		// this는 자기자신의 포인터이고 *을 붙여서 자기자신을 역참조하여 모든 데이터를 복사하게 한다. 얕은 복사이다.
		//*this = pt;
	}

	_tagPoint& operator=(const _tagPoint& pt){
		cout << "operator=&" << endl;
		//*this = pt; // 함수 정의에서 함수를 호출하므로 stack overflow 난다. 
		this->x = pt.x;
		return *this;
	}

	// 호출되는 곳이 없다. 있었던거 같은데...
	_tagPoint& operator=(const _tagPoint&& pt) {
		cout << "operator=&&" << endl;
		this->x = pt.x;

		return *this;
	}

	~_tagPoint() {
		cout << "destr " << x << endl;
	}

	// + 연산자 재정의
	_tagPoint operator +(const _tagPoint& ptr) {
		cout << "operator+ _tagPoint" << endl;

		//_tagPoint result = _tagPoint(this->x + ptr.x);
		//return result;
		/*
		init const // 임시객체가 생성되고 result 변수의 값으로 바로 할당된다.
		move const // 리턴 시 새로운 임시 객체가 생성되며 이동 생성자가 호출된다.
		destr // 함수 내 임시객체 삭제
		destr // 반환된 임시객체 삭제
		*/

		return _tagPoint(this->x + ptr.x);
		/*
		init const // 임시객체가 생성되고 반환 객체로 바로 할당된다.
		destr 3 // 반환된 임시객체 삭제
		*/
	}

	// + 연산자 오버로딩
	_tagPoint operator+(int i) {
		cout << "operator+ int" << endl;

		// 이렇게 하면 임시객체가 생성되고(초기화 생성자 호출) 리턴시 임시객체가 또 생성된다.(이동 생성자 호출)
		//_tagPoint result = _tagPoint(this->x + i);
		
		// 이렇게 하면 임시객체가 생성되고 바로 반환객체로 되기 때문에 반환용 임시객체를 생성하지 않는다. 디버깅에는 불리할 수 있다.
		return _tagPoint(this->x + i);
	}

	// << 연산자 재정의
	void operator<<(const _tagPoint& pt) {
		cout << "operator<<" << endl;
		this->x = pt.x;
	}

	// >> 연산자 재정의
	void operator>>(_tagPoint& pt) {
		cout << "operator>>" << endl;
		pt.x = this->x;
	}

	// 클래스 외부에서 정의할 연산자 선언
	// 클래스 내부에서 선언해주지 않으면 외부에서 정의할 수 없다.
		// IDE(Integrated Development Environment)에서 "operator +=에 대한 함수 정의가 없습니다." 경고 뜨는 경우는 
		// 다음과 같이 스코프 지정을 Point 등의 별칭으로 해서 그렇다. void Point::operator += (int i) 
	void operator+= (_tagPoint&);
	void operator+= (int);

	// ++p 연산
	// 참조값을 반환하는 이유 : ++(++p)와 같이 현재 객체가 연속적으로 연산되게 하기 위함이다.
	// 참조값을 반환하지 않으면 객체의 복사본이 반환되기 때문에 바깥쪽 ++연산의 객체와 안쪽 ++연산객체인 p와 다른 객체가 된다.
	// 만약 참조대신 포인터를 반환하면 ++(*(++pt3));와 같이 써야해서 불편하다.
	_tagPoint& operator++ () {
		cout << "operator++" << endl;
		this->x += 1;

		// 리턴값이 참조이기 때문에 역참조값을 반환한다.
		return *this;
	}

	// p++ 연산
	// 복사 객체를 반환하는 이유 : 현재 코드에서 증가된 값이 아닌 이전 값을 사용하기 때문에 복사된 이전값을 반환한다. 그렇다고 _tagPoint&를 반환하면 반환 즉시 사라지는 객체기 때문에 안된다. 따라서 _tagPoint를 반환한다.
	// int dummy는 p++ 꼴로 작동하게 하는 역할만 한다.
	// 후위 증가 연산자의 반환형은 이전 값을 가진 임시 객체로 이 객체를 사용해서 ++연산을 다시하는 것은 의미가 없으므로 const를 붙여서 막아야한다. 여기서는 테스트를 위해 const를 붙이지 않았다.
		//const _tagPoint operator++ (int dummy)
		// 반환하는 객체의 타입이 const일 뿐 반환 객체를 받는 변수의 타입이 const가 아니라면 받은 변수의 값을 바꾸는 것은 가능하다.
	_tagPoint operator++ (int dummy) { // dummy는 int 타입이어야한다. 17TemplateDoubleLinkedList에서 다른 타입 사용해보니 에러남.
		cout << "operator++ dummy" << endl;

		Point temp(x); // 증가 연산 이전의 값을 복사
		//Point temp = *this; // 이렇게 하면 복사 생성자가 호출

		// 증가연산
		this->x += 1;

		// temp는 지역변수이기 때문에 참조로 반환하지 않는다.
		return temp; // 증가 연산이전의 값을 반환
	}

	// 외부에서 전역 함수로 연산자 오버로딩할 연산자
	// 선언하지 않아도 외부에서 전역함수로 연산자 재정의를 할 수 있지만 (선언하지 않으면 멤버 함수 연산자 재정의는 안된다)
	// 연산자 함수 내부에서 private 멤버에 접근하려면 friend 선언을 해줘야한다.
	friend _tagPoint& operator--(_tagPoint&);
	//_tagPoint& operator--(_tagPoint& p); // 외부 전역 함수로 정의 시 friend 키워드 없이 하면 "operator--에 대한 함수정의가 없습니다." 에러난다.

	private :
		int y;
} Point, *PPoint;

// 클래스 멤버 연산자 오버로딩, 연산자 재정의를 클래스 블럭 외부에서 한다.
// 연산자 이름 앞에 범위지정 연산자를 쓰는 것 말고는 동일한다.
// 클래스 타입을 아래처럼 별칭으로하면 함수의 정의를 찾을 수 없다고 뜬다. 컴파일에는 문제 없다.
	//void Point::operator+= (_tagPoint& other) {
void _tagPoint::operator+= (_tagPoint& other) {
	cout << "operator+= _tagPoint&" << endl;
	this->x += other.x;
}

void _tagPoint::operator+= (int i) {
	cout << "operator+= int" << endl;
	this->x += i;
}

// ===== 전역함수로 단항 연산자 재정의 s ===== 
// 전역함수로 연산자 재정의는 this를 찾을 수 없기 때문에 단항 연산자라도 대상 객체를 받아야한다.
// 호출 형식 : --(Point)
_tagPoint& operator-- (_tagPoint& p) {
	cout << "operator-- front global" << endl;
	p.x--;
	//p.y = 0; // 이 함수는 클래스 내부에서 friend 선언했으므로 private 멤버에 접근할 수 있다.

	return p;
}

// 호출 형식 : (Point)--
// int dummy는 후위연산자임을 나타내는 더미 인자
// 원래는 반환값이 const를 붙여서 반환되는 임시객체 자체를 사용할 수 없게 해야한다. 이렇게 막아도 임시객체를 바로 사용하는 것이 아닌 const 아닌 변수에 담아서 사용은 가능하다.
_tagPoint operator-- (_tagPoint& p, int dummy) {
	cout << "operator-- back global" << endl;
	_tagPoint tmp = p;
	p.x--;

	//p.y = 0; // 이 함수는 클래스 내부에서 friend 선언하지 않았으므로 private 멤버에 접근할 수 없다.

	return tmp;
}

// 굳이 (_tagPoint--)-- 를 쓰기 위한 코드
// 임시 객체를 반환하고 그 반환된 임시객체가 매개변수가 되기 때문에 우측값 레퍼런스를 받는 함수를 정의해야한다.
// 연산자 재정의를 멤버 함수로 했다면 반환되는 값이 연산자 함수 호출 시 this가 되어 rvalue가 아니지만
	// 전역 함수로 재정의 시 반환된 임시객체는 전역 함수의 인자가 되어 rvalue를 받는 함수가 있어야한다.
	// 어렵다.
// 이렇게 꼬을 수도 있다는 것만 알아두고 이렇게 사용하면 안된다.
_tagPoint operator-- (_tagPoint&& p, int dummy) {
	cout << "operator-- back && global" << endl;
	_tagPoint tmp = p;
	p.x--;

	//p.y = 0; // 이 함수는 클래스 내부에서 friend 선언하지 않았으므로 private 멤버에 접근할 수 없다.

	return tmp;
}
// ===== 전역함수로 단항 연산자 재정의 e ===== 


// ===== 전역함수로 이항 연산자 재정의 s ===== 
// 호출 형식 :Point - Point
Point operator- (Point& lp, Point& rp) {
	cout << "operator- global" << endl;

	// 이렇게 하면 초기화 생성자, 이동 생성자 호출
	//Point result(lp.x - rp.x);
	//return result;

	// 이렇게 하면 초기화 생성자만 호출 됨. 반환값에 직접 할당되기 때문
	return Point(lp.x - rp.x);
}
// ===== 전역함수로 이항 연산자 재정의 e ===== 


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

		/*
		참조 반환 시 참조로 받으면 외부에서 내부 멤버를 변경할 수 있고
		참조 반환 시 일반 변수로 받으면 값이 복사되므로 내부 멤버와 상관없어진다.
		*/
	}
};
// ===== [] 배열 접근 연산자 재정의 e ===== 

//int main() {
void _1401_operator() {
	cout << "===== default const =====" << endl;
	Point p1; // const 0
	p1.x = 1;

	cout << "===== init const =====" << endl;
	Point p2(2); // const 0

	cout << "===== copy const =====" << endl;
	{
		Point p = p1;
		/*
		copy const0
		operator=&
		destr
		*/
	}

	cout << "===== move const =====" << endl;
	{
		Point p = Point();
		/*
		const 0 // 컴파일러 최적화로 생성된 객체를 바로 변수의 값으로 만들기 때문에 일반 생성자가 한번만 호출된다.
		destr

		rvalue를 만드려면 함수의 반환값이 유일한가?
		*/
	}

	cout << "===== operator+ _tagPoint =====" << endl;
	p1 + p2;
	/*
	operator+ _tagPoint // operator+ 함수 호출
	init const 3 // operator+ 함수 내부에서 새로운 임시객체 생성
	destr 3 // 반환된 임시객체 제거
	*/

	cout << "===== operator+ _tagPoint, operator= =====" << endl;
	{
		Point pt3 = p1 + p2;
		cout << "end " << endl;
		/*
		operator+ _tagPoint // operator+ 함수 호출
		init const 3 // operator+ 함수 내부에서 새로운 임시객체 생성
		// 반환된 임시객체가 pt3 변수에 바로 할당(컴파일러 최적화)
		end // destr 3이 찍히기 전에 이게 찍혔다는건 반환되고 곧 바로 제거된게 아니라는 뜻
		destr 3 // 코드블럭 나가며 제거
		*/
	}

	cout << "===== operator+ int, operator= =====" << endl;
	{
		Point pt3 = p1 + 10;
		cout << "end " << endl;
		/*
		operator+ int // operator+ int 연산자 호출
		init const 11 // 내부에서 10을 더한 임시객체 생성, 반환되며 pt3에 바로 할당
		end // 반환 임시객체가 바로 삭제되지 않았음
		destr 11 // 코드블록 나가며 제거
		*/
	}

	cout << "===== operator+= _tagPoint =====" << endl;
	{
		Point p;
		p += p1;
		cout << "end " << endl;
		/*
		const 0 // 변수 p 생성
		operator+= _tagPoint& // operator+= 호출
		end
		destr 1 // 코드블록 나가며 제거
		*/
	}

	cout << "===== operator+= int =====" << endl;
	{
		Point p;
		p += 10;
		cout << "end " << endl;
		/*
		const 0 // 변수 p 생성
		operator+= int // operator+= 호출
		end
		destr 10 // 코드블록 나가며 제거
		*/
	}

	cout << "===== operator<< =====" << endl;
	{
		Point p1(1);
		Point p2(2);
		p1 << p2;
		cout << p1.x << ", " << p2.x << endl;
		/*
		init const 1 // 변수 p1 생성
		init const 2 // 변수 p2 생성
		operator<< // operator<< 호출
		2, 2 // p1의 값 변경됨
		destr 2 // 코드블록 나가며 제거
		destr 2 // 코드블록 나가며 제거
		*/
	}

	cout << "===== operator>> =====" << endl;
	{
		Point p1(1);
		Point p2(2);
		p1 >> p2;
		cout << p1.x << ", " << p2.x << endl;
		/*
		init const 1 // 변수 p1 생성
		init const 2 // 변수 p2 생성
		operator>> // operator>> 호출
		1, 1 // p2의 값 변경됨
		destr 1 // 코드블록 나가며 제거
		destr 1 // 코드블록 나가며 제거
		*/
	}

	cout << "===== operator++ front =====" << endl;
	{
		Point p;
		++p;
		/*
		const 0 // p변수 생성
		operator++ // operator++ 함수 호출
		*/
	}

	cout << "===== operator++ back =====" << endl;
	{
		Point p;
		p++;
		cout << p.x << endl;
		/*
		const 0 // p변수 생성
		operator++ dummy // operator++ dummy 함수 호출
		init const 0 // 이전값을 복사하며 임시객체 생성
		move const 0 // 반환 임시객체를 생성하며 인자값으로 함수내에서 생성된 임시객체를 전달. 곧 사라질 rvalue값이므로 반환 임시객체의 이동 생성자 호출.
		destr 0 // 함수내에서 생성된 임시객체 제거
		destr 0 // 함수에서 반환된 임시객체 제거, 만약 Point pp = p++;이렇게 변수로 받았다면 바로 제거되지 않음.
		1 // p의 값 1로 증가
		*/
	}

	cout << "===== operator++ front nest =====" << endl;
	{
		Point p;
		++(++p);
		/*
		operator++ // operator++ 함수 호출
		operator++ // operator++ 함수 호출
		destr 3 // 코드블록 나가며 제거
		*/
	}

	cout << "===== operator++ back nest =====" << endl;
	{
		Point p;
		(p++)++; // 테스트를 위한 것일 뿐, 반환된 임시 객체를 변경하는 것은 무의미하기 때문에 후위 연산자를 연속해서 쓰면 안된다. 
		cout << p.x << endl;
		/*
		const 0 // p변수 생성
		operator++ dummy // operator++ dummy 함수 호출
		init const 0 // 이전값을 복사하며 임시객체 생성
		move const 0 // 반환 임시객체를 생성하며 인자값으로 함수내에서 생성된 임시객체를 전달. 곧 사라질 rvalue값이므로 반환 임시객체의 이동 생성자 호출.
		destr 0 // 첫번째 호출된 함수내에서 생성된 임시객체 제거
		operator++ dummy // 반환된 임시객체를 대상으로(인자는 아니다) operator++ dummy 함수 호출
		init const 0 // 이전값을 복사하며 임시객체 생성
		move const 0 // 반환 임시객체를 생성하며 인자값으로 함수내에서 생성된 임시객체를 전달. 곧 사라질 rvalue값이므로 반환 임시객체의 이동 생성자 호출.
		destr 0 // 두번째 호출된 함수내에서 생성된 임시객체 제거
		destr 0 // 두번째 호출된 함수의 반환 임시객체 제거
		destr 1 // 첫번째 호출된 함수의 반환 임시객체 제거, 두번재 operator++ dummy 함수가 호출되며 이 객체의 x값이 1로 증가됨.
		1
		destr 1 // 코드블록 나가며 p변수 제거
		*/
	}

	cout << "===== operator-- front =====" << endl;
	{
		Point p;
		--p;
		cout << p.x << endl;
		/*
		const 0 // p변수 생성
		operator-- f global // 전역으로 정의된 operator-- 함수 호출
		-1 
		destr -1 // 코드블록 나가며 p변수 제거
		*/
	}

	cout << "===== operator-- back =====" << endl;
	{
		Point p;
		p--;
		cout << p.x << endl;
		/*
		const 0 // p변수 생성
		operator-- b global // 전역으로 정의된 operator-- 함수 호출
		copy const 0 // 현재 값 반환을 위한 함수 내 임시객체를 생성하며 복사 생성자 호출
		operator=& // 복사 생성자 내에서 operator= 호출
		move const 0 // 함수의 반환 임시객체가 생성되며 이동 생성자 호출
		destr 0 // 함수 내 임시객체 소멸
		destr 0 // 함수의 반환 임시객체 소멸
		-1 
		destr -1 // 코드블록 나가며 p변수 제거
		*/
	}

	cout << "===== operator-- front nest =====" << endl;
	{
		Point p;
		--(--p);
		cout << p.x << endl;
		/*
		const 0 // p변수 생성
		operator-- f global // 전역으로 정의된 operator-- 함수 호출
		operator-- f global // 전역으로 정의된 operator-- 함수 호출
		-2
		destr -2 // 코드블록 나가며 p변수 제거
		*/
	}

	cout << "===== operator-- back nest =====" << endl;
	{
		Point p;
		(p--)--;
		cout << p.x << endl;
		/*
		const 0 // p변수 생성
		operator-- back global  // p변수를 전역으로 정의된 _tagPoint operator-- (_tagPoint& p, int dummy) 함수의 인자로 전달하며 호출
		copy const 0 // 이전 객체 값을 반환하기 위해 임시객체를 생성하며 복사 생성자 호출
		operator=& // 복사 생성자 내부에서 operator= 호출
		move const 0 // 함수의 반환값을 위한 객체 생성 시 이동 생성자 호출
		destr 0 // 함수 내 임시객체 소멸
		operator-- back && global // 반환된 객체를 전역으로 정의된 _tagPoint operator-- (_tagPoint&& p, int dummy) 함수의 인자로 전달하며 호출
		copy const 0 // 이전 객체 값을 반환하기 위해 임시객체를 생성하며 복사 생성자 호출
		operator=& // 복사 생성자 내부에서 operator= 호출
		move const 0 // 함수의 반환값을 위한 객체 생성 시 이동 생성자 호출
		destr 0 // 함수 내 임시객체 소멸
		destr 0 // 반환된 임시객체 소멸
		destr -1 // 처음 반환된 임시객체 소멸
		-1
		destr -1 // 코드블록을 나가며 p변수 제거
		*/
	}

	cout << "===== operator- =====" << endl;
	{
		Point p1(1);
		Point p2(2);
		Point p3 = p1 - p2;
		cout << p3.x << endl;
		/*
		init const 1 // p1 변수 생성
		init const 2 // p2 변수 생성
		operator- global // 전역 연산자 재정의 함수 operator- 호출
		init const -1 // 임시객체 생성(바로 리턴하도록해서 반환 객체로 직접 할당)
		-1 // 반환값이 p3 변수에 직접 할당
		destr -1 // 코드블록을 나가며 변수 p3 제거
		destr 2 // 코드블록을 나가며 변수 p2 제거
		destr 1 // 코드블록을 나가며 변수 p1 제거
		// 생성 순서 반대로 제거되나?
		*/
	}

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

		//int& b = ctnr1[0]; // const 객체이므로 const int* operator()(const int& idx) const 함수가 호출되어 반환값이 const int& 이므로 비 const 변수로 받을 수 없다.
		//int* b = ctnr1(0); // const 객체이므로 const int* operator()(const int& idx) const 함수가 호출되어 반환값이 const int* 이므로 비 const 포인터 변수로 받을 수 없다.

		cout << "-----" << endl;

		Container ctnr2;

		int& a = ctnr2[0]; // 비 const 객체이므로 int& operator[](const int& idx)가 호출되어 외부에서 참조 변수로 받은 뒤 변경 가능하다.
		a = 11;
		cout << ctnr2[0] << endl; // 11

		cout << ctnr2[1] << endl; // 2
		ctnr2[1] = 9; // 비 const 객체이므로 값수정 가능, int& operator[](const int& idx) 함수 호출
		cout << ctnr2[1] << endl; // 9
	}

	cout << "복사 생성자와 대입 연산자 호출 시점" << endl;
	{
		class A {
		public:
			A() {
				cout << "A() " << this << endl;
			}

			A(A& a) {
				cout << "A(A) " << this << endl;
				this->i = a.i;
			}

			A(int i) {
				cout << "A(int) " << this << endl;
				this->i = i;
			}

			~A() {
				cout << "~A " << this << endl;
			}
			void print() {
				cout << this << ", " << i << endl;
			}

			void operator=(const A& a) {
				cout << "A operator=" << endl;
				this->i = a.i;
			}
			int i = 0;
		};

		/*
		복사 생성자 호출 1. : 기존에 생성된 객체를 이용하여 새로운 객체를 초기화하는 경우 
			복사 생성자에 explicit 지정하면 암시적 호출이 안되므로 복사 생성자를 찾지 못해서 컴파일 에러남.
			todo 함수 인자, 리턴에도 어떤 결과가 나오는지 확인요.
		*/
		{
			/*
			객체를 초기화할 때 기존 객체를 대입하면 복사 생성자 호출
			*/
			A a(1); // A(int) 0116F81C : 생성자 호출
			A b = a; // A(A) 0116F810 : 복사 생성자 호출
			//A b(a); // A(A) : 복사 생성자 호출

			/*
			초기화가 끝난 객체에 대입하면 operator= 연산자 호출
			*/
			a = b; // A operator=
			//a = A(2); // A operator=
		}

		/*
		복사 생성자 호출 2. : call-by-value 방식으로 함수에 인자를 전달하는 경우
		*/

		/*
		복사 생성자 호출 3. : 참조가 아닌 방식(포인터도 아닌 일반 타입)으로 객체를 반환하는 경우
		*/
	}
}
