/**
 @file		FileUtility.h
 @brief		ファイルハンドルを伴わないファイルIOに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "File.h"
#include "TString.h"
#include "Array.hpp"

namespace alt
{
	/**
	 @class		FileUtility
	 @brief		ファイルハンドルを伴わないファイルIOに関するWindowsAPIを集約したクラス
	 */
	class DLL_DECLSPEC FileUtility : public WindowsLibrary
	{
	public:
		static BOOL Delete(LPCTSTR name);
		static BOOL Copy(LPCTSTR source, LPCTSTR dest, BOOL bFailIfExists = FALSE);
		static BOOL Move(LPCTSTR source, LPCTSTR dest);
		static BOOL MakeDir(LPCTSTR name);
		static BOOL RemoveDir(LPCTSTR name);
		static BOOL IsExist(LPCTSTR name);
		static skeleton::Array<TString> Find(LPCTSTR name);
		static BOOL DirectoryWatch(LPCTSTR watchDirectory);

		/**
		 @brief SymbolicLinkはdirコマンドで'SYMLINK'、'SYMLINKD'と
		        表示される。またエクスプローラではショートカットの
		        矢印がアイコンに表示される。ただし、管理者権限が作成
		        に必要となる。
		        コマンドは、mklink ～またはmklink /d ～で作成する
		*/
		static BOOL MakeSymbolicLink(LPCTSTR source, LPCTSTR link, BOOL isFile = TRUE);

		/**
		 @brief HardLinkはdirコマンドで区別がつかない。アイコンにも
		        変化が現れない。こちらは管理者権限が不要である。
		        コマンドは、mklink /h ～で作成する。削除はdel。
		        ディレクトリに対しては作成不可。同一ボリュームのみ。
		*/
		static BOOL MakeHardLink(LPCTSTR source, LPCTSTR link);
	};
}
