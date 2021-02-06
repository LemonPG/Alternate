//! @file	Statement.h
//! @brief	SqLite3����N���X(Statement)
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.4

#pragma once

#include <Windows.h>
#include "sqlite3.h"
#include "Core.h"
#include "Engine.h"

namespace alt
{
	namespace db
	{
		//! @class Statement
		//! @brief SqLite3����N���X(Statement)
		class Statement : public Core
		{
		public:
			//! @brief �R���X�g���N�^
			Statement()
				:Core()
			{
				_statement = nullptr;
			}

			//! @brief �f�X�g���N�^
			virtual ~Statement()
			{
				if (_statement) Finalize();
			}

			//! @brief		SQL�X�e�[�g�����g�̏���
			//! @param[in]	engine		Engine�C���X�^���X
			//! @param[in]	lpctszSQL	SQL�X�e�[�g�����g
			//! @return		���s����
			//! @retval		true	����
			//! @retval		false	���s
			//! @todo		Engine��Engine&��
			bool Prepare(Engine engine, LPCTSTR lpctszSQL)
			{
				_lastError = ::sqlite3_prepare16(engine.GetEngine(), lpctszSQL, -1, &_statement, nullptr);
				return getResponse() && _statement != nullptr;
			}

			//! @brief		�p�����[�^�̃o�C���h����
			//! @param[in]	position ��ԍ�
			//! @return		���s����
			//! @retval		true	����
			//! @retval		false	���s
			//! @note		�J������nullptr��ݒ肵�܂�
			bool Bind(int position)
			{
				_lastError = ::sqlite3_bind_null(_statement, position);
				return getResponse();
			}

			//! @brief		�p�����[�^�̃o�C���h����
			//! @param[in]	position	��ԍ�
			//! @param[in]	value		int�l
			//! @return		���s����
			//! @retval		true	����
			//! @retval		false	���s
			bool Bind(int position, int value)
			{
				_lastError = ::sqlite3_bind_int(_statement, position, value);
				return getResponse();
			}

			//! @brief		�p�����[�^�̃o�C���h����
			//! @param[in]	position	��ԍ�
			//! @param[in]	value		sqlite3_int64�l
			//! @return		���s����
			//! @retval		true	����
			//! @retval		false	���s
			bool Bind(int position, sqlite3_int64 value)
			{
				_lastError = ::sqlite3_bind_int64(_statement, position, value);
				return getResponse();
			}

			//! @brief		�p�����[�^�̃o�C���h����
			//! @param[in]	position	��ԍ�
			//! @param[in]	value		double�l
			//! @return		���s����
			//! @retval		true	����
			//! @retval		false	���s
			bool Bind(int position, double value)
			{
				_lastError = ::sqlite3_bind_double(_statement, position, value);
				return getResponse();
			}

			//! @brief		�p�����[�^�̃o�C���h����
			//! @param[in]	position	��ԍ�
			//! @param[in]	value		LPCSTR�l
			//! @return		���s����
			//! @retval		true	����
			//! @retval		false	���s
			bool Bind(int position, LPCSTR value)
			{
				_lastError = ::sqlite3_bind_text(_statement, position, value, (int)lstrlenA(value), nullptr);
				return getResponse();
			}

			//! @brief		�p�����[�^�̃o�C���h����
			//! @param[in]	position	��ԍ�
			//! @param[in]	value		LPCWSTR�l
			//! @return		���s����
			//! @retval		true	����
			//! @retval		false	���s
			bool Bind(int position, LPCWSTR value)
			{
				_lastError = ::sqlite3_bind_text16(_statement, position, value, (int)lstrlenW(value) * sizeof(wchar_t), nullptr);
				return getResponse();
			}

			//! @todo blob, blob64

			//! @brief	�X�e�[�g�����g���s
			//! @return	���s����
			//! @retval	true	����
			//! @retval	false	���s
			bool Execute()
			{
				_lastError = ::sqlite3_step(_statement);
				return getResponse();
			}

			//! @brief	�o�C���h�̃��Z�b�g
			//! @return	���s����
			//! @retval	true	����
			//! @retval	false	���s
			bool ResetBind()
			{
				_lastError = ::sqlite3_reset(_statement);
				bool ret = getResponse();
				if (!ret) return ret;

				_lastError = ::sqlite3_clear_bindings(_statement);
				return getResponse();
			}

			//! @brief	�J�������̎擾
			//! @return	�J������
			int GetColumns()
			{
				return ::sqlite3_column_count(_statement);
			}

			//! @brief	�J�������̎擾
			//! @return	�J������
			LPCTSTR GetColumnName(int position)
			{
				return (LPCTSTR)::sqlite3_column_name16(_statement, position);
			}

			//! @brief	�J�����^�C�v�̎擾
			//! @return �J�����^�C�v
			LPCTSTR GetColumnType(int position)
			{
				return (LPCTSTR)::sqlite3_column_decltype16(_statement, position);
			}

			//! @brief		�s�f�[�^�̎擾
			//! @param[in]	position	�J�����ʒu
			//! @return		�J�����l(int)
			int GetIntValue(int position)
			{
				return ::sqlite3_column_int(_statement, position);
			}

			//! @brief		�s�f�[�^�̎擾
			//! @param[in]	position	�J�����ʒu
			//! @return		�J�����l(sqlite3_int64)
			sqlite3_int64 GetInt64Value(int position)
			{
				return ::sqlite3_column_int64(_statement, position);
			}

			//! @brief		�s�f�[�^�̎擾
			//! @param[in]	position	�J�����ʒu
			//! @return		�J�����l(double)
			double GetDoubleValue(int position)
			{
				return ::sqlite3_column_double(_statement, position);
			}

			//! @brief		�s�f�[�^�̎擾
			//! @param[in]	position	�J�����ʒu
			//! @return		�J�����l(LPCSTR)
			LPCSTR GetStringValue(int position)
			{
				return (LPCSTR)::sqlite3_column_text(_statement, position);
			}

			//! @brief		�s�f�[�^�̎擾
			//! @param[in]	position	�J�����ʒu
			//! @return		�J�����l(LPCTSTR)
			LPCTSTR GetString16Value(int position)
			{
				return (LPCTSTR)::sqlite3_column_text16(_statement, position);
			}

			//! @brief	�I������
			//! @return	���s����
			//! @retval	true	����
			//! @retval	false	���s
			bool Finalize()
			{
				_lastError = sqlite3_finalize(_statement);
				_statement = nullptr;
				return getResponse();
			}

		protected:
			//! @brief �X�e�[�g�����g
			sqlite3_stmt* _statement;
		};
	}
}