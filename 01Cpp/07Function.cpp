#include <iostream>

using namespace std;

int main() {

	int a = 10;
	int &b = a;
	b = 5;
	int *c = &b;

	cout << a << ", " << b << ", " << *c;

	// call by value: 함수 인자를 값을 복사하여 전달, fn(int a)
	// call by address: 함수 인자를 변수의 주소(포인터)로 전달, fn(int *a)
	// call by reference: 함수의 인자를 레퍼런스를 이용하여 전달, fn(int &a)

	return 0;
}