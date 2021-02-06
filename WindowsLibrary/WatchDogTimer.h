//! @file	WatchDogTimer.h
//! @brief	�^�C�}�[�Ɋւ���WindowsAPI���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "WindowsLibrary.h"
#include "FunctionPointers.hpp"

namespace alt
{
	//! @class	QueryPerformance
	//! @brief	������\���Ԍv���N���X
	class DLL_DECLSPEC QueryPerformance : public WindowsLibrary
	{
	public:
		//! @brief �R���X�g���N�^
		QueryPerformance()
		{
			_startTick.QuadPart = 0;
			_stopTick.QuadPart = 0;
			::QueryPerformanceFrequency(&_frequency);
		};

		//! @brief �v�����J�n���܂��B
		VOID Start() { ::QueryPerformanceCounter(&_startTick); };

		//! @brief �v�����I�����܂��B
		VOID Stop() { ::QueryPerformanceCounter(&_stopTick); };

		//! @brief	�v���J�n�`�v���I���܂ł̎��Ԃ��o�͂��܂��B
		//! @note	�P�ʂ̓~���b�ŏo�͂���܂��B
		//! @note	�L���l�͏����_��S�ʂ܂�
		double PastTime()
		{
			return (_stopTick.QuadPart - _startTick.QuadPart) * 1000.0 \
				/ (double)_frequency.QuadPart;
		}

		//! @brief Start()���̃J�E���^�[�l���擾���܂��B
		LARGE_INTEGER GetStartTick() { return _startTick; };

		//! @brief Stop()���̃J�E���^�[�l���擾���܂��B
		LARGE_INTEGER GetStopTick() { return _stopTick; };

		//! @brief ���݂̃^�C�}�[����\���擾���܂��B
		LARGE_INTEGER GetFrequency() { return _frequency; };

	private:
		//! @brief �J�n���^�C�}�[�l
		LARGE_INTEGER _startTick;

		//! @brief �I�����^�C�}�[�l
		LARGE_INTEGER _stopTick;

		//! @brief ���݂̃^�C�}�[����\
		LARGE_INTEGER _frequency;
	};

	//! @class	WatchDogTimer
	//! @brief	�^�C�}�[�Ɋւ���WindowsAPI���W�񂵂��N���X
	class DLL_DECLSPEC WatchDogTimer : public WaitableHandleLibrary
	{
	public:
		//! @brief �R���X�g���N�^
		WatchDogTimer();

		//! @brief �f�X�g���N�^
		WatchDogTimer(skeleton::ITimeup* timeup);

		BOOL InitTimer(LPCTSTR lpctszTimerName = nullptr);
		BOOL StartTimer(DWORD dwTime);
		DWORD WaitTimer();
		BOOL StopTimer();

	private:
		//! @brief �R�[���o�b�N�֐����`�����N���X
		skeleton::ITimeup* _timeup;
	};
}