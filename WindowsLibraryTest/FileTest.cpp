/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API リファレンス
 */
#include "pch.h"
#include "File.h"
#include "FileUtility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define TEST_FILE _T(".\\CreateTest.txt")

namespace WindowsLibraryTest
{
	TEST_CLASS(FileTest)
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
			alt::FileUtility::Delete(TEST_FILE);
		}

		TEST_METHOD_CLEANUP(MethodCleanup)
		{
			Logger::WriteMessage("method cleanup.\n");
		}

		TEST_METHOD(CreateFileTest)
		{
			Logger::WriteMessage("CreateFileTest\n");

			BOOL ret;
			alt::File* pFile = new alt::File();
			ret = pFile->Create(TEST_FILE, GENERIC_ALL, FILE_SHARE_READ, CREATE_NEW);
			Assert::IsTrue(ret, _T("ファイルの作成に失敗しました。"));
			Assert::IsTrue(alt::FileUtility::IsExist(TEST_FILE), _T("ファイルの作成が確認できません。"));

			LPCTSTR lpctszString1 = _T("TEST TEST TEST");
			DWORD dwLen = pFile->Write(lpctszString1, static_cast<DWORD>(_tcslen(lpctszString1) * sizeof(TCHAR)));
			Assert::AreEqual<DWORD>(static_cast<DWORD>(_tcslen(lpctszString1) * sizeof(TCHAR)), dwLen, _T("ファイルの書き込みに失敗しました。"));

			ret = pFile->Flush();
			Assert::IsTrue(ret, _T("ファイルのフラッシュに失敗しました。"));

			ret = pFile->SetPointer(FILE_BEGIN);
			Assert::IsTrue(ret, _T("ファイルポインタ移動(先頭)に失敗しました。"));

			TCHAR tszBuf[256];
			DWORD dwSize = pFile->Read(tszBuf, sizeof(tszBuf));
			Assert::IsTrue(ret, _T("ファイルの読み込みに失敗しました。"));
			tszBuf[dwSize / sizeof(TCHAR)] = '\0';
			Assert::AreEqual<int>(0, _tcscmp(lpctszString1, tszBuf));

			ret = pFile->Close();
			Assert::IsTrue(ret);

			alt::FileUtility::Delete(TEST_FILE);
		}

		TEST_METHOD(OpenFileTest)
		{
			Logger::WriteMessage("OpenFileTest\n");

			BOOL ret;
			alt::File* testFile = new alt::File();
			ret = testFile->Create(TEST_FILE, GENERIC_ALL, FILE_SHARE_READ, CREATE_NEW);
			Assert::IsTrue(ret);
			delete testFile;

			alt::File* pFile = new alt::File();
			ret = pFile->Create(TEST_FILE, GENERIC_READ, FILE_SHARE_READ, OPEN_EXISTING);
			Assert::IsTrue(ret, _T("ファイルのオープンに失敗しました。"));
			delete pFile;

			alt::FileUtility::Delete(TEST_FILE);
		}
	};
}
