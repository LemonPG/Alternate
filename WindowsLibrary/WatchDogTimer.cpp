//! @file	WatchDogTimer.cpp
//! @brief	タイマーに関するWindowsAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#include "pch.h"
#include "WatchDogTimer.h"

using namespace alt;

WatchDogTimer::WatchDogTimer()
{
	_timeup = nullptr;
}

WatchDogTimer::WatchDogTimer(skeleton::ITimeup* timeup)
{
	_timeup = timeup;
}

BOOL WatchDogTimer::InitTimer(LPCTSTR lpctszTimerName)
{
	BOOL ret = TRUE;

	_hObject = ::CreateWaitableTimer(nullptr, 0, lpctszTimerName);
	if (_hObject == INVALID_HANDLE_VALUE)
	{
		ret = FALSE;
	}

	return ret;
}

BOOL WatchDogTimer::StartTimer(DWORD dwTime)
{
	BOOL ret = FALSE;
	LARGE_INTEGER interval;
	interval.QuadPart = -((LONGLONG)dwTime * 10000); // マイナス設定は現在時刻から、プラス設定はエポックタイムから
	LONG period = dwTime;

	ret = ::SetWaitableTimer(
		_hObject, &interval, period,
		_timeup == nullptr ? nullptr : _timeup->TimeupCall,
		_timeup, FALSE);
	if (ret == FALSE)
	{
		return ret;
	}

	return TRUE;
}

DWORD WatchDogTimer::WaitTimer()
{
	return ::WaitForSingleObjectEx(_hObject, INFINITE, TRUE);
}

BOOL WatchDogTimer::StopTimer()
{
	return ::CancelWaitableTimer(_hObject);
}