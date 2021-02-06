//! @file	WatchDogTimer.h
//! @brief	タイマーに関するWindowsAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "WindowsLibrary.h"
#include "FunctionPointers.hpp"

namespace alt
{
	//! @class	QueryPerformance
	//! @brief	高分解能時間計測クラス
	class DLL_DECLSPEC QueryPerformance : public WindowsLibrary
	{
	public:
		//! @brief コンストラクタ
		QueryPerformance()
		{
			_startTick.QuadPart = 0;
			_stopTick.QuadPart = 0;
			::QueryPerformanceFrequency(&_frequency);
		};

		//! @brief 計測を開始します。
		VOID Start() { ::QueryPerformanceCounter(&_startTick); };

		//! @brief 計測を終了します。
		VOID Stop() { ::QueryPerformanceCounter(&_stopTick); };

		//! @brief	計測開始～計測終了までの時間を出力します。
		//! @note	単位はミリ秒で出力されます。
		//! @note	有効値は小数点第４位まで
		double PastTime()
		{
			return (_stopTick.QuadPart - _startTick.QuadPart) * 1000.0 \
				/ (double)_frequency.QuadPart;
		}

		//! @brief Start()時のカウンター値を取得します。
		LARGE_INTEGER GetStartTick() { return _startTick; };

		//! @brief Stop()時のカウンター値を取得します。
		LARGE_INTEGER GetStopTick() { return _stopTick; };

		//! @brief 現在のタイマー分解能を取得します。
		LARGE_INTEGER GetFrequency() { return _frequency; };

	private:
		//! @brief 開始時タイマー値
		LARGE_INTEGER _startTick;

		//! @brief 終了時タイマー値
		LARGE_INTEGER _stopTick;

		//! @brief 現在のタイマー分解能
		LARGE_INTEGER _frequency;
	};

	//! @class	WatchDogTimer
	//! @brief	タイマーに関するWindowsAPIを集約したクラス
	class DLL_DECLSPEC WatchDogTimer : public WaitableHandleLibrary
	{
	public:
		//! @brief コンストラクタ
		WatchDogTimer();

		//! @brief デストラクタ
		WatchDogTimer(skeleton::ITimeup* timeup);

		BOOL InitTimer(LPCTSTR lpctszTimerName = nullptr);
		BOOL StartTimer(DWORD dwTime);
		DWORD WaitTimer();
		BOOL StopTimer();

	private:
		//! @brief コールバック関数を定義したクラス
		skeleton::ITimeup* _timeup;
	};
}