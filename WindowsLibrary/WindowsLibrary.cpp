//! @file	WindowsLibrary.cpp
//! @brief	WindowsAPIを集約したプロジェクトファイル
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#include "pch.h"
#include "WindowsLibrary.h"

using namespace alt;

#pragma comment (linker, "/section:SharedZone,rws")
#pragma data_seg("SharedZone")
// --------------------------------------------------------------------------
namespace SharedZone
{
	// この#pragma区間はDLLを共有するEXE間で同じデータを見ることになります。
	ULONGLONG testCounter = 0;
}
// --------------------------------------------------------------------------
#pragma data_seg()

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpvReserved)
{
	switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			OutputDebugString(_T("WindowsLibrary.dll DLL_PROCESS_ATTACH.\n"));
			break;

		case DLL_THREAD_ATTACH:
			OutputDebugString(_T("WindowsLibrary.dll DLL_THREAD_ATTACH.\n"));
			break;

		case DLL_THREAD_DETACH:
			OutputDebugString(_T("WindowsLibrary.dll DLL_THREAD_DETACH.\n"));
			break;

		case DLL_PROCESS_DETACH:
			OutputDebugString(_T("WindowsLibrary.dll DLL_PROCESS_DETACH.\n"));
			break;
	}

	return TRUE;
}

DWORD WindowsLibrary::GetErrNo()
{
	return ::GetLastError();
}

HandleLibrary::HandleLibrary()
{
	_hObject = INVALID_HANDLE_VALUE;
}

HandleLibrary::~HandleLibrary()
{
	this->Close();
}

HANDLE HandleLibrary::GetHandle()
{
	return _hObject;
}

BOOL HandleLibrary::Close()
{
	BOOL ret = TRUE;

	if (_hObject != INVALID_HANDLE_VALUE)
	{
		ret = ::CloseHandle(_hObject);
		_hObject = INVALID_HANDLE_VALUE;
	}

	return ret;
}

DWORD ReadWriteHandleLibrary::Read(LPVOID lpvBuffer, DWORD dwSize)
{
	DWORD dwNumberOfBytesRead = 0;

	BOOL ret = ::ReadFile(
		_hObject,
		lpvBuffer,
		dwSize,
		&dwNumberOfBytesRead,
		nullptr);
	if (ret == FALSE)
	{
		dwNumberOfBytesRead = (DWORD)-1;
	}

	return dwNumberOfBytesRead;
}

DWORD ReadWriteHandleLibrary::Write(LPCVOID lpcvBuffer, DWORD dwSize)
{
	DWORD dwNumberOfBytesWritten = 0;

	BOOL ret = ::WriteFile(
		_hObject,
		lpcvBuffer,
		dwSize,
		&dwNumberOfBytesWritten,
		nullptr);
	if (ret == FALSE)
	{
		dwNumberOfBytesWritten = (DWORD)-1;
	}

	return dwNumberOfBytesWritten;
}

BOOL ReadWriteHandleLibrary::Flush()
{
	return ::FlushFileBuffers(_hObject);
}

DWORD WaitableHandleLibrary::Wait(DWORD dwWaitTime)
{
	return ::WaitForSingleObject(_hObject, dwWaitTime);
}

SocketLibrary::SocketLibrary()
{
	_socket = INVALID_SOCKET;
}

SocketLibrary::~SocketLibrary()
{
	this->Close();
}

int SocketLibrary::Close()
{
	int ret = TRUE;

	if (_socket != INVALID_SOCKET)
	{
		ret = ::closesocket(_socket);
		_socket = INVALID_SOCKET;
	}

	return ret;
}

DWORD SocketLibrary::GetErrNo()
{
	return ::WSAGetLastError();
}

BOOL SocketLibrary::SetKeepAliveValue(ULONG onoff, ULONG time, ULONG interval)
{
	struct tcp_keepalive keepAlive;
	keepAlive.onoff = onoff;
	keepAlive.keepalivetime = time;
	keepAlive.keepaliveinterval = interval;
	DWORD dwVal = 0;

	int ret = this->WSAIoctl(SIO_KEEPALIVE_VALS, &keepAlive, sizeof(keepAlive), nullptr, 0, &dwVal, nullptr, nullptr);

	return ret == 0 ? TRUE : FALSE;
}

int SocketLibrary::WSAIoctl(DWORD dwIoControlCode, LPVOID lpvInBuffer, DWORD dwInBuffer,
							LPVOID lpvOutBuffer, DWORD dwOutBuffer, LPDWORD lpdwBytesReturned,
							LPWSAOVERLAPPED lpOverlapped, LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine)
{
	return ::WSAIoctl(_socket, dwIoControlCode, lpvInBuffer, dwInBuffer, lpvOutBuffer,
					  dwOutBuffer, lpdwBytesReturned, lpOverlapped, lpCompletionRoutine);
}