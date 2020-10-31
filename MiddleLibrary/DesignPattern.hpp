//
// DesignPattern.h
//
#pragma once

#include "framework.h"
#include "pch.h"

namespace alt
{
	namespace skeleton
	{
		//
		// テンプレートクラスなのでDLL_DECLSPECは付けません。
		//
		template <class T>
		class ISupplier
		{
		public:
			virtual T get() = 0;
		};

		template <class T>
		class IConsumer
		{
		public:
			virtual void accept(T t) = 0;
		};

		template <class T>
		class IPredicate
		{
		public:
			virtual bool test(T t) = 0;
		};

		template <class T, class V>
		class IFunction
		{
		public:
			virtual V apply(T t) = 0;
		};

		template<typename Data>
		class IObserver
		{
		public:
			virtual void Update(Data data) = 0;
		};

		template<typename Data>
		class ISubscriber
		{
		public:
			virtual void Notify(Data data)
			{
				for (IObserver<Data>* observer : _observers)
				{
					observer->Update(data);
				}
			}

			virtual void Add(IObserver<Data>* observer)
			{
				_observers.push_back(observer);
			}

			virtual void Remove(IObserver<Data>* observer)
			{
				for (auto item : _observers)
				{
					if (item == observer)
					{
						// TODO:消し方は後で実装する
					}
				}
			}

		private:
			std::vector<IObserver<Data>*> _observers;
		};

		template<class T, class V>
		class Strategy
		{
		public:
			Strategy() {};
			virtual ~Strategy() {};

			virtual V Get(T t)
			{
				return _strategy[t];
			};

			virtual void Set(T t, V v)
			{
				_strategy.insert(std::make_pair(t, v));
			};

		private:
			std::map<T, V> _strategy;
		};

		template<class T>
		class Singleton
		{
		public:
			static T* Instance()
			{
				if (_instance == nullptr)
				{
					_instance = new T();
				}

				return _instance;
			};

		private:
			Singleton() {};

			static T* _instance;
		};

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