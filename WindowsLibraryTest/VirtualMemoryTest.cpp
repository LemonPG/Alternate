/**
 @file		VirtualMemoryTest.cpp
 @brief		仮想メモリに関するWindowsAPIを集約したクラスのテストクラス
 @author	kumakuma0421@gmail.com
 @date		2020.2.24
 */
#include "pch.h"
#include "VirtualMemory.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(VirtualMemoryTest)
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

		TEST_METHOD(VirtualMemoryTest1)
		{
			Logger::WriteMessage("VirtualMemoryTest1\n");

			alt::VirtualMemory* memory = new alt::VirtualMemory();

			LPVOID lpvMem = memory->Alloc(1024 * 1024 * 10);
			Assert::IsNotNull(lpvMem);

			FillMemory(lpvMem, 1024 * 1024 * 10, 'A');

			BOOL ret = memory->Free();
			Assert::IsTrue(ret);
		}

		TEST_METHOD(VirtualMemoryTest2)
		{
			Logger::WriteMessage("VirtualMemoryTest2\n");

			alt::VirtualMemory* memory = new alt::VirtualMemory();

			BOOL ret;
			ret = memory->Reserve(1024 * 1024 * 10); // 10MB
			Assert::IsTrue(ret);

			LPVOID lpvMem = memory->Commit();
			Assert::IsNotNull(lpvMem);

			FillMemory(lpvMem, 1024 * 1024 * 10, 'A');

			ret = memory->Decommit();
			Assert::IsTrue(ret);

			ret = memory->Release();
			Assert::IsTrue(ret);
		}
	};
}
