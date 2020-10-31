/**
 @file		Exception.hpp
 @brief		例外に関するクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

#define ALT_REASON_INVALID_ARGUMENT _T("引数の設定が異常です。")
#define ALT_REASON_RUNTIME_ERROR	_T("実行時にエラーが発生しました。")

namespace alt
{
	/**
	 @class	Exception
	 @brief	基底となる例外クラス
	 */
	class Exception : public WindowsLibrary
	{
	public:
		Exception() {};
		~Exception() {};
	};

	/**
	 @class	InvalidArgmentException
	 @brief	引数設定エラー例外
	 */
	class InvalidArgmentException : Exception
	{
	public:
		InvalidArgmentException() {};
		~InvalidArgmentException() {};

		LPCTSTR getReason() { return ALT_REASON_INVALID_ARGUMENT; }
	};

	//
	// 実行時エラー例外
	//
	/**
	 @class	RuntimeException
	 @brief	実行時エラー例外
	 */
	class RuntimeException : Exception
	{
	public:
		RuntimeException() {};
		~RuntimeException() {};

		LPCTSTR getReason() { return ALT_REASON_RUNTIME_ERROR; }
	};
}