/**
 @file		NamedPipe.h
 @brief		���O�t���p�C�v�Ɋւ���WindowsAPI���W�񂵂��N���X
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
	 @brief	���O�t���p�C�v�Ɋւ���WindowsAPI���W�񂵂��N���X
	*/
	class DLL_DECLSPEC NamedPipe : public ReadWriteHandleLibrary
	{
	public:
		/**
		 @brief		�p�C�v���쐬���܂��B
		 @param[in]	lpctszName �p�C�v��
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		 @details	�p�C�v���͓����Ő������ɕ⊮���܂��B
		 */
		BOOL Create(LPCTSTR lpctszName);

		/**
		 @brief		�T�[�o�[���ŃN���C�A���g�ڑ���ҋ@���܂��B
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		 */
		BOOL Connect();

		/**
		 @brief	�p�C�v���I�[�v�����܂��B
		 @param[in]	lpctszName �p�C�v��
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		 @details	�p�C�v���͓����Ő������ɕ⊮���܂��B
		 */
		BOOL Open(LPCTSTR lpctszName);

		/**
		 @brief	�N���C�A���g���ŃT�[�o�[�ڑ���ҋ@���܂��B
		 @param[in]	lpctszName	�p�C�v��
		 @param[in]	dwTimeout	�^�C���A�E�g����(�~���b)
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		 */
		BOOL Wait(LPCTSTR lpctszName, DWORD dwTimeout = NMPWAIT_USE_DEFAULT_WAIT);
	};
}