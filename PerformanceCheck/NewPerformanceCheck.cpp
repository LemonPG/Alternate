/**
 @file		NewPerformanceCheck.cpp
 @brief		newの性能測定用
 @author	kumakuma0421@gmail.com
 @date		2020.4.11
 */

#include "pch.h"
#include "NewPerformanceCheck.h"

using namespace PerfCheck;

NewPerformanceCheck::NewPerformanceCheck()
	:PerformanceCheck()
{
}

NewPerformanceCheck::~NewPerformanceCheck()
{
}

BOOL NewPerformanceCheck::Init(alt::Console& console)
{
	return PerformanceCheck::Init(console);
}

BOOL NewPerformanceCheck::DoAction()
{
	return this->Core(0);
}

BOOL NewPerformanceCheck::Core(const int param1)
{
	alt::QueryPerformance Q;

	auto threadFunc = [](LPVOID lpvParam)->DWORD
	{
		NewPerformanceCheck* me = (NewPerformanceCheck*)lpvParam;
		alt::Event event;
		int loop = me->_loop;

		event.Open(_T("START_EVENT"));
		event.Wait();

		OutputDebugString(_T("Thread action is started.\n"));
		do
		{
			int index = rand() % 10;
			TCHAR tsz[10];
			wsprintf(tsz, _T("%d(%d),"), GetCurrentThreadId(), index);
			OutputDebugString(tsz);

			LPVOID lpvMem = new BYTE[me->_allocSize[index]];
			ZeroMemory(lpvMem, me->_allocSize[index]);

			delete[] lpvMem;

		} while (--loop);
		OutputDebugString(_T("Thread action is finished.\n"));

		return 0;
	};

	alt::Event event;
	event.Create(_T("START_EVENT"), TRUE, FALSE);
	Write(_T("Event作成\n"));

	const int numOfThreads = 48;
	this->_loop = 50000;

	alt::Thread thread[numOfThreads];
	for (auto& item : thread)
	{
		item.Create(threadFunc, (LPVOID)this);
		SwitchToThread();
	}
	Write(_T("Thread作成\n"));

	HANDLE threadHandles[numOfThreads];
	for (int i = 0; i < numOfThreads; i++)
	{
		threadHandles[i] = thread[i].GetHandle();
	}
	Write(_T("Thread Handle収集\n"));

	Write(_T("計測開始\n"));
	Q.Start();

	event.Set();
	WaitForMultipleObjects(numOfThreads, threadHandles, TRUE, INFINITE);

	Q.Finish();
	Write(_T("計測終了\n"));

	int msec = static_cast<int>(Q.PastTime());

	TCHAR tszMsg[128];
	wsprintf(tszMsg, _T("It takes %dmsec.\n"), msec);
	this->Write(tszMsg);

	return TRUE;
}