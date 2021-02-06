//! @file	HeapMemory.cpp
//! @brief	ヒープメモリに関するAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.3.7

#include "pch.h"
#include "HeapMemory.h"

using namespace alt;

HeapMemory::HeapMemory(int boundary)
	:HandleLibrary()
{
	_bCreateHeap = false;
	_boundary = boundary;

}

HeapMemory::~HeapMemory()
{
	this->Destroy();
}

//! @sa https://ameblo.jp/sgl00044/entry-12521242424.html
BOOL HeapMemory::Create(BOOL bUseSystemMemory)
{
	if (bUseSystemMemory)
	{
		_hObject = ::GetProcessHeap();
	}
	else
	{
		DWORD   flOptions = 0;
		SIZE_T  dwInitialSize = 0;
		SIZE_T  dwMaximumSize = 0;
		_bCreateHeap = true;

		_hObject = ::HeapCreate(flOptions, dwInitialSize, dwMaximumSize);
	}

	return _hObject == NULL ? FALSE : TRUE;
}

BOOL HeapMemory::Destroy()
{
	BOOL ret = TRUE;

	if (_bCreateHeap)
	{
		_bCreateHeap = false;
		ret = ::HeapDestroy(_hObject);
	}

	_hObject = INVALID_HANDLE_VALUE; // HeapのハンドルはCloseHandle()不要

	return ret;
}

LPVOID HeapMemory::Allocate(SIZE_T bytes, DWORD dwFlags)
{
	return ::HeapAlloc(_hObject, dwFlags, this->BoundarySize(bytes));
}

LPVOID HeapMemory::Reallocate(LPVOID lpvBase, SIZE_T bytes, DWORD dwFlags)
{
	return ::HeapReAlloc(_hObject, dwFlags, lpvBase, bytes);
}

BOOL HeapMemory::Free(LPVOID lpvMem)
{
	return ::HeapFree(_hObject, 0, lpvMem);
}

SIZE_T HeapMemory::Compact()
{
	return ::HeapCompact(_hObject, 0);
}

SIZE_T HeapMemory::BoundarySize(SIZE_T bytes)
{
	return _boundary + (bytes - (bytes & (_boundary - 1LL)));
}