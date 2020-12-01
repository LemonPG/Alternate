//! @file	CriticalSection.h
//! @brief	CriticalSection�Ɋւ���WindowsAPI���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	//! @class	CriticalSection
	//! @brief	CriticalSection�Ɋւ���WindowsAPI���W�񂵂��N���X
	class DLL_DECLSPEC CriticalSection : public WindowsLibrary
	{
	public:
		CriticalSection();
		virtual ~CriticalSection();

		VOID Enter();
		VOID Leave();

	private:
		CRITICAL_SECTION _criticalSection;
	};
}