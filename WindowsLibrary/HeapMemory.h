//! @file	HeapMemory.h
//! @brief	ヒープメモリに関するAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.3.7

#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	//! @class	HeapMemory
	//! @brief	ヒープメモリに関するAPIを集約したクラス
	class DLL_DECLSPEC HeapMemory : public HandleLibrary
	{
	public:
		HeapMemory(int boundary = 8);
		virtual ~HeapMemory();

		BOOL Create(BOOL bUseSystemMemory = TRUE);
		BOOL Destroy();

		LPVOID Allocate(SIZE_T bytes, DWORD dwFlags = HEAP_ZERO_MEMORY);
		LPVOID Reallocate(LPVOID lpvBase, SIZE_T bytes, DWORD dwFlags = HEAP_ZERO_MEMORY);
		BOOL Free(LPVOID lpvMem);
		SIZE_T Compact();

	private:
		SIZE_T BoundarySize(SIZE_T bytes);

		bool _bCreateHeap;
		int _boundary;
	};
}