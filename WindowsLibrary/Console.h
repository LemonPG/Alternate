/**
 @file		Console.h
 @brief		コンソールに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	/**
	 @enum	ForeColor
	 @brief	コンソール出力時の文字色設定
	 */
	enum class ForeColor
	{
		//! 黒
		Black = 0,
		//! 青
		Blue = FOREGROUND_BLUE,
		//! 青(強調)
		BlueH = Blue | FOREGROUND_INTENSITY,
		//! 緑
		Green = FOREGROUND_GREEN,
		//! 緑(強調)
		GreenH = Green | FOREGROUND_INTENSITY,
		//! 赤
		Red = FOREGROUND_RED,
		//! 赤(強調)
		RedH = Red | FOREGROUND_INTENSITY,
		//! シアン
		Cyan = (Blue | Green),
		//! シアン(強調)
		CyanH = Cyan | FOREGROUND_INTENSITY,
		//! マゼンタ
		Magenta = (Blue | Red),
		//! マゼンタ(強調)
		MagentaH = Magenta | FOREGROUND_INTENSITY,
		//! 黄
		Yellow = (Green | Red),
		//! 黄(強調)
		YellowH = Yellow | FOREGROUND_INTENSITY,
		//! 白
		White = (Blue | Green | Red),
		//! 白(強調)
		WhiteH = White | FOREGROUND_INTENSITY
	};

	/**
	 @enum	BackColor
	 @brief	コンソール出力時の背景色設定
	 */
	enum class BackColor
	{
		//! 黒
		Black = 0,
		//! 青
		Blue = BACKGROUND_BLUE,
		//! 青(強調)
		BlueH = Blue | BACKGROUND_INTENSITY,
		//! 緑
		Green = BACKGROUND_GREEN,
		//! 緑(強調)
		GreenH = Green | BACKGROUND_INTENSITY,
		//! 赤
		Red = BACKGROUND_RED,
		//! 赤(強調)
		RedH = Red | BACKGROUND_INTENSITY,
		//! シアン
		Cyan = (Blue | Green),
		//! シアン(強調)
		CyanH = Cyan | BACKGROUND_INTENSITY,
		//! マゼンタ
		Magenta = (Blue | Red),
		//! マゼンタ(強調)
		MagentaH = Magenta | BACKGROUND_INTENSITY,
		//!	黄
		Yellow = (Green | Red),
		//! 黄(強調)
		YellowH = Yellow | BACKGROUND_INTENSITY,
		//! 白
		White = (Blue | Green | Red),
		//! 白(強調)
		WhiteH = White | BACKGROUND_INTENSITY
	};

	/**
	 @class	Console
	 @brief	コンソールに関するクラス
	 */
	class DLL_DECLSPEC Console : public HandleLibrary
	{
	public:
		//! @brief コンストラクタ
		Console();

		//! @brief デストラクタ
		virtual ~Console();

		//! @brief コンソール出力ウィンドウを作成します。
		BOOL Create();

		//! @brief Consoleクラスを初期化します。
		BOOL Init();

		//! @brief 文字色、背景色を設定します。
		BOOL SetColor(ForeColor foreColor, BackColor backColor);

		//! @brief コンソールに文字を出力します。
		DWORD Write(LPCTSTR lpctszString);

		//! @brief コンソールに文字を出力します。
		VOID Format(LPCTSTR format, ...);

		//! @brief コンソールタイトルを設定します。
		BOOL SetTitle(LPCTSTR lpctszTitle);

		//! @brief 出力位置を設定します。
		BOOL SetCursorPosition(SHORT x, SHORT y);

		//! @brief バッファサイズを設定します。
		BOOL SetBufferSize(SHORT x, SHORT y);

		//! @brief ウィンドウサイズを設定します。
		BOOL SetWindowInfo(SHORT width, SHORT height);

		//! @brief コンソールをクリアします。
		VOID Clear();

	private:
		BOOL GetScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO& csbi);

		//! @brief コンソールウィンドウ出力情報
		CONSOLE_SCREEN_BUFFER_INFO _prevConsoleScreenBufferInfo;
	};
}

