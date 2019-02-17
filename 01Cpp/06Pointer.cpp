#include <iostream>
#include <tchar.h>


using namespace std;

int main() {
	// x86과 x64에서 포인터의 크기 차이, 빌드 시 플랫폼을 변경하면 확인할 수 있다.
	cout << "----- 포인터 변수의 크기 -----" << endl;
	cout << sizeof(int) << endl;
	cout << sizeof(int*) << endl;
	cout << sizeof(double) << endl;
	cout << sizeof(double*) << endl;

	// 포인터와 배열의 관계 : 배열명은 포인터다.

	cout << "----- 배열과 포인터 -----" << endl;
	// 문자열을 포인터에 저장하면 내부적으로 const로 저장후 그 주소값을 저장한다.
	const char *pText1 = "배열은 포인터다";
	//(*pText1) = 'a';  // 에러, const형식의 데이터를 바꿀 수 없다.
	cout << pText1 << endl; // pText1의 내용을 출력한다.
	cout << (int*)pText1 << endl; // 메모리 주소를 출력하기 위해 (int*)로 형변환한다.
	cout << &pText1 << endl;
	cout << "-----" << endl;

	// 문자열을 배열에 저장하면 각각의 문자가 배열의 요소로 저장되기 때문에 추후 변경이 가능해진다.
	char pText2[32] = "한글"; // 멀티바이트 문자열
	(*pText2) = 'b';
	// "한글"은 멀티바이트로 저장되기 때문에 첫번째 주소에 'b'만 저장하면
	// 2바이트로 이루어지는 "한" 문자가 깨지고 다음 문자도 제대로 읽을 수 없게 된다.
	cout << pText2 << endl; 
	cout << "-----" << endl;

	// 한글 유니코드를 wcout으로 출력하기 위한 설정 코드.
	// wcin 사용시 다음 추가 : std::wcin.imbue( std::locale( "kor" ) );
	std::wcout.imbue(std::locale("kor"));

	const wchar_t *pText3 = L"가나ab"; // 유니코드 문자열, 앞에 L(Long)을 붙인다.
	cout << pText3 << endl; // cout이 wchar_t에 대응하지 않기 때문에 메모리 주소가 출력된다.
	wcout << pText3 << endl; // "ab가나" 정상 출력된다.
	wcout << *pText3 << endl; // 포인터의 값을 출력하기 때문에 "가나ab"에서 첫번째인 "가"가 출력된다.
	wcout << &pText3 << endl; // 00,6FF,DE4 이런 값이 출력되는데 무슨 뜻인지 모르겠다.
	cout << "-----" << endl;

	// void : 타입이 없다. void의 포인터타입을 활용할 수 있다.
	// void* 변수를 선언하게 되면 이 변수는 어떤 타입의 메모리 주소든 모두 저장가능하다.
	// 단, 역참조가 불가능하고 메모리 주소만 저장 가능한다.
	wchar_t pText4[32] = L"a한글"; 
	void *pVoid = (void *)pText4; // void  변수에 메모리 값을 넣는다.
	wchar_t *pText5 = (wchar_t *)(pVoid); // pVoid 변수를 원래 타입으로 형변환해 변수에 할당한다.

	wcout << pText4 << endl; // "한글"
	wcout << pVoid << endl; // 00,BEF,CDC 이런 값이 출력된다.
	wcout << pText5 << endl; // "a한글"
	pText5[0] = L'bb'; // 'b', L'bb' : "b한글" 출력, 'bb' error 다음 라인이 출력안된다. 왜 에러가 나는지는 모르겠다.
	wcout << pText5 << endl; // "b한글"
	pText5[1] = L'c';
	wcout << pText5 << endl; // "bc글", wchar_t는 2바이트이고 L'c'도 2바이트이기 때문에 'c'가 '한'을 제대로 대체했다.
	pText5[2] = L'd';
	wcout << pText5 << endl; // "bcd"

	/*
	유니코드 : 모든 문자를 2byte로 저장, wcslen 등의 함수를 사용, 리터럴 문자열은 앞에 L을 붙여서 사용, 출력 시 wcout 사용
	멀티바이트 : ASCII는 1byte, 한글등은 2byte로 저장 strlen 등의 함수를 사용, 리터럴 문자는 ""로 사용, 출력 시 cout 사용
	TCHAR : 환경 설정에 따라 유니코드와 멀티바이트를 변환해서 컴파일 시켜주는 형식, 리터럴 문자는 TEXT("")로 사용한다. _tcslen 등의 함수를 사용.
	*/

	// 이중포인터 : 포인터 변수의 포인터, 즉 포인터 변수의 주소를 갖는 변수이다.
	cout << "----- 이중포인터 -----" << endl;
	int v = 9;
	int *pv = &v;
	int **ppv = &pv;
	cout << "v: " << v << ", pv: " << pv << ", &pv" << &pv << ", ppv: " << ppv << ", &ppv: " << &ppv << endl;
	cout << "v: " << v << ", *pv: " << *pv << ", *ppv: " << *ppv << ", **ppv: " << **ppv << endl;
	// pv는 v의 주소값을 갖고 ppv는 pv의 주소를 갖는다.
	// *pv는 v의 값을 가리키고 **ppv는 pv의 값(주소)의 값을 가리키므로 v의 값을 가리킨다.


	return 0;
}