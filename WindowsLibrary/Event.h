//! @file	Event.h
//! @brief	�C�x���g�Ɋւ���WindowsAPI���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#pragma once

#include "WindowsLibrary.h"

namespace alt
{
	//! @class	Event
	//! @brief	�C�x���g�Ɋւ���WindowsAPI���W�񂵂��N���X
	class DLL_DECLSPEC Event : public WaitableHandleLibrary
	{
	public:
		//! @brief		�C�x���g���쐬���܂��B
		//! @param[in]	lpctszEventName �C�x���g��
		//! @param[in]	bManualReset TRUE:�蓮���Z�b�g FALSE:�������Z�b�g
		//! @param[in]	bInitialState TRUE:������ԂŃV�O�i����� FALSE:������ԂŔ�V�O�i�����
		//! @return		BOOL
		//! @retval		TRUE:����
		//! @retval		FALSE:���s
		BOOL Create(LPCTSTR lpctszEventName, BOOL bManualReset, BOOL bInitialState);

		//! @brief		�C�x���g���I�[�v�����܂��B
		//! @param[in]	lpctszEventName �C�x���g��
		//! @return		BOOL
		//! @retval		TRUE:����
		//! @retval		FALSE:���s
		BOOL Open(LPCTSTR lpctszEventName);

		//! @brief	�C�x���g���Z�b�g(�V�O�i����Ԃ�)���܂��B
		//! @return	BOOL
		//! @retval	TRUE:����
		//! @retval	FALSE:���s
		BOOL Set();

		//! @brief	�C�x���g�����Z�b�g(��V�O�i����Ԃ�)���܂��B
		//! @return	BOOL
		//! @retval	TRUE:����
		//! @retval	FALSE:���s
		BOOL Reset();

		//! @brief	�����C�x���g���p���X(�V�O�i����ԁ���V�O�i����Ԃ�)���܂��B
		//! @return	BOOL
		//! @retval	TRUE:����
		//! @retval	FALSE:���s
		BOOL Pulse();
	};
}