//! @file	Logger.h
//! @brief	ログに関するクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "framework.h"
#include "WindowsLibrary.h"
#include "TString.h"
#include "Console.h"
#include "LogFile.h"

namespace alt
{
	//! @class	Logger
	//! @brief	ログに関するクラス
	class DLL_DECLSPEC Logger : public WindowsLibrary
	{
	public:
		void Log(LPCTSTR lpctszMessage);

		static void init();

		static void error(TString& message);
		static void warn(TString& message);
		static void info(TString& message);
		static void debug(TString& message);
		static void trace(TString& message);

	private:
		Logger();
		Logger(const Logger&);
		Logger& operator = (const Logger&);
		virtual ~Logger();

		static Logger* _instance;
		static Console* _console;
		static LogFile* _log;
	};
}