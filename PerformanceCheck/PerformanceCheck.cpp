/**
 @file		PerformanceCheck.cpp
 @brief		性能測定用
 @author	kumakuma0421@gmail.com
 @date		2020.03.01
 */

#include "pch.h"
#include "PerformanceCheck.h"
#include "ConsolePerformanceCheck.h"
#include "FilePerformanceCheck.h"
#include "VectorPerformanceCheck.h"
#include "ArrayPerformanceCheck.h"
#include "TStringPerformanceCheck.h"
#include "StdFilePerformanceCheck.h"
#include "HeapPerformanceCheck.h"
#include "NewPerformanceCheck.h"
#include "WatchDocTimerPerformanceCheck.h"
#include "TCPPerformanceCheck.h"
#include "UDPPerformanceCheck.h"
#include "LoggerPerformanceCheck.h"

using namespace PerfCheck;

PerformanceCheck::PerformanceCheck()
{
	_con = nullptr;
}

PerformanceCheck::~PerformanceCheck()
{
}

VOID PerformanceCheck::Init(alt::Console& console)
{
	_con = &console;
}

void PerformanceCheck::Write(LPCTSTR message)
{
	_con->Write(message);
}

void PerformanceCheck::Pos(SHORT x, SHORT y)
{
	_con->SetCursorPosition(x, y);
}

void PerformanceCheck::Size(SHORT width, SHORT height)
{
	_con->SetWindowInfo(width, height);
}

void PerformanceCheck::Buffer(SHORT x, SHORT y)
{
	_con->SetBufferSize(x, y);
}

void PerformanceCheck::Clear()
{
	_con->Clear();
}

int _tmain(int argc, TCHAR* argv[])
{
	alt::Console console;
	console.Init();

	wchar_t* locale = _tsetlocale(LC_ALL, _T("Japanese"));
	console.Format(_T("Now locale is %s\n"), locale);
	
	int action = ::GetPrivateProfileInt(
		_T("Target"),
		_T("Action"),
		-1,
		CONFIG_FILE);

	if (action == -1)
	{
		console.Format(_T("Actionの設定値が異常(%d)です。\n"), action);
		return -1;
	}

	if (action == 1)
	{
		auto t = new PerfCheck::ConsolePerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 2)
	{
		auto t = new PerfCheck::FilePerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 3)
	{
		auto t = new PerfCheck::StdFilePerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 4)
	{
		auto t = new VectorPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 5)
	{
		auto t = new PerfCheck::ArrayPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 6)
	{
		auto t = new PerfCheck::TStringPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 7)
	{
		auto t = new PerfCheck::HeapPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 8)
	{
		auto t = new PerfCheck::NewPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 9)
	{
		auto t = new PerfCheck::WatchDocTimerPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 10)
	{
		auto t = new PerfCheck::TCPPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 11)
	{
		auto t = new PerfCheck::UDPPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}

	if (action == 12)
	{
		auto t = new PerfCheck::LoggerPerformanceCheck();
		t->Init(console);
		t->DoAction();
		delete t;
	}
}