/* �����R�[�h�͂r�i�h�r ���s�R�[�h�͂b�q�k�e */
/* $Id: utv_core.cpp 807 2011-11-26 17:36:37Z umezawa $ */

#include "stdafx.h"
#include "utvideo.h"
#include "TunedFunc.h"

#ifdef _WIN32

HMODULE hModule;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	//_RPT3(_CRT_WARN, "DllMain(HMODULE, DWORD, LPVOID) hModule=%p dwReason=%08X lpReserved=%p\n", hModule, dwReason, lpReserved);

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		::hModule = hModule;
	}

	return TRUE;
}

#endif

#ifdef _DEBUG

#include "Predict.h"

DLLEXPORT void UnitTest_core(void)
{
	UnitTest_Predict();
}

#endif
