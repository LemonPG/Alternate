/**
 @file		VectorPerformanceCheck.h
 @brief		std::vector<T>性能測定用
 @author	kumakuma0421@gmail.com
 @date		2020.03.15
 */
#pragma once

#include "PerformanceCheck.h"
#include "ObjectHolder.h"
#include "WatchDogTimer.h"
#include "Console.h"

namespace PerfCheck
{
	/**
	 @class	VectorPerformanceCheck
	 @brief	std::vector<T>クラス性能測定用
	*/
	class VectorPerformanceCheck : public PerformanceCheck
	{
	public:
		VectorPerformanceCheck();
		virtual ~VectorPerformanceCheck();

		virtual BOOL DoAction();

	protected:
		virtual BOOL Core(const int param1);
	};
}