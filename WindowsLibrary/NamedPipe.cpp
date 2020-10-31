/**
 @file		NamedPipe.cpp
 @brief		���O�t���p�C�v�Ɋւ���WindowsAPI���W�񂵂��N���X
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#include "pch.h"
#include "NamedPipe.h"

using namespace alt;

BOOL NamedPipe::Create(LPCTSTR lpctszName)
{
	BOOL ret = TRUE;
	TCHAR tszPipeName[MAX_PATH];
	// PIPE_ACCESS_INBOUND, PIPE_ACCESS_OUTBOUND, PIPE_ACCESS_DUPLEX
	// FILE_FLAG_WRITE_THROUGH �o�C�g�^�C�v���[�_�������[�gPC�̎��̂ݗL��
	// FILE_FLAG_OVERLAPPED �񓯊����[�h
	DWORD dwOpenMode = PIPE_ACCESS_DUPLEX;
	// PIPE_TYPE_BYTE �ʏ�̃o�C�i������
	// PIPE_TYPE_MESSAGE ��x�Ɉꕶ
	// PIPE_READMODE_BYTE �o�C�g�X�g���[��
	// PIPE_READMODE_MESSAGE ���b�Z�[�W�X�g���[��
	// PIPE_WAIT ��������܂Ő����Ԃ��Ȃ�
	// PIPE_NO_WAIT ReadFile, WriteFile, ConnectNamedPipe�͐���������Ԃ�
	DWORD dwPipeMode = PIPE_TYPE_BYTE | PIPE_READMODE_BYTE;
	DWORD dwMaxInstance = PIPE_UNLIMITED_INSTANCES;
	DWORD dwOutBuffSize = USHRT_MAX;
	DWORD dwInBufSize = USHRT_MAX;
	DWORD dwDefaultTimeOut = SHRT_MAX;

	wsprintf(tszPipeName, PIPE_NAME_FORMAT, lpctszName);

	_hObject = ::CreateNamedPipe(tszPipeName, dwOpenMode, dwPipeMode, dwMaxInstance, dwOutBuffSize, dwInBufSize, dwDefaultTimeOut, nullptr);
	if (_hObject == INVALID_HANDLE_VALUE)
	{
		ret = FALSE;
	}

	return ret;
}

BOOL NamedPipe::Connect()
{
	return ::ConnectNamedPipe(_hObject, nullptr);
}

BOOL NamedPipe::Open(LPCTSTR lpctszName)
{
	BOOL ret = TRUE;
	TCHAR tszPipeName[MAX_PATH];
	
	wsprintf(tszPipeName, PIPE_NAME_FORMAT, lpctszName);

	_hObject = ::CreateFile(tszPipeName, GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (_hObject == INVALID_HANDLE_VALUE)
	{
		ret = FALSE;
	}

	return ret;
}

BOOL NamedPipe::Wait(LPCTSTR lpctszName, DWORD dwTimeout)
{
	TCHAR tszPipeName[MAX_PATH];

	wsprintf(tszPipeName, PIPE_NAME_FORMAT, lpctszName);
	
	return ::WaitNamedPipe(tszPipeName, dwTimeout);
}