/**
 @file		VirtualMemory.cpp
 @brief		仮想メモリに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2020.2.24
 */
#include "pch.h"
#include "VirtualMemory.h"

using namespace alt;

VirtualMemory::VirtualMemory()
{
	_lpvAddress = nullptr;
	_size = 0;
}

VirtualMemory::~VirtualMemory()
{
	if (_lpvAddress != nullptr)
	{
		this->Unlock();
		this->Free();
		_lpvAddress = nullptr;
		_size = 0;
	}
}

LPVOID VirtualMemory::Alloc(SIZE_T size)
{
	LPVOID lpvAddress = nullptr;
	DWORD dwAllocationType = MEM_COMMIT | MEM_RESERVE;

	_lpvAddress = ::VirtualAlloc(lpvAddress, size, dwAllocationType, _cdwProtect);
	_size = size;

	return _lpvAddress;
}

BOOL VirtualMemory::Free()
{
	DWORD dwFreeType = MEM_RELEASE;

	// MEM_RELEASEの場合は、sizeに０を指定する。
	return ::VirtualFree(_lpvAddress, 0, dwFreeType);
}

BOOL VirtualMemory::Reserve(SIZE_T size)
{
	_lpvAddress = ::VirtualAlloc(nullptr, size, MEM_RESERVE, _cdwProtect);
	_size = size;

	return _lpvAddress == nullptr ? FALSE : TRUE;
}

LPVOID VirtualMemory::Commit()
{
	return ::VirtualAlloc(_lpvAddress, _size, MEM_COMMIT, _cdwProtect);
}

BOOL VirtualMemory::Release()
{
	BOOL ret = ::VirtualFree(_lpvAddress, 0, MEM_RELEASE);
	_lpvAddress = nullptr;
	_size = 0;

	return ret;
}

//! @sa https://www.wabiapp.com/WabiSampleSource/windows/pragma_warning_push_pop.html
BOOL VirtualMemory::Decommit()
{
#pragma warning(push)
#pragma warning(disable:6250)
	return ::VirtualFree(_lpvAddress, _size, MEM_DECOMMIT);
#pragma warning(pop)
}

BOOL VirtualMemory::Lock()
{
	return ::VirtualLock(_lpvAddress, _size);
}

BOOL VirtualMemory::Unlock()
{
	return ::VirtualUnlock(_lpvAddress, _size);
}