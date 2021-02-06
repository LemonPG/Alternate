//! @file	TStringMemoryLeakCheck.h
//! @brief	TString�̃������[���[�N���m�F���܂��B
//! @author	kumakuma0421@gmail.com
//! @date	2020.03.01

#pragma once

#include "TString.h"

namespace LeakCheck
{
	//! @class		TStringMemoryLeakCheck
	//! @brief		TString�̃������[���[�N�`�F�b�N�N���X
	class TStringMemoryLeakCheck
	{
	public:
		//! @brief �R���X�g���N�^
		TStringMemoryLeakCheck();

		//! @brief �f�X�g���N�^
		virtual ~TStringMemoryLeakCheck();

		//! @brief ����������
		virtual BOOL Init();

		//! @brief �������[���[�N����
		virtual BOOL DoAction();

	private:
		BOOL DoAction1();
		BOOL DoAction2();
		BOOL DoAction3();
		BOOL DoAction4();
	};
}