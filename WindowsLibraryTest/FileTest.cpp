/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ���t�@�����X
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
			Assert::IsTrue(ret, _T("�t�@�C���̍쐬�Ɏ��s���܂����B"));
			Assert::IsTrue(alt::FileUtility::IsExist(TEST_FILE), _T("�t�@�C���̍쐬���m�F�ł��܂���B"));

			LPCTSTR lpctszString1 = _T("TEST TEST TEST");
			DWORD dwLen = pFile->Write(lpctszString1, static_cast<DWORD>(_tcslen(lpctszString1) * sizeof(TCHAR)));
			Assert::AreEqual<DWORD>(static_cast<DWORD>(_tcslen(lpctszString1) * sizeof(TCHAR)), dwLen, _T("�t�@�C���̏������݂Ɏ��s���܂����B"));

			ret = pFile->Flush();
			Assert::IsTrue(ret, _T("�t�@�C���̃t���b�V���Ɏ��s���܂����B"));

			ret = pFile->SetPointer(FILE_BEGIN);
			Assert::IsTrue(ret, _T("�t�@�C���|�C���^�ړ�(�擪)�Ɏ��s���܂����B"));

			TCHAR tszBuf[256];
			DWORD dwSize = pFile->Read(tszBuf, sizeof(tszBuf));
			Assert::IsTrue(ret, _T("�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B"));
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
			Assert::IsTrue(ret, _T("�t�@�C���̃I�[�v���Ɏ��s���܂����B"));
			delete pFile;

			alt::FileUtility::Delete(TEST_FILE);
		}
	};
}
