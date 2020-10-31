/**
 @file		Process.h
 @brief		プロセスに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2020.3.31
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"
#include "Pipe.h"

namespace alt
{
	/**
	 @enum	Priority
	 @brief	プロセスの優先度設定値
	*/
	enum class Priority
	{
		Realtime = REALTIME_PRIORITY_CLASS,
		High = HIGH_PRIORITY_CLASS,
		AboveNormal = ABOVE_NORMAL_PRIORITY_CLASS,
		Normal = NORMAL_PRIORITY_CLASS,
		BelowNormal = BELOW_NORMAL_PRIORITY_CLASS,
		Idle = IDLE_PRIORITY_CLASS
	};

	/**
	 @class	Process
	 @brief	プロセスに関するWindowsAPIを集約したクラス
	 @sa https://docs.microsoft.com/en-us/windows/win32/ProcThread/creating-a-child-process-with-redirected-input-and-output
	*/
	class DLL_DECLSPEC Process : public WindowsLibrary
	{
	public:
		Process();
		virtual ~Process();

		BOOL Create(
			LPCTSTR lpctszApplicationName,
			LPTSTR lptszCommandLine,
			LPCTSTR lpctszCurrentDirectory = nullptr);
		BOOL CreateAsUser();
		BOOL CreateWithLogon();
		DWORD GetExitCode();
		BOOL Terminate();
		VOID SetWindowInfo(DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight);
		VOID SetConsoleInfo(DWORD dwX, DWORD dwY, DWORD dwWidth, DWORD dwHeight, DWORD dwXChars, DWORD dwYChars);
		VOID SetTitle(LPTSTR lptszConsoleTitle);

		HANDLE GetProcessHandle() { return _pi.hProcess; };
		HANDLE GetStdIn() { return _si.hStdInput; };
		HANDLE GetStdOut() { return _si.hStdOutput; };
		HANDLE GetStdErr() { return _si.hStdError; };
		BOOL SetPriority(Priority priority);

		DWORD Peek(LPVOID lpvBuf, DWORD dwSize);
		DWORD Read(LPVOID lpvBuf, DWORD dwSize);
		DWORD Write(LPVOID lpvBuf, DWORD dwSize);

	private:
		PROCESS_INFORMATION _pi;
		STARTUPINFO         _si;
		Pipe                _pipeRead;
		Pipe                _pipeWrite;
		Pipe                _pipeError;
		DWORD               _dwCreationFlags;
	};
}