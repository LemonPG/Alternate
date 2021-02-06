//! @file	Core.h
//! @brief	SqLite3����N���X(Core)
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.4

#pragma once

#include <Windows.h>
#include "sqlite3.h"

namespace alt
{
	namespace db
	{
		//! @class Core
		//! @brief SqLite3����N���X(Core)
		//! @sa https://www.sqlite.org/cintro.html
		class Core
		{
		public:
			//! @brief �R���X�g���N�^
			Core() { _lastError = SQLITE_OK; }

			//! @brief �f�X�g���N�^
			virtual ~Core() {}

		protected:
			//! @brief �e�֐��̖߂�l���苤��
			bool getResponse() { return _lastError != SQLITE_OK ? false : true; }

			//! @brief SQLite3�֐��G���[�l
			int _lastError;
		};
	}
}