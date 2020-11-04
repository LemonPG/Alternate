/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API リファレンス
 */
#include "pch.h"
#include "Logger.h"
#include "Thread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(LoggerTest)
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

		TEST_METHOD(LoggerTest1)
		{
			Logger::WriteMessage("LoggerTest1\n");

			alt::Logger::init();

			alt::TString message(_T("sample message"));

			alt::Logger::error(message);
			alt::Logger::warn(message);
			alt::Logger::info(message);
			alt::Logger::debug(message);
			alt::Logger::trace(message);
		}
	};
}
