//! @file	LogFile.h
//! @brief	Fileをベースとしたログに関する機能を集約したクラス
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
	//! @brief	ログの出力レベル
	enum class LogLevel
	{
		//! (0)異常終了レベル
		Fatal,
		//! (1)エラー
		Error,
		//! (2)警告
		Warn,
		//! (3)情報
		Info,
		//! (4)デバッグ
		Debug,
		//! (5)トレース
		Trace
	};

	//! @enum	LogMode
	//! @brief	起動時の既存ファイルの扱い方
	enum class LogMode
	{
		//! 新規作成モード
		Create,
		//! 追加モード
		Append
	};

	//! @class	LogFile
	//! @brief	Fileをベースとしたログに関する機能を集約したクラス
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

		File _file;					//! 現在出力中のログファイル
		LogLevel _level;			//! 出力ログレベル
		TString _baseFileName;		//! ログファイルユーザー設定名
		TString _logFileName;		//! ログファイル完全名
		SYSTEMTIME _localTime;		//! ログに出力するシステム時刻
		DWORD _dwCurrentWriteSize;	//! 現在までに書き込んでいるログファイルサイズ
		SHORT _sFileCount;			//! 現在までに確認できる履歴ファイル数
		SHORT _sRotation;			//! ログローテーション数
		DWORD _dwFileSize;			//! ログファイルサイズ
		CriticalSection _lock;		//! 書き込み時ロック
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