//! @file	LoggerPerformanceCheck.h
//! @brief	Logger�N���X���\����p
//! @author	kumakuma0421@gmail.com
//! @date	2020.11.07

#pragma once

#include "PerformanceCheck.h"
#include "Logger.h"

namespace PerfCheck
{
	//! @class	LoggerPerformanceCheck
	//! @brief	Logger�N���X���\����p
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