/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ƒŠƒtƒ@ƒŒƒ“ƒX
 */
#include "pch.h"
#include "Console.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(ConsoleTest)
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

		TEST_METHOD(ConsoleTest1)
		{
			Logger::WriteMessage("ConsoleTest1\n");

			alt::Console console;
			BOOL ret;
			
			ret = console.Create();
			//Assert::IsTrue(ret, _T("Console::Create() failed."));

			ret = console.Init();
			//Assert::IsTrue(ret, _T("Console::Init() failed."));

			ret = console.SetColor(alt::ForeColor::Red, alt::BackColor::Black);
			DWORD dwRet = console.Write(_T("TEST TEST TEST"));
			//Assert::AreEqual<DWORD>(14, dwRet, _T("Console::Write() failed."));
		}

		TEST_METHOD(PrintTest1)
		{
			Logger::WriteMessage("PrintTest1\n");

			for (int i = 0; i < 10000; i++)
			{
				_tprintf(_T("this is a test.\n"));
			}
		}

		TEST_METHOD(ConsoleOutTest1)
		{
			Logger::WriteMessage("ConsoleOutTest1\n");
			alt::Console con;

			for (int i = 0; i < 10000; i++)
			{
				con.Write(_T("this is a test.\n"));
			}
		}

		TEST_METHOD(ConsoleOutTest2)
		{
			Logger::WriteMessage("ConsoleOutTest2\n");
			alt::Console con;

			for (int i = 0; i < 100; i++)
			{
				con.Format(_T("Test No.%d"), i);
			}
		}
	};
}
