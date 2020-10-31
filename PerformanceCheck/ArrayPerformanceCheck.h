/**
 @file		ArrayPerformanceCheck.h
 @brief		Array�N���X���\����p
 @author	kumakuma0421@gmail.com
 @date		2020.03.15
 */
#pragma once

#include "PerformanceCheck.h"
#include "ObjectHolder.h"
#include "Utility.h"
#include "WatchDogTimer.h"
#include "Console.h"

namespace PerfCheck
{
	/**
	 @class	ArrayPerformanceCheck
	 @brief	Array�N���X���\����p
	*/
	class ArrayPerformanceCheck : public PerformanceCheck
	{
	public:
		ArrayPerformanceCheck();
		virtual ~ArrayPerformanceCheck();

		virtual BOOL Init(alt::Console& console);
		virtual BOOL DoAction();

	protected:
		virtual BOOL Core();
	};
}