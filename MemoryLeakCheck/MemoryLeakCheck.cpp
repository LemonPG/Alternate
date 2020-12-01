//! @file	MemoryLeakCheck.cpp
//! @brief	TestProject�ł͌��o�ł��Ȃ��A�������[���[�N���m�F���܂��B
//! @author	kumakuma0421@gmail.com
//! @date	2020.03.01

#include "pch.h"
#include "MemoryLeakCheck.h"
#include "ArrayMemoryLeakCheck.h"
#include "TStringMemoryLeakCheck.h"

int _tmain(int argc, TCHAR* argv[])
{
	CRT_SET_DEBUG_FLAG;

	int action = ::GetPrivateProfileInt(
		_T("Target"),
		_T("Action"),
		-1,
		CONFIG_FILE);

	if (action == -1)
	{
		_tprintf(_T("Action�̐ݒ�l���ُ�(%d)�ł��B\n"), action);
		return -1;
	}

	if (action == 1)
	{
		LeakCheck::ArrayMemoryLeakCheck* check1 = new LeakCheck::ArrayMemoryLeakCheck();
		check1->Init();
		check1->DoAction();
		delete check1;
	}

	if (action == 2)
	{
		LeakCheck::TStringMemoryLeakCheck* check2 = new LeakCheck::TStringMemoryLeakCheck();
		check2->Init();
		check2->DoAction();
		delete check2;
	}
}