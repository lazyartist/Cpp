#include <iostream>

using namespace std;

void _0705_function_exercise() {
	cout << "====== 문제1 =====" << endl;
	{
		/*
		다음 Equal 클래스의 객체가 cmp일 때 두 정수가 같으면 true, 아니면 false를
		반환하는 Equal 클래스를 작성하세요.
		*/
		struct Equal {
			bool operator()(int l, int r) {
				return l == r;
			}
		};

		Equal equal;
		if (equal(10, 10)) {
			cout << "equal" << endl; // equal
		}
		else {
			cout << "difference" << endl;
		}
	}

	cout << "====== 문제2 =====" << endl;
	{
		/*
		다음 Adder 클래스의 객체가 add일 때 두 정수의 합을 반환하는 Adder 클래스를 작성하세요.
		*/
		struct Adder {
			int operator()(int l, int r) {
				return l + r;
			}
		};

		Adder add;
		cout << add(10, 10) << endl; // 20
	}
}