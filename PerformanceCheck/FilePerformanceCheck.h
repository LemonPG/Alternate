/**
 @file		FilePerformanceCheck.h
 @brief		File�N���X���\����p
 @author	kumakuma0421@gmail.com
 @date		2020.03.15
 */
#pragma once

#include "PerformanceCheck.h"
#include "File.h"
#include "WatchDogTimer.h"
#include "Console.h"

namespace PerfCheck
{
	/**
	 @class	FilePerformanceCheck
	 @brief	File�N���X���\����p
	*/
	class FilePerformanceCheck : public PerformanceCheck
	{
	public:
		FilePerformanceCheck();
		virtual ~FilePerformanceCheck();

		virtual BOOL Init(alt::Console& console);
		virtual BOOL DoAction();

	protected:
		virtual BOOL Core(const int param1);
		virtual BOOL Core1(const int param1);
		virtual BOOL Core2(const int param1);

		size_t _maxFileSize;
	};
}