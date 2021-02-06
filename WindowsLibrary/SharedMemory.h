//! @file	SharedMemory.h
//! @brief	共有メモリに関するWindowsAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.2

#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	//! @class	SharedMemory
	//! @brief	共有メモリに関するWindowsAPIを集約したクラス
	class DLL_DECLSPEC SharedMemory : public HandleLibrary
	{
	public:
		SharedMemory();
		virtual ~SharedMemory();

		BOOL Create(LPCTSTR lpctszName, DWORD dwSize);
		BOOL Open(LPCTSTR lpctszName);

		LPVOID Mapped();
		BOOL Unmapped();

	private:
		LPVOID _lpvMapped;
	};

}