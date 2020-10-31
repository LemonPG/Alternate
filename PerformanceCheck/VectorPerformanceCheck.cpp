/**
 @file		VectorPerformanceCheck.cpp
 @brief		std::vector<T>«”\‘ª’è—p
 @author	kumakuma0421@gmail.com
 @date		2020.03.15
 */

#include "pch.h"
#include "VectorPerformanceCheck.h"

using namespace PerfCheck;

VectorPerformanceCheck::VectorPerformanceCheck()
    :PerformanceCheck()
{
}

VectorPerformanceCheck::~VectorPerformanceCheck()
{
}

BOOL VectorPerformanceCheck::Init(alt::Console& console)
{
    return PerformanceCheck::Init(console);
}

BOOL VectorPerformanceCheck::DoAction()
{
    return this->Core(10000);
}

BOOL VectorPerformanceCheck::Core(const int param1)
{
    alt::QueryPerformance Q;
    std::vector<ObjectHolder<int>> array;

    Q.Start();

    for (int i = 0; i < param1; i++)
    {
        ObjectHolder<int> value(i);
        array.push_back(value);
    }

    std::vector<ObjectHolder<int>> arrayCopy = array;
    array.clear();

    for (int i = 0; i < arrayCopy.size(); i++)
    {
        ObjectHolder<int> value = arrayCopy.at(i);
        if (i != value.Get())
        {
            throw "Test failed.";
        }
    }

    arrayCopy.clear();

    Q.Finish();

    int msec = static_cast<int>(Q.PastTime());

    TCHAR tszMsg[128];
    wsprintf(tszMsg, _T("It takes %dmsec.\n"), msec);
    this->Write(tszMsg);

    return TRUE;
}