//! @file	RingBufferTest.cpp
//! @brief	リングバッファに関するクラスのテストクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.4

#include "pch.h"
#include "RingBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(RingBufferTest)
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

		TEST_METHOD(RingBufferTest1)
		{
			Logger::WriteMessage("RingBufferTest1\n");

			const size_t bufferSize = 32;
			const size_t chunkSize = 6;

			alt::RingBuffer ringBuffer;
			Assert::IsTrue(ringBuffer.Init(bufferSize));

			BYTE byWriteBuf[chunkSize];
			BYTE byReadBuf[chunkSize];

			for (size_t i = 0; i < 24; i++)
			{
				FillMemory(byWriteBuf, sizeof(byWriteBuf), (BYTE)(i + 'A'));

				Assert::IsTrue(ringBuffer.Write(byWriteBuf, sizeof(byWriteBuf)));
				Assert::AreEqual<size_t>(chunkSize, ringBuffer.Remain());

				ZeroMemory(byReadBuf, sizeof(byReadBuf));

				Assert::IsTrue(ringBuffer.Read(byReadBuf, sizeof(byReadBuf)));

				int cmp = memcmp(byWriteBuf, byReadBuf, chunkSize);
				Assert::AreEqual(0, cmp);
			}
		}

		TEST_METHOD(RingBufferTest2)
		{
			Logger::WriteMessage("RingBufferTest2\n");

			const size_t bufferSize = 64;
			const size_t chunkSize = 5;

			alt::RingBuffer ringBuffer;
			Assert::IsTrue(ringBuffer.Init(bufferSize));

			BYTE byWriteBuf[chunkSize];
			BYTE byReadBuf[chunkSize];
			BYTE byCheckBuf[chunkSize];

			for (int i = 0; i < 24; i++)
			{
				for (size_t j = 0; j < 5; j++)
				{
					FillMemory(byWriteBuf, sizeof(byWriteBuf), (BYTE)(i + j + '0'));
					Assert::IsTrue(ringBuffer.Write(byWriteBuf, sizeof(byWriteBuf)));
					Assert::AreEqual<size_t>(chunkSize * (j + 1), ringBuffer.Remain());
				}

				for (size_t j = 0; j < 5; j++)
				{
					ZeroMemory(byReadBuf, sizeof(byReadBuf));
					FillMemory(byCheckBuf, sizeof(byCheckBuf), (BYTE)(i + j + '0'));
					Assert::IsTrue(ringBuffer.Read(byReadBuf, sizeof(byReadBuf)));
					Assert::AreEqual<size_t>(chunkSize * (5 - (j + 1)), ringBuffer.Remain());

					int cmp = memcmp(byCheckBuf, byReadBuf, chunkSize);
					Assert::AreEqual(0, cmp);
				}
			}
		}

		TEST_METHOD(RingBufferTest3)
		{
			Logger::WriteMessage("RingBufferTest3\n");

			const size_t bufferSize = 2048;
			const size_t chunkSize = 128;

			alt::RingBuffer ringBuffer;

			Assert::IsTrue(ringBuffer.Init(bufferSize));

			BYTE byBuf[chunkSize];
			ZeroMemory(byBuf, chunkSize);

			for (size_t i = 1; i <= 16; i++)
			{
				Assert::IsTrue(ringBuffer.Write(byBuf, chunkSize), _T("not over flow\n"));
				Assert::AreEqual<size_t>(chunkSize * i, ringBuffer.Remain());
			}

			Assert::IsFalse(ringBuffer.Write(byBuf, 1), _T("over flow\n"));

			for (size_t i = 1; i <= 16; i++)
			{
				Assert::IsTrue(ringBuffer.Read(byBuf, chunkSize));
				Assert::AreEqual<size_t>(chunkSize * (16 - i), ringBuffer.Remain());
			}

			Assert::IsFalse(ringBuffer.Read(byBuf, 1));
		}
	};
}