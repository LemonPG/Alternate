/**
 @file		FileUtilityTest.cpp
 @brief		�t�@�C���n���h���𔺂�Ȃ��t�@�C��IO�Ɋւ���WindowsAPI���W�񂵂��N���X�̃e�X�g�N���X
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#include "pch.h"
#include "FileUtility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(FileUtilityTest)
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

		TEST_METHOD(FindTest)
		{
			auto response = alt::FileUtility::Find(_T(".\\*.dll"));
			for (int i = 0; i < response.Size(); i++)
			{
				Logger::WriteMessage(response[i]->Ctr());
				Logger::WriteMessage(_T("\r\n"));
			}
		}

		//TEST_METHOD(DirectoryWatchTest)
		//{
		//	const TString path(TEXT("C:\\Users\\User01\\Desktop"));
		//	FileUtility::DirectoryWatch(path.Ctr());
		//}

		// TODO:�Ǘ��Ҍ������J���҃��[�h�ɂ��Ȃ��Ǝ��s�ł��܂���B
		//TEST_METHOD(SymbolicLinkFileTest)
		//{
		//	BOOL ret;
		//	LPCTSTR lpctszBase = _T(".\\WindowsLibrary.dll");
		//	LPCTSTR lpctszTarget = _T(".\\linkBase.bin");
		//	LPCTSTR lpctszSymlink = _T(".\\linkSymbolic.bin");

		//	ret = FileUtility::Copy(lpctszBase, lpctszTarget);
		//	Assert::IsTrue(ret);
		//	ret = FileUtility::MakeSymbolicLink(lpctszTarget, lpctszSymlink);
		//	Assert::IsTrue(ret);
		//	ret = FileUtility::Delete(lpctszSymlink);
		//	Assert::IsTrue(ret);
		//	ret = FileUtility::Delete(lpctszTarget);
		//	Assert::IsTrue(ret);
		//}

		//TEST_METHOD(SymbolicLinkDirectoryTest)
		//{

		//}

		TEST_METHOD(HardLinkFileTest)
		{
			BOOL ret;
			LPCTSTR lpctszBase = _T(".\\WindowsLibrary.dll");
			LPCTSTR lpctszTarget = _T(".\\linkBase.bin");
			LPCTSTR lpctszSymlink = _T(".\\linkHard.bin");

			ret = alt::FileUtility::Copy(lpctszBase, lpctszTarget);
			Assert::IsTrue(ret);
			ret = alt::FileUtility::MakeHardLink(lpctszTarget, lpctszSymlink);
			Assert::IsTrue(ret);
			ret = alt::FileUtility::Delete(lpctszSymlink);
			Assert::IsTrue(ret);
			ret = alt::FileUtility::Delete(lpctszTarget);
			Assert::IsTrue(ret);
		}
	};
}
