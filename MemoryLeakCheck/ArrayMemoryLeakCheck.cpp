#include "pch.h"
#include "ArrayMemoryLeakCheck.h"

using namespace LeakCheck;

ArrayMemoryLeakCheck::ArrayMemoryLeakCheck()
{

}

ArrayMemoryLeakCheck::~ArrayMemoryLeakCheck()
{

}

BOOL ArrayMemoryLeakCheck::Init()
{
    return TRUE;
}

BOOL ArrayMemoryLeakCheck::DoAction()
{
    _tprintf(_T("ArrayMemoryLeakCheck::DoAction()\n"));
    CRT_SET_DEBUG_FLAG;

    alt::skeleton::Array<ObjectHolder<int>> array;

    for (int i = 0; i < 100; i++)
    {
        ObjectHolder<int> value(i);
        array.Add(&value);
        _tprintf(_T("now Add() value=%d counter is %d\r"), value.Get(), i);
    }
    _tprintf(_T("\n"));

    alt::skeleton::Array<ObjectHolder<int>> arrayCopy = array;
    array.Clear(true);

    for (int i = 0; i < arrayCopy.Size(); i++)
    {
        ObjectHolder<int>* value = arrayCopy.Get(i);
        ASSERT(i == value->Get());
        _tprintf(_T("now Get()=%d counter is %d\r"), value->Get(), i);
    }
    _tprintf(_T("\n"));

    arrayCopy.Clear(true);

    return TRUE;
}