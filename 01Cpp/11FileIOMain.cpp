#include <iostream>

using namespace std;

int main() {
	FILE* pFile = NULL;

	// 1 : 파일의 이중포인터
	// 2 : 파일 경로, 파일이 생성되는 기준 경로는 현재 프로젝트가 있는 폴더 기준이다.
	// 만약 실행파일로 실행했을 경우에는 해당 exe파일이 있는 경로를 기준으로 생성해준다.
	// 3 : 파일 모드, 모드는 크게 2가지로 구분
	// 파일 읽기, 쓰기, 접근 | 파일 형태(텍스트파일, 바이너리파일)
	// 이 2가지 모드를 합쳐서 사용한다.
	// r : 읽기, w : 쓰기, a : 접근 | t : 텍스트 파일, b : 바이너리 파일
	//fopen_s(&pFile, "test.txt", "wt");

	// 파일 쓰기
	//fopen_s(&pFile, "test.txt", "wt");
	//if (pFile != NULL) {
	//	// fwrite, fread : 쓰기, 읽기
	//	// fputs, fgets : 쓰기, 읽기

	//	const char* pText = "abcd";
	//	// 1번 인자로 void 포인터를 받기 때문에 요소의 크기와 길이를 함께 전달해야 fwrite함수내에서 파일에 어떻게 쓸지를 결정할 수 있다.
	//	fwrite(pText, sizeof(char), sizeof(pText) / sizeof(char), pFile);

	//	fclose(pFile);
	//}

	// 파일 읽기
	fopen_s(&pFile, "test.txt", "rt");

	if (pFile != NULL) {
		char strText[5] = {};
		fread_s(strText, 5, 1, 5, pFile);
		cout << strText << endl;

		fclose(pFile);
	}

	// 바이너리 파일로 저장 
	char name[10] = "name";
	FILE* pFileBinary;
	fopen_s(&pFileBinary, "fileBinary.b", "wb");
	fwrite(name, 1, 10, pFileBinary);
	fclose(pFileBinary);

	// 바이너리 파일 읽기
	fopen_s(&pFileBinary, "fileBinary.b", "rb");
	char name2[10];
	fread_s(name2, 10, 1, 10, pFileBinary);
	fclose(pFileBinary);
} 