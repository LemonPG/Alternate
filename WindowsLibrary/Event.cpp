//! @file	Event.cpp
//! @brief	イベントに関するWindowsAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#include "pch.h"
#include "Event.h"

using namespace alt;

BOOL Event::Create(LPCTSTR lpctszEventName, BOOL bManualReset, BOOL bInitialState)
{
	BOOL ret = TRUE;

	_hObject = ::CreateEvent(NULL, bManualReset, bInitialState, lpctszEventName);
	if (_hObject == INVALID_HANDLE_VALUE)
	{
		ret = FALSE;
	}

	return ret;
}

BOOL Event::Open(LPCTSTR lpctszEventName)
{
	BOOL ret = TRUE;

	_hObject = ::OpenEvent(EVENT_ALL_ACCESS, FALSE, lpctszEventName);
	if (_hObject == INVALID_HANDLE_VALUE)
	{
		ret = FALSE;
	}

	return ret;
}

BOOL Event::Set()
{
	return ::SetEvent(_hObject);
}

BOOL Event::Reset()
{
	return ::ResetEvent(_hObject);
}

BOOL Event::Pulse()
{
	return ::PulseEvent(_hObject);
}