/**
 @file		VirtualMemory.h
 @brief		仮想メモリに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2020.2.24
 */
#pragma once

#include "WindowsLibrary.h"

namespace alt
{
	/**
	 @class	VirtualMemory
	 @brief	仮想メモリに関するクラス
	*/
	class DLL_DECLSPEC VirtualMemory : public WindowsLibrary
	{
	public:
		VirtualMemory();
		virtual ~VirtualMemory();

		LPVOID Alloc(SIZE_T size);
		BOOL Free();

		BOOL Reserve(SIZE_T size);
		LPVOID Commit();
		BOOL Decommit();
		BOOL Release();

		BOOL Lock();
		BOOL Unlock();

	private:
		const DWORD _cdwProtect = PAGE_READWRITE;
		LPVOID _lpvAddress;
		SIZE_T _size;
	};
}

