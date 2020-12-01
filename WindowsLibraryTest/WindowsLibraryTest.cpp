//! @file	WindowsLibraryTest.cpp
//! @brief	WindowsLibraryプロジェクトのテストクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21
//! @sa     https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
//!         Microsoft.VisualStudio.TestTools.CppUnitTestFramework API リファレンス

#include "pch.h"
#include "WindowsLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_MODULE_INITIALIZE(ModuleInitialize)
	{
		Logger::WriteMessage("module initialize.\n");
	}

	TEST_MODULE_CLEANUP(ModuleCleanup)
	{
		Logger::WriteMessage("module cleanup.\n");
	}

	TEST_CLASS(WindowsLibraryTest)
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

		TEST_METHOD(dllmainTest)
		{
			HMODULE hModule = NULL;
			DWORD  ul_reason_for_call = 0;
			LPVOID lpvReserved = NULL;
			BOOL ret;

			ret = DllMain(hModule, ul_reason_for_call, lpvReserved);
		}
	};
}