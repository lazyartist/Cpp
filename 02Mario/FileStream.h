#pragma once
#include "value.h"

using namespace std;

class FileStream
{
public:
	FileStream();
	~FileStream();
	bool Open(const char* fileName, const char* mode);
	void Close();
	void Read(void* pBuffer, int iElementSize);
	void ReadLine(void* pBuffer, int& iReadSize);
	void Write(void* pBuffer, int iElementSize);
	void WriteLine(void* pBuffer, int iElementSize);

private:
	FILE* m_pFile;
	int m_iFileSize;
	bool m_bOpened;
};

