/**
 @file		TString.h
 @brief		文字列に関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"
#include "Array.hpp"

namespace alt
{
	/**
	 @class TString
	 @brief 文字列に関するWindowsAPIを集約したクラス
	 */
	class DLL_DECLSPEC TString : public WindowsLibrary
	{
	public:
		//! @brief コンストラクタ
		TString();

		//! @brief		コンストラクタ
		//! @param[in]	lpctszString 生成時に格納する文字列
		TString(LPCTSTR lpctszString);

		//! @brief		コンストラクタ
		//! @param[in]	string 生成時に格納する文字列
		TString(const TString& string);

		//! @brief		コンストラクタ
		//! @param[in]	length 生成時に確保するメモリサイズ(文字数)
		//! @note		APIなどで、TCHAR[256]が必要な場合に使用します。
		//!             Ptr()を使用すると、メモリ確保済みのポインタが
		//!             使用できます。
		TString(int length);

		//! @brief デストラクタ
		virtual ~TString();

		//! @brief 内部で確保している文字列ポインタを取得します。
		//! @return 保持している文字列のポインタ
		LPTSTR Ptr() const { return _lptszString; };

		//! @brief 内部で確保している文字列ポインタを取得します。
		//! @return 保持している文字列のポインタ
		LPCTSTR Ctr() const { return (LPCTSTR)_lptszString; };

		//! @brief 内部で確保している文字列数を取得します。
		//! @return 文字列長
		int Len() const { return lstrlen(_lptszString); };

		//! @brief 内部で確保している文字列(バイト数)を取得します。
		//! @return バイト長
		int Byte() const { return this->Len() * sizeof(TCHAR); };

		//! @brief 文字列と比較します。
		//1 @param[in]	lpctszString 比較する文字列
		//! @return 一致するか否か
		//! @retval TRUE 一致する
		//! @retval FALSE 一致しない
		BOOL operator == (LPCTSTR lpctszString);

		//! @brief TStringと文字列を比較します。
		//! @param[in]	string 比較するTStringオブジェクト
		//! @return 一致するか否か
		//! @retval TRUE 一致する
		//! @retval FALSE 一致しない
		BOOL operator == (const TString& string);

		//! @brief 文字列と比較します。
		//1 @param[in]	lpctszString 比較する文字列
		//! @return 一致しないか否か
		//! @retval TRUE 一致する
		//! @retval FALSE 一致しない
		BOOL operator != (LPCTSTR lpctszString);

		//! @brief TStringと文字列を比較します。
		//! @param[in]	string 比較するTStringオブジェクト
		//! @return 一致しないか否か
		//! @retval TRUE 一致する
		//! @retval FALSE 一致しない
		BOOL operator != (const TString& string);

		//! @brief 文字列を代入します。
		//! @param[in]	lpctszString 文字列
		VOID operator = (LPCTSTR lpctszString);

		//! @brief 文字列を代入します。
		//! @param[in]	string 文字列
		VOID operator = (const TString& string);

		//! @brief 文字列を代入します。
		//! @param[in]	lpctszString 文字列
		//! @return 代入された自分自身
		TString& operator << (LPCTSTR lpctszString);

		//! @brief 文字列を代入します。
		//! @param[in]	string 文字列
		//! @return 代入された自分自身
		TString& operator << (const TString& string);

		//! @brief 数値を代入します。
		//! @param[in]	iValue 数値
		//! @return 代入された自分自身
		TString& operator << (const int iValue);

		//! @brief 文字列を追加します。
		//! @param[in]	string 文字列
		//! @return 追加された文字列の結果
		TString operator + (LPCTSTR lpctszString);

		//! @brief 文字列を追加します。
		//! @param[in]	string 文字列
		//! @return 追加された文字列の結果
		TString operator + (TString& string);

		//! @brief 数値を代入します。
		//! @param[in]	iValue 数値
		//! @return 代入された自分自身
		TString& operator += (LPCTSTR lpctszString);

		//! @brief 数値を代入します。
		//! @param[in]	iValue 数値
		//! @return 代入された自分自身
		TString& operator += (const TString& string);

		//! @brief 文字列の一部を取り出します。
		//! @param[in]	index 場所の指定
		//! @return 指定された場所にある文字
		TCHAR operator [] (int index) const;

		//! @brief 文字列の大小を比較します。
		//! @param[in]	string 比較対象
		//! @return 比較結果
		//! @retval true 比較する側が小さい
		//! @retval false 比較する側が大きい
		bool operator < (const TString& string) const;

		//! @brief 左側の余白を切り取ります。
		//! @return 左側余白を切り取った自分自身
		TString& TrimLeft();

		//! @brief 右側の余白を切り取ります。
		//! @return 右側余白を切り取った自分自身
		TString& TrimRight();

		//! @brief 左右の余白を切り取ります。
		//! @return 左右の余白を切り取った自分自身
		TString& Trim();

		//! @brief 文字列を切り出します。
		//! @param[in] startPos 切り出し開始位置
		//! @param[in] length 切り出しサイズ
		//! @return 切り出した文字列
		TString Substring(int startPos, int length = 0);

		//! @brief 文字列を置換します。
		//! @param[in] charsBefore 検索する文字列
		//! @param[in] charsAfter 置換する文字列
		//! @return 検索結果を置換した文字列
		TString Replace(TString& charsBefore, TString& charsAfter);

		//! @brief 文字列を置換します。
		//! @param[in] charsBefore 検索する文字列
		//! @param[in] charsAfter 置換する文字列
		//! @return 検索結果をすべて置換した文字列
		TString ReplaceAll(TString& charsBefore, TString& charsAfter);

		//! @brief 文字列を指定した文字列で分割します。
		//! @param[in] delimiters 分割する文字の集合
		//! @return delimiters単位で分割した文字列群
		//! @note delimiterに入っている文字はすべて分割対象です。
		skeleton::Array<TString> Split(const TString& delimiters);

		//! @brief 文字列を検索します。
		//! @param[in] keyword 検索する文字列
		//! @param[in] position 検索開始位置
		//! @return 検索した文字列の開始位置
		int Find(TString keyword, int position = 0);

		//! @brief フォーマットに従ってパラメータを文字列化します。
		//! @param[in] format 文字列フォーマット
		//! @return フォーマットに従って書式化した自分自身
		TString& Format(LPCTSTR format, ...);

		//! @brief SJIS文字列を取り込みます。
		//! @param[in] lpcszSJIS ヌルターミネートされた文字列
		//! @return 変換に成功か否か
		//! @retval true 成功
		//! @retval false 失敗
		bool FromSJIS(LPCSTR lpcszSJIS);

		//! @brief SJIS文字列を出力します。
		//! @param[out] lpszSJIS SJIS文字列
		//! @param[in] dwLen SJIS文字列を格納するバッファサイズ
		//! @return 書き込んだバイト数
		int ToSJIS(LPSTR lpszSJIS, DWORD dwLen);

	protected:
		VOID Copy(LPCTSTR lpctszString);
		VOID Add(LPCTSTR lpctszString);
		int Compare(LPCTSTR lpctszString1, LPCTSTR lpctszString2, int size);

		LPTSTR _lptszString;
	};
}
