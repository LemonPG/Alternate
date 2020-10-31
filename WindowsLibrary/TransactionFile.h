/**
 @file		TransactionFile.h
 @brief		�g�����U�N�V����NTFS�Ɋւ���N���X
 @author	kumakuma0421@gmail.com
 @date		2020.3.27
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"
#include "File.h"

namespace alt
{
	/**
	 @class	TransactionFileUtility
	 @brief	�g�����U�N�V����NTFS�Ɋւ��郆�[�e�B���e�B�N���X
	 @sa http://s-kita.hatenablog.com/entry/20121217/1355764523
	*/
	class DLL_DECLSPEC TransactionFileUtility : public HandleLibrary
	{
	public:
		BOOL Init(LPWSTR lpwszDescription);
		BOOL Commit();
		BOOL Rollback();
		BOOL CreateFolder(LPCTSTR lpctszFolderName);
		BOOL Delete(LPCTSTR lpctszFileName);
		BOOL Copy(LPCTSTR lpctszSrcFileName, LPCTSTR lpctszDstFileName);
		BOOL Move(LPCTSTR lpctszSrcFileName, LPCTSTR lpctszDstFileName);
		BOOL MakeSymbolicLink(LPCTSTR lpctszSrcFileName, LPCTSTR lpctszLinkFileName, BOOL isFile = TRUE);
		BOOL MakeHardLink(LPCTSTR lpctszSrcFileName, LPCTSTR lpctszLinkFileName);
	};

	/**
	 @class	TransactionFile
	 @brief	�g�����U�N�V����NTFS�Ɋւ���N���X
	*/
	class DLL_DECLSPEC TransactionFile : public File
	{
	public:
		/**
		 @brief		�t�@�C�����쐬�A�I�[�v�����܂��B
		 @param[in] hTransaction �g�����U�N�V�����n���h��
		 @param[in]	pctszFilename (�쐬����t�@�C����)
		 @param[in] dwDesiredAccess {GENERIC_READ, GENERIC_WRITE, GENERIC_ALL}
		 @param[in] dwShareMod {FILE_SHARE_READ, FILE_SHARE_WRITE}
		 @param[in] dwCreationDisposition {CREATE_ALWAYS, OPEN_EXISTING}
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		*/
		BOOL Create(HANDLE hTransaction, LPCTSTR pctszFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition);
	};
}