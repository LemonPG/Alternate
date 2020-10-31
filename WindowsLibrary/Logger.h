/**
 @file		Logger.h
 @brief		ログに関するクラス
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
     @brief		ログに関するクラス
     */
    class DLL_DECLSPEC Logger : public WindowsLibrary
	{
	public:
		Logger();
		virtual ~Logger();

		void Log(LPCTSTR lpctszMessage);
	};
}


