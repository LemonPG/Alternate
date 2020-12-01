//! @file	ObjectHolder.h
//! @brief	PerformanceCheckソリューション用コンテナクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.4.11

#pragma once

namespace PerfCheck
{
	//! @class	ObjectHolder
	//! @brief	PerformanceCheckソリューション用コンテナクラス
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

		ObjectHolder<T>(const ObjectHolder<T>& base)
			: ObjectHolder<T>()
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
}