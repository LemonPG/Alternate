//! @file	RingBuffer.h
//! @brief	リングバッファに関するクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.4

#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	//! @class	RingBuffer
	//! @brief	リングバッファに関するクラス
	class DLL_DECLSPEC RingBuffer : public WindowsLibrary
	{
	public:
		RingBuffer();
		RingBuffer(size_t size);
		virtual ~RingBuffer();

		BOOL Init(size_t size);
		BOOL Clear();
		BOOL Write(LPBYTE lpbyBuffer, size_t size);
		BOOL Read(LPBYTE lpbyBuf, size_t size);
		size_t Remain();

	private:
		LPBYTE _lpbyStartPoint;
		LPBYTE _lpbyEndPoint;
		size_t _size;
		size_t _remainSize;

		LPBYTE _lpbyReadPoint;
		LPBYTE _lpbyWritePoint;
	};
}