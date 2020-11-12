/**
 @file		Thread.h
 @brief		�X���b�h�Ɋւ���WindowsAPI���W�񂵂��N���X
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "WindowsLibrary.h"
#include "FunctionPointers.hpp"

namespace alt
{
	/**
	 @enum	ThreadPriority
	 @brief	�X���b�h�̗D�揇��
	 */
	enum class ThreadPriority
	{
		Critical = THREAD_PRIORITY_TIME_CRITICAL,
		Highest = THREAD_PRIORITY_HIGHEST,
		AboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,
		Normal = THREAD_PRIORITY_NORMAL,
		BelowNormal = THREAD_PRIORITY_BELOW_NORMAL,
		Lowest = THREAD_PRIORITY_LOWEST,
		Idle = THREAD_PRIORITY_IDLE
	};

	/**
	 @class	Thread
	 @brief	�X���b�h�Ɋւ���WindowsAPI���W�񂵂��N���X
	 */
	class DLL_DECLSPEC Thread : public WaitableHandleLibrary
	{
	public:
		Thread();
		Thread(skeleton::ICallback* callback);

		/**
		 @brief		�X���b�h���쐬���܂��B
		 @param[in]	function �X���b�h�N������֐�
		 @param[in] lpvParam �X���b�h�@�\����֐��ւ̃p�����[�^
		 @param[in]	dwCreationFlag CREATE_SUSPENDED���w�肷��ƋN���Ɠ����ɒ�~���܂��B
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		 */
		BOOL Create(PTHREAD_START_ROUTINE function = nullptr, LPVOID lpvParam = nullptr, DWORD dwCreationFlag = 0);

		/**
		 @brief		�X���b�h���ꎞ��~���܂��B
		 @return	DWORD
		 @retval	�O��܂łɒ�~������
		 @retval	-1(���s)
		 */
		DWORD Suspend();

		/**
		 @brief		�X���b�h���ĊJ���܂��B
		 @return	DWORD
		 @retval	�O��܂łɒ�~������
		 @retval	-1(���s)
		 */
		DWORD Resume();

		/**
		 @brief		�X���b�h���s�D��x��ύX���܂��B
		 @param[in]	priority �X���b�h���s�D��x
		 @return	BOOL
		 @retval	TRUE(����)
		 @retval	FALSE(���s)
		 */
		BOOL SetPriority(ThreadPriority priority);

	protected:

		skeleton::ICallback* _callback;
		DWORD					_threadID;
	};
}