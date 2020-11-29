/**
 @file		ArrayMemoryLeakCheck.h
 @brief		Array�̃������[���[�N���m�F���܂��B
 @author	kumakuma0421@gmail.com
 @date		2020.03.01
 */

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