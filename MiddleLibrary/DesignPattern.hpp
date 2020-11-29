/**
 @file		DesignPattern.hpp
 @brief		��X�̃f�U�C���p�^�[���̎����N���X
 @author	kumakuma0421@gmail.com
 @date		2020.2.24
 */

#pragma once

#include "framework.h"
#include "pch.h"

namespace alt
{
	namespace skeleton
	{
		/**
		 @brief	ISupplier�C���^�[�t�F�[�X�N���X
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template <class T>
		class ISupplier
		{
		public:
			/**
			 @brief		T��Ԃ��֐� get()
			 @return	T
			*/
			virtual T get() = 0;
		};

		/**
		 @brief	IConsumer�C���^�[�t�F�[�X�N���X
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template <class T>
		class IConsumer
		{
		public:
			/**
			 @brief		T�������Ƃ���֐� accept()
			 @param[in]	t �e���v���[�gT
			*/
			virtual void accept(T t) = 0;
		};

		/**
		 @brief	IPredicate�C���^�[�t�F�[�X�N���X
		 @note	test(T t):bool
		 @attension	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template <class T>
		class IPredicate
		{
		public:
			/**
			 @brief		T�������Ƃ���֐� test()
			 @param[in] t �e���v���[�gT
			 @return	bool
			 @retval	true:����
			 @retval	false:���s
			*/
			virtual bool test(T t) = 0;
		};

		/**
		 @brief	IFunction�C���^�[�t�F�[�X�N���X
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template <class T, class V>
		class IFunction
		{
		public:
			/**
			 @brief		T�������Ƃ���֐� apply()
			 @param[in] t �e���v���[�gT
			 @return	V �e���v���[�gV
			*/
			virtual V apply(T t) = 0;
		};

		/**
		 @brief	IObserver�C���^�[�t�F�[�X�N���X
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template<typename Data>
		class IObserver
		{
		public:
			/**
			 @brief Data�������Ƃ���֐� Update()
			 @param data �e���v���[�gData
			*/
			virtual void Update(Data data) = 0;
		};

		/**
		 @brief	ISubscriber�C���^�[�t�F�[�X�N���X
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template<typename Data>
		class ISubscriber
		{
		public:
			/**
			 @brief Data�������Ƃ���֐� Notify()
			 @param data �e���v���[�gData
			*/
			virtual void Notify(Data data)
			{
				for (IObserver<Data>* observer : _observers)
				{
					observer->Update(data);
				}
			}

			/**
			 @brief		IObserver<Data>*�������Ƃ���֐� Add()
			 @param[in] observer Subscriber�ɓo�^����Observer�I�u�W�F�N�g
			*/
			virtual void Add(IObserver<Data>* observer)
			{
				_observers.push_back(observer);
			}

			/**
			 @brief		IObserver<Data>*�������Ƃ���֐� Remove()
			 @param[in] observer Subscriber����폜����Observer�I�u�W�F�N�g
			*/
			virtual void Remove(IObserver<Data>* observer)
			{
				for (auto item : _observers)
				{
					if (item == observer)
					{
						//! @todo �������͌�Ŏ�������
					}
				}
			}

		private:
			//! @brief Subscriber���Ǘ�����Observer�̕ۑ��p
			std::vector<IObserver<Data>*> _observers;
		};

		/**
		 @brief	Strategy
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template<class T, class V>
		class Strategy
		{
		public:
			//! @brief �R���X�g���N�^
			Strategy() {};

			//! @brief �f�X�g���N�^
			virtual ~Strategy() {};

			/**
			 * @brief	�e���v���[�g����T�ɉ����āA�e���v���[�gV��ԋp���܂��B
			 * @param	t �e���v���[�gT
			 * @return	V �e���v���[�gV
			 * @retval	���O��Set()�Őݒ肵���AT�ɕR�t���I�u�W�F�N�g
			*/
			virtual V Get(T t)
			{
				return _strategy[t];
			};

			/**
			 * @brief	�e���v���[�gT���L�[�Ƃ����e���v���[�gV��ݒ肵�܂��B
			 * @param	t �e���v���[�gT
			 * @param	v �e���v���[�gV
			*/
			virtual void Set(T t, V v)
			{
				_strategy.insert(std::make_pair(t, v));
			};

		private:
			//! @brief Set()�œo�^���ꂽ�I�u�W�F�N�g���Ǘ�����}�b�v
			std::map<T, V> _strategy;
		};

		/**
		 @brief	Singleton
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template<class T>
		class Singleton
		{
		public:
			/**
			 * @brief �B��ƂȂ�C���X�^���X���擾���܂��B
			 * @return T*�C���X�^���X
			*/
			static T* Instance()
			{
				if (_instance == nullptr)
				{
					_instance = new T();
				}

				return _instance;
			};

		private:
			//! @brief �R���X�g���N�^(private�Ŕ铽���)
			Singleton() {};

			//! @brief �B��ƂȂ�C���X�^���X���Ǘ�����ϐ�
			static T* _instance;
		};

		/**
		 @brief	Command
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template<typename CommandFunction>
		class Command
		{
		public:
			Command()
			{
				_function = nullptr;
				_waitTime = 0;
			};

			void SetFunction(CommandFunction function) { _function = function; };
			virtual bool Execute(size_t count, size_t total) { return _function(count, total); };
			long GetWaitTime() { return _waitTime; };
			void SetWaitTime(long time) { _waitTime = time; };

		private:
			CommandFunction _function;
			long _waitTime;
		};

		/**
		 @brief	Commander
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		template<typename CommandFunction>
		class Commander
		{
		public:
			void Add(Command<CommandFunction>* command) { _commands.push_back(command); };
			bool Execute()
			{
				int ret = 0;
				size_t count = 0;
				const size_t total = _commands.size();

				for (auto command : _commands)
				{
					ret = command->Execute(++count, total);
					if (ret == false) break;

					long waitTime = command->GetWaitTime();
					Sleep(waitTime);
				}

				return ret;
			};

		private:
			std::vector<Command<CommandFunction>*> _commands;
		};

		/**
		 @brief	CompositeLeaf
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		class CompositeLeaf
		{
		public:
			std::wstring GetName() { return _leafName; };

			void SetName(std::wstring& name) { _leafName = name; };

			void Add(std::wstring key, std::wstring value)
			{
				_properties.insert(std::make_pair<std::wstring&, std::wstring&>(key, value));
			}

			std::wstring Get(std::wstring key) { return _properties[key]; };

		private:
			std::wstring _leafName;
			std::map<std::wstring, std::wstring> _properties;
		};

		/**
		 @brief	CompositeNode
		 @note	�e���v���[�g�N���X�Ȃ̂�DLL_DECLSPEC�͕t���܂���B
		*/
		class CompositeNode
		{
		public:
			std::wstring GetName() { return _nodeName; };

			void SetName(std::wstring name) { _nodeName = name; };

			void Add(std::wstring key, CompositeNode& node)
			{
				_nodes.insert(std::make_pair<std::wstring&, CompositeNode&>(key, node));
			};

			CompositeNode& GetNode(std::wstring key) { return _nodes[key]; };

			std::vector<std::wstring> GetNodeKeys()
			{
				std::vector<std::wstring> response;

				for (auto itr = _nodes.begin(); itr != _nodes.end(); ++itr)
				{
					response.push_back(itr->first);
				}

				return response;
			};

			std::vector<CompositeNode> GetNodeValues()
			{
				std::vector<CompositeNode> response;

				for (auto itr = _nodes.begin(); itr != _nodes.end(); ++itr)
				{
					response.push_back(itr->second);
				}

				return response;
			}

			void Add(std::wstring key, CompositeLeaf& leaf)
			{
				_leafs.insert(std::make_pair<std::wstring&, CompositeLeaf&>(key, leaf));
			};

			CompositeLeaf& GetLeaf(std::wstring key) { return _leafs[key]; };

			std::vector<std::wstring> GetLeafKeys()
			{
				std::vector<std::wstring> response;

				for (auto itr = _leafs.begin(); itr != _leafs.end(); ++itr)
				{
					response.push_back(itr->first);
				}

				return response;
			};

			std::vector<CompositeLeaf> GetLeafValues()
			{
				std::vector<CompositeLeaf> response;

				for (auto itr = _leafs.begin(); itr != _leafs.end(); ++itr)
				{
					response.push_back(itr->second);
				}

				return response;
			}

		private:
			std::wstring _nodeName;
			std::map<std::wstring, CompositeNode>_nodes;
			std::map<std::wstring, CompositeLeaf> _leafs;
		};
	}
}