/**
 @file		Logger.h
 @brief		���O�Ɋւ���N���X
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
    /**
     @class		Logger
     @brief		���O�Ɋւ���N���X
     */
    class DLL_DECLSPEC Logger : public WindowsLibrary
	{
	public:
		Logger();
		virtual ~Logger();

		void Log(LPCTSTR lpctszMessage);
	};
}


