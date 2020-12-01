//! @file	Utility.h
//! @brief	汎用的に使えるユーティリティクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.2.24

#pragma once

#include "framework.h"
#include "TString.h"

namespace alt
{
	//! @class	Utility
	//! @brief	汎用的に使えるユーティリティクラス
	class DLL_DECLSPEC Utility
	{
	public:
		static const GUID CreateGUID();
		static const TString MakeGUID();
		static SYSTEMTIME GetLocalTime();
		static TString GetFormatTime(SYSTEMTIME& systemTime);
		static ULARGE_INTEGER GetLocalTimeQuad();
		static SYSTEMTIME GetTimeByFileTime(FILETIME& fileTime);

		//! @brief Windowsが起動してからの時間を返します。
		//! @note 49.7日でゼロに戻ります。
#pragma warning (push)
#pragma warning (disable:28159)
		static DWORD GetPastTick() { return ::GetTickCount(); };
#pragma warning (pop)

		//! @brief Windowsが起動してからの時間を返します。
		static ULONGLONG GetPastTick64() { return ::GetTickCount64(); };

		//! @brief テンポラリフォルダを取得します。
		static TString GetTemporaryPath();

		//! @brief テンポラリファイル名を取得します。
		//! @param[in] lpctszPath ファイルパス
		//! @param[in] lpctszPrefix ファイル名プレフィックス(３文字まで)
		//! @param[in] nNumber ファイル名に使用される番号(下位１６ビットまで)
		//! @note nNumberに０を指定するとシステムが生成します。
		static TString GetTemporaryFileName(LPCTSTR lpctszPath, LPCTSTR lpctszPrefix, UINT nNumber);

		static BOOL Base64Encode(LPBYTE lppbyString, DWORD dwLength, TString& response);
		static BOOL Base64Decode(TString& source, LPBYTE lpbyBuffer, DWORD& dwBuffer);

		static skeleton::Array<TString> GetEnvironments();
		static TString GetEnv(LPCTSTR lpctszKeyword);
	};
}