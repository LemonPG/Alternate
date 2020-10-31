/**
 @file		Array.hpp
 @brief		可変配列に関するクラス
 @author	kumakuma0421@gmail.com
 @date		2020.2.24
 */
#pragma once

#include "framework.h"
#include "HeapMemory.h"

namespace alt
{
	namespace skeleton
	{
		/**
		 @class	Array
		 @brief	サイズ可変の配列を具現したクラス
		 @note	構造体、クラス以外は動作が不安定です。
		 */
		template<class T>
		class Array
		{
		public:
			Array<T>()
			{
				_arraySize = 0;
				_array = nullptr;
				_memory.Create();
			};

			Array<T>(const Array<T>& base)
			{
				_arraySize = base._arraySize;
				_memory.Create();
				_array = static_cast<T*>(_memory.Allocate(sizeof(T) * _arraySize));
				for (size_t i = 0; i < _arraySize; i++)
				{
					CopyMemory(&_array[i], &base._array[i], sizeof(LPVOID));
					_array[i] = base._array[i];
				}
			};

			virtual ~Array<T>()
			{
				this->Clear(true);
			};

			T* Get(size_t index)
			{
				if (index >= _arraySize) return (T*)nullptr;
				return &(_array[index]);
			}

			T* operator[](size_t index)
			{
				return this->Get(index);
			};

			void Add(T* append)
			{
				if (_arraySize == 0)
				{
					_array = static_cast<T*>(_memory.Allocate(sizeof(T)));
				}
				else
				{
					_array = static_cast<T*>(_memory.Reallocate(_array, sizeof(T) * (_arraySize + 1)));
				}

				CopyMemory(&_array[_arraySize], append, sizeof(LPVOID));
				_array[_arraySize] = *append;
				_arraySize++;
			}

			void Clear(bool bWithDelete = false)
			{
				if (_arraySize)
				{
					if (bWithDelete)
					{
						for (int i = 0; i < this->Size(); i++)
						{
							(&_array[i])->~T();
						}
					}
					_memory.Free(_array);
					_array = nullptr;
					_arraySize = 0;
				}
			};

			size_t Size()
			{
				return _arraySize;
			}

			const T* begin()
			{
				return &_array[0];
			}

			const T* end()
			{
				return &_array[_arraySize];
			}

		private:
			HeapMemory _memory;
			size_t _arraySize;
			T* _array;
		};
	}
}