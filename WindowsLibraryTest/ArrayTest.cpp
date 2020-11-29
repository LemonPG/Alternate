/**
 @file		ArrayTest.cpp
 @brief		可変配列に関するクラスのテストクラス
 @author	kumakuma0421@gmail.com
 @date		2020.2.24
 */
#include "pch.h"
#include "Array.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(ArrayTest)
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("class initialize.\n");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("class cleanup.\n");
		}

		TEST_METHOD_INITIALIZE(MethodInitialize)
		{
			Logger::WriteMessage("method initialize.\n");
		}

		TEST_METHOD_CLEANUP(MethodCleanup)
		{
			Logger::WriteMessage("method cleanup.\n");
		}

		typedef struct _Freight
		{
			int a;
			int b;
			int c;
		} Freight;

		template<class T>
		class ObjectHolder
		{
		public:
			ObjectHolder<T>()
			{
				_value = nullptr;
			};

			ObjectHolder<T>(T& t)
			{
				_value = new T();
				*_value = t;
			}

			ObjectHolder<T>(T* pT)
			{
				_value = new T();
				*_value = *pT;
			}

			ObjectHolder<T>(const ObjectHolder<T>& base) : ObjectHolder<T>()
			{
				if (_value == nullptr) _value = new T();
				*_value = *base._value;
			}

			virtual ~ObjectHolder<T>()
			{
				delete _value;
				_value = nullptr;
			}

			T Get()
			{
				return *_value;
			}

			void Set(T& t)
			{
				if (_value == nullptr) _value = new T();
				*_value = t;
			}

			void Set(T* pT)
			{
				if (_value == nullptr) _value = new T();
				*_value = *pT;
			}

			void operator = (const ObjectHolder<T>& base)
			{
				if (_value == nullptr) _value = new T();
				*_value = *base._value;
			}

		private:
			T* _value;
		};

		//TEST_METHOD(ArrayTest1)
		//{
		//	Logger::WriteMessage("ArrayTest1\n");

		//	Array<int> array;

		//	for (int i = 0; i < 1000; i++)
		//	{
		//		array.Add(&i);
		//	}

		//	Array<int> arrayCopy = array;
		//	array.Clear(true);

		//	for (int i = 0; i < arrayCopy.Size(); i++)
		//	{
		//		Assert::AreEqual<int>(i, *(arrayCopy.Get(i)));
		//	}

		//	arrayCopy.Clear(true);
		//}
		//! @todo 動かない原因を後で追及

		TEST_METHOD(ArrayTest2)
		{
			Logger::WriteMessage("ArrayTest2\n");

			alt::skeleton::Array<Freight> array;

			for (int i = 0; i < 1000; i++)
			{
				Freight freight;
				freight.a = i;
				freight.b = i * i;
				freight.c = i + i + i;
				array.Add(&freight);
			}

			alt::skeleton::Array<Freight> arrayCopy = array;
			array.Clear(true);

			for (int i = 0; i < arrayCopy.Size(); i++)
			{
				Freight* freight = arrayCopy.Get(i);
				Assert::AreEqual<int>(i, freight->a);
			}

			int i = 0;
			for (auto item : arrayCopy)
			{
				TCHAR tszMsg[80];
				wsprintf(tszMsg, _T("%d-%d-%d\n"), item.a, item.b, item.c);
				Logger::WriteMessage(tszMsg);
				Assert::AreEqual<int>(i++, item.a);
			}

			arrayCopy.Clear(true);
		}

		TEST_METHOD(ArrayTest3)
		{
			Logger::WriteMessage("ArrayTest3\n");

			alt::skeleton::Array<ObjectHolder<int>> array;

			for (int i = 0; i < 1000; i++)
			{
				ObjectHolder<int> value(i);
				array.Add(&value);
			}

			alt::skeleton::Array<ObjectHolder<int>> arrayCopy = array;
			array.Clear(true);

			for (int i = 0; i < arrayCopy.Size(); i++)
			{
				ObjectHolder<int>* value = arrayCopy.Get(i);
				Assert::AreEqual<int>(i, value->Get());
			}

			int i = 0;
			for (auto item : arrayCopy)
			{
				TCHAR tszMsg[80];
				wsprintf(tszMsg, _T("%d\n"), item.Get());
				Logger::WriteMessage(tszMsg);
				Assert::AreEqual<int>(i++, item.Get());
			}

			arrayCopy.Clear(true);
		}

		TEST_METHOD(VectorTest2)
		{
			Logger::WriteMessage("VectorTest2\n");

			std::vector<Freight> array;

			for (int i = 0; i < 1000; i++)
			{
				Freight freight;
				freight.a = i;
				freight.b = i * i;
				freight.c = i + i + i;
				array.push_back(freight);
			}

			std::vector<Freight> arrayCopy = array;
			array.clear();

			for (int i = 0; i < arrayCopy.size(); i++)
			{
				Freight value = arrayCopy.at(i);
				Assert::AreEqual<int>(i, value.a);
			}

			int i = 0;
			for (auto item : arrayCopy)
			{
				TCHAR tszMsg[80];
				wsprintf(tszMsg, _T("%d\n"), item.a);
				Logger::WriteMessage(tszMsg);
				Assert::AreEqual<int>(i++, item.a);
			}

			arrayCopy.clear();
		}

		TEST_METHOD(VectorTest3)
		{
			Logger::WriteMessage("VectorTest3\n");

			std::vector<ObjectHolder<int>> array;

			for (int i = 0; i < 1000; i++)
			{
				ObjectHolder<int> value(i);
				array.push_back(value);
			}

			std::vector<ObjectHolder<int>> arrayCopy = array;
			array.clear();

			for (int i = 0; i < arrayCopy.size(); i++)
			{
				ObjectHolder<int> value = arrayCopy.at(i);
				Assert::AreEqual<int>(i, value.Get());
			}

			int i = 0;
			for (auto item : arrayCopy)
			{
				TCHAR tszMsg[80];
				wsprintf(tszMsg, _T("%d\n"), item.Get());
				Logger::WriteMessage(tszMsg);
				Assert::AreEqual<int>(i++, item.Get());
			}

			arrayCopy.clear();
		}

	};
}