/**
 @file		OSSLibrary.cpp
 @brief		Open Source Software ���W�񂵂��v���W�F�N�g�t�@�C��
 @note		DllMain()�̃v���g�^�C�v�������Ő錾���Ă��܂��B
 @author	kumakuma0421@gmail.com
 @date		2020.05.07
 */
#pragma once

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpvReserved);

namespace oss
{
	class DLL_DECLSPEC OSSLibrary
	{
	public:
		OSSLibrary();
		virtual ~OSSLibrary();
	};
}