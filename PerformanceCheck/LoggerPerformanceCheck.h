//! @file	LoggerPerformanceCheck.h
//! @brief	Loggerクラス性能測定用
//! @author	kumakuma0421@gmail.com
//! @date	2020.11.07

#pragma once

#include "PerformanceCheck.h"
#include "Logger.h"

namespace PerfCheck
{
	//! @class	LoggerPerformanceCheck
	//! @brief	Loggerクラス性能測定用
	class LoggerPerformanceCheck : public PerformanceCheck
	{
	public:
		LoggerPerformanceCheck();
		virtual ~LoggerPerformanceCheck();

		virtual BOOL DoAction();

	protected:
		virtual BOOL Core();
	};
}