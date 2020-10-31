// ----------------------------------------------------------------------------
// TaskDrive.hpp:
// ----------------------------------------------------------------------------
#pragma once

#include "MiddleLibrary.h"
#include "CriticalSection.h"

namespace alt
{
	class DLL_DECLSPEC ITaskTemplate : public MiddleLibrary
	{
	public:
		virtual bool PreProcess() = 0;
		virtual bool DoProcess() = 0;
		virtual bool PostProcess() = 0;
	};

	class DLL_DECLSPEC TaskDrive : public ITaskTemplate
	{
	public:
		TaskDrive(ITaskTemplate* task) { _task = task; };
		virtual ~TaskDrive() {};

		virtual bool Action();

	protected:
		virtual bool PreProcess();
		virtual bool DoProcess();
		virtual bool PostProcess();

	private:
		TaskDrive() { _task = nullptr; };
		ITaskTemplate* _task;
		CriticalSection _lock;
	};
}