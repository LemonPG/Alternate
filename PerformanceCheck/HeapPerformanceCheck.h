//! @file	HeapPerformanceCheck.h
//! @brief	HeapMemory�N���X���\����p
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.11

#pragma once

#include "PerformanceCheck.h"
#include "WatchDogTimer.h"
#include "HeapMemory.h"
#include "Thread.h"
#include "Event.h"

namespace PerfCheck
{
	//! @class	HeapPerformanceCheck
	//! @brief	HeapMemory�N���X���\����p
	class HeapPerformanceCheck : public PerformanceCheck
	{
	public:
		HeapPerformanceCheck();
		virtual ~HeapPerformanceCheck();

		virtual BOOL DoAction();

		int _allocSize[10] = { 128,256,512,1024,2048,4096,8192,16384,32768,65536 };
		int _loop = 0;

	protected:
		virtual BOOL Core(const int param1);
	};
}