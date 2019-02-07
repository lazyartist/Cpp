#include "FileStream.h"



FileStream::FileStream()
{
}


FileStream::~FileStream()
{
	Close();
}

bool FileStream::Open(const char * fileName, const char * mode)
{
	if (m_bOpened) return false;

	fopen_s(&m_pFile, fileName, mode);

	if (m_pFile == NULL) {
		return false;
	}

	m_bOpened = true;

	// 파일커서를 가장 되로 이동시킨다.
	// fseek 함수는 파일 커서를 원하는 위치로 이동시킬 수 있다.
	// SEEK_SET : 파일의 제일 처음을 의미
	// SEEK_CUR : 현재 가리키고 있는 파일 커서의 위치를 의미
	// SEEK_END : 파일의 가장 마지막을 의미
	// 2번째 인자인 offset에 들어가는 바이트수 만큼 3번째 인자에서 지정한 위치로부터 이동하게 된다.
	fseek(m_pFile, 0, SEEK_END);

	// ftell : 파일 커서의 위치를 얻어오는 함수
	// 위에서 파일커서를 가장 마지막으로 이동시켰기 때문에 ftell을 이용해서 파일커서의 위치를 얻어오면
	// 곧 파일 크기가 된다.
	m_iFileSize = ftell(m_pFile);

	// 파일 크기를 구한 후에 가장 앞으로 다시 이동시킨다.
	fseek(m_pFile, 0, SEEK_SET);

	return true;
}

void FileStream::Close()
{
	if (m_bOpened == false) return;

	m_bOpened = false;

	fclose(m_pFile);
	m_pFile = NULL;
	m_iFileSize = 0;
}

void FileStream::Read(void * pBuffer, int iElementSize)
{
	if (m_bOpened == false) return;

	fread(pBuffer, iElementSize, 1, m_pFile);
	//fread_s(data, iSize, 1, 1, m_pFile);
}

void FileStream::ReadLine(void * pBuffer, int& iReadSize)
{
	if (m_bOpened == false) return;

	iReadSize = 0;
	char* pCharBuffer = (char*)pBuffer;
	char ch;
	// feof : end of file
	// 파일커서가 파일의 끝에 도달했는지를 체크한다.
	// 파일의 끝에 도달하면 0을 리턴, 그렇지 않으면 0이 아닌 수를 리턴한다.
	while (feof(m_pFile) == 0) // 파일의 끝에 도달하면 루프를 빠져나간다.
	{
		//Read(pBuffer, char_size);
		fread(&ch, char_size, 1, m_pFile);

		if (ch == '\n') {
			pCharBuffer[iReadSize] = 0;
			break;
		}

		pCharBuffer[iReadSize++] = ch;
		//pBuffer[iReadSize++] = ch; // void 포인터는 역참조가 불가능하다.
	}
}

void FileStream::Write(void * pBuffer, int iElementSize)
{
	if (m_bOpened == false) return;

	fwrite(pBuffer, iElementSize, 1, m_pFile);
}

void FileStream::WriteLine(void * pData, int iBufferSize)
{
	if (m_bOpened == false) return;

	int iTotalBufferSize = iBufferSize + 1;

	const char* strBuffer = (char*)pData;
	char* strTemp = new char[iTotalBufferSize];
	//strTemp[iTotalBufferSize] = '\n';
	*(strTemp+iTotalBufferSize) = '\n'; // 위와 같은 코드

	//strcpy(strTemp, strBuffer); // 보안때문에 컴파일되지 않는다.
	strcpy_s(strTemp, iTotalBufferSize, strBuffer);

	fwrite(strTemp, iTotalBufferSize, 1, m_pFile);
}
