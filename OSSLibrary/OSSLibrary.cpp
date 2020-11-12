/**
 @file		OSSLibrary.cpp
 @brief		Open Source Software を集約したプロジェクトファイル
 @author	kumakuma0421@gmail.com
 @date		2020.05.07
 */
#include "pch.h"
#include "OSSLibrary.h"

using namespace oss;

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpvReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			OutputDebugString(_T("WindowsLibrary.dll DLL_PROCESS_ATTACH.\n"));
			break;

		case DLL_THREAD_ATTACH:
			OutputDebugString(_T("WindowsLibrary.dll DLL_THREAD_ATTACH.\n"));
			break;

		case DLL_THREAD_DETACH:
			OutputDebugString(_T("WindowsLibrary.dll DLL_THREAD_DETACH.\n"));
			break;

		case DLL_PROCESS_DETACH:
			OutputDebugString(_T("WindowsLibrary.dll DLL_PROCESS_DETACH.\n"));
			break;
	}

	return TRUE;
}

OSSLibrary::OSSLibrary()
{

}

OSSLibrary::~OSSLibrary()
{

}