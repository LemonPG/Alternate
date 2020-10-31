/**
 @file		ConsolePerformanceCheck.h
 @brief		Console性能測定用
 @author	kumakuma0421@gmail.com
 @date		2020.03.15
 */
#pragma once

#include "PerformanceCheck.h"
#include "WatchDogTimer.h"
#include "Console.h"

namespace PerfCheck
{
    /**
     @class	ConsolePerformanceCheck
     @brief	Console性能測定用
    */
    class ConsolePerformanceCheck : public PerformanceCheck
    {
    public:
        ConsolePerformanceCheck();
        virtual ~ConsolePerformanceCheck();

        virtual BOOL Init(alt::Console& console);
        virtual BOOL DoAction();

    protected:
        virtual BOOL Core(const int param1);
        int response0;
        int response1;
        int response2;
    };
}