/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ƒŠƒtƒ@ƒŒƒ“ƒX
 */
#include "pch.h"
#include "SharedMemory.h"
#include "Thread.h"
#include "Mutex.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(SharedMemoryTest)
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

		TEST_METHOD(SharedMemoryTest1)
		{
			Logger::WriteMessage("SharedMemoryTest1\n");

			alt::Thread thread1;
			alt::Thread thread2;
			alt::Mutex mutex;
			alt::SharedMemory shmem;

			auto threadFunc1 = [](LPVOID lpvParam)->DWORD
			{
				alt::SharedMemory shmem;
				alt::Mutex mutex;
				Assert::IsTrue(shmem.Open(_T("SHMEM")));
				Assert::IsTrue(mutex.Open(_T("MUTEX")));

				LPVOID lpvMem = shmem.Mapped();
				Assert::IsNotNull(lpvMem);
				
				for (int i = 0; i < 1000; i++)
				{
					mutex.Wait();
					FillMemory(lpvMem, 10240, '1');
					Logger::WriteMessage("1");
					mutex.Release();
					SwitchToThread();
				}

				Assert::IsTrue(shmem.Unmapped());

				return 0;
			};

			auto threadFunc2 = [](LPVOID lpvParam)->DWORD
			{
				alt::SharedMemory shmem;
				alt::Mutex mutex;
				Assert::IsTrue(shmem.Open(_T("SHMEM")));
				Assert::IsTrue(mutex.Open(_T("MUTEX")));

				LPVOID lpvMem = shmem.Mapped();
				Assert::IsNotNull(lpvMem);

				for (int i = 0; i < 1000; i++)
				{
					mutex.Wait();
					FillMemory(lpvMem, 10240, '2');
					Logger::WriteMessage("2");
					mutex.Release();
					SwitchToThread();
				}

				Assert::IsTrue(shmem.Unmapped());

				return 0;
			};

			Assert::IsTrue(mutex.Create(_T("MUTEX")));
			Assert::IsTrue(shmem.Create(_T("SHMEM"), 10240));

			Assert::IsTrue(thread1.Create(threadFunc1));
			Assert::IsTrue(thread2.Create(threadFunc2));

			HANDLE hThreads[2];
			hThreads[0] = thread1.GetHandle();
			hThreads[1] = thread2.GetHandle();
			WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
		}
	};
}
