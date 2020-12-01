//! @file	Event.h
//! @brief	イベントに関するWindowsAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "WindowsLibrary.h"

namespace alt
{
	//! @class	Event
	//! @brief	イベントに関するWindowsAPIを集約したクラス
	class DLL_DECLSPEC Event : public WaitableHandleLibrary
	{
	public:
		//! @brief		イベントを作成します。
		//! @param[in]	lpctszEventName イベント名
		//! @param[in]	bManualReset TRUE:手動リセット FALSE:自動リセット
		//! @param[in]	bInitialState TRUE:初期状態でシグナル状態 FALSE:初期状態で非シグナル状態
		//! @return		BOOL
		//! @retval		TRUE:成功
		//! @retval		FALSE:失敗
		BOOL Create(LPCTSTR lpctszEventName, BOOL bManualReset, BOOL bInitialState);

		//! @brief		イベントをオープンします。
		//! @param[in]	lpctszEventName イベント名
		//! @return		BOOL
		//! @retval		TRUE:成功
		//! @retval		FALSE:失敗
		BOOL Open(LPCTSTR lpctszEventName);

		//! @brief	イベントをセット(シグナル状態に)します。
		//! @return	BOOL
		//! @retval	TRUE:成功
		//! @retval	FALSE:失敗
		BOOL Set();

		//! @brief	イベントをリセット(非シグナル状態に)します。
		//! @return	BOOL
		//! @retval	TRUE:成功
		//! @retval	FALSE:失敗
		BOOL Reset();

		//! @brief	自動イベントをパルス(シグナル状態→非シグナル状態に)します。
		//! @return	BOOL
		//! @retval	TRUE:成功
		//! @retval	FALSE:失敗
		BOOL Pulse();
	};
}