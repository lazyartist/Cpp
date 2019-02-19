#include <iostream>

using namespace std;

template<typename T>
inline void GPrint(const T * arr, const size_t size, const char sep = ',') {
	for (size_t i = 0; i < size; i++)
	{
		if (arr[0] == 0) {
			cout << "Null" << sep;
		}else if (i + 1 == size) {
			cout << arr[i];
		}
		else {
			cout << arr[i] << sep;
		}
	}
	cout << endl;
}

#define SAFE_DELETE(p) if(p) delete p; p = nullptr;