//! @file	Engine.h
//! @brief	SqLite3����N���X(Engine)
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.4

#pragma once

#include <Windows.h>
#include "sqlite3.h"
#include "Core.h"

namespace alt
{
	namespace db
	{
		//! @class	Engine
		//! @brief SqLite3����N���X(Engine)
		class Engine : public Core
		{
		public:
			//! @brief �R���X�g���N�^
			Engine()
				:Core()
			{
				_engine = nullptr;
				_lastError = SQLITE_OK;
			}

			//! @brief �f�X�g���N�^
			virtual ~Engine()
			{
				if (_engine != nullptr) Close();
			}

			//! @brief �G���[���b�Z�[�W�̎擾
			LPCTSTR GetErrorMessage()
			{
				return (LPCTSTR)::sqlite3_errmsg16(_engine);
			}

			//! @brief		DB�t�@�C���̍쐬�E�I�[�v��
			//! @param[in]	lpctszDBName �f�[�^�x�[�X�t�@�C����
			bool Create(LPCTSTR lpctszDBName)
			{
				_lastError = ::sqlite3_open16(lpctszDBName, &_engine);
				return getResponse();
			}

			//! @brief DB�t�@�C���̃N���[�Y
			bool Close()
			{
				_lastError = ::sqlite3_close(_engine);
				_engine = nullptr;
				return getResponse();
			}

			//! @brief		SQL�X�e�[�g�����g���s
			//! @param[in]	lpcszSQL SQL�X�e�[�g�����g
			bool Execute(LPCSTR lpcszSQL)
			{
				_lastError = ::sqlite3_exec(_engine, lpcszSQL, nullptr, nullptr, nullptr);
				return getResponse();
			}

			//! @brief �g�����U�N�V�����J�n
			bool BeginTransaction()
			{
				return Execute("BEGIN;");
			}

			//! @brief �g�����U�N�V�����R�~�b�g
			bool CommitTransaction()
			{
				return Execute("COMMIT;");
			}

			//! @brief �g�����U�N�V�������[���o�b�N
			bool RollbackTransaction()
			{
				return Execute("ROLLBACK;");
			}

			//! @brief �󂫗̈�̐���
			bool Vacuum()
			{
				return Execute("VACUUM;");
			}

			//! @brief �Ō�̎��s����ROWID���擾
			ULONGLONG GetLastRowID()
			{
				return ::sqlite3_last_insert_rowid(_engine);
			}

			//! @brief �G���W�������擾
			sqlite3* GetEngine()
			{
				return _engine;
			}

		protected:
			//! @brief SQLite3�R���e�L�X�g
			sqlite3* _engine;
		};
	}
}