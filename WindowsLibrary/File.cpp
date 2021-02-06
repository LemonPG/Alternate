//! @file	File.cpp
//! @brief	ファイルIOに関するWindowsAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#include "pch.h"
#include "File.h"

using namespace alt;

BOOL File::Create(LPCTSTR lpctszFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition)
{
	BOOL ret = TRUE;
	PSECURITY_ATTRIBUTES pSecurityAttributes = nullptr;
	DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL;
	HANDLE hTemplateFile = nullptr;

	_hObject = ::CreateFile(
		lpctszFileName,
		dwDesiredAccess,
		dwShareMode,
		pSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile);
	if (_hObject == INVALID_HANDLE_VALUE)
	{
		ret = FALSE;
	}

	return ret;
}

BOOL File::SetPointer(DWORD dwMoveMethod, LARGE_INTEGER liDistanceToMove)
{
	return ::SetFilePointerEx(
		_hObject,
		liDistanceToMove,
		nullptr,
		dwMoveMethod);
}

BOOL File::SetEOF()
{
	return ::SetEndOfFile(_hObject);
}

LONGLONG File::GetSize()
{
	LARGE_INTEGER liFileSize;
	LONGLONG response;

	BOOL ret = ::GetFileSizeEx(_hObject, &liFileSize);
	if (ret == TRUE)
	{
		response = liFileSize.QuadPart;
	}
	else
	{
		response = (LONGLONG)-1;
	}

	return response;
}

DWORD File::GetType()
{
	return ::GetFileType(_hObject);
}