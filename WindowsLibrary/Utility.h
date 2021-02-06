//! @file	Utility.h
//! @brief	�ėp�I�Ɏg���郆�[�e�B���e�B�N���X
//! @author	kumakuma0421@gmail.com
//! @date	2020.2.24

#pragma once

#include "framework.h"
#include "TString.h"

namespace alt
{
	//! @class	Utility
	//! @brief	�ėp�I�Ɏg���郆�[�e�B���e�B�N���X
	class DLL_DECLSPEC Utility
	{
	public:
		static const GUID CreateGUID();
		static const TString MakeGUID();
		static SYSTEMTIME GetLocalTime();
		static TString GetFormatTime(SYSTEMTIME& systemTime);
		static ULARGE_INTEGER GetLocalTimeQuad();
		static SYSTEMTIME GetTimeByFileTime(FILETIME& fileTime);

		//! @brief Windows���N�����Ă���̎��Ԃ�Ԃ��܂��B
		//! @note 49.7���Ń[���ɖ߂�܂��B
#pragma warning (push)
#pragma warning (disable:28159)
		static DWORD GetPastTick() { return ::GetTickCount(); };
#pragma warning (pop)

		//! @brief Windows���N�����Ă���̎��Ԃ�Ԃ��܂��B
		static ULONGLONG GetPastTick64() { return ::GetTickCount64(); };

		//! @brief �e���|�����t�H���_���擾���܂��B
		static TString GetTemporaryPath();

		//! @brief �e���|�����t�@�C�������擾���܂��B
		//! @param[in] lpctszPath �t�@�C���p�X
		//! @param[in] lpctszPrefix �t�@�C�����v���t�B�b�N�X(�R�����܂�)
		//! @param[in] nNumber �t�@�C�����Ɏg�p�����ԍ�(���ʂP�U�r�b�g�܂�)
		//! @note nNumber�ɂO���w�肷��ƃV�X�e�����������܂��B
		static TString GetTemporaryFileName(LPCTSTR lpctszPath, LPCTSTR lpctszPrefix, UINT nNumber);

		static BOOL Base64Encode(LPBYTE lppbyString, DWORD dwLength, TString& response);
		static BOOL Base64Decode(TString& source, LPBYTE lpbyBuffer, DWORD& dwBuffer);

		static skeleton::Array<TString> GetEnvironments();
		static TString GetEnv(LPCTSTR lpctszKeyword);
	};
}