//! @file	FunctionPointers.hpp
//! @brief	コールバック機能を集約したクラス
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
		//! @brief CreateThread()に渡すスレッド実行関数のテンプレート
		typedef DWORD(*Invoker)(LPVOID me);

		//! @class	ICallback
		//! @brief	Threadクラスのスレッド実行関数を設定します。
		//! @note	Invoker()は直後にInvoke()を呼び出します。
		//! 		Invoke()は純粋仮想関数なので、スレッド実行させたい機能は、
		//!			継承先で実装してください。
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
		//! @brief	WatchDogTimerクラスのコールバック関数を設定します。
		//! @note	TimeupCall()は直後にTimeup()を呼び出します。
		//! 		Timeup()は純粋仮想関数なので、コールバック後に実行する機能は、
		//! 		継承先で実装してください。
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