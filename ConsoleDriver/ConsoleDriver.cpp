//! @file	ConsoleDriver.cpp
//! @brief	Console����V�X�e�����N�����܂��B
//! @author	kumakuma0421@gmail.com
//! @date	2020.01.03

#include "pch.h"
#include "ConsoleDriver.h"
#include "DesignPattern.hpp"
#include "TString.h"
#include "Console.h"
#include "PipelineFactoryMethod.h"
#include "File.h"
#include "FileUtility.h"

alt::skeleton::Strategy<alt::TString, std::function<void()>> _strategy;
alt::TString _action(MAX_PATH);
alt::TString _configFile;

volatile bool __loopKeep = true;

//! @brief		�G���g���[�|�C���g(���C���֐�)�ł��B
//! @param[in]	argc �p�����[�^��
//! @param[in]	argv �p�����[�^
//! @note		argv[0]�͂���EXE�̃t�@�C�����ɂȂ�܂��B
int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(_T("main(%d, TCHAR*) IN.\n"), argc);

	if (argc == 3)
	{
		_configFile = argv[2];
		BOOL bCheck = alt::FileUtility::IsExist(_configFile.Ctr());
		if (!bCheck)
		{
			_tprintf(_T("Can't find config file.\n"));
			return 1;
		}

		lstrcpy(_action.Ptr(), argv[1]);
	}

	if (argc == 2)
	{
		_configFile = CONFIG_FILE;
		BOOL bCheck = alt::FileUtility::IsExist(CONFIG_FILE);
		if (!bCheck)
		{
			_tprintf(_T("Can't find config file.\n"));
			return 1;
		}

		lstrcpy(_action.Ptr(), argv[1]);
	}

	if (argc == 1)
	{
		_configFile = CONFIG_FILE;
		BOOL bCheck = alt::FileUtility::IsExist(CONFIG_FILE);
		if (!bCheck)
		{
			_tprintf(_T("Can't find config file.\n"));
			return 1;
		}

		DWORD dwRet = ::GetPrivateProfileString(SECTION_GENERAL, KEYWORD_ACTION, nullptr, _action.Ptr(), MAX_PATH, _configFile.Ctr());
		if (dwRet == 0)
		{
			_tprintf(_T("Can't find action.\n"));
			return 1;
		}
	}

	Init();

	auto target = _strategy.Get(_action.Ptr());
	if (target)
	{
		target();
	}
	else
	{
		_tprintf(_T("Invalid Parameter %s\n"), _action.Ctr());
		return 2;
	}

	_tprintf(_T("main(%d, TCHAR*) OUT.\n"), argc);
	return 0;
}

//! @brief		�X�g���e�W�[�̏��������s���܂��B
//! @details	INI�t�@�C���̃Z�N�V�������Ŋ֐��N����؂�ւ��܂��B
//! @return		void
void Init()
{
	_tprintf(_T("Init() IN.\n"));

	_strategy.Set(SECTION_PIPELINE_FACTORY, DrivePipelineFactory);

	_tprintf(_T("Init() OUT.\n"));
}

BOOL DrivePipelineFactoryHandler(DWORD dwType)
{
	_tprintf(_T("DrivePipelineFactoryHandler(%d) IN.\n"), dwType);

	BOOL ret = false;

	timeEndPeriod(1);

	switch (dwType)
	{
		case 0: // Ctrl + C
		case 1: // Ctrl + Break
			__loopKeep = false;
			ret = TRUE; // �I�������܂���B
			break;

		case 2: // Console Close
		case 3: // Log off
		case 4: // Shut down
			ret = FALSE; // ���Ɉς˂܂��B
			break;
	}

	_tprintf(_T("DrivePipelineFactoryHandler(%d) OUT.\n"), dwType);
	return ret;
}

void DrivePipelineFactory()
{
	_tprintf(_T("DrivePipelineFactory() IN.\n"));

	timeBeginPeriod(1);

	bool ret;

	auto factory = new alt::FactoryMethod::PipelineFactoryMethod();
	auto manager = (alt::FactoryMethod::ProductManager*)factory->Buildup();
	auto config = new alt::FactoryMethod::Config();
	ret = config->Load(_configFile.Ctr());
	if (ret == false)
	{
		_tprintf(_T("Error:config->Load()\n"));
		return;
	}

	manager->Init(config);

	while (__loopKeep)
	{
		manager->Start();

		Sleep(30000); // 30�b

		manager->Stop();

		Sleep(3000); // 3�b
	}

	manager->Exit();

	Sleep(10000); // 10�b

	_tprintf(_T("DrivePipelineFactory() OUT.\n"));
}