//! @file	FunctionPointers.hpp
//! @brief	�R�[���o�b�N�@�\���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "framework.h"
#include "pch.h"
#include "WindowsLibrary.h"

namespace alt
{
	namespace skeleton
	{
		//! @brief CreateThread()�ɓn���X���b�h���s�֐��̃e���v���[�g
		typedef DWORD(*Invoker)(LPVOID me);

		//! @class	ICallback
		//! @brief	Thread�N���X�̃X���b�h���s�֐���ݒ肵�܂��B
		//! @note	Invoker()�͒����Invoke()���Ăяo���܂��B
		//! 		Invoke()�͏������z�֐��Ȃ̂ŁA�X���b�h���s���������@�\�́A
		//!			�p����Ŏ������Ă��������B
		class DLL_DECLSPEC ICallback : public WindowsLibrary
		{
		public:
			ICallback() {};
			virtual ~ICallback() {};

			virtual DWORD Invoke(LPVOID lpvParam) = 0;

			static DWORD WINAPI Invoker(LPVOID me)
			{
				ICallback* function = (ICallback*)me;
				return function->Invoke(me);
			};
		};

		//! @class	ITimeup
		//! @brief	WatchDogTimer�N���X�̃R�[���o�b�N�֐���ݒ肵�܂��B
		//! @note	TimeupCall()�͒����Timeup()���Ăяo���܂��B
		//! 		Timeup()�͏������z�֐��Ȃ̂ŁA�R�[���o�b�N��Ɏ��s����@�\�́A
		//! 		�p����Ŏ������Ă��������B
		class DLL_DECLSPEC ITimeup : public WindowsLibrary
		{
		public:
			ITimeup() {};
			virtual ~ITimeup() {};

			virtual void Timeup(LPVOID me, DWORD dwHiTime, DWORD dwLoTime) = 0;

			static void WINAPI TimeupCall(LPVOID me, DWORD dwHiTime, DWORD dwLoTime)
			{
				ITimeup* function = (ITimeup*)me;
				function->Timeup(me, dwHiTime, dwLoTime);
			}
		};
	}
}