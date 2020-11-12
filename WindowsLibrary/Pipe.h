/**
 @file		Pipe.h
 @brief		パイプに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2020.4.6
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	/**
	 @class	Pipe
	 @brief	パイプに関するWindowsAPIを集約したクラス
	 */
	class DLL_DECLSPEC Pipe : public WindowsLibrary
	{
	public:
		Pipe();
		virtual ~Pipe();

		BOOL Create();
		DWORD Peek(LPVOID lpvBuf, DWORD dwSize);
		DWORD Read(LPVOID lpvBuf, DWORD dwSize);
		BOOL Write(LPVOID lpvBuf, DWORD dwSize);
		BOOL Close();

		HANDLE GetReadHandle() { return _hRead; };
		HANDLE GetWriteHandle() { return _hWrite; };

	private:
		HANDLE _hRead;
		HANDLE _hWrite;
	};
}