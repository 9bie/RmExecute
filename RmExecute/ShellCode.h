#include <Windows.h>
#include <windows.h>
#include <winternl.h>
#include <winhttp.h>
#include <string.h>
#include "api.h"


EXTERN_C VOID
mmLoaderSCStart();//������������shellcode�Ŀ�ʼ

void __stdcall Strat();//��ں���main

EXTERN_C VOID
mmLoaderSCEnd();//�뿪ͷ��Ӧ�Ľ�β