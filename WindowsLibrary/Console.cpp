/**
 @file		Console.cpp
 @brief		コンソールに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#include "pch.h"
#include "Console.h"

using namespace alt;

Console::Console()
	:HandleLibrary()
{
	ZeroMemory(&_prevConsoleScreenBufferInfo, sizeof(_prevConsoleScreenBufferInfo));
}

Console::~Console()
{
	::SetConsoleTextAttribute(_hObject, _prevConsoleScreenBufferInfo.wAttributes);
}

BOOL Console::Create()
{
	return ::AllocConsole();
}

BOOL Console::Init()
{
	BOOL response = FALSE;

	_hObject = ::GetStdHandle(STD_OUTPUT_HANDLE);
	if (_hObject != INVALID_HANDLE_VALUE)
	{
		response = this->GetScreenBufferInfo(_prevConsoleScreenBufferInfo);
		if (response != FALSE)
		{
			response = this->SetColor(ForeColor::White, BackColor::Black);
		}
	}

	return response;
}

BOOL Console::SetColor(ForeColor foreColor, BackColor backColor)
{
	WORD wAttribute = static_cast<int>(foreColor) | static_cast<int>(backColor);
	return ::SetConsoleTextAttribute(_hObject, wAttribute);
}

DWORD Console::Write(LPCTSTR lpctszString)
{
	DWORD dwWritten;
	BOOL ret = ::WriteConsole(_hObject, lpctszString, lstrlen(lpctszString), &dwWritten, nullptr);
	return dwWritten;
}

VOID Console::Format(LPCTSTR format, ...)
{
	va_list args;
	int len;
	TCHAR* ptszString;

	va_start(args, format);

	len = (_vsctprintf(format, args) + 1) * sizeof(TCHAR);
	ptszString = new TCHAR[len];

	if (ptszString != nullptr)
	{
		_vstprintf_s(ptszString, len, format, args);
	}

	this->Write(ptszString);
	delete[] ptszString;

	va_end(args);
}

BOOL Console::SetTitle(LPCTSTR lpctszTitle)
{
	return ::SetConsoleTitle(lpctszTitle);
}

BOOL Console::SetCursorPosition(SHORT x, SHORT y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	return ::SetConsoleCursorPosition(_hObject, coord);
}

BOOL Console::SetBufferSize(SHORT x, SHORT y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	DWORD dwNumbberOfCharsWritten;

	::WriteConsoleOutputCharacter(_hObject, _T(" "), sizeof(TCHAR), coord, &dwNumbberOfCharsWritten);
	return ::SetConsoleScreenBufferSize(_hObject, coord);
}

BOOL Console::SetWindowInfo(SHORT width, SHORT height)
{
	SMALL_RECT rect;
	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = height - 1;
	rect.Right = width - 1;

	return ::SetConsoleWindowInfo(_hObject, TRUE, &rect);
}

VOID Console::Clear()
{
	BOOL ret;
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	do
	{
		ret = this->GetScreenBufferInfo(csbi);
		if (!ret) break;
		DWORD dwSize = csbi.dwSize.X * csbi.dwSize.Y;

		COORD coord = { 0, 0 };
		DWORD dwWritten;
		ret = FillConsoleOutputCharacter(
			_hObject, (TCHAR)' ', dwSize, coord, &dwWritten);
		if (!ret) break;

		ret = this->GetScreenBufferInfo(csbi);
		if (!ret) break;

		ret = FillConsoleOutputAttribute(
			_hObject, csbi.wAttributes, dwSize, coord, &dwWritten);
		if (!ret) break;

		ret = this->SetCursorPosition(0, 0);
	} while (false);
}

// private functions --------------------------------------------------

BOOL Console::GetScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO& csbi)
{
	return ::GetConsoleScreenBufferInfo(_hObject, &csbi);
}