// ----------------------------------------------------------------------------
// framework.h
// ----------------------------------------------------------------------------
#pragma once

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーからほとんど使用されていない部分を除外する

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
