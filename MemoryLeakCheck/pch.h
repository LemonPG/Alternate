/**
 @file		pch.h
 @brief		�v���R���p�C���ς݃w�b�_�[ �t�@�C���ł��B
 @note      ���̃t�@�C���́A���̌�̃r���h�̃r���h �p�t�H�[�}���X�����コ���邽�� 1 �񂾂��R���p�C������܂��B
			�R�[�h�⊮�⑽���̃R�[�h�Q�Ƌ@�\�Ȃǂ� IntelliSense �p�t�H�[�}���X�ɂ��e�����܂��B
			�������A�����Ɉꗗ�\������Ă���t�@�C���́A�r���h�Ԃł����ꂩ���X�V�����ƁA���ׂĂ��ăR���p�C������܂��B
			�p�ɂɍX�V����t�@�C���������ɒǉ����Ȃ��ł��������B�ǉ�����ƁA�p�t�H�[�}���X��̗��_���Ȃ��Ȃ�܂��B
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

// �v���R���p�C������w�b�_�[�������ɒǉ����܂�
#include "framework.h"

#ifdef _DEBUG
#include "crtdbg.h"
#define malloc(X) _malloc_dbg(X,_NORMAL_BLOCK,__FILE__,__LINE__) 
#define new ::new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define CRT_SET_DEBUG_FLAG _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_DELAY_FREE_MEM_DF | _CRTDBG_CHECK_ALWAYS_DF | _CRTDBG_LEAK_CHECK_DF)
#else
#define CRT_SET_DEBUG_FLAG
#endif

