/**
 @file		VirtualMemory.h
 @brief		���z�������Ɋւ���WindowsAPI���W�񂵂��N���X
 @author	kumakuma0421@gmail.com
 @date		2020.2.24
 */
#pragma once

#include "WindowsLibrary.h"

namespace alt
{
	/**
	 @class	VirtualMemory
	 @brief	���z�������Ɋւ���N���X
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

