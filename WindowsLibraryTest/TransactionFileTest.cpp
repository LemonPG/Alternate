//! @file	TransactionFileTest.cpp
//! @brief	トランザクションNTFSに関するAPIを集約したクラスのテストクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.3.27

#include "pch.h"
#include "TransactionFile.h"
#include "FileUtility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(TransactionFileTest)
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

		TEST_METHOD(TransactionInitializeCommitTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;

			ret = tran.Init(_T("TransactionInitializeTest"));
			Assert::IsTrue(ret);

			ret = tran.Commit();
			Assert::IsTrue(ret);
		}

		TEST_METHOD(TransactionInitializeRollbackTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;

			ret = tran.Init(_T("TransactionInitializeTest"));
			Assert::IsTrue(ret);

			ret = tran.Rollback();
			Assert::IsTrue(ret);
		}

		TEST_METHOD(TransactionCreateDirectoryTest)
		{
			BOOL ret;
			alt::TransactionFileUtility* tran = new alt::TransactionFileUtility();
			ret = tran->Init(_T("TransactionCreateDirectoryTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFolderName = _T("TranTest");
			ret = tran->CreateFolder(lpctszFolderName);
			Assert::IsTrue(ret);

			delete tran; // run destructor;

			ret = alt::FileUtility::IsExist(lpctszFolderName);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionCreateDirectoryCommitTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionCreateDirectoryCommitTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFolderName = _T("TranTest");

			ret = alt::FileUtility::IsExist(lpctszFolderName);
			if (ret)
			{
				ret = alt::FileUtility::RemoveDir(lpctszFolderName);
				Assert::IsTrue(ret);
			}

			ret = tran.CreateFolder(lpctszFolderName);
			Assert::IsTrue(ret);

			ret = tran.Commit();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFolderName);
			Assert::IsTrue(ret);
		}

		TEST_METHOD(TransactionCreateDirectoryRollbackTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionCreateDirectoryRollbackTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFolderName = _T("TranTest");

			ret = alt::FileUtility::IsExist(lpctszFolderName);
			if (ret)
			{
				ret = alt::FileUtility::RemoveDir(lpctszFolderName);
				Assert::IsTrue(ret);
			}

			ret = tran.CreateFolder(lpctszFolderName);
			Assert::IsTrue(ret);

			ret = tran.Rollback();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFolderName);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionDeleteTest)
		{
			BOOL ret;
			alt::TransactionFileUtility* tran = new alt::TransactionFileUtility();
			ret = tran->Init(_T("TransactionDeleteTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran->Delete(lpctszFileName);
			Assert::IsTrue(ret);

			delete tran; // run destructor;

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsTrue(ret);

			ret = alt::FileUtility::Delete(lpctszFileName);
			Assert::IsTrue(ret);
		}

		TEST_METHOD(TransactionDeleteCommitTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionDeleteCommitTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.Delete(lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.Commit();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionDeleteRollbackTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionDeleteRollbackTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.Delete(lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.Rollback();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsTrue(ret);
		}

		TEST_METHOD(TransactionCopyTest)
		{
			BOOL ret;
			alt::TransactionFileUtility* tran = new alt::TransactionFileUtility();
			ret = tran->Init(_T("TransactionCopyTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}

			ret = tran->Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			delete tran; // run destructor;

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionCopyCommitTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionCopyCommitTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}

			ret = tran.Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.Commit();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsTrue(ret);
		}

		TEST_METHOD(TransactionCopyRollbackTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionCopyRollbackTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}

			ret = tran.Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.Rollback();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionMoveTest)
		{
			BOOL ret;
			alt::TransactionFileUtility* tran = new alt::TransactionFileUtility();
			ret = tran->Init(_T("TransactionMoveTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			LPCTSTR lpctszFileName2 = _T("TranTest2.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}
			if (alt::FileUtility::IsExist(lpctszFileName2))
			{
				ret = alt::FileUtility::Delete(lpctszFileName2);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran->Move(lpctszFileName, lpctszFileName2);
			Assert::IsTrue(ret);

			delete tran; // run destructor;

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName2);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionMoveCommitTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionMoveCommitTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			LPCTSTR lpctszFileName2 = _T("TranTest2.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}
			if (alt::FileUtility::IsExist(lpctszFileName2))
			{
				ret = alt::FileUtility::Delete(lpctszFileName2);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.Move(lpctszFileName, lpctszFileName2);
			Assert::IsTrue(ret);

			ret = tran.Commit();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsFalse(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName2);
			Assert::IsTrue(ret);
		}

		TEST_METHOD(TransactionMoveRollbackTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionMoveRollbackTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			LPCTSTR lpctszFileName2 = _T("TranTest2.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}
			if (alt::FileUtility::IsExist(lpctszFileName2))
			{
				ret = alt::FileUtility::Delete(lpctszFileName2);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.Move(lpctszFileName, lpctszFileName2);
			Assert::IsTrue(ret);

			ret = tran.Rollback();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName2);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionMakeHardLinkTest)
		{
			BOOL ret;
			alt::TransactionFileUtility* tran = new alt::TransactionFileUtility();
			ret = tran->Init(_T("TransactionMakeHardLinkTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			LPCTSTR lpctszFileName2 = _T("TranTest2.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}
			if (alt::FileUtility::IsExist(lpctszFileName2))
			{
				ret = alt::FileUtility::Delete(lpctszFileName2);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran->MakeHardLink(lpctszFileName, lpctszFileName2);
			Assert::IsTrue(ret);

			delete tran; // run destructor;

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName2);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionMakeHardLinkCommitTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionMakeCommitTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			LPCTSTR lpctszFileName2 = _T("TranTest2.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}
			if (alt::FileUtility::IsExist(lpctszFileName2))
			{
				ret = alt::FileUtility::Delete(lpctszFileName2);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.MakeHardLink(lpctszFileName, lpctszFileName2);
			Assert::IsTrue(ret);

			ret = tran.Commit();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName2);
			Assert::IsTrue(ret);
		}

		TEST_METHOD(TransactionMakeHardLinkRollbackTest)
		{
			BOOL ret;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionMakeHardLinkRollbackTest"));
			Assert::IsTrue(ret);

			LPCTSTR lpctszFileName = _T("TranTest.bin");
			LPCTSTR lpctszFileName2 = _T("TranTest2.bin");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}
			if (alt::FileUtility::IsExist(lpctszFileName2))
			{
				ret = alt::FileUtility::Delete(lpctszFileName2);
				Assert::IsTrue(ret);
			}

			ret = alt::FileUtility::Copy(_T("WindowsLibrary.dll"), lpctszFileName);
			Assert::IsTrue(ret);

			ret = tran.MakeHardLink(lpctszFileName, lpctszFileName2);
			Assert::IsTrue(ret);

			ret = tran.Rollback();
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName);
			Assert::IsTrue(ret);

			ret = alt::FileUtility::IsExist(lpctszFileName2);
			Assert::IsFalse(ret);
		}

		TEST_METHOD(TransactionIOTest1)
		{
			BOOL ret;
			DWORD dwLen;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionIOTest1"));
			Assert::IsTrue(ret);
			LPCTSTR lpctszFileName = _T("TranTest.txt");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}

			alt::TransactionFile tranFile;
			ret = tranFile.Create(
				tran.GetHandle(),
				lpctszFileName,
				GENERIC_READ | GENERIC_WRITE, // GENERIC_ALLはNG
				0,
				CREATE_ALWAYS);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			LPCTSTR lpctszContext = _T("TEST TEST TEST");
			dwLen = tranFile.Write(lpctszContext, static_cast<DWORD>(_tcslen(lpctszContext) * sizeof(TCHAR)));
			Assert::AreEqual<size_t>(_tcslen(lpctszContext) * sizeof(TCHAR), dwLen);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			auto size = tranFile.GetSize();
			Assert::AreEqual<LONGLONG>(_tcslen(lpctszContext) * sizeof(TCHAR), size);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			ret = tranFile.SetPointer(FILE_BEGIN);
			Assert::IsTrue(ret);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			TCHAR tszBuf[256];
			dwLen = tranFile.Read(tszBuf, sizeof(tszBuf));
			tszBuf[dwLen / sizeof(TCHAR)] = '\0';
			Assert::AreEqual<DWORD>(static_cast<DWORD>(_tcslen(lpctszContext) * sizeof(TCHAR)), dwLen);
			Assert::AreEqual<int>(0, _tcscmp(lpctszContext, tszBuf));

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			ret = tranFile.Flush();
			Assert::IsTrue(ret);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			ret = tranFile.Close();
			Assert::IsTrue(ret);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			ret = tran.Commit();
			Assert::IsTrue(ret);

			Assert::IsTrue(alt::FileUtility::IsExist(lpctszFileName));
		}

		TEST_METHOD(TransactionIOTest2)
		{
			BOOL ret;
			DWORD dwLen;
			alt::TransactionFileUtility tran;
			ret = tran.Init(_T("TransactionIOTest2"));
			Assert::IsTrue(ret);
			LPCTSTR lpctszFileName = _T("TranTest.txt");
			if (alt::FileUtility::IsExist(lpctszFileName))
			{
				ret = alt::FileUtility::Delete(lpctszFileName);
				Assert::IsTrue(ret);
			}

			alt::TransactionFile tranFile;
			ret = tranFile.Create(
				tran.GetHandle(),
				lpctszFileName,
				GENERIC_READ | GENERIC_WRITE, // GENERIC_ALLはNG
				0,
				CREATE_ALWAYS);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			LPCTSTR lpctszContext = _T("TEST TEST TEST");
			dwLen = tranFile.Write(lpctszContext, static_cast<DWORD>(_tcslen(lpctszContext) * sizeof(TCHAR)));
			Assert::AreEqual<size_t>(_tcslen(lpctszContext) * sizeof(TCHAR), dwLen);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			LONGLONG size = tranFile.GetSize();
			Assert::AreEqual<LONGLONG>(_tcslen(lpctszContext) * sizeof(TCHAR), size);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			ret = tranFile.SetPointer(FILE_BEGIN);
			Assert::IsTrue(ret);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			TCHAR tszBuf[256];
			dwLen = tranFile.Read(tszBuf, sizeof(tszBuf));
			tszBuf[dwLen / sizeof(TCHAR)] = '\0';
			Assert::AreEqual<size_t>(_tcslen(lpctszContext) * sizeof(TCHAR), dwLen);
			Assert::AreEqual<int>(0, _tcscmp(lpctszContext, tszBuf));

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			ret = tranFile.Flush();
			Assert::IsTrue(ret);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			ret = tranFile.Close();
			Assert::IsTrue(ret);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));

			ret = tran.Rollback();
			Assert::IsTrue(ret);

			Assert::IsFalse(alt::FileUtility::IsExist(lpctszFileName));
		}
	};
}