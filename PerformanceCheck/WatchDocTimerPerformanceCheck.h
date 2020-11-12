/**
 @file		WatchDocTimerPerformanceCheck.h
 @brief		WatchDocTimer�N���X���\����p
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
	 @struct	WatchDogData
	 @brief     WatchDocTimer�f�[�^�ۑ��p
	*/
	typedef struct _WatchDogData
	{
		DWORD Tick;
		double Elapsed;
		SYSTEMTIME SystemTime;
		LARGE_INTEGER StartTick;
		LARGE_INTEGER StopTick;
		LARGE_INTEGER Frequency;
	} WatchDogData;

	/**
	 @class	WatchDocTimerPerformanceCheck
	 @brief	WatchDocTimer�N���X���\����p
	*/
	class WatchDocTimerPerformanceCheck : public PerformanceCheck
	{
	public:
		WatchDocTimerPerformanceCheck();
		virtual ~WatchDocTimerPerformanceCheck();

		virtual BOOL DoAction();

	protected:
		virtual BOOL Core();
	};
}