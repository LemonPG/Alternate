//! @file	Mutex.cpp
//! @brief	�~���[�e�b�N�X�Ɋւ���WindowsAPI���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2020.3.29

#include "pch.h"
#include "Mutex.h"

using namespace alt;

BOOL Mutex::Create(LPCTSTR lpctszName)
{
	_hObject = ::CreateMutex(nullptr, FALSE, lpctszName);

	return _hObject == INVALID_HANDLE_VALUE ? FALSE : TRUE;
}

BOOL Mutex::Open(LPCTSTR lpctszName)
{
	_hObject = ::OpenMutex(MUTEX_ALL_ACCESS, FALSE, lpctszName);

	return _hObject == INVALID_HANDLE_VALUE ? FALSE : TRUE;
}

BOOL Mutex::Release()
{
	return ::ReleaseMutex(_hObject);
}