/**
 @file		TStringMemoryLeakCheck.h
 @brief		TStringのメモリーリークを確認します。
 @author	kumakuma0421@gmail.com
 @date		2020.03.01
 */

#pragma once

#include "TString.h"

namespace LeakCheck
{
	class TStringMemoryLeakCheck
	{
	public:
		TStringMemoryLeakCheck();
		virtual ~TStringMemoryLeakCheck();

		virtual BOOL Init();
		virtual BOOL DoAction();

	private:
		BOOL DoAction1();
		BOOL DoAction2();
		BOOL DoAction3();
		BOOL DoAction4();
	};
}