// ----------------------------------------------------------------------------
// WorkerTemplate.hpp:
// ----------------------------------------------------------------------------
#pragma once

#include "CriticalSection.h"

namespace alt
{
	enum class WorkerStatus
	{
		Created,
		BeforeInitialize,
		Initialized,
		BeforeStart,
		Started,
		BeforeExecute,
		Executed,
		BeforeProcess,
		Processed,
		BeforeStop,
		Stopped,
		BeforeExit,
		Exited
	};

	class Message
	{
	public:
		Message()
		{
			_from = -1;
			_to = -1;
			_command = -1;
		};

		virtual ~Message() {};

		int GetFrom() { return _from; };
		void SetFrom(int from) { _from = from; };

		int GetTo() { return _to; };
		void SetTo(int to) { _to = to; };

		int GetCommand() { return _command; };
		void SetCommand(int command) { _command = command; };

	private:
		int _from;
		int _to;
		int _command;
	};

	class Data
	{
	public:
		Data(DWORD dwMaxSize)
		{
			_dwMaxSize = dwMaxSize;
			_dwCurrentSize = 0;
			_lpbyData = new BYTE[_dwMaxSize];
			ZeroMemory(_lpbyData, _dwMaxSize);
		};

		Data(const Data& data)
		{
			_dwMaxSize = data._dwMaxSize;
			_dwCurrentSize = data._dwCurrentSize;
			_lpbyData = new BYTE[data._dwMaxSize];
			CopyMemory(_lpbyData, data._lpbyData, data._dwMaxSize);
		};
		virtual ~Data() { delete[] _lpbyData; };

		LPBYTE GetByte() { return _lpbyData; };
		DWORD GetMaxSize() { return _dwMaxSize; };
		DWORD GetCurrentSize() { return _dwCurrentSize; };

		void SetByte(LPBYTE pbyData, DWORD dwSize)
		{
			if (dwSize <= _dwMaxSize)
			{
				CopyMemory(_lpbyData, pbyData, dwSize);
				_dwCurrentSize = dwSize;
			}
		};

	private:
		Data()
		{
			_dwMaxSize = 0;
			_dwCurrentSize = 0;
			_lpbyData = nullptr;
		};
		LPBYTE _lpbyData;
		DWORD _dwMaxSize;
		DWORD _dwCurrentSize;
	};

	class WorkerTemplate
	{
	public:
		//! �R���X�g���N�^
		WorkerTemplate()
		{
			_workerStatus = WorkerStatus::Created;
		}

		//! �f�X�g���N�^
		virtual ~WorkerTemplate() {};

		//! ����������
		template <typename Function>
		bool Init(Function function)
		{
			_workerStatus = WorkerStatus::BeforeInitialize;

			bool ret = this->CriticalAction(function);

			_workerStatus = WorkerStatus::Initialized;

			return ret;
		}

		//! �J�n����
		template <typename Function>
		bool Start(Function function)
		{
			_workerStatus = WorkerStatus::BeforeStart;

			bool ret = this->CriticalAction(function);

			_workerStatus = WorkerStatus::Started;

			return ret;
		}

		//! �R�}���h����
		template <typename Function>
		bool Command(Function function, Message message)
		{
			_workerStatus = WorkerStatus::BeforeExecute;

			bool ret = this->CriticalCommand(function, message);

			_workerStatus = WorkerStatus::Executed;

			return ret;
		}

		//! �v���Z�X����
		template <typename Function>
		Data Process(Function function, Data data)
		{
			_workerStatus = WorkerStatus::BeforeProcess;

			Data ret = this->CriticalProcess(function, data);

			_workerStatus = WorkerStatus::Processed;

			return ret;
		}

		//! �I������
		template <typename Function>
		bool Stop(Function function)
		{
			_workerStatus = WorkerStatus::BeforeStop;

			bool ret = this->CriticalAction(function);

			_workerStatus = WorkerStatus::Stopped;

			return ret;
		}

		//! �ޏo����
		template <typename Function>
		bool Exit(Function function)
		{
			_workerStatus = WorkerStatus::BeforeExit;

			bool ret = this->CriticalAction(function);

			_workerStatus = WorkerStatus::Exited;

			return ret;
		}

		//! ��Ԏ擾
		WorkerStatus GetStatus() { return _workerStatus; };

	protected:
		//! �r����������
		template <typename Function>
		bool CriticalAction(Function function)
		{
			_criticalSection.Enter();

			bool ret = function();

			_criticalSection.Leave();

			return ret;
		}

		//! Command����
		template <typename Function>
		bool CriticalCommand(Function function, Message message)
		{
			_criticalSection.Enter();

			bool ret = function(message);

			_criticalSection.Leave();

			return ret;
		}

		//! Process����
		template <typename Function>
		Data CriticalProcess(Function function, Data data)
		{
			_criticalSection.Enter();

			Data ret = function(data);

			_criticalSection.Leave();

			return ret; // TODO:C4172 ���[�J���ϐ��܂��̓e���|�����̃A�h���X��Ԃ��܂�
		}

	private:
		WorkerStatus _workerStatus;
		CriticalSection _criticalSection;
	};
}