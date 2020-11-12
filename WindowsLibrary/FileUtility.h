/**
 @file		FileUtility.h
 @brief		�t�@�C���n���h���𔺂�Ȃ��t�@�C��IO�Ɋւ���WindowsAPI���W�񂵂��N���X
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
	 @brief		�t�@�C���n���h���𔺂�Ȃ��t�@�C��IO�Ɋւ���WindowsAPI���W�񂵂��N���X
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
		 @brief SymbolicLink��dir�R�}���h��'SYMLINK'�A'SYMLINKD'��
		        �\�������B�܂��G�N�X�v���[���ł̓V���[�g�J�b�g��
		        ��󂪃A�C�R���ɕ\�������B�������A�Ǘ��Ҍ������쐬
		        �ɕK�v�ƂȂ�B
		        �R�}���h�́Amklink �`�܂���mklink /d �`�ō쐬����
		*/
		static BOOL MakeSymbolicLink(LPCTSTR source, LPCTSTR link, BOOL isFile = TRUE);

		/**
		 @brief HardLink��dir�R�}���h�ŋ�ʂ����Ȃ��B�A�C�R���ɂ�
		        �ω�������Ȃ��B������͊Ǘ��Ҍ������s�v�ł���B
		        �R�}���h�́Amklink /h �`�ō쐬����B�폜��del�B
		        �f�B���N�g���ɑ΂��Ă͍쐬�s�B����{�����[���̂݁B
		*/
		static BOOL MakeHardLink(LPCTSTR source, LPCTSTR link);
	};
}
