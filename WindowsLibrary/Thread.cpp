/**
 @file		Thread.cpp
 @brief		スレッドに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#include "pch.h"
#include "Thread.h"

using namespace alt;

Thread::Thread()
{
	_callback = nullptr;
	_threadID = 0;
}

Thread::Thread(skeleton::ICallback* callback)
{
	_callback = callback;
	_threadID = 0;
}

BOOL Thread::Create(PTHREAD_START_ROUTINE function, LPVOID lpvParam, DWORD dwCreationFlag)
{
	BOOL ret = TRUE;

	PTHREAD_START_ROUTINE threadFunction = function == nullptr ? _callback->Invoker : function;
	lpvParam = function == nullptr ? _callback : lpvParam;

	_hObject = ::CreateThread(nullptr, 0, threadFunction, lpvParam, dwCreationFlag, &_threadID);
	if (_hObject == nullptr)
	{
		ret = FALSE;
	}

	return ret;
}

DWORD Thread::Suspend()
{
	return ::SuspendThread(_hObject);
}

DWORD Thread::Resume()
{
	return ::ResumeThread(_hObject);
}

BOOL Thread::SetPriority(ThreadPriority priority)
{
	return ::SetThreadPriority(_hObject, (int)priority);
}