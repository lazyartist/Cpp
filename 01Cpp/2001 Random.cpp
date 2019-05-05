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
	//float_random_bunch();
	linear_congruential();
}

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

void float_random_bunch() {
	srand(time(NULL));

	float min = 7.0;
	float max = 8.0;
	float range = max - min;
	int range_bunch_count = 3;

	for (size_t i = 0; i < 100; i++)
	{
		int raw_random = rand() % range_bunch_count;
		//float random = min + (((float)raw_random / (range_bunch)) * range); // max 포함
		float random = min + (((float)raw_random / (range_bunch_count - 1)) * range); // max 미포함
		cout << raw_random << "\t" << random << endl;
	}
}

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