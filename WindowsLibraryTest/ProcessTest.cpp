/**
 @file		ProcessTest.cpp
 @brief		プロセスに関するWindowsAPIを集約したクラスのテストクラス
 @author	kumakuma0421@gmail.com
 @date		2020.3.31
 */
#include "pch.h"
#include "Process.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(ProcessTest)
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("class initialize.\n");
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

		TEST_METHOD(ConsoleProcessTest1)
		{
			Logger::WriteMessage("ConsoleProcessTest1\n");

			alt::Process testProcess;
			//BOOL ret = testProcess.Create(_T("C:\\Windows\\System32\\PING.exe"), _T("192.168.2.1"));
			TCHAR tszCmdline[MAX_PATH]{ _T("PING 192.168.2.1") };
			BOOL ret = testProcess.Create(nullptr, tszCmdline);
			Assert::IsTrue(ret);

			CHAR szBuf[1024];
			DWORD dwSize;

			for (int i = 0; i < 100; i++)
			{
				ZeroMemory(szBuf, sizeof(szBuf));
				dwSize = testProcess.Peek(szBuf, sizeof(szBuf));
				if (dwSize > 0)
				{
					dwSize = testProcess.Read(szBuf, sizeof(szBuf));
					Logger::WriteMessage(szBuf);
				}

				if (testProcess.GetErrNo() != ERROR_SUCCESS) break;

				DWORD dwRet = WaitForSingleObject(testProcess.GetProcessHandle(), 20);
				if (dwRet == WAIT_TIMEOUT) continue;
				if (dwRet == WAIT_OBJECT_0) break;
			}

			WaitForSingleObject(testProcess.GetProcessHandle(), INFINITE);
			DWORD dwExitCode = testProcess.GetExitCode();
			Assert::AreEqual<DWORD>(0, dwExitCode);
		}

		TEST_METHOD(ConsoleProcessTest2)
		{
			Logger::WriteMessage("ConsoleProcessTest2\n");

			alt::Process testProcess;
			TCHAR tszCmdline[MAX_PATH]{ _T("PING -t 192.168.2.1") };
			testProcess.SetTitle(_T("ConsoleProcessTest2"));
			testProcess.SetConsoleInfo(0, 0, 80, 25, 80, 25);
			BOOL ret = testProcess.Create(nullptr, tszCmdline);
			Assert::IsTrue(ret);

			CHAR szBuf[1024];
			DWORD dwSize;

			for (int i = 0; i < 10; i++)
			{
				ZeroMemory(szBuf, sizeof(szBuf));
				dwSize = testProcess.Peek(szBuf, sizeof(szBuf));
				if (dwSize > 0)
				{
					dwSize = testProcess.Read(szBuf, sizeof(szBuf));
					Logger::WriteMessage(szBuf);
				}

				if (testProcess.GetErrNo() != ERROR_SUCCESS) break;

				DWORD dwRet = WaitForSingleObject(testProcess.GetProcessHandle(), 100);
				if (dwRet == WAIT_TIMEOUT) continue;
				if (dwRet == WAIT_OBJECT_0) break;
			}

			WaitForSingleObject(testProcess.GetProcessHandle(), 5000);
			Assert::IsTrue(testProcess.Terminate());
			WaitForSingleObject(testProcess.GetProcessHandle(), INFINITE);
			DWORD dwExitCode = testProcess.GetExitCode();
			Assert::AreEqual<DWORD>(0, dwExitCode);
		}

		TEST_METHOD(ConsoleProcessTest3)
		{
			Logger::WriteMessage("ConsoleProcessTest3\n");

			alt::Process testProcess;
			TCHAR tszCmdline[MAX_PATH]{ _T("notepad.exe ..\\..\\README.MD") };
			BOOL ret = testProcess.Create(nullptr, tszCmdline);
			Assert::IsTrue(ret);

			WaitForSingleObject(testProcess.GetProcessHandle(), 5000);
			Assert::IsTrue(testProcess.Terminate());
			WaitForSingleObject(testProcess.GetProcessHandle(), INFINITE);
			DWORD dwExitCode = testProcess.GetExitCode();
			Assert::AreEqual<DWORD>(0, dwExitCode);
		}

		TEST_METHOD(ConsoleProcessTest4)
		{
			Logger::WriteMessage("ConsoleProcessTest4\n");

			alt::Process testProcess;
			TCHAR tszCmdline[MAX_PATH]{ _T("notepad.exe ..\\..\\README.MD") };
			testProcess.SetWindowInfo(2, 2, 320, 200);
			BOOL ret = testProcess.Create(nullptr, tszCmdline);
			Assert::IsTrue(ret);

			WaitForSingleObject(testProcess.GetProcessHandle(), 5000);
			Assert::IsTrue(testProcess.Terminate());
			WaitForSingleObject(testProcess.GetProcessHandle(), INFINITE);
			DWORD dwExitCode = testProcess.GetExitCode();
			Assert::AreEqual<DWORD>(0, dwExitCode);
		}

		TEST_METHOD(ConsoleProcessTest5)
		{
			Logger::WriteMessage("ConsoleProcessTest5\n");

			alt::Process testProcess;
			TCHAR tszCmdline[MAX_PATH]{ _T("CMD /K") };
			testProcess.SetTitle(_T("ConsoleProcessTest5"));
			testProcess.SetConsoleInfo(0, 0, 80, 25, 80, 25);
			BOOL ret = testProcess.Create(nullptr, tszCmdline);
			Assert::IsTrue(ret);

			CHAR szBuf[1024];
			DWORD dwSize;

			for (int i = 0; i < 10; i++)
			{
				sprintf_s(szBuf, "DIR C:\\Windows"); //! @todo インタラクティブに動かない
				//sprintf_s(szBuf, "find TEST ..\\..\\README.md"); //! @todo インタラクティブに動かない
				dwSize = (DWORD)strlen(szBuf);

				DWORD dwWrite = testProcess.Write(szBuf, dwSize);
				Assert::AreEqual<DWORD>(dwWrite, dwSize);

				ZeroMemory(szBuf, sizeof(szBuf));
				dwSize = testProcess.Peek(szBuf, sizeof(szBuf));
				if (dwSize > 0)
				{
					dwSize = testProcess.Read(szBuf, sizeof(szBuf));
					Logger::WriteMessage(szBuf);
				}

				if (testProcess.GetErrNo() != ERROR_SUCCESS) break;

				DWORD dwRet = WaitForSingleObject(testProcess.GetProcessHandle(), 100);
				if (dwRet == WAIT_TIMEOUT) continue;
				if (dwRet == WAIT_OBJECT_0) break;
			}

			WaitForSingleObject(testProcess.GetProcessHandle(), 5000);
			Assert::IsTrue(testProcess.Terminate());
			WaitForSingleObject(testProcess.GetProcessHandle(), INFINITE);
			DWORD dwExitCode = testProcess.GetExitCode();
			Assert::AreEqual<DWORD>(0, dwExitCode);
		}
	};
}