/**
 @file		Logger.cpp
 @brief		ƒƒO‚ÉŠÖ‚·‚éƒNƒ‰ƒX
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#include "pch.h"
#include "Logger.h"

using namespace alt;

Logger* Logger::_instance;
Console* Logger::_console;
LogFile* Logger::_log;

Logger::Logger()
	:WindowsLibrary()
{
}

Logger::Logger(const Logger&)
{

}

Logger& Logger::operator = (const Logger&)
{
	return *this;
}

Logger::~Logger()
{
}

void Logger::Log(LPCTSTR lpctszMessage)
{

}

void Logger::init()
{
	if (_instance == nullptr)
	{
		_instance = new Logger();
		_console = new Console();
		_console->Create();
		_console->Init();
		_log = new LogFile(alt::LogLevel::Info, _T("TEST"), 10, 100 * 10);
	}
}

void Logger::error(TString& message)
{
	_console->Write(message.Ctr());
	OutputDebugString(message.Ctr());
	_log->LogError(message.Ctr());
}

void Logger::warn(TString& message)
{
	_console->Write(message.Ctr());
	OutputDebugString(message.Ctr());
	_log->LogWarn(message.Ctr());
}

void Logger::info(TString& message)
{
	_console->Write(message.Ctr());
	OutputDebugString(message.Ctr());
	_log->LogInfo(message.Ctr());
}

void Logger::debug(TString& message)
{
	_console->Write(message.Ctr());
	OutputDebugString(message.Ctr());
	_log->LogDebug(message.Ctr());
}

void Logger::trace(TString& message)
{
	_console->Write(message.Ctr());
	OutputDebugString(message.Ctr());
	_log->LogTrace(message.Ctr());
}