/**
 @file		MutexTest.cpp
 @brief		ミューテックスに関するWindowsAPIを集約したクラスのテストクラス
 @author	kumakuma0421@gmail.com
 @date		2020.3.29
 */
#include "pch.h"
#include "Mutex.h"
#include "Thread.h"
#include "TString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
#define MUTEX_NAME _T("MutexTest")
#define EVENT_NAME _T("EventTest")

	TEST_CLASS(MutexTest)
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

		TEST_METHOD(MutexTest1)
		{
			Logger::WriteMessage("MutexTest1.\n");

			auto ThreadFunction = [](LPVOID lpvParam)->DWORD
			{
				LPCTSTR lpctszWord = (LPCTSTR)lpvParam;
				alt::TString msg;
				BOOL ret;
				alt::Mutex mutex;
				ret = mutex.Open(MUTEX_NAME);
				Assert::IsTrue(ret);

				msg.Format(_T("Thread %s start\n"), lpctszWord);
				Logger::WriteMessage(msg.Ctr());

				for (int i = 0; i < 10; i++)
				{
					mutex.Wait();

					msg.Format(_T("Thread %s %d.\n"), lpctszWord, i);
					Logger::WriteMessage(msg.Ctr());

					ret = mutex.Release();
					Assert::IsTrue(ret);
					Sleep(100);
				}

				msg.Format(_T("Thread %s stopped.\n"), lpctszWord);
				Logger::WriteMessage(msg.Ctr());

				return 0;
			};

			alt::Mutex mutex;
			alt::Thread MutexThreads[10];
			HANDLE hMutexs[10];
			BOOL ret;
			alt::TString Keyword;

			ret = mutex.Create(MUTEX_NAME);
			mutex.Wait();

			for (int i = 0; i < 10; i++)
			{
				Keyword.Format(_T("Thread_%02d"), i);
				ret = MutexThreads[i].Create(ThreadFunction, (LPVOID)Keyword.Ctr());
				Assert::IsTrue(ret);

				hMutexs[i] = MutexThreads[i].GetHandle();
			}

			mutex.Release();

			WaitForMultipleObjects(10, hMutexs, TRUE, INFINITE);
		}
	};
}
