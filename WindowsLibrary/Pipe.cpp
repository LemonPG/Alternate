/**
 @file		Pipe.cpp
 @brief		�p�C�v�Ɋւ���WindowsAPI���W�񂵂��N���X
 @author	kumakuma0421@gmail.com
 @date		2020.4.6
 */
#include "pch.h"
#include "Pipe.h"

using namespace alt;

Pipe::Pipe()
{
	_hRead = INVALID_HANDLE_VALUE;
	_hWrite = INVALID_HANDLE_VALUE;
}

Pipe::~Pipe()
{
	this->Close();
}

BOOL Pipe::Create()
{
	SECURITY_ATTRIBUTES sa;
	sa.nLength = sizeof(SECURITY_ATTRIBUTES);
	sa.bInheritHandle = TRUE;
	sa.lpSecurityDescriptor = nullptr;

	return ::CreatePipe(&_hRead, &_hWrite, &sa, 0);

}

DWORD Pipe::Peek(LPVOID lpvBuf, DWORD dwSize)
{
	DWORD dwReadSize;
	DWORD dwAvail;
	DWORD dwLeft;

	BOOL ret = ::PeekNamedPipe(_hRead, lpvBuf, dwSize, &dwReadSize, &dwAvail, &dwLeft);
	return ret == TRUE ? dwReadSize : -1;
}

DWORD Pipe::Read(LPVOID lpvBuf, DWORD dwSize)
{
	DWORD dwReadSize;

	BOOL ret = ReadFile(_hRead, lpvBuf, dwSize, &dwReadSize, nullptr);
	return ret == TRUE ? dwReadSize : -1;
}

BOOL Pipe::Write(LPVOID lpvBuf, DWORD dwSize)
{
	DWORD dwWrittenSize;

	BOOL ret = WriteFile(_hWrite, lpvBuf, dwSize, &dwWrittenSize, nullptr);
	return ret == TRUE ? dwWrittenSize : -1;
}

BOOL Pipe::Close()
{
	BOOL ret1 = ::CloseHandle(_hRead);
	_hRead = INVALID_HANDLE_VALUE;
	BOOL ret2 = ::CloseHandle(_hWrite);
	_hWrite = INVALID_HANDLE_VALUE;

	return ret1 == TRUE && ret2 == TRUE ? TRUE : FALSE;
}