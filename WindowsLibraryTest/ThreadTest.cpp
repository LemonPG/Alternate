/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ƒŠƒtƒ@ƒŒƒ“ƒX
 */
#include "pch.h"
#include "Thread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	class Callback : public alt::skeleton::ICallback
	{
	public:
		virtual DWORD Invoke(LPVOID lpvParam)
		{
			for (int i = 0; i < 100; i++)
			{
				Logger::WriteMessage(_T("Invoke() working...\n"));
				Sleep(20);
			}

			Logger::WriteMessage(_T("Invoke() stopped.\n"));
			return 0;
		}
	};

	class MyThread : public alt::Thread, public alt::skeleton::ICallback
	{
	public:
		MyThread() { _callback = this; };
		virtual ~MyThread() {};

		virtual DWORD Invoke(LPVOID lpvParam)
		{
			for (int i = 0; i < 100; i++)
			{
				Logger::WriteMessage(_T("Invoke() working...\n"));
				Sleep(20);
			}

			Logger::WriteMessage(_T("Invoke() stopped.\n"));
			return 0;
		}

	};

	TEST_CLASS(ThreadTest)
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

		TEST_METHOD(ThreadTest1)
		{
			Logger::WriteMessage("ThreadTest1\n");
			static int threadCounter = 0;

			Callback* pCallback = new Callback();
			alt::Thread* pThread = new alt::Thread(pCallback);
			BOOL ret1 = pThread->Create();
			Assert::IsTrue(ret1);

			for (int i = 0; i < 100; i++)
			{
				threadCounter++;
				Logger::WriteMessage(_T("ThreadTest1() working...\n"));
				Sleep(30);
			}

			Logger::WriteMessage(_T("ThreadTest1() stopped.\n"));

			DWORD dwReason = pThread->Wait();
			Assert::AreEqual(WAIT_OBJECT_0, dwReason);
			Assert::AreEqual(100, threadCounter);
		}

		TEST_METHOD(ThreadTest2)
		{
			Logger::WriteMessage("ThreadTest2.\n");
			static int threadCounter = 0;

			auto pWorker = new MyThread();
			BOOL ret1 = pWorker->Create();
			Assert::IsTrue(ret1);

			for (int i = 0; i < 100; i++)
			{
				threadCounter++;
				Logger::WriteMessage(_T("ThreadTest2() working...\n"));
				Sleep(30);
			}

			Logger::WriteMessage(_T("ThreadTest2() stopped.\n"));

			DWORD dwReason = pWorker->Wait();
			Assert::AreEqual(WAIT_OBJECT_0, dwReason);
			Assert::AreEqual(100, threadCounter);
		}

		TEST_METHOD(ThreadTest3)
		{
			Logger::WriteMessage("ThreadTest3.\n");

			alt::Thread* thread = new alt::Thread();
			static int threadCounter = 0;
			auto function = [](LPVOID lpvParam)->DWORD
			{
				int* waitTime = (int*)lpvParam;

				for (int i = 0; i < 100; i++)
				{
					threadCounter++;
					Logger::WriteMessage(_T("."));
					Sleep(*waitTime);
				}

				Logger::WriteMessage(_T("ThreadTest3() stopped.\n"));

				return true;
			};

			LONGLONG waitTime = 30;
			thread->Create(function, &waitTime);
			thread->Wait();

			Assert::AreEqual(100, threadCounter);
		}

		TEST_METHOD(ThreadTest4)
		{
			static int threadCounter[20];
			for (int i = 0; i < 20; i++)
			{
				threadCounter[i] = 0;
			}

			auto function = [](LPVOID lpvParam)->DWORD
			{
				int* index = (int*)lpvParam;
				TCHAR tszMsg[128];

				for (int i = 0; i < 30; i++)
				{
					threadCounter[*index]++;
					wsprintf(tszMsg, _T("thread(%02d) count(%02d)\n"), *index, i);
					Logger::WriteMessage(tszMsg);
					Sleep(10);
				}

				Logger::WriteMessage(_T("ThreadTest4() stopped.\n"));

				return *index;
			};

			BOOL ret;
			HANDLE hThreads[20];
			int param[20];

			alt::Thread* thread = new alt::Thread[20];
			for (int i = 0; i < 20; i++)
			{
				param[i] = i;
				ret = thread[i].Create(function, &param[i], CREATE_SUSPENDED);
				Assert::IsTrue(ret);
				hThreads[i] = thread[i].GetHandle();
			}

			for (int i = 0; i < 20; i++)
			{
				int divide = i % 7;
				switch (divide)
				{
					case 0:
						thread[i].SetPriority(alt::ThreadPriority::Critical);
						break;
					case 1:
						thread[i].SetPriority(alt::ThreadPriority::Highest);
						break;
					case 2:
						thread[i].SetPriority(alt::ThreadPriority::AboveNormal);
						break;
					case 3:
						thread[i].SetPriority(alt::ThreadPriority::Normal);
						break;
					case 4:
						thread[i].SetPriority(alt::ThreadPriority::BelowNormal);
						break;
					case 5:
						thread[i].SetPriority(alt::ThreadPriority::Lowest);
						break;
					case 6:
						thread[i].SetPriority(alt::ThreadPriority::Idle);
						break;
				}
				thread[i].Resume();
			}

			WaitForMultipleObjects(20, hThreads, TRUE, INFINITE);

			Logger::WriteMessage(_T("\nThreadTest4() stopped.\n"));

			for (int i = 0; i < 20; i++)
			{
				Assert::AreEqual(30, threadCounter[i]);
			}
		}
	};
}
