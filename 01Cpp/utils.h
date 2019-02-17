#include <iostream>

using namespace std;

inline void printNumbers123(int *numbers, int size) {
	for (size_t i = 0; i < size; i++)
	{
		cout << *numbers << " ";
		numbers++;
	}
	cout << endl;
}

#define SAFE_DELETE(p) if(p) delete p;