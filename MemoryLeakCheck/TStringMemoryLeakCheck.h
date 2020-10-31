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
	};
}