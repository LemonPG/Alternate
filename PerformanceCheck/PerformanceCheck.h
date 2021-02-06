//! @file	PerformanceCheck.h
//! @brief	���\����p
//! @author	kumakuma0421@gmail.com
//! @date	2020.03.01

#pragma once

#include "TString.h"
#include "Console.h"

#define CONFIG_FILE _T(".\\PerformanceCheck.ini")

namespace PerfCheck
{
	//! @class	PerformanceCheck
	//! @brief	���\����p
	class PerformanceCheck
	{
	public:
		//! @brief �R���X�g���N�^
		PerformanceCheck();

		//! @brief �f�X�g���N�^
		virtual ~PerformanceCheck();

		//! @brief		����������
		//! @param[in]	console Console�I�u�W�F�N�g
		//! @note		Console�͏��������Ă������ƁB
		virtual VOID Init(alt::Console& console);

		//! @brief  �����J�n
		//! @return ��������
		//! @retval TRUE:����
		//! @retval FALSE:���s
		//! @note   �������z�֐��ł��B
		virtual BOOL DoAction() = 0;

		void Write(LPCTSTR message);
		void Pos(SHORT x, SHORT y);
		void Size(SHORT width, SHORT height);
		void Buffer(SHORT x, SHORT y);
		void Clear();

	private:
		alt::Console* _con;
	};
}