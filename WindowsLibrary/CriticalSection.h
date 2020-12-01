//! @file	CriticalSection.h
//! @brief	CriticalSectionに関するWindowsAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	//! @class	CriticalSection
	//! @brief	CriticalSectionに関するWindowsAPIを集約したクラス
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