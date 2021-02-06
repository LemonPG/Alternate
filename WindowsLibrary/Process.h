//! @file	Process.h
//! @brief	�v���Z�X�Ɋւ���WindowsAPI���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2020.3.31

#pragma once

#include "framework.h"
#include "WindowsLibrary.h"
#include "Pipe.h"

namespace alt
{
	//! @enum	Priority
	//! @brief	�v���Z�X�̗D��x�ݒ�l
	enum class Priority
	{
		//! ���A���^�C��
		Realtime = REALTIME_PRIORITY_CLASS,

		//! �D��F�^�C���N���e�B�J��
		High = HIGH_PRIORITY_CLASS,

		//! �ʏ��菭����
		AboveNormal = ABOVE_NORMAL_PRIORITY_CLASS,

		//! �ʏ�F��ʓI�ȃv���Z�X
		Normal = NORMAL_PRIORITY_CLASS,

		//! �ʏ��菭����
		BelowNormal = BELOW_NORMAL_PRIORITY_CLASS,

		//! �A�C�h���F�V�X�e�����A�C�h����Ԃ̎��Ɏ��s�����B
		Idle = IDLE_PRIORITY_CLASS
	};

	//! @class	Process
	//! @brief	�v���Z�X�Ɋւ���WindowsAPI���W�񂵂��N���X
	//! @sa		https://docs.microsoft.com/en-us/windows/win32/ProcThread/creating-a-child-process-with-redirected-input-and-output
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