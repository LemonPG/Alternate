// ----------------------------------------------------------------------------
// TaskTemplate.hpp:
// ----------------------------------------------------------------------------
#pragma once

#include <functional>

namespace alt
{
	enum class TaskStatus
	{
		beforeProcess,
		preProcess,
		doProcess,
		postProcess,
		afterProcess
	};

	typedef std::function<bool()> Function;

	class TaskTemplate
	{
	public:
		TaskTemplate() { _taskStatus = TaskStatus::beforeProcess; };
		virtual ~TaskTemplate() {};

		//! �^�X�N���s
		bool DoAction(Function functions[])
		{
			bool ret;

			do
			{
				_taskStatus = TaskStatus::preProcess;
				ret = this->PreProcess(functions[0]);
				if (!ret) break;

				_taskStatus = TaskStatus::doProcess;
				ret = this->DoProcess(functions[1]);
				if (!ret) break;

				_taskStatus = TaskStatus::postProcess;
				ret = this->PostProcess(functions[2]);
				if (!ret) break;

				_taskStatus = TaskStatus::afterProcess;

			} while (false);

			return ret;
		}

		TaskStatus GetStatus() { return _taskStatus; }

	protected:
		//! �^�X�N���O����
		bool PreProcess(Function function) { return function(); }

		//! �^�X�N�{����
		bool DoProcess(Function function) { return function(); }

		//! �^�X�N�I������
		bool PostProcess(Function function) { return function(); }

	private:
		TaskStatus _taskStatus;
	};
}