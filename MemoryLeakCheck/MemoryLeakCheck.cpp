/**
 @file		MemoryLeakCheck.cpp
 @brief		TestProjectでは検出できない、メモリーリークを確認します。
 @author	kumakuma0421@gmail.com
 @date		2020.03.01
 */

#include "pch.h"
#include "MemoryLeakCheck.h"

int _tmain(int argc, TCHAR* argv[])
{
    CRT_SET_DEBUG_FLAG;

    LeakCheck::ArrayMemoryLeakCheck* check1 = new LeakCheck::ArrayMemoryLeakCheck();
    check1->Init();
    check1->DoAction();
    delete check1;

    LeakCheck::TStringMemoryLeakCheck* check2 = new LeakCheck::TStringMemoryLeakCheck();
    check2->Init();
    check2->DoAction();
    delete check2;
}