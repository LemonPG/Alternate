//! @file	SharedMemory.h
//! @brief	���L�������Ɋւ���WindowsAPI���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.2

#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	//! @class	SharedMemory
	//! @brief	���L�������Ɋւ���WindowsAPI���W�񂵂��N���X
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