/**
 @file		Console.h
 @brief		�R���\�[���Ɋւ���WindowsAPI���W�񂵂��N���X
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
	 @brief	�R���\�[���o�͎��̕����F�ݒ�
	 */
	enum class ForeColor
	{
		//! ��
		Black = 0,
		//! ��
		Blue = FOREGROUND_BLUE,
		//! ��(����)
		BlueH = Blue | FOREGROUND_INTENSITY,
		//! ��
		Green = FOREGROUND_GREEN,
		//! ��(����)
		GreenH = Green | FOREGROUND_INTENSITY,
		//! ��
		Red = FOREGROUND_RED,
		//! ��(����)
		RedH = Red | FOREGROUND_INTENSITY,
		//! �V�A��
		Cyan = (Blue | Green),
		//! �V�A��(����)
		CyanH = Cyan | FOREGROUND_INTENSITY,
		//! �}�[���^
		Magenta = (Blue | Red),
		//! �}�[���^(����)
		MagentaH = Magenta | FOREGROUND_INTENSITY,
		//! ��
		Yellow = (Green | Red),
		//! ��(����)
		YellowH = Yellow | FOREGROUND_INTENSITY,
		//! ��
		White = (Blue | Green | Red),
		//! ��(����)
		WhiteH = White | FOREGROUND_INTENSITY
	};

	/**
	 @enum	BackColor
	 @brief	�R���\�[���o�͎��̔w�i�F�ݒ�
	 */
	enum class BackColor
	{
		//! ��
		Black = 0,
		//! ��
		Blue = BACKGROUND_BLUE,
		//! ��(����)
		BlueH = Blue | BACKGROUND_INTENSITY,
		//! ��
		Green = BACKGROUND_GREEN,
		//! ��(����)
		GreenH = Green | BACKGROUND_INTENSITY,
		//! ��
		Red = BACKGROUND_RED,
		//! ��(����)
		RedH = Red | BACKGROUND_INTENSITY,
		//! �V�A��
		Cyan = (Blue | Green),
		//! �V�A��(����)
		CyanH = Cyan | BACKGROUND_INTENSITY,
		//! �}�[���^
		Magenta = (Blue | Red),
		//! �}�[���^(����)
		MagentaH = Magenta | BACKGROUND_INTENSITY,
		//!	��
		Yellow = (Green | Red),
		//! ��(����)
		YellowH = Yellow | BACKGROUND_INTENSITY,
		//! ��
		White = (Blue | Green | Red),
		//! ��(����)
		WhiteH = White | BACKGROUND_INTENSITY
	};

	/**
	 @class	Console
	 @brief	�R���\�[���Ɋւ���N���X
	 */
	class DLL_DECLSPEC Console : public HandleLibrary
	{
	public:
		//! @brief �R���X�g���N�^
		Console();

		//! @brief �f�X�g���N�^
		virtual ~Console();

		//! @brief �R���\�[���o�̓E�B���h�E���쐬���܂��B
		BOOL Create();

		//! @brief Console�N���X�����������܂��B
		BOOL Init();

		//! @brief �����F�A�w�i�F��ݒ肵�܂��B
		BOOL SetColor(ForeColor foreColor, BackColor backColor);

		//! @brief �R���\�[���ɕ������o�͂��܂��B
		DWORD Write(LPCTSTR lpctszString);

		//! @brief �R���\�[���ɕ������o�͂��܂��B
		VOID Format(LPCTSTR format, ...);

		//! @brief �R���\�[���^�C�g����ݒ肵�܂��B
		BOOL SetTitle(LPCTSTR lpctszTitle);

		//! @brief �o�͈ʒu��ݒ肵�܂��B
		BOOL SetCursorPosition(SHORT x, SHORT y);

		//! @brief �o�b�t�@�T�C�Y��ݒ肵�܂��B
		BOOL SetBufferSize(SHORT x, SHORT y);

		//! @brief �E�B���h�E�T�C�Y��ݒ肵�܂��B
		BOOL SetWindowInfo(SHORT width, SHORT height);

		//! @brief �R���\�[�����N���A���܂��B
		VOID Clear();

	private:
		BOOL GetScreenBufferInfo(CONSOLE_SCREEN_BUFFER_INFO& csbi);

		//! @brief �R���\�[���E�B���h�E�o�͏��
		CONSOLE_SCREEN_BUFFER_INFO _prevConsoleScreenBufferInfo;
	};
}

