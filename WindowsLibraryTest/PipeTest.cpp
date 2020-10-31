/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ƒŠƒtƒ@ƒŒƒ“ƒX
 */
#include "pch.h"
#include "Pipe.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(PipeTest)
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

		TEST_METHOD(PipeTest1)
		{
			alt::Pipe pipe;
			
			Assert::IsTrue(pipe.Create());

			CHAR szBuf[256];
			FillMemory(szBuf, sizeof(szBuf), 'A');

			Assert::IsTrue(pipe.Write(szBuf, sizeof(szBuf)));
			
			ZeroMemory(szBuf, sizeof(szBuf));
			Assert::AreEqual<DWORD>(sizeof(szBuf), pipe.Peek(szBuf, sizeof(szBuf)));
			Assert::AreEqual<DWORD>(sizeof(szBuf), pipe.Read(szBuf, sizeof(szBuf)));
			Logger::WriteMessage(szBuf);

			Assert::IsTrue(pipe.Close());
		}

		TEST_METHOD(PipeTest2)
		{
			alt::Pipe pipe;

			Assert::IsTrue(pipe.Create());

			CHAR szBuf[256];
			ZeroMemory(szBuf, sizeof(szBuf));

			Assert::AreEqual<DWORD>(0, pipe.Peek(szBuf, sizeof(szBuf)));

			Assert::IsTrue(pipe.Close());
		}
	};
}