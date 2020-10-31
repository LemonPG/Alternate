/**
 @file		NamedPipe.h
 @brief		名前付きパイプに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

#define PIPE_NAME_FORMAT _T("\\\\.\\pipe\\%s")

namespace alt
{
	/**
	 @class	NamedPipe
	 @brief	名前付きパイプに関するWindowsAPIを集約したクラス
	*/
	class DLL_DECLSPEC NamedPipe : public ReadWriteHandleLibrary
	{
	public:
		/**
		 @brief		パイプを作成します。
		 @param[in]	lpctszName パイプ名
		 @return	BOOL
		 @retval	TRUE(成功)
		 @retval	FALSE(失敗)
		 @details	パイプ名は内部で正式名に補完します。
		 */
		BOOL Create(LPCTSTR lpctszName);

		/**
		 @brief		サーバー側でクライアント接続を待機します。
		 @return	BOOL
		 @retval	TRUE(成功)
		 @retval	FALSE(失敗)
		 */
		BOOL Connect();

		/**
		 @brief	パイプをオープンします。
		 @param[in]	lpctszName パイプ名
		 @return	BOOL
		 @retval	TRUE(成功)
		 @retval	FALSE(失敗)
		 @details	パイプ名は内部で正式名に補完します。
		 */
		BOOL Open(LPCTSTR lpctszName);

		/**
		 @brief	クライアント側でサーバー接続を待機します。
		 @param[in]	lpctszName	パイプ名
		 @param[in]	dwTimeout	タイムアウト時間(ミリ秒)
		 @return	BOOL
		 @retval	TRUE(成功)
		 @retval	FALSE(失敗)
		 */
		BOOL Wait(LPCTSTR lpctszName, DWORD dwTimeout = NMPWAIT_USE_DEFAULT_WAIT);
	};
}