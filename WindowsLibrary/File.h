/**
 @file		File.h
 @brief		�t�@�C��IO�Ɋւ���WindowsAPI���W�񂵂��N���X
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	/**
	 @class	File
	 @brief	�t�@�C��IO�Ɋւ���WindowsAPI���W�񂵂��N���X
	*/
	class DLL_DECLSPEC File : public ReadWriteHandleLibrary
	{
	public:
		/**
		 @brief		�t�@�C�����쐬�A�I�[�v�����܂��B
		 @param[in]	lpctszFileName �쐬����t�@�C����
		 @param[in] dwDesiredAccess {GENERIC_READ, GENERIC_WRITE, GENERIC_ALL}
		 @param[in] dwShareMode {FILE_SHARE_READ, FILE_SHARE_WRITE}
		 @param[in] dwCreationDisposition {CREATE_ALWAYS, OPEN_EXISTING}
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		*/
		BOOL Create(LPCTSTR lpctszFileName, DWORD dwDesiredAccess, DWORD dwShareMode, DWORD dwCreationDisposition);

		/**
		 @brief		�t�@�C���|�C���^���ړ����܂��B
		 @param[in]	dwMoveMethod {FILE_BEGIN, FILE_CURRENT, FILE_END}
		 @param[in]	liDistanceToMove �t�@�C���|�C���^�̈ړ�����
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		 */
		BOOL SetPointer(DWORD dwMoveMethod, LARGE_INTEGER liDistanceToMove = { 0 });
		
		/**
		 @brief		���̃t�@�C���ǂݍ��݈ʒu�Ńt�@�C�����I�[���܂��B
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		 */
		BOOL SetEOF();

		/**
		 @brief		�t�@�C���T�C�Y���擾���܂��B
		 @return	�t�@�C���T�C�Y(�o�C�g)
		 */
		LONGLONG GetSize();

		/**
		 @brief		�t�@�C���̎�ނ��擾���܂��B
		 @return	DWORD
		 @retval	FILE_TYPE_CHAR(0x0002)
		 @retval	FILE_TYPE_DISK(0x0001)
		 @retval	FILE_TYPE_PIPE(0x0003)
		 @retval	FILE_TYPE_REMOTE(0x8000) unused.
		 @retval	FILE_TYPE_UNKNOWN(0x0000)
		 @note		WindowsAPI GetFileType()���g�p���܂��B
		 */
		DWORD GetType();

		/**
		 @brief		�t�@�C�������łɑ���\���ۂ��B
		 @return	BOOL
		 @retval	FALSE(�܂��t�@�C������͂ł��Ȃ�)
		 @retval	TRUE(�t�@�C������\)
		 */
		BOOL IsOpen() { return _hObject == INVALID_HANDLE_VALUE ? FALSE : TRUE; };
	};
}