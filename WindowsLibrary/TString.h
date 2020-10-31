/**
 @file		TString.h
 @brief		������Ɋւ���WindowsAPI���W�񂵂��N���X
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"
#include "Array.hpp"

namespace alt
{
	/**
	 @class TString
	 @brief ������Ɋւ���WindowsAPI���W�񂵂��N���X
	 */
	class DLL_DECLSPEC TString : public WindowsLibrary
	{
	public:
		//! @brief �R���X�g���N�^
		TString();

		//! @brief		�R���X�g���N�^
		//! @param[in]	lpctszString �������Ɋi�[���镶����
		TString(LPCTSTR lpctszString);

		//! @brief		�R���X�g���N�^
		//! @param[in]	string �������Ɋi�[���镶����
		TString(const TString& string);

		//! @brief		�R���X�g���N�^
		//! @param[in]	length �������Ɋm�ۂ��郁�����T�C�Y(������)
		//! @note		API�ȂǂŁATCHAR[256]���K�v�ȏꍇ�Ɏg�p���܂��B
		//!             Ptr()���g�p����ƁA�������m�ۍς݂̃|�C���^��
		//!             �g�p�ł��܂��B
		TString(int length);

		//! @brief �f�X�g���N�^
		virtual ~TString();

		//! @brief �����Ŋm�ۂ��Ă��镶����|�C���^���擾���܂��B
		//! @return �ێ����Ă��镶����̃|�C���^
		LPTSTR Ptr() const { return _lptszString; };

		//! @brief �����Ŋm�ۂ��Ă��镶����|�C���^���擾���܂��B
		//! @return �ێ����Ă��镶����̃|�C���^
		LPCTSTR Ctr() const { return (LPCTSTR)_lptszString; };

		//! @brief �����Ŋm�ۂ��Ă��镶���񐔂��擾���܂��B
		//! @return ������
		int Len() const { return lstrlen(_lptszString); };

		//! @brief �����Ŋm�ۂ��Ă��镶����(�o�C�g��)���擾���܂��B
		//! @return �o�C�g��
		int Byte() const { return this->Len() * sizeof(TCHAR); };

		//! @brief ������Ɣ�r���܂��B
		//1 @param[in]	lpctszString ��r���镶����
		//! @return ��v���邩�ۂ�
		//! @retval TRUE ��v����
		//! @retval FALSE ��v���Ȃ�
		BOOL operator == (LPCTSTR lpctszString);

		//! @brief TString�ƕ�������r���܂��B
		//! @param[in]	string ��r����TString�I�u�W�F�N�g
		//! @return ��v���邩�ۂ�
		//! @retval TRUE ��v����
		//! @retval FALSE ��v���Ȃ�
		BOOL operator == (const TString& string);

		//! @brief ������Ɣ�r���܂��B
		//1 @param[in]	lpctszString ��r���镶����
		//! @return ��v���Ȃ����ۂ�
		//! @retval TRUE ��v����
		//! @retval FALSE ��v���Ȃ�
		BOOL operator != (LPCTSTR lpctszString);

		//! @brief TString�ƕ�������r���܂��B
		//! @param[in]	string ��r����TString�I�u�W�F�N�g
		//! @return ��v���Ȃ����ۂ�
		//! @retval TRUE ��v����
		//! @retval FALSE ��v���Ȃ�
		BOOL operator != (const TString& string);

		//! @brief ������������܂��B
		//! @param[in]	lpctszString ������
		VOID operator = (LPCTSTR lpctszString);

		//! @brief ������������܂��B
		//! @param[in]	string ������
		VOID operator = (const TString& string);

		//! @brief ������������܂��B
		//! @param[in]	lpctszString ������
		//! @return ������ꂽ�������g
		TString& operator << (LPCTSTR lpctszString);

		//! @brief ������������܂��B
		//! @param[in]	string ������
		//! @return ������ꂽ�������g
		TString& operator << (const TString& string);

		//! @brief ���l�������܂��B
		//! @param[in]	iValue ���l
		//! @return ������ꂽ�������g
		TString& operator << (const int iValue);

		//! @brief �������ǉ����܂��B
		//! @param[in]	string ������
		//! @return �ǉ����ꂽ������̌���
		TString operator + (LPCTSTR lpctszString);

		//! @brief �������ǉ����܂��B
		//! @param[in]	string ������
		//! @return �ǉ����ꂽ������̌���
		TString operator + (TString& string);

		//! @brief ���l�������܂��B
		//! @param[in]	iValue ���l
		//! @return ������ꂽ�������g
		TString& operator += (LPCTSTR lpctszString);

		//! @brief ���l�������܂��B
		//! @param[in]	iValue ���l
		//! @return ������ꂽ�������g
		TString& operator += (const TString& string);

		//! @brief ������̈ꕔ�����o���܂��B
		//! @param[in]	index �ꏊ�̎w��
		//! @return �w�肳�ꂽ�ꏊ�ɂ��镶��
		TCHAR operator [] (int index) const;

		//! @brief ������̑召���r���܂��B
		//! @param[in]	string ��r�Ώ�
		//! @return ��r����
		//! @retval true ��r���鑤��������
		//! @retval false ��r���鑤���傫��
		bool operator < (const TString& string) const;

		//! @brief �����̗]����؂���܂��B
		//! @return �����]����؂������������g
		TString& TrimLeft();

		//! @brief �E���̗]����؂���܂��B
		//! @return �E���]����؂������������g
		TString& TrimRight();

		//! @brief ���E�̗]����؂���܂��B
		//! @return ���E�̗]����؂������������g
		TString& Trim();

		//! @brief �������؂�o���܂��B
		//! @param[in] startPos �؂�o���J�n�ʒu
		//! @param[in] length �؂�o���T�C�Y
		//! @return �؂�o����������
		TString Substring(int startPos, int length = 0);

		//! @brief �������u�����܂��B
		//! @param[in] charsBefore �������镶����
		//! @param[in] charsAfter �u�����镶����
		//! @return �������ʂ�u������������
		TString Replace(TString& charsBefore, TString& charsAfter);

		//! @brief �������u�����܂��B
		//! @param[in] charsBefore �������镶����
		//! @param[in] charsAfter �u�����镶����
		//! @return �������ʂ����ׂĒu������������
		TString ReplaceAll(TString& charsBefore, TString& charsAfter);

		//! @brief ��������w�肵��������ŕ������܂��B
		//! @param[in] delimiters �������镶���̏W��
		//! @return delimiters�P�ʂŕ�������������Q
		//! @note delimiter�ɓ����Ă��镶���͂��ׂĕ����Ώۂł��B
		skeleton::Array<TString> Split(const TString& delimiters);

		//! @brief ��������������܂��B
		//! @param[in] keyword �������镶����
		//! @param[in] position �����J�n�ʒu
		//! @return ��������������̊J�n�ʒu
		int Find(TString keyword, int position = 0);

		//! @brief �t�H�[�}�b�g�ɏ]���ăp�����[�^�𕶎��񉻂��܂��B
		//! @param[in] format ������t�H�[�}�b�g
		//! @return �t�H�[�}�b�g�ɏ]���ď����������������g
		TString& Format(LPCTSTR format, ...);

		//! @brief SJIS���������荞�݂܂��B
		//! @param[in] lpcszSJIS �k���^�[�~�l�[�g���ꂽ������
		//! @return �ϊ��ɐ������ۂ�
		//! @retval true ����
		//! @retval false ���s
		bool FromSJIS(LPCSTR lpcszSJIS);

		//! @brief SJIS��������o�͂��܂��B
		//! @param[out] lpszSJIS SJIS������
		//! @param[in] dwLen SJIS��������i�[����o�b�t�@�T�C�Y
		//! @return �������񂾃o�C�g��
		int ToSJIS(LPSTR lpszSJIS, DWORD dwLen);

	protected:
		VOID Copy(LPCTSTR lpctszString);
		VOID Add(LPCTSTR lpctszString);
		int Compare(LPCTSTR lpctszString1, LPCTSTR lpctszString2, int size);

		LPTSTR _lptszString;
	};
}
