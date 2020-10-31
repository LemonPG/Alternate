/**
 @file		Exception.hpp
 @brief		��O�Ɋւ���N���X
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

#define ALT_REASON_INVALID_ARGUMENT _T("�����̐ݒ肪�ُ�ł��B")
#define ALT_REASON_RUNTIME_ERROR	_T("���s���ɃG���[���������܂����B")

namespace alt
{
	/**
	 @class	Exception
	 @brief	���ƂȂ��O�N���X
	 */
	class Exception : public WindowsLibrary
	{
	public:
		Exception() {};
		~Exception() {};
	};

	/**
	 @class	InvalidArgmentException
	 @brief	�����ݒ�G���[��O
	 */
	class InvalidArgmentException : Exception
	{
	public:
		InvalidArgmentException() {};
		~InvalidArgmentException() {};

		LPCTSTR getReason() { return ALT_REASON_INVALID_ARGUMENT; }
	};

	//
	// ���s���G���[��O
	//
	/**
	 @class	RuntimeException
	 @brief	���s���G���[��O
	 */
	class RuntimeException : Exception
	{
	public:
		RuntimeException() {};
		~RuntimeException() {};

		LPCTSTR getReason() { return ALT_REASON_RUNTIME_ERROR; }
	};
}