#pragma once

#include <Windows.h>
#include "sqlite3.h"

namespace alt
{
	namespace db
	{
		// @sa https://www.sqlite.org/cintro.html
		class Core
		{
		public:
			Core()
			{
				_lastError = SQLITE_OK;
			}

			virtual ~Core()
			{

			}

		protected:
			//
			// @brief �e�֐��̖߂�l���苤��
			//
			bool getResponse()
			{
				return _lastError != SQLITE_OK ? false : true;
			}

			// @brief SQLite3�֐��߂�l
			int _lastError;
		};
	}
}