/**
 @file		framework.h
 @brief		���̃v���W�F�N�g�̃|�[�e�B���O�Ɋւ�����
 @author	kumakuma0421@gmail.com
 @date		2020.05.05
 */
#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����قƂ�ǎg�p����Ă��Ȃ����������O����

#ifdef MIDDLELIBRARY_EXPORTS
#pragma message("DLL EXPORTING...")
#define DLL_DECLSPEC __declspec(dllexport)
#else
#define DLL_DECLSPEC __declspec(dllimport)
#pragma comment(lib, "MiddleLibrary")
#pragma message("MiddleLibrary is now importing...")
#pragma comment(lib, "WindowsLibrary")
#pragma message("WindowsLibrary is now importing...")
#endif

#include <windows.h>
#include <tchar.h>
#include <limits.h>
#include <exception>
#include <vector>
#include <memory>
#include <functional>
#include <map>
#include <string>
#include <queue>
