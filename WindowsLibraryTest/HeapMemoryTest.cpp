/**
 @file		HeapMemoryTest.cpp
 @brief		ヒープメモリに関するAPIを集約したクラスのテストクラス
 @author	kumakuma0421@gmail.com
 @date		2020.3.7
 */
#include "pch.h"
#include "HeapMemory.h"
#include "TString.h"
#include "Thread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(HeapMemoryTest)
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

		void NewTestByte(int size, int count)
		{
			alt::Thread* thread = new alt::Thread[10];
			static const int paramSize = size;
			static const int paramCount = count;

			auto function = [](LPVOID lpvParam)->DWORD
			{
				for (int i = 0; i < paramCount; i++)
				{
					LPVOID lpvMemory = new BYTE[paramSize];
					ZeroMemory(lpvMemory, paramSize);
					delete[] lpvMemory;
				}
				return true;
			};

			for (int i = 0; i < 10; i++)
			{
				thread[i].Create(function);
			}

			HANDLE hThreads[10];
			for (int i = 0; i < 10; i++)
			{
				hThreads[i] = thread[i].GetHandle();
			}
			::WaitForMultipleObjects(10, hThreads, TRUE, INFINITE);
		}

		void HeapTestByte(int size, int count, BOOL bUseSystemHeap)
		{
			alt::Thread* thread = new alt::Thread[10];
			static const int paramSize = size;
			static const int paramCount = count;
			static const BOOL parambUseSystemHeap = bUseSystemHeap;

			auto function = [](LPVOID lpvParam)->DWORD
			{
				alt::HeapMemory heapMemory;
				BOOL ret1 = heapMemory.Create(parambUseSystemHeap);
				Assert::IsTrue(ret1);

				for (int i = 0; i < paramCount; i++)
				{
					LPVOID lpvMemory = heapMemory.Allocate(paramSize);
					ZeroMemory(lpvMemory, paramSize);
					BOOL ret2 = heapMemory.Free(lpvMemory);
					Assert::IsTrue(ret2);
				}

				heapMemory.Compact();

				BOOL ret3 = heapMemory.Destroy();
				Assert::IsTrue(ret3);
				return true;
			};

			for (int i = 0; i < 10; i++)
			{
				thread[i].Create(function);
			}

			HANDLE hThreads[10];
			for (int i = 0; i < 10; i++)
			{
				hThreads[i] = thread[i].GetHandle();
			}
			::WaitForMultipleObjects(10, hThreads, TRUE, INFINITE);
		}

		TEST_METHOD(NewMemoryTest512)
		{
			Logger::WriteMessage("NewMemoryTest512\n");
			NewTestByte(512, 100000);
		}

		TEST_METHOD(NewMemoryTest1024)
		{
			Logger::WriteMessage("NewMemoryTest1024\n");
			NewTestByte(1024, 100000);
		}

		TEST_METHOD(NewMemoryTest2048)
		{
			Logger::WriteMessage("NewMemoryTest2048\n");
			NewTestByte(2048, 100000);
		}

		TEST_METHOD(NewMemoryTest4096)
		{
			Logger::WriteMessage("NewMemoryTest4096\n");
			NewTestByte(4096, 100000);
		}

		TEST_METHOD(SystemHeapMemoryTest512)
		{
			Logger::WriteMessage("SystemHeapMemoryTest512\n");
			HeapTestByte(512, 100000, TRUE);
		}

		TEST_METHOD(SystemHeapMemoryTest1024)
		{
			Logger::WriteMessage("SystemHeapMemoryTest1024\n");
			HeapTestByte(1024, 100000, TRUE);
		}

		TEST_METHOD(SystemHeapMemoryTest2048)
		{
			Logger::WriteMessage("SystemHeapMemoryTest2048\n");
			HeapTestByte(2048, 100000, TRUE);
		}

		TEST_METHOD(SystemHeapMemoryTest4096)
		{
			Logger::WriteMessage("SystemHeapMemoryTest4096\n");
			HeapTestByte(4096, 100000, TRUE);
		}

		TEST_METHOD(UserHeapMemoryTest512)
		{
			Logger::WriteMessage("UserHeapMemoryTest512\n");
			HeapTestByte(512, 100000, FALSE);
		}

		TEST_METHOD(UserHeapMemoryTest1024)
		{
			Logger::WriteMessage("UserHeapMemoryTest1024\n");
			HeapTestByte(1024, 100000, FALSE);
		}

		TEST_METHOD(UserHeapMemoryTest2048)
		{
			Logger::WriteMessage("UserHeapMemoryTest2048\n");
			HeapTestByte(2048, 100000, FALSE);
		}

		TEST_METHOD(UserHeapMemoryTest4096)
		{
			Logger::WriteMessage("UserHeapMemoryTest4096\n");
			HeapTestByte(4096, 100000, FALSE);
		}

		TEST_METHOD(HeapReallocTest)
		{
			alt::HeapMemory heapMemory;
			BOOL ret1 = heapMemory.Create();
			Assert::IsTrue(ret1);

			int allocSize = 1024;
			LPVOID lpvMemory = heapMemory.Allocate(allocSize);
			FillMemory(lpvMemory, allocSize, 'a');

			for (int i = 0; i < 100; i++)
			{
				allocSize += 512;
				lpvMemory = heapMemory.Reallocate(lpvMemory, allocSize);
				FillMemory(lpvMemory, allocSize, ('a' + i));
			}

			BOOL ret2 = heapMemory.Free(lpvMemory);
			Assert::IsTrue(ret2);
			BOOL ret3 = heapMemory.Destroy();
			Assert::IsTrue(ret3);
		}
	};
}
