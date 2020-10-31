#pragma once

#include "Array.hpp"
#include "ObjectHolder.h"

namespace LeakCheck
{
	class ArrayMemoryLeakCheck
	{
	public:
		ArrayMemoryLeakCheck();
		virtual ~ArrayMemoryLeakCheck();

		virtual BOOL Init();
		virtual BOOL DoAction();
	};
}