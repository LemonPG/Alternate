//! @file	Diagnostics.h
//! @brief	�V�X�e�����\�Ɋւ���WindowsAPI���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.24

#pragma once

#include "WindowsLibrary.h"

namespace alt
{
	//! @class	Diagnostics
	//! @brief	�V�X�e�����\�Ɋւ���WindowsAPI���W�񂵂��N���X
	class DLL_DECLSPEC Diagnostics : public HandleLibrary
	{
	public:
		//! @brief �R���X�g���N�^
		Diagnostics();

		//! @brief �v���Z�X�����������擾���܂��B
		//! @sa https://blog.goo.ne.jp/masaki_goo_2006/e/7a33fc63935919da2fd3f3bec37f8695
		//typedef struct _PROCESS_MEMORY_COUNTERS {
		//  DWORD  cb;                         //! �\���̂̃T�C�Y
		//  DWORD  PageFaultCount;             //! �y�[�W�E�t�H�[���g��
		//  SIZE_T PeakWorkingSetSize;         //! �ő像�[�L���O�Z�b�g(�������g�p��)
		//  SIZE_T WorkingSetSize;             //! ���݃��[�L���O�Z�b�g(�ő僁�����g�p��)
		//  SIZE_T QuotaPeakPagedPoolUsage;    //! �ő�y�[�W�v�[���̎g�p�T�C�Y(�y�[�W�v�[��)
		//  SIZE_T QuotaPagedPoolUsage;        //! ���݃y�[�W�v�[���̎g�p�T�C�Y
		//  SIZE_T QuotaPeakNonPagedPoolUsage; //! �ő��y�[�W�v�[���̎g�p�T�C�Y(��y�[�W�v�[��)
		//  SIZE_T QuotaNonPagedPoolUsage;     //! ���ݔ�y�[�W�v�[���̎g�p�T�C�Y
		//  SIZE_T PagefileUsage;              //! ���݃y�[�W���O�t�@�C���̎g�p�T�C�Y(���z�������T�C�Y)
		//  SIZE_T PeakPagefileUsage;          //! �ő�y�[�W���O�t�@�C���̎g�p�T�C�Y
		//} PROCESS_MEMORY_COUNTERS, * PPROCESS_MEMORY_COUNTERS;
		//�J�b�R���̓^�X�N�}�l�[�W���ł̕\���ł��B
		BOOL GetProcessMemory(PROCESS_MEMORY_COUNTERS& processMemoryCounters);

		//! @brief �v���Z�XI/O�����擾���܂��B
		//! @sa https://blog.goo.ne.jp/masaki_goo_2006/e/caa997ca0797fe3d240438f179bdab55
		//typedef struct _IO_COUNTERS {
		//  ULONGLONG ReadOperationCount;  // I/O�ǂݎ��
		//  ULONGLONG WriteOperationCount; // I/O��������
		//  ULONGLONG OtherOperationCount; // I/O���̑�
		//  ULONGLONG ReadTransferCount;   // I/O�ǂݎ��o�C�g��
		//  ULONGLONG WriteTransferCount;  // I/O�������݃o�C�g��
		//  ULONGLONG OtherTransferCount;  // I/O���̑��o�C�g��
		//} IO_COUNTERS, * PIO_COUNTERS;
		BOOL GetProcessIO(IO_COUNTERS& ioCounters);

		//! @brief �l�b�g���[�NI/O�����擾���܂��B
		//! @sa http://www.geekpage.jp/programming/iphlpapi/getipstatistics.php
		//typedef struct _MIB_IPSTATS {
		//  DWORD dwForwarding;
		//  DWORD dwDefaultTTL;
		//  DWORD dwInReceives;
		//  DWORD dwInHdrErrors;
		//  DWORD dwInAddrErrors;
		//  DWORD dwForwDatagrams;
		//  DWORD dwInUnknownProtos;
		//  DWORD dwInDiscards;
		//  DWORD dwInDelivers;
		//  DWORD dwOutRequests;
		//  DWORD dwRoutingDiscards;
		//  DWORD dwOutDiscards;
		//  DWORD dwOutNoRoutes;
		//  DWORD dwReasmTimeout;
		//  DWORD dwReasmReqds;
		//  DWORD dwReasmOks;
		//  DWORD dwReasmFails;
		//  DWORD dwFragOks;
		//  DWORD dwFragFails;
		//  DWORD dwFragCreates;
		//  DWORD dwNumIf;
		//  DWORD dwNumAddr;
		//  DWORD dwNumRoutes;
		//} MIB_IPSTATS, *PMIB_IPSTATS;
		BOOL GetIpStatistics(MIB_IPSTATS& mibIPStats);
	};
}