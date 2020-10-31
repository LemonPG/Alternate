/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API リファレンス
 */
#include "pch.h"
#include "NamedPipe.h"
#include "Thread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(NamedPipeTest)
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

		TEST_METHOD(CreateNamedPipeTest1)
		{
			Logger::WriteMessage("CreateNamedPipeTest1\n");

			auto serverFunc = [](LPVOID lpvParam)->DWORD
			{
				alt::NamedPipe pipe;

				BOOL ret1 = pipe.Create(_T("TEST_PIPE"));
				Assert::IsTrue(ret1);
				Logger::WriteMessage("S)NamedPipe::Create() passed.\n");

				BOOL ret2 = pipe.Connect();
				Assert::IsTrue(ret2);
				Logger::WriteMessage("S)NamedPipe::Connect() passed.\n");

				TCHAR tszBuf[MAX_PATH];
				DWORD dwRet3 = pipe.Read(tszBuf, MAX_PATH);
				Assert::AreEqual<DWORD>(6 * sizeof(TCHAR), dwRet3);
				tszBuf[20] = '\0'; // C6054対策
				Assert::AreEqual(0, lstrcmp(_T("12345"), tszBuf));
				Logger::WriteMessage("S)NamedPipe::Read() passed.\n");

				BOOL ret4 = pipe.Close();
				Logger::WriteMessage("S)NamedPipe::Close() passed.\n");

				return 0;
			};

			auto clientFunc = [](LPVOID lpvParam)->DWORD
			{
				alt::NamedPipe pipe;

				BOOL ret1 = pipe.Wait(_T("TEST_PIPE"));
				Assert::IsTrue(ret1);
				Logger::WriteMessage("C)NamedPipe::Wait() passed.\n");

				BOOL ret2 = pipe.Open(_T("TEST_PIPE"));
				Assert::IsTrue(ret2);
				Logger::WriteMessage("C)NamedPipe::Open() passed.\n");

				TCHAR tszBuf[MAX_PATH];
				wsprintf(tszBuf, _T("%s"), _T("12345"));
				DWORD dwRet3 = pipe.Write(tszBuf, 6 * sizeof(TCHAR));
				Assert::AreEqual<DWORD>(6 * sizeof(TCHAR), dwRet3);
				Logger::WriteMessage("C)NamedPipe::Write() passed.\n");

				BOOL ret4 = pipe.Close();
				Assert::IsTrue(ret4);
				Logger::WriteMessage("C)NamedPipe::Close() passed.\n");

				return 0;
			};

			alt::Thread* serverThread = new alt::Thread();
			serverThread->Create(serverFunc);

			Sleep(3000);

			alt::Thread* clientThread = new alt::Thread();
			clientThread->Create(clientFunc);

			clientThread->Wait();
			serverThread->Wait();
		}

		class ServerPipe : public alt::skeleton::ICallback
		{
		public:
			bool Create()
			{
				BOOL ret = _pipe.Create(_T("TEST_PIPE"));
				Assert::IsTrue(ret);
				Logger::WriteMessage("S)NamedPipe::Create() passed.\n");

				return ret;
			};

			bool Connect()
			{
				BOOL ret = _pipe.Connect();
				Assert::IsTrue(ret);
				Logger::WriteMessage("S)NamedPipe::Connect() passed.\n");

				return ret;
			};

			DWORD Read(LPVOID lpvBuf, DWORD dwSize)
			{
				return _pipe.Read(lpvBuf, dwSize);
			};

			DWORD Write(LPVOID lpvBuf, DWORD dwSize)
			{
				return _pipe.Write(lpvBuf, dwSize);
			};

			DWORD Invoke(LPVOID lpvParam)
			{
				BYTE byBuffer[MAX_PATH];

				for (;;)
				{
					ZeroMemory(byBuffer, MAX_PATH);
					DWORD dwSize = this->Read(byBuffer, MAX_PATH);
					if (dwSize == (DWORD)-1)
					{
						Logger::WriteMessage("Maybe disconnect.\n");
						break;
					}
					else
					{
						TCHAR tszBuf[MAX_PATH];
						wsprintf(tszBuf, _T("Server received:%s\n"), (LPCTSTR)byBuffer);
						Logger::WriteMessage(tszBuf);

					}
					this->Write(byBuffer, dwSize);
				}

				return 0;
			};

		private:
			alt::NamedPipe _pipe;
		};

		class ClientPipe : public alt::skeleton::ICallback
		{
		public:
			bool Wait()
			{
				BOOL ret = _pipe.Wait(_T("TEST_PIPE"));
				Assert::IsTrue(ret);
				Logger::WriteMessage("C)NamedPipe::Wait() passed.\n");

				return ret;
			};

			bool Open()
			{
				BOOL ret = _pipe.Open(_T("TEST_PIPE"));
				Assert::IsTrue(ret);
				Logger::WriteMessage("C)NamedPipe::Open() passed.\n");

				return ret;
			};

			DWORD Read(LPVOID lpvBuf, DWORD dwSize)
			{
				return _pipe.Read(lpvBuf, dwSize);
			};

			DWORD Write(LPVOID lpvBuf, DWORD dwSize)
			{
				return _pipe.Write(lpvBuf, dwSize);
			};

			DWORD Invoke(LPVOID lpvParam)
			{
				TCHAR tszBuffer[MAX_PATH];
				TCHAR tszFormat[MAX_PATH];

				for (int i = 0; i < 100; i++)
				{
					wsprintf(tszBuffer, _T("SERVER SEND %03d"), i);
					DWORD dwWrite = this->Write(tszBuffer, lstrlen(tszBuffer) * sizeof(TCHAR));
					
					DWORD dwRead = this->Read(tszBuffer, dwWrite);
					wsprintf(tszFormat, _T("Client received:%s\n"), tszBuffer);
					Logger::WriteMessage(tszFormat);
				}

				return 0;
			};

		private:
			alt::NamedPipe _pipe;
		};

		TEST_METHOD(CreateNamedPipeTest2)
		{
			Logger::WriteMessage("CreateNamedPipeTest2\n");

			auto serverFunc = [](LPVOID lpvParam)->DWORD
			{
				ServerPipe serverPipe;
				serverPipe.Create();
				serverPipe.Connect();

				alt::Thread thread(&serverPipe);
				thread.Create();
				thread.Wait();

				return 0;
			};

			auto clientFunc = [](LPVOID lpvParam)->DWORD
			{
				ClientPipe clientPipe;
				clientPipe.Wait();
				clientPipe.Open();

				alt::Thread thread(&clientPipe);
				thread.Create();
				thread.Wait();

				return 0;
			};

			alt::Thread* serverThread1 = new alt::Thread();
			serverThread1->Create(serverFunc);

			alt::Thread* serverThread2 = new alt::Thread();
			serverThread2->Create(serverFunc);

			// 同じパイプ名だが、インスタンスは作成可能

			Sleep(3000);

			alt::Thread* clientThread1 = new alt::Thread();
			clientThread1->Create(clientFunc);

			alt::Thread* clientThread2 = new alt::Thread();
			clientThread2->Create(clientFunc);

			// どっちのクライアントがどっちのサーバーに
			// つながったのかわからない。接続シーケンス
			// をしっかり考えないと意図しない接続と
			// なりそう。

			clientThread1->Wait();
			clientThread2->Wait();
			serverThread1->Wait();
			serverThread2->Wait();
		}
	};
}
