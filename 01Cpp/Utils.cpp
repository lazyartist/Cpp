#include <iostream>

using namespace std;

void printNumbers123();

void printNumbers123(int *numbers, int size) {
	for (size_t i = 0; i < size; i++)
	{
		cout << *numbers << " ";
		numbers++;
	}
	cout << endl;
}