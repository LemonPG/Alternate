/**
 @file		LogFileTest.cpp
 @brief		Fileをベースとしたログに関する機能を集約したクラスのテストクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#include "pch.h"
#include "LogFile.h"
#include "Thread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	alt::LogFile __threadLogFile;

	auto loopAction = [](int index, int loopMax)
	{
		alt::TString message;
		for (int i = 0; i < loopMax; i++)
		{
			message << _T("ThreadFunction_") << index << _T("_") << i << _T("_★★★★★★★★★★★★★★★★★★★");
			__threadLogFile.LogInfo(message.Ctr());
			Sleep(0);
			message = _T("");
		}

		return 0;
	};

	DWORD ThreadFunction1(LPVOID lpvParam)
	{
		loopAction(1, 1000);
		return 0;
	}

	DWORD ThreadFunction2(LPVOID lpvParam)
	{
		loopAction(2, 1000);
		return 0;
	}

	DWORD ThreadFunction3(LPVOID lpvParam)
	{
		loopAction(3, 1000);
		return 0;
	}

	DWORD ThreadFunction4(LPVOID lpvParam)
	{
		loopAction(4, 1000);
		return 0;
	}

	DWORD ThreadFunction5(LPVOID lpvParam)
	{
		loopAction(5, 1000);
		return 0;
	}

	DWORD ThreadFunction6(LPVOID lpvParam)
	{
		loopAction(6, 1000);
		return 0;
	}

	DWORD ThreadFunction7(LPVOID lpvParam)
	{
		loopAction(7, 1000);
		return 0;
	}

	DWORD ThreadFunction8(LPVOID lpvParam)
	{
		loopAction(8, 1000);
		return 0;
	}

	TEST_CLASS(LogFileTest)
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("class initialize.\n");
			auto response = alt::FileUtility::Find(_T(".\\TestLog*"));
			for (int i = 0; i < response.Size(); i++)
			{
				alt::FileUtility::Delete(response[i]->Ctr());
			}
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("class cleanup.\n");
		}

		TEST_METHOD_INITIALIZE(MethodInitialize)
		{
			Logger::WriteMessage("method initialize.\n");
		}

		TEST_METHOD_CLEANUP(MethodCleanup)
		{
			Logger::WriteMessage("method cleanup.\n");
		}

		TEST_METHOD(LogFileTest1)
		{
			Logger::WriteMessage("LogFileTest1\n");

			alt::LogFile logFile(alt::LogLevel::Trace, _T(".\\TestLog1"), 10, 1024 * 1024);

			for (int i = 0; i < 900; i++)
			{
				logFile.LogDebug(_T("DebugLog -------------------------------------------"));
				logFile.LogTrace(_T("TraceLog -------------------------------------------"));
				logFile.LogInfo(_T("InfoLog --------------------------------------------"));
				logFile.LogWarn(_T("WarnLog --------------------------------------------"));
				logFile.LogError(_T("ErrorLog -------------------------------------------"));
				logFile.LogFatal(_T("FatalLog -------------------------------------------"));
			}
		}

		TEST_METHOD(LogFileTest2)
		{
			Logger::WriteMessage("LogFileTest2\n");

			alt::LogFile logFile(alt::LogLevel::Debug, _T(".\\TestLog2"), 10, 1024 * 1024);

			for (int i = 0; i < 1000; i++)
			{
				logFile.LogDebug(_T("DebugLog --------------------------------------------------------------------"));
				logFile.LogTrace(_T("TraceLog --------------------------------------------------------------------"));
				logFile.LogInfo(_T("InfoLog ---------------------------------------------------------------------"));
				logFile.LogWarn(_T("WarnLog ---------------------------------------------------------------------"));
				logFile.LogError(_T("ErrorLog --------------------------------------------------------------------"));
				logFile.LogFatal(_T("FatalLog --------------------------------------------------------------------"));
			}
		}

		TEST_METHOD(LogFileTest3)
		{
			Logger::WriteMessage("LogFileTest3\n");

			alt::LogFile logFile(alt::LogLevel::Info, _T(".\\TestLog3"), 10, 1024 * 1024);

			for (int i = 0; i < 1000; i++)
			{
				logFile.LogDebug(_T("DebugLog --------------------------------------------------------------------"));
				logFile.LogTrace(_T("TraceLog --------------------------------------------------------------------"));
				logFile.LogInfo(_T("InfoLog ---------------------------------------------------------------------"));
				logFile.LogWarn(_T("WarnLog ---------------------------------------------------------------------"));
				logFile.LogError(_T("ErrorLog --------------------------------------------------------------------"));
				logFile.LogFatal(_T("FatalLog --------------------------------------------------------------------"));
			}
		}

		TEST_METHOD(LogFileTest4)
		{
			Logger::WriteMessage("LogFileTest4\n");

			alt::LogFile logFile(alt::LogLevel::Warn, _T(".\\TestLog4"), 10, 1024 * 1024);

			for (int i = 0; i < 1000; i++)
			{
				logFile.LogDebug(_T("DebugLog --------------------------------------------------------------------"));
				logFile.LogTrace(_T("TraceLog --------------------------------------------------------------------"));
				logFile.LogInfo(_T("InfoLog ---------------------------------------------------------------------"));
				logFile.LogWarn(_T("WarnLog ---------------------------------------------------------------------"));
				logFile.LogError(_T("ErrorLog --------------------------------------------------------------------"));
				logFile.LogFatal(_T("FatalLog --------------------------------------------------------------------"));
			}
		}

		TEST_METHOD(LogFileTest5)
		{
			Logger::WriteMessage("LogFileTest5\n");

			alt::LogFile logFile(alt::LogLevel::Error, _T(".\\TestLog5"), 10, 1024 * 1024);

			for (int i = 0; i < 1000; i++)
			{
				logFile.LogDebug(_T("DebugLog --------------------------------------------------------------------"));
				logFile.LogTrace(_T("TraceLog --------------------------------------------------------------------"));
				logFile.LogInfo(_T("InfoLog ---------------------------------------------------------------------"));
				logFile.LogWarn(_T("WarnLog ---------------------------------------------------------------------"));
				logFile.LogError(_T("ErrorLog --------------------------------------------------------------------"));
				logFile.LogFatal(_T("FatalLog --------------------------------------------------------------------"));
			}
		}

		TEST_METHOD(LogFileTest6)
		{
			Logger::WriteMessage("LogFileTest6\n");

			alt::LogFile logFile(alt::LogLevel::Fatal, _T(".\\TestLog6"), 10, 1024 * 1024);

			for (int i = 0; i < 1000; i++)
			{
				logFile.LogDebug(_T("DebugLog --------------------------------------------------------------------"));
				logFile.LogTrace(_T("TraceLog --------------------------------------------------------------------"));
				logFile.LogInfo(_T("InfoLog ---------------------------------------------------------------------"));
				logFile.LogWarn(_T("WarnLog ---------------------------------------------------------------------"));
				logFile.LogError(_T("ErrorLog --------------------------------------------------------------------"));
				logFile.LogFatal(_T("FatalLog --------------------------------------------------------------------"));
			}
		}

		TEST_METHOD(LogFileThreadTest)
		{
			Logger::WriteMessage("LogFileThreadTest\n");

			__threadLogFile.Init(alt::LogLevel::Trace, _T(".\\TestLog"), 10, 1024 * 1024 * 1);

			alt::Thread thread1;
			alt::Thread thread2;
			alt::Thread thread3;
			alt::Thread thread4;
			alt::Thread thread5;
			alt::Thread thread6;
			alt::Thread thread7;
			alt::Thread thread8;

			thread1.Create(ThreadFunction1);
			thread2.Create(ThreadFunction2);
			thread3.Create(ThreadFunction3);
			thread4.Create(ThreadFunction4);
			thread5.Create(ThreadFunction5);
			thread6.Create(ThreadFunction6);
			thread7.Create(ThreadFunction7);
			thread8.Create(ThreadFunction8);

			thread1.Wait();
			thread2.Wait();
			thread3.Wait();
			thread4.Wait();
			thread5.Wait();
			thread6.Wait();
			thread7.Wait();
			thread8.Wait();
		}
	};
}
