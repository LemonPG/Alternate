/**
 @file		RingBuffer.cpp
 @brief		�����O�o�b�t�@�Ɋւ���N���X
 @author	kumakuma0421@gmail.com
 @date		2020.4.4
 */
#include "pch.h"
#include "RingBuffer.h"

using namespace alt;

RingBuffer::RingBuffer()
	:WindowsLibrary()
{
	_lpbyStartPoint = nullptr;
	_lpbyEndPoint = nullptr;
	_size = 0;
	_remainSize = 0;
	_lpbyReadPoint = nullptr;
	_lpbyWritePoint = nullptr;
}

RingBuffer::RingBuffer(size_t size)
	:RingBuffer()
{
	this->Init(size);
}

RingBuffer::~RingBuffer()
{
	if (_lpbyStartPoint != nullptr) delete[] _lpbyStartPoint;
}

BOOL RingBuffer::Init(size_t size)
{
	_lpbyStartPoint = new BYTE[size];
	_lpbyEndPoint = _lpbyStartPoint + size;
	_size = size;
	_remainSize = 0;
	_lpbyReadPoint = _lpbyStartPoint;
	_lpbyWritePoint = _lpbyStartPoint;

	return TRUE;
}

BOOL RingBuffer::Clear()
{
	delete[] _lpbyStartPoint;
	_lpbyStartPoint = new BYTE[_size];
	_lpbyEndPoint = _lpbyStartPoint + _size;
	_remainSize = 0;
	_lpbyReadPoint = nullptr;
	_lpbyWritePoint = nullptr;

	return TRUE;
}

BOOL RingBuffer::Write(LPBYTE lpbyBuffer, size_t size)
{
	LPBYTE lpbyWritePointEnd = _lpbyWritePoint + size;

	// �������ݗʂ��o�b�t�@�T�C�Y�𒴂��Ă͂����Ȃ��B
	if ((_remainSize + size) > _size) return FALSE;

	if (lpbyWritePointEnd <= _lpbyEndPoint)
	{
		// �����O�o�b�t�@�̓����Ŋ���
		CopyMemory(_lpbyWritePoint, lpbyBuffer, size);
		_lpbyWritePoint = lpbyWritePointEnd;
	}
	else
	{
		// �������݂��ő�o�b�t�@�𒴂���ꍇ�́A�������ď������ށB
		size_t writeSize1 = _lpbyEndPoint - _lpbyWritePoint;
		CopyMemory(_lpbyWritePoint, lpbyBuffer, writeSize1);

		size_t writeSize2 = size - writeSize1;
		CopyMemory(_lpbyStartPoint, &lpbyBuffer[writeSize1], writeSize2);

		_lpbyWritePoint = _lpbyStartPoint + writeSize2;
	}

	_remainSize += size;

	return TRUE;
}

BOOL RingBuffer::Read(LPBYTE lpbyBuffer, size_t size)
{
	LPBYTE lpbyReadPointStart = _lpbyReadPoint;
	LPBYTE lpbyReadPointEnd = _lpbyReadPoint + size;

	// �ǂݍ��ݗʂ��������ݗʂ𒴂��Ă͂����Ȃ��B
	if (size > _remainSize) return FALSE;

	if (lpbyReadPointEnd <= _lpbyEndPoint)
	{
		// �����O�o�b�t�@�̓����Ŋ���
		CopyMemory(lpbyBuffer, _lpbyReadPoint, size);
		_lpbyReadPoint = lpbyReadPointEnd;
	}
	else
	{
		// �ǂݍ��݂��ő�o�b�t�@�𒴂���ꍇ�́A�������ēǂݍ��ށB
		size_t readSize1 = _lpbyEndPoint - _lpbyReadPoint;
		CopyMemory(lpbyBuffer, _lpbyReadPoint, readSize1);

		size_t readSize2 = size - readSize1;
		CopyMemory(&lpbyBuffer[readSize1], _lpbyStartPoint, readSize2);

		_lpbyReadPoint = _lpbyStartPoint + readSize2;
	}

	_remainSize -= size;

	return TRUE;
}

size_t RingBuffer::Remain()
{
	return _remainSize;
}