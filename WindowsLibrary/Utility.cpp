/**
 @file		Utility.cpp
 @brief		汎用的に使えるユーティリティクラス
 @author	kumakuma0421@gmail.com
 @date		2020.2.24
 */

#include "pch.h"
#include "Utility.h"

using namespace alt;

const GUID Utility::CreateGUID()
{
	GUID guid;

	HRESULT res = ::CoCreateGuid(&guid);

	return guid;
}

const TString Utility::MakeGUID()
{
	GUID guid = CreateGUID();

	TString ret;
	// xxxxxxxx-xxxx-xxxx-xxxx-xxxxxxxxxxxx
	ret.Format(_T("%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X%02X%02X"),
		guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2],
		guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);

	return ret;
}

SYSTEMTIME Utility::GetLocalTime()
{
	SYSTEMTIME systemTime;
	::GetLocalTime(&systemTime);
	return systemTime;
}

TString Utility::GetFormatTime(SYSTEMTIME& systemTime)
{
	TString response;
	response.Format(_T("%04d/%02d/%02d %02d:%02d:%02d.%03d"),
		systemTime.wYear, systemTime.wMonth, systemTime.wDay,
		systemTime.wHour, systemTime.wMinute, systemTime.wSecond,
		systemTime.wMilliseconds);

	return response;
}

ULARGE_INTEGER Utility::GetLocalTimeQuad()
{
	SYSTEMTIME systemTime = Utility::GetLocalTime();

	FILETIME fileTime;
	BOOL ret = ::SystemTimeToFileTime(&systemTime, &fileTime);

	ULARGE_INTEGER response{ 0, 0 };

	if (ret)
	{
		response.HighPart = fileTime.dwHighDateTime;
		response.LowPart = fileTime.dwLowDateTime;
	}

	return response;
}

SYSTEMTIME Utility::GetTimeByFileTime(FILETIME& fileTime)
{
	SYSTEMTIME localTime{ 0, 0, 0, 0, 0, 0, 0, 0 };

	::FileTimeToSystemTime(&fileTime, &localTime);

	return localTime;
}

TString Utility::GetTemporaryPath()
{
	TString response(MAX_PATH);
	GetTempPath(MAX_PATH, response.Ptr());
	return response;
}

TString Utility::GetTemporaryFileName(LPCTSTR lpctszPath, LPCTSTR lpctszPrefix, UINT nNumber)
{
	TString response(MAX_PATH);
	::GetTempFileName(lpctszPath, lpctszPrefix, nNumber, response.Ptr());
	return response;
}

BOOL Utility::Base64Encode(LPBYTE lpbyString, DWORD dwLength, TString& response)
{
	BOOL bResponse = FALSE;
	DWORD dwBuffer = 0;
	LPTSTR lptszBuffer;

	if (::CryptBinaryToString(lpbyString, dwLength, CRYPT_STRING_BASE64, nullptr, &dwBuffer))
	{
		lptszBuffer = new TCHAR[dwBuffer + sizeof(TCHAR)];
		if (::CryptBinaryToString(lpbyString, dwLength, CRYPT_STRING_BASE64, lptszBuffer, &dwBuffer))
		{
			response = lptszBuffer;
			bResponse = TRUE;
		}

		delete[] lptszBuffer;
	}

	return bResponse;
}

BOOL Utility::Base64Decode(TString& source, LPBYTE lpbyBuffer, DWORD& dwBuffer)
{
	BOOL bResponse = FALSE;

	if (lpbyBuffer == nullptr)
	{
		bResponse = ::CryptStringToBinary(source.Ctr(), source.Len(), CRYPT_STRING_BASE64, nullptr, &dwBuffer, nullptr, nullptr);
	}
	else
	{
		bResponse = ::CryptStringToBinary(source.Ctr(), source.Len(), CRYPT_STRING_BASE64, lpbyBuffer, &dwBuffer, nullptr, nullptr);
	}

	return bResponse;
}

// @sa https://docs.microsoft.com/ja-jp/windows/win32/procthread/changing-environment-variables#example-3
skeleton::Array<TString> Utility::GetEnvironments()
{
	skeleton::Array<TString> response;

	LPTCH lptchEnv = ::GetEnvironmentStrings();
	if (lptchEnv == nullptr) return response;

	LPTSTR lptszVariable = (LPTSTR)lptchEnv;

	while (*lptszVariable)
	{
		response.Add(new TString(lptszVariable));
		lptszVariable += (lstrlen(lptszVariable) + (size_t)1);
	}

	FreeEnvironmentStrings(lptchEnv);

	return response;
}

TString Utility::GetEnv(LPCTSTR lpctszKeyword)
{
	DWORD dwRet;
	TString enpty;

	dwRet = ::GetEnvironmentVariable(lpctszKeyword, nullptr, 0);
	if (dwRet == 0) return enpty;

	TString response(dwRet);
	::GetEnvironmentVariable(lpctszKeyword, response.Ptr(), dwRet);

	return response;
}
