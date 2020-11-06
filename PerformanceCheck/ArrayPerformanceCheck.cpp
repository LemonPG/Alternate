/**
 @file		ArrayPerformanceCheck.cpp
 @brief		Array«”\‘ª’è—p
 @author	kumakuma0421@gmail.com
 @date		2020.03.15
 */

#include "pch.h"
#include "ArrayPerformanceCheck.h"

using namespace PerfCheck;

ArrayPerformanceCheck::ArrayPerformanceCheck()
	:PerformanceCheck()
{
}

ArrayPerformanceCheck::~ArrayPerformanceCheck()
{
}

BOOL ArrayPerformanceCheck::DoAction()
{
	return this->Core();
}

BOOL ArrayPerformanceCheck::Core()
{
	alt::QueryPerformance Q;
	alt::skeleton::Array<ObjectHolder<int>> array;

	Q.Start();

	for (int i = 0; i < 10000; i++)
	{
		ObjectHolder<int> value(i);
		array.Add(&value);
	}

	alt::skeleton::Array<ObjectHolder<int>> arrayCopy = array;
	array.Clear(true);

	for (int i = 0; i < arrayCopy.Size(); i++)
	{
		ObjectHolder<int>* value = arrayCopy.Get(i);
		if (i != value->Get())
		{
			throw "Test failed.";
		}
	}

	arrayCopy.Clear(true);

	Q.Stop();

	int msec = static_cast<int>(Q.PastTime());

	TCHAR tszMsg[128];
	wsprintf(tszMsg, _T("It takes %dmsec.\n"), msec);
	this->Write(tszMsg);

	return TRUE;
}