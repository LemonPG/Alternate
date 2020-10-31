/**
 @file		ConsolePerformanceCheck.cpp
 @brief		Console«”\‘ª’è—p
 @author	kumakuma0421@gmail.com
 @date		2020.03.15
 */

#include "pch.h"
#include "ConsolePerformanceCheck.h"

using namespace PerfCheck;

ConsolePerformanceCheck::ConsolePerformanceCheck()
{
    response0 = 0;
    response1 = 0;
    response2 = 0;
}

ConsolePerformanceCheck::~ConsolePerformanceCheck()
{

}

BOOL ConsolePerformanceCheck::Init(alt::Console& console)
{
    return PerformanceCheck::Init(console);
}

BOOL ConsolePerformanceCheck::DoAction()
{
    this->Core(0);
    this->Core(1);
    this->Core(2);
    
    TCHAR tszMsg[128];
    wsprintf(tszMsg, _T("response0 = %dmsec response1 = %dmsec response2 = %dmsec\n"),
        response0, response1, response2);
    this->Write(tszMsg);
    
    return TRUE;
}

BOOL ConsolePerformanceCheck::Core(const int param1)
{
    const int count = 1000;
    alt::QueryPerformance Q;

    Q.Start();

    this->Clear();
    if (param1 == 2)
    {
        this->Size(80, 25);
        this->Buffer(80, 25);
    }

    for (int i = 0; i < count; i++)
    {
        if (param1 == 0)
        {
            _tprintf(_T("ABCDEFGHIJKLMLOPQRSTUVWXYZ\n"));
            _tprintf(_T("™™™™™™™™™™\n"));
        }
        else if (param1 == 1)
        {
            this->Write(_T("abcdefghijklmnopqrstuvwxyz\n"));
            this->Write(_T("šššššššššš\n"));
        }
        else
        {
            this->Pos(10, 10);
            this->Write(_T("abcdefghijklmnopqrstuvwxyz\n"));
            this->Pos(10, 20);
            this->Write(_T("Ÿ ¡Ÿ ¡Ÿ\n"));
        }
    }
    Q.Finish();

    int msec = static_cast<int>(Q.PastTime());
    if (param1 == 0) response0 = msec;
    if (param1 == 1) response1 = msec;
    if (param1 == 2) response2 = msec;

    return TRUE;
}