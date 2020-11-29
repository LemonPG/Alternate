/**
 @file		LoggerPerformanceCheck.cpp
 @brief		Loggerクラス性能測定用
 @author	kumakuma0421@gmail.com
 @date		2020.11.07
 */

#include "pch.h"
#include "LoggerPerformanceCheck.h"

using namespace PerfCheck;

LoggerPerformanceCheck::LoggerPerformanceCheck()
	:PerformanceCheck()
{
}

LoggerPerformanceCheck::~LoggerPerformanceCheck()
{
}

BOOL LoggerPerformanceCheck::DoAction()
{
	return this->Core();
}

BOOL LoggerPerformanceCheck::Core()
{
	alt::Logger::init();
	alt::TString message;

	message = _T("TEST ERROR MESSAGE.\n");
	alt::Logger::error(message);

	message = _T("TEST WARN MESSAGE.\n");
	alt::Logger::warn(message);

	message = _T("TEST INFO MESSAGE.\n");
	alt::Logger::info(message);

	message = _T("TEST DEBUG MESSAGE.\n");
	alt::Logger::debug(message);

	message = _T("TEST TRACE MESSAGE.\n");
	alt::Logger::trace(message);

	return TRUE;
}