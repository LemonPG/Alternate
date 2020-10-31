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
			// @brief 各関数の戻り値判定共通
			//
			bool getResponse()
			{
				return _lastError != SQLITE_OK ? false : true;
			}

			// @brief SQLite3関数戻り値
			int _lastError;
		};
	}
}