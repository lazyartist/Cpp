// #include : 헤더파일을 여기에 포함시키는 기능이다.
#include <iostream>
#include <time.h>

using namespace std;

enum NUM {
	num1
};

void lotto();
void baseball();
void printNumbers2(int *numbers, int size);

// 실행과정 : 컴파일 -> 빌드 -> 실행
// 컴파일 : 번역작업이다.
// Ctrl + Shift + B를 이용해서 빌드를 할 수 있다.

// C++의 시작점은 main함수이다. main함수는 반드시 있어야한다.
int main2() 
{
	// C++ 표준 기능의 대부분은 std라는 namespace 안에 존재하고 있다.
	// 이름이 겹치는 것을 방지해주기 위해서이다.
	// cout : 콘솔창에 출력해주는 기능이다. 뒤에 있는 "" 안에 있는 문자들을 화면에 출력해준다.
	// endl : 개행기능
	std::cout << "test" << std::endl;

	cout << "std namespace 사용" << endl;

	/*
	변수 : 변하는 수
	용량의 최소단위 : bit
	1byte = 8bit
	1kbyte = 1024byte
	1mbyte = 1024kbyte
	1gbyte = 1024mbyte
	1tbyte = 1024gbyte

	문자를 표현하는 방법 : ASCII 코드 표를 가지고 있다.
	true : 0이 아닌 모든 수, false : 0

	종류		|	용량		|	데이터	|	표현범위			|	unsigned	|
	char	|	1byte	|	문자		|	-128~127		|	0~255		|
	bool	|	1byte	|	참/거짓	|	true/false		|	true/false	|
	short	|	2byte	|	정수		|	-32768~32767	|	0~65535		|
	int		|	4byte	|	정수		|	약 -22억 ~ 21억	|	0~약 43억	|
	float	|	4byte	|	실수		|
	double	|	8byte	|	실수		|
	*/

	/* 숫자 리터럴 접미사 https://boycoding.tistory.com/155
	Data Type		Suffix										Meaning
	int				u or U										unsigned int
	int				l or L										long
	int				ul, uL, Ul, UL, lu, lU, Lu, or LU			unsigned long
	int				ll or LL									long long
	int				ull, uLL, Ull, ULL, llu, llU, LLu, or LLU	unsigned long long
	double			f or F										float
	double			l or L										long double
	*/

	// = : 대입연산자, 오른쪽의 값을 왼쪽에 대입한다.
	int number = 10;
	cout << number << endl;

	bool bTest = true;
	cout << bTest << endl;

	// 영문이나 숫자는 1byte를 차지한다. 하지만 한글이나 한문, 등의 문자들은 2byte를 차지하기 때문에 char 변수 하나에 저장하기가 힘들다.
	char cTest = 't';
	cout << cTest << endl;

	float fNumber = 3.14; // f 안붙이면 double형이된다.
	cout << fNumber << endl;

	double dNumber = 3.14; // f 안붙이면 double형이된다.
	cout << dNumber << endl;

	// 난수 테이블 발생
	srand((unsigned int)time(0));
	cout << "random number : " << rand() << endl;

	// 열거체 타입의 변수는 무조건 4byte를 차지하게 된나.
	// sizeof(타입 or 변수)를 하게 되면 해당 타입 혹은 변수의 메모리 크기를 구해준ㄷ.
	NUM eNum;
	cout << sizeof(NUM) << endl;

	// typeid(타입 or 변수).name()을 하게 되면 typeid안에 들어간 타입 혹은 변수의 타입을 문자열로 반환해준다.
	cout << typeid(eNum).name() << endl;

	//lotto();

	baseball();

	return 0;
}

void baseball() {
	cout << "=== baseball ===" << endl;

	// 배열 인덱스를 벗어났는데 뻗지를 않았다.

	// fill 1~9
	const int numberRange = 9;
	int numbers[numberRange];
	for (size_t i = 0; i < numberRange; i++)
	{
		numbers[i] = i+1;
	}

	// swap
	for (size_t i = 0; i < numberRange; i++)
	{
		int idx1 = rand() % numberRange;
		int idx2 = rand() % numberRange;
		int temp = numbers[idx1];
		numbers[idx1] = numbers[idx2];
		numbers[idx2] = temp;
	}

	// choice number 3
	const int numberCount = 3;
	int choseNumbers[numberCount];
	srand((unsigned int)time(0));
	for (size_t i = 0; i < numberCount; i++)
	{
		choseNumbers[i] = numbers[i];
	}

	printNumbers2(numbers, sizeof(numbers) / sizeof(int));
	printNumbers2(choseNumbers, sizeof(choseNumbers) / sizeof(int));

	while (true) 
	{
		bool isEnd = false;

		// input number 3
		int inputNumbers[numberCount];
		for (size_t i = 0; i < numberCount; i++)
		{
			int inputNumber;
			cin >> inputNumber;

			isEnd = inputNumber == 0;
			if (isEnd) 
			{
				break;
			}
			else
			{
				inputNumbers[i] = inputNumber;
			}
		}

		cout << "Input Numbers : ";
		printNumbers2(inputNumbers, sizeof(inputNumbers) / sizeof(int));

		// check
		int strike = 0, ball = 0;
		for (size_t i = 0; i < numberCount; i++)
		{
			for (size_t j = 0; j < numberCount; j++)
			{
				if (choseNumbers[i] == inputNumbers[j]) {
					if (i == j)
					{
						strike++;
					}
					else 
					{
						ball++;
					}
					break;
				}
			}
		}

		// result
		cout << "strike : " << strike << ", ball : " << ball << endl;

		if(strike == numberCount) 
		{
			cout << strike << "Game End!!!"<< endl;
			isEnd = true;
		}

		if (isEnd) break;
	}
}

void lotto() {
	const int lottoMaxNum = 5;
	int lottoNums[lottoMaxNum];
	int swapCount = lottoMaxNum;

	// fill numbers
	for (size_t i = 0; i < swapCount; i++)
	{
		lottoNums[i] = i + 1;
	}

	// swap numbers
	srand((unsigned int)time(0));
	for (size_t i = 0; i < swapCount; i++)
	{
		// random index
		int idx1 = rand() % lottoMaxNum;
		int idx2 = rand() % lottoMaxNum;
		// swap
		int temp = lottoNums[idx1];
		lottoNums[idx1] = lottoNums[idx2];
		lottoNums[idx2] = temp;
	}

	// print lotto numbers
	printNumbers2(lottoNums, sizeof(lottoNums) / sizeof(int));
	cout << endl;
}

void printNumbers2(int *numbers, int size) {
	for (size_t i = 0; i < size; i++)
	{
		cout << *numbers << " ";
		numbers++;
	}
	cout << endl;
}