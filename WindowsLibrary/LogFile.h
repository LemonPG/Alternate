//! @file	LogFile.h
//! @brief	File���x�[�X�Ƃ������O�Ɋւ���@�\���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "framework.h"
#include "File.h"
#include "FileUtility.h"
#include "TString.h"
#include "CriticalSection.h"

namespace alt
{
	//! @enum	LogLevel
	//! @brief	���O�̏o�̓��x��
	enum class LogLevel
	{
		//! (0)�ُ�I�����x��
		Fatal,
		//! (1)�G���[
		Error,
		//! (2)�x��
		Warn,
		//! (3)���
		Info,
		//! (4)�f�o�b�O
		Debug,
		//! (5)�g���[�X
		Trace
	};

	//! @enum	LogMode
	//! @brief	�N�����̊����t�@�C���̈�����
	enum class LogMode
	{
		//! �V�K�쐬���[�h
		Create,
		//! �ǉ����[�h
		Append
	};

	//! @class	LogFile
	//! @brief	File���x�[�X�Ƃ������O�Ɋւ���@�\���W�񂵂��N���X
	class DLL_DECLSPEC LogFile : public WindowsLibrary
	{
	public:
		LogFile();
		LogFile(LogLevel logLevel, LPCTSTR fileName, SHORT sRotation, DWORD dwFileSize);
		~LogFile();

		BOOL Init(LogLevel logLevel, LPCTSTR fileName, SHORT sRotation, DWORD dwFileSize);

		VOID LogFatal(LPCTSTR message, DWORD dwThreadID = GetCurrentThreadId());
		VOID LogError(LPCTSTR message, DWORD dwThreadID = GetCurrentThreadId());
		VOID LogWarn(LPCTSTR message, DWORD dwThreadID = GetCurrentThreadId());
		VOID LogInfo(LPCTSTR message, DWORD dwThreadID = GetCurrentThreadId());
		VOID LogDebug(LPCTSTR message, DWORD dwThreadID = GetCurrentThreadId());
		VOID LogTrace(LPCTSTR message, DWORD dwThreadID = GetCurrentThreadId());


	protected:
		BOOL AppendLog();
		BOOL CreateLog();
		BOOL OpenLog();
		VOID FindHistory();
		VOID RotateLogFile();
		LPCTSTR GetLogLevelString(LogLevel logLevel);

	private:
		VOID LogWrite(LogLevel logLevel, LPCTSTR pctszMessage, DWORD dwThreadID);

		File _file;					//! ���ݏo�͒��̃��O�t�@�C��
		LogLevel _level;			//! �o�̓��O���x��
		TString _baseFileName;		//! ���O�t�@�C�����[�U�[�ݒ薼
		TString _logFileName;		//! ���O�t�@�C�����S��
		SYSTEMTIME _localTime;		//! ���O�ɏo�͂���V�X�e������
		DWORD _dwCurrentWriteSize;	//! ���݂܂łɏ�������ł��郍�O�t�@�C���T�C�Y
		SHORT _sFileCount;			//! ���݂܂łɊm�F�ł��闚���t�@�C����
		SHORT _sRotation;			//! ���O���[�e�[�V������
		DWORD _dwFileSize;			//! ���O�t�@�C���T�C�Y
		CriticalSection _lock;		//! �������ݎ����b�N
		LPCTSTR _format = _T("%04d/%02d/%02d %02d:%02d:%02d.%03d %5d %5s %s\r\n");

		LPCTSTR _lpctszExtension = _T(".log");
		LPCTSTR _lpctszLogFileName = _T("%s.log");
		LPCTSTR _lpctszSearchKeyword = _T("??.log");
		LPCTSTR _lpctszRotationFileName = _T("%s%02d.log");

		LPCTSTR _lpctszLogLevelFatal = _T("Fatal");
		LPCTSTR _lpctszLogLevelError = _T("Error");
		LPCTSTR _lpctszLogLevelWarn = _T("Warn ");
		LPCTSTR _lpctszLogLevelInfo = _T("Info ");
		LPCTSTR _lpctszLoglevelDebug = _T("Debug");
		LPCTSTR _lpctszLogLevelTrace = _T("Trace");
	};
}