/**
 @file		framework.h
 @brief		このプロジェクトのポーティングに関する情報
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する

#ifdef WINDOWSLIBRARY_EXPORTS
#pragma message("DLL EXPORTING...")
#ifndef DLL_DECLSPEC
#define DLL_DECLSPEC __declspec(dllexport)
#endif
#else
#ifndef DLL_DECLSPEC
#define DLL_DECLSPEC __declspec(dllimport)
#endif
#pragma comment(lib, "WindowsLibrary")
#pragma message("WindowsLibrary is now importing...")
#endif

#include <windows.h>
#include <tchar.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <mstcpip.h>
#include <timeapi.h>
#include <psapi.h>
#include <iphlpapi.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ktmw32.h>
#include <objbase.h>
#include <wincrypt.h>

#pragma comment (lib, "ws2_32")
#pragma comment (lib, "winmm")
#pragma comment (lib, "psapi")
#pragma comment (lib, "iphlpapi.lib")
#pragma comment (lib, "KtmW32.lib")
#pragma comment (lib, "crypt32.lib")