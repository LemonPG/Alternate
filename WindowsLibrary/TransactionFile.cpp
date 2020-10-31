/**
 @file		TransactionFile.cpp
 @brief		トランザクションNTFSに関するクラス
 @author	kumakuma0421@gmail.com
 @date		2020.3.27
 */
#include "pch.h"
#include "TransactionFile.h"

using namespace alt;

// -- TransactionFileUtility ------------------------------------------------

BOOL TransactionFileUtility::Init(LPWSTR lpwszDescription)
{
	DWORD dwOption = 0;

	_hObject = ::CreateTransaction(
		nullptr,
		0,
		dwOption,
		0,
		0,
		INFINITE,
		lpwszDescription);

	return _hObject == INVALID_HANDLE_VALUE ? FALSE : TRUE;
}

BOOL TransactionFileUtility::Commit()
{
	return ::CommitTransaction(_hObject);
}

BOOL TransactionFileUtility::Rollback()
{
	return ::RollbackTransaction(_hObject);
}

BOOL TransactionFileUtility::CreateFolder(LPCTSTR lpctszFolderName)
{
	return ::CreateDirectoryTransacted(
		nullptr,
		lpctszFolderName,
		nullptr,
		_hObject);
}

BOOL TransactionFileUtility::Delete(LPCTSTR lpctszFileName)
{
	return ::DeleteFileTransacted(lpctszFileName, _hObject);
}

BOOL TransactionFileUtility::Copy(LPCTSTR lpctszSrcFileName, LPCTSTR lpctszDstFileName)
{
	DWORD dwFlags = COPY_FILE_FAIL_IF_EXISTS;

	return ::CopyFileTransacted(
		lpctszSrcFileName,
		lpctszDstFileName,
		nullptr,
		nullptr,
		nullptr,
		dwFlags,
		_hObject);
}

BOOL TransactionFileUtility::Move(LPCTSTR lpctszSrcFileName, LPCTSTR lpctszDstFileName)
{
	DWORD dwFlags = MOVEFILE_REPLACE_EXISTING;

	return ::MoveFileTransacted(
		lpctszSrcFileName,
		lpctszDstFileName,
		nullptr,
		nullptr,
		dwFlags,
		_hObject);
}

BOOL TransactionFileUtility::MakeSymbolicLink(LPCTSTR lpctszSrcFileName, LPCTSTR lpctszLinkFileName, BOOL isFile)
{
	DWORD dwFlags = isFile == TRUE ? 0 : SYMBOLIC_LINK_FLAG_DIRECTORY;
	dwFlags |= SYMBOLIC_LINK_FLAG_ALLOW_UNPRIVILEGED_CREATE;

	return ::CreateSymbolicLinkTransacted(
		lpctszLinkFileName,
		lpctszSrcFileName,
		dwFlags,
		_hObject);
}

BOOL TransactionFileUtility::MakeHardLink(LPCTSTR lpctszSrcFileName, LPCTSTR lpctszLinkFileName)
{
	return ::CreateHardLinkTransacted(
		lpctszLinkFileName,
		lpctszSrcFileName,
		nullptr,
		_hObject);
}

// -- TransactionFile ------------------------------------------------

BOOL TransactionFile::Create(HANDLE hTransaction, LPCTSTR pctszFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition)
{
	PSECURITY_ATTRIBUTES pSecurityAttributes = nullptr;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	HANDLE hTemplateFile = nullptr;

	_hObject = ::CreateFileTransacted(
		pctszFileName,
		dwDesiredAccess,
		dwShareMode,
		pSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile,
		hTransaction,
		nullptr,
		nullptr);

	return _hObject == INVALID_HANDLE_VALUE ? FALSE : TRUE;
}
