/**
 @file		Process.cpp
 @brief		プロセスに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2020.3.31
 */
#include "pch.h"
#include "Process.h"

using namespace alt;

Process::Process()
{
	ZeroMemory(&_pi, sizeof(_pi));
	ZeroMemory(&_si, sizeof(_si));
	_si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	_si.wShowWindow = SW_HIDE;
	_dwCreationFlags = NORMAL_PRIORITY_CLASS | CREATE_UNICODE_ENVIRONMENT;
}

Process::~Process()
{
	if (_si.hStdInput) CloseHandle(_si.hStdInput);
	if (_si.hStdOutput) CloseHandle(_si.hStdOutput);
	if (_si.hStdError) CloseHandle(_si.hStdError);
	if (_pi.hProcess) CloseHandle(_pi.hProcess);
}

BOOL Process::Create(
	LPCTSTR lpctszApplicationName,
	LPTSTR lptszCommandLine,
	LPCTSTR lpctszCurrentDirectory)
{
	_si.cb = sizeof(STARTUPINFO);
	_si.lpReserved = nullptr;
	_si.cbReserved2 = 0;
	_si.lpReserved2 = nullptr;

	_pipeRead.Create();
	_pipeWrite.Create();
	_pipeError.Create();
	_si.hStdInput = _pipeWrite.GetReadHandle();
	_si.hStdOutput = _pipeRead.GetWriteHandle();
	_si.hStdError = _pipeRead.GetWriteHandle();

	BOOL ret = ::CreateProcess(
		lpctszApplicationName,
		lptszCommandLine,
		nullptr,
		nullptr,
		TRUE,
		_dwCreationFlags,
		nullptr,
		lpctszCurrentDirectory,
		&_si,
		&_pi);

	return ret;
}

BOOL Process::CreateAsUser()
{
	// CreateProcessAsUser()
	return FALSE;
}

BOOL Process::CreateWithLogon()
{
	// CreateProcessWithLogon()
	return FALSE;
}

DWORD Process::GetExitCode()
{
	DWORD dwRet;
	BOOL ret = ::GetExitCodeProcess(_pi.hProcess, &dwRet);

	return ret == TRUE ? dwRet : -1;
}

BOOL Process::Terminate()
{
	return ::TerminateProcess(_pi.hProcess, 0);
}

VOID Process::SetWindowInfo(DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight)
{
	_si.dwX = dwX;
	_si.dwY = dwY;
	_si.dwXSize = dwWidth;
	_si.dwYSize = dwHeight;
	_si.dwFlags = STARTF_USEPOSITION;
	_si.dwFlags |= STARTF_USESIZE;
}

VOID Process::SetConsoleInfo(DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight, DWORD dwXChars, DWORD dwYChars)
{
	_si.dwX = dwX;
	_si.dwY = dwY;
	_si.dwXSize = dwWidth;
	_si.dwYSize = dwHeight;
	_si.dwXCountChars = dwXChars;
	_si.dwYCountChars = dwYChars;
	_si.dwFlags = STARTF_USECOUNTCHARS | STARTF_USESTDHANDLES;

	_dwCreationFlags |= CREATE_NEW_CONSOLE;
}

VOID Process::SetTitle(LPTSTR lptszConsoleTitle)
{
	_si.lpTitle = lptszConsoleTitle;
}

BOOL Process::SetPriority(Priority priority)
{
	return ::SetPriorityClass(GetProcessHandle(), (DWORD)priority);
}

DWORD Process::Peek(LPVOID lpvBuf, DWORD dwSize)
{
	return _pipeRead.Peek(lpvBuf, dwSize);
}

DWORD Process::Read(LPVOID lpvBuf, DWORD dwSize)
{
	return _pipeRead.Read(lpvBuf, dwSize);
}

DWORD Process::Write(LPVOID lpvBuf, DWORD dwSize)
{
	return _pipeWrite.Write(lpvBuf, dwSize);
}