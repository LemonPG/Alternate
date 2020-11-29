/**
 @file		PipeTest.cpp
 @brief		�p�C�v�Ɋւ���WindowsAPI���W�񂵂��N���X�̃e�X�g�N���X
 @author	kumakuma0421@gmail.com
 @date		2020.4.6
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