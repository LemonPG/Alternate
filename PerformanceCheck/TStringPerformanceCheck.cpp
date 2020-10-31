/**
 @file		TStringPerformanceCheck.cpp
 @brief		TString«”\‘ª’è—p
 @author	kumakuma0421@gmail.com
 @date		2020.03.21
 */

#include "pch.h"
#include "TStringPerformanceCheck.h"

using namespace PerfCheck;

TStringPerformanceCheck::TStringPerformanceCheck()
	:PerformanceCheck()
{
}

TStringPerformanceCheck::~TStringPerformanceCheck()
{
}

BOOL TStringPerformanceCheck::Init(alt::Console& console)
{
	return PerformanceCheck::Init(console);
}

BOOL TStringPerformanceCheck::DoAction()
{
	this->Core(1);
	this->Core(2);
	this->Core(3);

	return TRUE;
}

BOOL TStringPerformanceCheck::Core(const int param1)
{
	alt::QueryPerformance Q;

	Q.Start();

	switch (param1)
	{
		case 1:
			this->Core1();
			break;

		case 2:
			this->Core2();
			break;

		case 3:
			this->Core3();
			break;
	}

	Q.Stop();

	DWORD pastTime = static_cast<DWORD>(Q.PastTime() * 1000);

	TCHAR tszMsg[128];
	wsprintf(tszMsg, _T("param1(%d) pastTick(%d)\n"), param1, pastTime);
	this->Write(tszMsg);

	return TRUE;
}

BOOL TStringPerformanceCheck::Core1()
{
	alt::File csvFile;

	BOOL ret = csvFile.Create(TEST_FILE, GENERIC_READ, 0, OPEN_EXISTING);
	if (!ret) return FALSE;

	DWORD dwFileSize = static_cast<DWORD>(csvFile.GetSize());
	alt::TString csvData(dwFileSize);

	DWORD dwReadSize = csvFile.Read(csvData.Ptr(), dwFileSize);
	if (dwReadSize != dwFileSize) return FALSE;

	alt::TString delimiter(_T("\r\n"));
	auto response = csvData.Split(delimiter);

	for (size_t i = 0; i < response.Size(); i++)
	{
		auto response2 = response[i]->Split(alt::TString(_T(",")));
		for (size_t j = 0; j < response2.Size(); j++)
		{
			alt::TString message;
			message.Format(_T("%s\t"), response2[j]->Ctr());
			this->Write(message.Ctr());
		}
		this->Write(_T("\n"));
	}

	ret = csvFile.Close();
	if (!ret) return FALSE;

	return TRUE;
}

BOOL TStringPerformanceCheck::Core2()
{
	alt::QueryPerformance Q;

	Q.Start();
	Q.Stop();
	DWORD pastTime = static_cast<DWORD>(Q.PastTime() * 1000);

	return TRUE;
}

BOOL TStringPerformanceCheck::Core3()
{
	return TRUE;
}