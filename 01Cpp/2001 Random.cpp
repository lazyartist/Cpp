#include <iostream>
#include <time.h>

void int_random();
void float_random();
void float_random_bunch();
void linear_congruential();

using namespace std;

void _2001_random() {
	//int_random();
	//float_random();
	float_random_bunch();
	//linear_congruential();
}

// min, max 사이의 정수 반환
void int_random() {
	srand(time(NULL));

	int min = 1;
	int max = 5;
	int range = max - min + 1;

	for (size_t i = 0; i < 10; i++)
	{
		int raw_random = rand();
		int random = min + (raw_random % range);
		cout << raw_random << "\t" << random << endl;
	}
}

// min, max 사이의 유리수 반환
void float_random() {
	srand(time(NULL));

	float min = 7.0;
	float max = 8.0;
	float range = max - min;

	for (size_t i = 0; i < 10; i++)
	{
		int raw_random = rand(); // max 포함
		//int raw_random = rand() % (RAND_MAX - 1); // max 미포함
		float random = min + (((float)raw_random / RAND_MAX) * range);
		cout << raw_random << "\t" << random << endl;
	}
}

// min, max 사이의 수를 지정한 숫자의 단계로 구분하여 출력
void float_random_bunch() {
	srand(time(NULL));

	float min = 7.0;
	float max = 8.0;
	float range = max - min;
	int range_bunch_count = 3;

	for (size_t i = 0; i < 100; i++)
	{
		int raw_random = rand() % range_bunch_count; // bunch_count로 나머지 연산하여 수의 범위를 0~bunch_count-1로 줄인다.

		// range_bunch_count - 1로 나누어서 나온 숫자가 range_bunch_count에서 어디에 위치했는지 계산하고
		// range를 곱하여 범위에 대응되는 숫자로 만든 후 min값을 더하여 완성한다.

		//float random = min + (((float)raw_random / (range_bunch)) * range); // max 포함
		float random = min + (((float)raw_random / (range_bunch_count - 1)) * range); // max 미포함

		cout << raw_random << "\t" << random << endl;
	}
}

/*
Linear Congruential Generator(LCG): 선형 합동 생성기, 널리 알려진 유사난수 생성기

선형 합동 생성기의 상태는 바로 이전에 생성된 난수이며, 이 난수는 최대 m가지 경우가 있으므로 난수의 주기는 최대 m임이 자명하다.
하지만 대부분의 경우 이 주기는 훨씬 짧으며, 최대 주기를 갖기 위한 필요충분조건은 다음과 같다.

1. b와 m이 서로소여야 한다.
a-1이 m의 모든 소인수로 나눠져야 한다.
m이 4의 배수일 경우, a-1도 4의 배수여야 한다.

선형 합동 생성기는 그 인자들과 마지막으로 생성된 난수를 알면 그 뒤에 만들어질 모든 난수를 예측할 수 있기 때문에 암호학적으로 안전한 유사난수 생성기가 아니다. 
또한 선형 합동 생성기가 생성해 내는 난수의 질은 그 인자에 따라 극적으로 달라지며, 인자에 따라서는 적절치 못한 초기값 때문에 문제가 생기기도 한다.
*/
void linear_congruential() {
	int m = 16;
	int a = 5;
	int b = 3;
	
	for (size_t i = 0; i < 20; i++)
	{
		int r = (a * i + b) % m;
		cout << r << endl;
	}
}