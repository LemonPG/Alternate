/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ƒŠƒtƒ@ƒŒƒ“ƒX
 */
#include "pch.h"
#include "Utility.h"
#include "File.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(UtilityTest)
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

		TEST_METHOD(CreateGUIDTest)
		{
			Logger::WriteMessage("CreateGUIDTest\n");

			for (int i = 0; i < 100; i++)
			{
				alt::TString guid = alt::Utility::MakeGUID();
				Logger::WriteMessage(guid.Ctr());
				Logger::WriteMessage(_T("\r\n"));
			}
		}

		TEST_METHOD(GetLocalTimeTest)
		{
			Logger::WriteMessage("GetLocalTimeTest\n");

			SYSTEMTIME t = alt::Utility::GetLocalTime();
		}

		TEST_METHOD(GetFormatTimeTest)
		{
			Logger::WriteMessage("GetFormatTimeTest\n");

			Logger::WriteMessage(alt::Utility::GetFormatTime(alt::Utility::GetLocalTime()).Ctr());
		}

		TEST_METHOD(GetLocalTimeQuadTest)
		{
			Logger::WriteMessage("GetLocalTimeQuadTest\n");

			auto res = alt::Utility::GetLocalTimeQuad();
			alt::TString res2;
			res2.Format(_T("%lld"), res.QuadPart);
			Logger::WriteMessage(res2.Ctr());
		}

		TEST_METHOD(GetTimeByFileTimeTest)
		{
			Logger::WriteMessage("GetTimeByFileTimeTest\n");

			auto t = alt::Utility::GetLocalTimeQuad();
			FILETIME t2;
			t2.dwLowDateTime = t.LowPart;
			t2.dwHighDateTime = t.HighPart;

			auto t3 = alt::Utility::GetTimeByFileTime(t2);
			auto t4 = alt::Utility::GetFormatTime(t3);
			Logger::WriteMessage(t4.Ctr());
		}

		TEST_METHOD(GetTemporaryPathTest)
		{
			Logger::WriteMessage("GetTemporaryPathTest\n");

			alt::TString response = alt::Utility::GetTemporaryPath();
			Logger::WriteMessage(response.Ctr());
			Logger::WriteMessage("\n");
		}

		TEST_METHOD(GetTemporaryFileNameTest)
		{
			{
				Logger::WriteMessage("GetTemporaryFileNameTest1\n");

				alt::TString response = alt::Utility::GetTemporaryFileName(
					alt::Utility::GetTemporaryPath().Ctr(),
					_T("alt"), 0);

				Logger::WriteMessage(response.Ctr());
				Logger::WriteMessage("\n");
			}

			{
				Logger::WriteMessage("GetTemporaryFileNameTest2\n");

				alt::TString response = alt::Utility::GetTemporaryFileName(
					alt::Utility::GetTemporaryPath().Ctr(),
					_T("alt"), 1);

				Logger::WriteMessage(response.Ctr());
				Logger::WriteMessage("\n");
			}

		}

		TEST_METHOD(Base64EncodeAndDecodeTest1)
		{
			Logger::WriteMessage("Base64EncodeAndDecodeTest1\n");

			BYTE byBinary[] = { 0,1,2,3,4,5,6,7,8,9,'A','B','C','D' };
			alt::TString response;

			BOOL ret = alt::Utility::Base64Encode(byBinary, sizeof(byBinary), response);
			Assert::IsTrue(ret);

			Logger::WriteMessage(response.Ctr());

			DWORD dwBuffer;
			ret = alt::Utility::Base64Decode(response, nullptr, dwBuffer);
			Assert::IsTrue(ret);

			LPBYTE lpbyBuffer = new BYTE[dwBuffer * sizeof(TCHAR)];
			ret = alt::Utility::Base64Decode(response, lpbyBuffer, dwBuffer);
			Assert::IsTrue(ret);
			for (int i = 0; i < sizeof(byBinary); i++)
			{
				Assert::AreEqual<BYTE>(byBinary[i], lpbyBuffer[i]);
			}
			delete[] lpbyBuffer;
		}

		TEST_METHOD(Base64EncodeAndDecodeTest2)
		{
			Logger::WriteMessage("Base64EncodeAndDecodeTest2\n");

			alt::File binFile;
			BOOL ret;

			ret = binFile.Create(_T("C:\\Windows\\Notepad.exe"), GENERIC_READ, 0, OPEN_EXISTING);
			Assert::IsTrue(ret);

			DWORD dwSize = (DWORD)binFile.GetSize();
			LPBYTE lpbyBinary = new BYTE[dwSize];

			DWORD dwReadSize = binFile.Read(lpbyBinary, dwSize);
			Assert::AreEqual<DWORD>(dwReadSize, dwSize);

			alt::TString response;
			ret = alt::Utility::Base64Encode(lpbyBinary, dwSize, response);
			Assert::IsTrue(ret);
			Logger::WriteMessage(response.Ctr());

			DWORD dwBuffer;
			ret = alt::Utility::Base64Decode(response, nullptr, dwBuffer);
			Assert::IsTrue(ret);

			LPBYTE lpbyBuffer = new BYTE[dwBuffer];
			ret = alt::Utility::Base64Decode(response, lpbyBuffer, dwBuffer);
			Assert::IsTrue(ret);
			for (DWORD i = 0; i < dwSize; i++)
			{
				Assert::AreEqual<BYTE>(lpbyBinary[i], lpbyBuffer[i]);
			}

			delete[] lpbyBuffer;
			delete[] lpbyBinary;
		}

		TEST_METHOD(GetEnvironmentsTest)
		{
			Logger::WriteMessage("GetEnvironmentsTest\n");

			auto ret = alt::Utility::GetEnvironments();
			for (auto item : ret)
			{
				Logger::WriteMessage(item.Ctr());
				Logger::WriteMessage(_T("\n"));
			}
		}

		TEST_METHOD(GetEnvTest)
		{
			Logger::WriteMessage("GetEnvTest\n");

			auto ret = alt::Utility::GetEnv(_T("PATH"));
			auto ret2 = ret.Split(alt::TString(_T(";")));
			for (auto item : ret2)
			{
				Logger::WriteMessage(item.Ctr());
				Logger::WriteMessage(_T("\n"));
			}

			auto ret3 = alt::Utility::GetEnv(_T("SolutionDir"));
			Assert::IsTrue(ret3.Len() == 0);
		}
	};
}