//! @file	EventTest.cpp
//! @brief	イベントに関するWindowsAPIを集約したクラスのテストクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#include "pch.h"
#include "Event.h"
#include "Thread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	//! @class	EventTest1
	//! @brief	自動リセットイベントテストクラス
	class EventTest1 : public alt::skeleton::ICallback
	{
	public:
		EventTest1(BOOL bOwner)
		{
			_bOwner = bOwner;
			_thread = nullptr;
		};

		virtual ~EventTest1()
		{
		};

		void Start()
		{
			if (_bOwner)
			{
				BOOL ret = _event.Create(_T("EventTest1"), FALSE, TRUE); // 自動リセットイベント
				Assert::IsTrue(ret);
			}
			else
			{
				BOOL ret = _event.Open(_T("EventTest1"));
				Assert::IsTrue(ret);
			}

			_thread = new alt::Thread(this);
			BOOL ret = _thread->Create();
			Assert::IsTrue(ret);
		};

		HANDLE GetHandle() { return _thread->GetHandle(); };

	protected:
		virtual DWORD Invoke(LPVOID lpvParam)
		{
			Logger::WriteMessage("Thread::Invoke() called.\n");

			if (_bOwner)
			{
				Logger::WriteMessage("--- Event pulse after 5 seconds ---\n");
				Sleep(5000);
				BOOL ret = _event.Pulse();
				Logger::WriteMessage("--- Event pulsed ---\n");
				Assert::IsTrue(ret);
			}
			else
			{
				DWORD dwRet = _event.Wait();
				Logger::WriteMessage("--- Event received ---\n");
				Assert::AreEqual(WAIT_OBJECT_0, dwRet);
			}

			Logger::WriteMessage("Thread::Invoke() stopped.\n");
			return 0;
		};

	private:
		alt::Thread* _thread;
		alt::Event _event;
		BOOL _bOwner;
	};

	//! @class	EventTest2
	//! @brief	手動リセットイベントテストクラス
	class EventTest2 : public alt::skeleton::ICallback
	{
	public:
		EventTest2(BOOL bOwner)
		{
			_bOwner = bOwner;
			_thread = nullptr;
		};

		virtual ~EventTest2()
		{
		};

		void Start()
		{
			if (_bOwner)
			{
				BOOL ret = _event.Create(_T("EventTest2"), TRUE, FALSE); // 手動リセットイベント
				Assert::IsTrue(ret);
			}
			else
			{
				BOOL ret = _event.Open(_T("EventTest2"));
				Assert::IsTrue(ret);
			}

			_thread = new alt::Thread(this);
			BOOL ret = _thread->Create();
			Assert::IsTrue(ret);
		};

		HANDLE GetHandle() { return _thread->GetHandle(); };

	protected:
		virtual DWORD Invoke(LPVOID lpvParam)
		{
			Logger::WriteMessage("Thread::Invoke() called.\n");

			BOOL ret;
			int iLoopCount = (_bOwner ? 5 : 20);
			for (int i = 0; i < iLoopCount; i++)
			{
				if (_bOwner)
				{
					Logger::WriteMessage("--- Event set after 5 seconds ---\n");

					Sleep(2000);
					ret = _event.Set();
					Logger::WriteMessage("--- Event set ---\n");
					Assert::IsTrue(ret);

					Sleep(2000);
					ret = _event.Reset();
					Logger::WriteMessage("--- Event reset ---\n");
					Assert::IsTrue(ret);
				}
				else
				{
					DWORD dwRet = _event.Wait();
					Logger::WriteMessage("--- Event received ---\n");
					Assert::AreEqual(WAIT_OBJECT_0, dwRet);
					Sleep(500);
				}
			}

			if (_bOwner)
			{
				ret = _event.Set();
				Assert::IsTrue(ret);
			}

			Logger::WriteMessage("Thread::Invoke() stopped.\n");
			return 0;
		};

	private:
		alt::Thread* _thread;
		alt::Event _event;
		BOOL _bOwner;
	};

	TEST_CLASS(EventTest)
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

		TEST_METHOD(EventTest1)
		{
			Logger::WriteMessage("EventTest1 Start.\n");

			WindowsLibraryTest::EventTest1 eventTestSender(TRUE);
			WindowsLibraryTest::EventTest1 eventTestReceiver1(FALSE);
			WindowsLibraryTest::EventTest1 eventTestReceiver2(FALSE);

			eventTestSender.Start();
			eventTestReceiver1.Start();
			eventTestReceiver2.Start();

			HANDLE hThreads[3];
			hThreads[0] = eventTestSender.GetHandle();
			hThreads[1] = eventTestReceiver1.GetHandle();
			hThreads[2] = eventTestReceiver2.GetHandle();

			WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);

			Logger::WriteMessage("EventTest1 stopped.\n");
		}

		TEST_METHOD(EventTest2)
		{
			Logger::WriteMessage("EventTest2 Start.\n");

			WindowsLibraryTest::EventTest2 eventTestSender(TRUE);
			WindowsLibraryTest::EventTest2 eventTestReceiver1(FALSE);
			WindowsLibraryTest::EventTest2 eventTestReceiver2(FALSE);

			eventTestSender.Start();
			eventTestReceiver1.Start();
			eventTestReceiver2.Start();

			HANDLE hThreads[3];
			hThreads[0] = eventTestSender.GetHandle();
			hThreads[1] = eventTestReceiver1.GetHandle();
			hThreads[2] = eventTestReceiver2.GetHandle();

			WaitForMultipleObjects(3, hThreads, TRUE, INFINITE);

			Logger::WriteMessage("EventTest2 stopped.\n");
		}
	};
}