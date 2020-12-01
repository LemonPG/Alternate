//! @file	LogFile.cpp
//! @brief	Fileをベースとしたログに関する機能を集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#include "pch.h"
#include "LogFile.h"

using namespace alt;

LogFile::LogFile()
{
	_level = LogLevel::Trace;
	_dwCurrentWriteSize = 0;
	_sRotation = 0;
	_dwFileSize = 0;
	ZeroMemory(&_localTime, sizeof(_localTime));
}

LogFile::LogFile(LogLevel logLevel, LPCTSTR fileName, SHORT sRotation, DWORD dwFileSize)
{
	this->Init(logLevel, fileName, sRotation, dwFileSize);
}

LogFile::~LogFile()
{
	_file.Close();
}

BOOL LogFile::Init(LogLevel logLevel, LPCTSTR fileName, SHORT sRotation, DWORD dwFileSize)
{
	_level = logLevel;
	_dwCurrentWriteSize = 0;
	_baseFileName = fileName;
	_sRotation = sRotation;
	_dwFileSize = dwFileSize;

	this->FindHistory();
	return this->AppendLog();
}

BOOL LogFile::AppendLog()
{
	BOOL ret = TRUE;

	_logFileName = _baseFileName + _lpctszExtension;

	if (!alt::FileUtility::IsExist(_logFileName.Ctr()))
	{
		ret = this->CreateLog();
	}
	else
	{
		ret = this->OpenLog();
		if (ret == TRUE)
		{
			_dwCurrentWriteSize = (int)_file.GetSize();
			ret = _file.SetPointer(FILE_END);
		}
	}

	return ret;
}

BOOL LogFile::CreateLog()
{
	BOOL ret = TRUE;

	ret = _file.Create(
		_logFileName.Ctr(), GENERIC_WRITE, FILE_SHARE_READ, CREATE_ALWAYS);

	return ret;
}

BOOL LogFile::OpenLog()
{
	BOOL ret = TRUE;

	ret = _file.Create(
		_logFileName.Ctr(), GENERIC_WRITE, FILE_SHARE_READ, OPEN_EXISTING);

	return ret;
}

LPCTSTR LogFile::GetLogLevelString(LogLevel logLevel)
{
	LPCTSTR ret = _T("");

	switch (logLevel)
	{
		case LogLevel::Fatal:
			ret = _lpctszLogLevelFatal;
			break;

		case LogLevel::Error:
			ret = _lpctszLogLevelError;
			break;

		case LogLevel::Warn:
			ret = _lpctszLogLevelWarn;
			break;

		case LogLevel::Info:
			ret = _lpctszLogLevelInfo;
			break;

		case LogLevel::Debug:
			ret = _lpctszLoglevelDebug;
			break;

		case LogLevel::Trace:
			ret = _lpctszLogLevelTrace;
			break;

		default:
			break;
	}

	return ret;
}

VOID LogFile::LogWrite(LogLevel logLevel, LPCTSTR lpctszMessage, DWORD dwThreadID)
{
	_lock.Enter();

	GetLocalTime(&_localTime);
	int length = lstrlen(lpctszMessage) + 40; // ヘッダー部(余裕あり)

	LPTSTR buffer = new TCHAR[length];
	wsprintf(buffer, _format,
			 _localTime.wYear, _localTime.wMonth, _localTime.wDay,
			 _localTime.wHour, _localTime.wMinute, _localTime.wSecond,
			 _localTime.wMilliseconds, dwThreadID, this->GetLogLevelString(logLevel), lpctszMessage);
	DWORD dwWriteSize = lstrlen(buffer) * sizeof(TCHAR);
	_file.Write(buffer, dwWriteSize);
	delete[] buffer;

	_dwCurrentWriteSize += (int)dwWriteSize;
	if (_dwCurrentWriteSize >= _dwFileSize)
	{
		_file.Close();
		this->FindHistory();	// 履歴状況を確認
		this->RotateLogFile();	// ログローテーション
		this->CreateLog();		// 新ファイルを作成
		_dwCurrentWriteSize = 0;
	}

	_lock.Leave();
}

VOID LogFile::FindHistory()
{
	TString findFileName = _baseFileName + _lpctszSearchKeyword;
	auto historyFiles = FileUtility::Find(findFileName.Ctr());
	_sFileCount = static_cast<SHORT>(historyFiles.Size());
}

VOID LogFile::RotateLogFile()
{
	TString previous(MAX_PATH);
	TString current(MAX_PATH);

	if (_sFileCount == _sRotation + 1)
	{
		wsprintf(current.Ptr(), _lpctszRotationFileName, _baseFileName.Ctr(), _sRotation);
		FileUtility::Delete(current.Ptr());
		_sFileCount--;
	}

	for (int i = _sFileCount - 1; i > 0; i--)
	{
		wsprintf(previous.Ptr(), _lpctszRotationFileName, _baseFileName.Ctr(), i);
		wsprintf(current.Ptr(), _lpctszRotationFileName, _baseFileName.Ctr(), i + 1);
		FileUtility::Move(previous.Ctr(), current.Ctr());
	}

	wsprintf(previous.Ptr(), _lpctszLogFileName, _baseFileName.Ctr());
	wsprintf(current.Ptr(), _lpctszRotationFileName, _baseFileName.Ctr(), 1);
	FileUtility::Move(previous.Ctr(), current.Ctr());
}

VOID LogFile::LogFatal(LPCTSTR lpctszMessage, DWORD dwThreadID)
{
	if (_level >= LogLevel::Fatal) this->LogWrite(LogLevel::Fatal, lpctszMessage, dwThreadID);
}

VOID LogFile::LogError(LPCTSTR lpctszMessage, DWORD dwThreadID)
{
	if (_level >= LogLevel::Error) this->LogWrite(LogLevel::Error, lpctszMessage, dwThreadID);
}

VOID LogFile::LogWarn(LPCTSTR lpctszMessage, DWORD dwThreadID)
{
	if (_level >= LogLevel::Warn) this->LogWrite(LogLevel::Warn, lpctszMessage, dwThreadID);
}

VOID LogFile::LogInfo(LPCTSTR lpctszMessage, DWORD dwThreadID)
{
	if (_level >= LogLevel::Info) this->LogWrite(LogLevel::Info, lpctszMessage, dwThreadID);
}

VOID LogFile::LogDebug(LPCTSTR lpctszMessage, DWORD dwThreadID)
{
	if (_level >= LogLevel::Debug) this->LogWrite(LogLevel::Debug, lpctszMessage, dwThreadID);
}

VOID LogFile::LogTrace(LPCTSTR lpctszMessage, DWORD dwThreadID)
{
	if (_level >= LogLevel::Trace) this->LogWrite(LogLevel::Trace, lpctszMessage, dwThreadID);
}