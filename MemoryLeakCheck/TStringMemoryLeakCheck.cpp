#include "pch.h"
#include "TStringMemoryLeakCheck.h"

using namespace LeakCheck;

TStringMemoryLeakCheck::TStringMemoryLeakCheck()
{

}

TStringMemoryLeakCheck::~TStringMemoryLeakCheck()
{

}

BOOL TStringMemoryLeakCheck::Init()
{
	return TRUE;
}

BOOL TStringMemoryLeakCheck::DoAction()
{
	this->DoAction1();
	this->DoAction2();
	this->DoAction3();

	return TRUE;
}

BOOL TStringMemoryLeakCheck::DoAction1()
{
	_tprintf(_T("TStringMemoryLeakCheck::DoAction1()\n"));
	CRT_SET_DEBUG_FLAG;

	alt::TString string1;
	alt::TString string2(_T("Check_TString01"));
	alt::TString string3(string2);
	alt::TString string4(MAX_PATH);

	return TRUE;
}

BOOL TStringMemoryLeakCheck::DoAction2()
{
	_tprintf(_T("TStringMemoryLeakCheck::DoAction2()\n"));
	CRT_SET_DEBUG_FLAG;

	alt::TString* string1 = new alt::TString();
	alt::TString* string2 = new alt::TString(_T("Check_TString02"));
	alt::TString* string3 = new alt::TString(*string2);
	alt::TString* string4 = new alt::TString(MAX_PATH);

	delete string1;
	delete string2;
	delete string3;
	delete string4;

	return TRUE;
}

BOOL TStringMemoryLeakCheck::DoAction3()
{
	_tprintf(_T("TStringMemoryLeakCheck::DoAction3()\n"));
	CRT_SET_DEBUG_FLAG;

	alt::TString string1;
	alt::TString string2;

	ASSERT(string1 == nullptr);
	ASSERT(string1 == string2);

	alt::TString string3(_T("string3"));
	alt::TString string4(_T("string4"));

	ASSERT(string3 == _T("string3"));
	ASSERT(string3 != string4);

	return TRUE;
}