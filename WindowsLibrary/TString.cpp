/**
 @file		TString.cpp
 @brief		文字列に関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#include "pch.h"
#include "TString.h"

using namespace alt;

TString::TString()
{
	_lptszString = nullptr;
}

TString::TString(LPCTSTR lpctszString)
	:TString()
{
	this->Copy(lpctszString);
}

TString::TString(const TString& string)
	: TString()
{
	this->Copy(string.Ptr());
}

TString::TString(int length)
{
	_lptszString = new TCHAR[length + sizeof(TCHAR)];
	ZeroMemory(_lptszString, length + sizeof(TCHAR));
}

TString::~TString()
{
	if (!_lptszString) delete[] _lptszString;
}

BOOL TString::operator == (LPCTSTR lpctszString)
{
	if (_lptszString == nullptr && lpctszString == nullptr) return TRUE;
	if (_lptszString == nullptr || lpctszString == nullptr) return FALSE;

	int result = lstrcmp(lpctszString, _lptszString);

	return result == 0 ? TRUE : FALSE;
}

BOOL TString::operator == (const TString& string)
{
	int result = lstrcmp(string.Ctr(), _lptszString);

	return result == 0 ? TRUE : FALSE;
}

BOOL TString::operator != (LPCTSTR lpctszString)
{
	return !this->operator==(lpctszString);
}

BOOL TString::operator != (const TString& string)
{
	return !this->operator==(string);
}

VOID TString::operator = (LPCTSTR lpctszString)
{
	this->Copy(lpctszString);
}

VOID TString::operator = (const TString& string)
{
	this->Copy(string.Ptr());
}

TString& TString::operator << (LPCTSTR lpctszString)
{
	this->Add(lpctszString);

	return *this;
}

TString& TString::operator << (const TString& string)
{
	this->Add(string.Ptr());

	return *this;
}

TString& TString::operator << (const int iValue)
{
	// UINT64_MAX 18446744073709551615
	TCHAR tszBuf[22];
	wsprintf(tszBuf, _T("%d"), iValue);
	this->Add(tszBuf);

	return *this;
}

TString TString::operator + (LPCTSTR lpctszString)
{
	TString string(_lptszString);
	string += lpctszString;

	return string;
}

TString TString::operator + (TString& string)
{
	TString baseString(_lptszString);
	baseString += string;

	return baseString;
}

TString& TString::operator += (LPCTSTR lpctszString)
{
	this->Add(lpctszString);

	return *this;
}

TString& TString::operator += (const TString& string)
{
	this->Add(string.Ptr());

	return *this;
}

bool TString::operator < (const TString& string) const
{
	int response = lstrcmp(this->_lptszString, string.Ctr());
	return response < 0 ? true : false;
};

TCHAR TString::operator [] (int index) const
{
	TCHAR ret;

	if (index <= this->Len())
	{
		ret = _lptszString[index];
	}
	else
	{
		ret = '\0';
	}

	return ret;
}

TString& TString::TrimLeft()
{
	int iStartPos = 0;
	int iLen = this->Len();

	for (int i = 0; i < iLen; i++)
	{
		if (_lptszString[i] != ' ')
		{
			iStartPos = i;
			break;
		}
	}

	for (int i = 0; i < (iLen - iStartPos); i++)
	{
		_lptszString[i] = _lptszString[i + iStartPos];
	}

	_lptszString[(iLen - iStartPos)] = 0;

	return *this;
}

TString& TString::TrimRight()
{
	int iStartPos = 0;
	int iLen = this->Len();

	for (int i = (iLen - 1); i >= 0; i--)
	{
		if (_lptszString[i] != ' ')
		{
			iStartPos = i;
			break;
		}
	}

	for (int i = (iLen - 1); i > iStartPos; i--)
	{
		_lptszString[i] = 0;
	}

	return *this;
}

TString& TString::Trim()
{
	this->TrimLeft();
	this->TrimRight();

	return *this;
}

TString TString::Substring(int startPos, int length)
{
	TString response1;
	int len = this->Len();
	int targetLen = startPos + length;
	if (targetLen > len || targetLen == 0) return response1;

	TString response2(length + sizeof(TCHAR));
	if (length) LPTSTR p = lstrcpyn(response2.Ptr(), &_lptszString[startPos], length + 1);
	else LPTSTR p = lstrcpyn(response2.Ptr(), &_lptszString[startPos], len - startPos + 1);

	return response2;
}

TString TString::Replace(TString& charsBefore, TString& charsAfter)
{
	int findPos = this->Find(charsBefore);
	if (findPos == -1) return *this;

	TString returnString = this->Substring(0, findPos);
	returnString += charsAfter;
	TString wordsAfter = this->Substring(findPos + charsBefore.Len());
	returnString += wordsAfter;

	return returnString;
}

TString TString::ReplaceAll(TString& charsBefore, TString& charsAfter)
{
	TString returnString;
	TString tempString = this->Ctr();

	for (;;)
	{
		int findPos = tempString.Find(charsBefore);
		if (findPos == -1) return tempString;

		returnString = tempString.Substring(0, findPos);
		returnString += charsAfter;
		TString wordsAfter = tempString.Substring(findPos + charsBefore.Len());
		returnString += wordsAfter;
		tempString = returnString;
	}

	return returnString;
}

skeleton::Array<TString> TString::Split(const TString& delimiters)
{
	int length = this->Len();
	int beginPos = 0;
	TCHAR check;
	TCHAR delimiter;
	skeleton::Array<TString> response;

	for (int i = 0; i <= length; i++) // 最後のnullまで確認する
	{
		check = _lptszString[i];
		for (int j = 0; j < delimiters.Len() + 1; j++) // delimitersも最後にnullを持っている
		{
			delimiter = delimiters[j];
			if (check == delimiter)
			{
				TString* item = new TString(i - beginPos);
				LPTSTR p = lstrcpyn(item->Ptr(), &_lptszString[beginPos], i - beginPos + 1);
				response.Add(item);
				beginPos = i + 1;
			}
		}
	}

	return response;
}

int TString::Find(TString keyword, int position)
{
	int ret = this->Compare(&_lptszString[position], keyword.Ptr(), keyword.Len());

	return ret == -1 ? -1 : ret + position;
}

TString& TString::Format(LPCTSTR format, ...)
{
	va_list args;
	int     len;

	va_start(args, format);

	len = (_vsctprintf(format, args) + 1) * sizeof(TCHAR);
	_lptszString = new TCHAR[len];

	if (_lptszString != nullptr)
	{
		_vstprintf_s(_lptszString, len, format, args);
	}

	va_end(args);

	return *this;
}

bool TString::FromSJIS(LPCSTR lpcszSJIS)
{
	// 必要サイズを取得
	DWORD dwWideSize = ::MultiByteToWideChar(
		CP_ACP, MB_PRECOMPOSED, lpcszSJIS, -1, _lptszString, 0);
	TString response(dwWideSize);

	DWORD dwResponse = ::MultiByteToWideChar(
		CP_ACP, MB_PRECOMPOSED, lpcszSJIS, -1, response.Ptr(), dwWideSize);
	*this = response;

	return dwResponse > 0 ? true : false;
}

int TString::ToSJIS(LPSTR lpszSJIS, DWORD dwLen)
{
	return ::WideCharToMultiByte(
		CP_ACP, 0, _lptszString, -1, lpszSJIS, dwLen, nullptr, nullptr);
}

// private functions --------------------------------------------------

VOID TString::Copy(LPCTSTR lpctszString)
{
	if (lpctszString)
	{
		DWORD dwLen = lstrlen(lpctszString);
		if (_lptszString)
		{
			delete _lptszString;
		}
		_lptszString = new TCHAR[dwLen + sizeof(TCHAR)];
		lstrcpy(_lptszString, lpctszString);
	}
}

VOID TString::Add(LPCTSTR lpctszString)
{
	if (lpctszString)
	{
		int length = this->Len() + lstrlen(lpctszString) + sizeof(TCHAR);
		PTCHAR ptszNewBuffer = new TCHAR[length];
		ZeroMemory(ptszNewBuffer, length);
		if (_lptszString) lstrcat(ptszNewBuffer, _lptszString);
		if (lpctszString) lstrcat(ptszNewBuffer, lpctszString);
		delete[] _lptszString;
		_lptszString = ptszNewBuffer;
	}
}

int TString::Compare(LPCTSTR lpctszString1, LPCTSTR lpctszString2, int size)
{
	int response;
	int pos = 0;

	LPCTSTR pctszS1 = lpctszString1;
	LPCTSTR pctszS2 = lpctszString2;
	int len = size;

	do
	{
		if (*pctszS1 == *pctszS2)
		{
			len--;
			pctszS2++;
		}
		else
		{
			pos++;
		}
		pctszS1++;

	} while (*pctszS1 != '\0' && *pctszS2 != '\0' && len != 0);

	if (len == 0)
	{
		response = pos;
	}
	else
	{
		response = -1;
	}

	return response;
}