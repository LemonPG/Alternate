// ----------------------------------------------------------------------------
// TaskDrive.cpp:
// ----------------------------------------------------------------------------
#include "pch.h"
#include "TaskDrive.h"

using namespace alt;

bool TaskDrive::Action()
{
	bool ret = false;

	try
	{
		do
		{
			ret = PreProcess();
			if (ret == false) break;

			ret = DoProcess();
			if (ret == false) break;

			ret = PostProcess();
			if (ret == false) break;

		} while (0);
	}
	catch (const std::exception&)
	{
		throw;
	}

	return ret;
}

bool TaskDrive::PreProcess()
{
	debug(_T("TaskDrive::PreProcess() IN"));

	_lock.Enter();

	bool ret = _task->PreProcess();

	_lock.Leave();

	debug(_T("TaskDrive::PreProcess() OUT"));
	return ret;
}

bool TaskDrive::DoProcess()
{
	debug(_T("TaskDrive::DoProcess() IN"));

	_lock.Enter();

	bool ret = _task->DoProcess();

	_lock.Leave();

	debug(_T("TaskDrive::DoProcess() OUT"));
	return ret;
}

bool TaskDrive::PostProcess()
{
	debug(_T("TaskDrive::PostProcess() IN"));

	_lock.Enter();

	bool ret = _task->PostProcess();

	_lock.Leave();

	debug(_T("TaskDrive::PostProcess() OUT"));
	return ret;
}