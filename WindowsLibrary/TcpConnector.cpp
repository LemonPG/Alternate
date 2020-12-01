//! @file	TcpConnector.cpp
//! @brief	TCP�ʐM�Ɋւ���WindowsAPI���W�񂵂��N���X
//! @author	kumakuma0421@gmail.com
//! @date	2019.12.21

#include "pch.h"
#include "TcpConnector.h"

using namespace alt;

INT TcpConnector::Send(LPVOID lpvBuf, DWORD dwSize)
{
	int ret = ::send(_socket, (PCHAR)lpvBuf, (int)dwSize, 0);

	return ret;
}

INT TcpConnector::Recv(LPVOID lpvBuf, DWORD dwSize, BOOL isBlocking)
{
	INT ret = 0;

	if (isBlocking)
	{
		DWORD dwRemain = dwSize;
		PCHAR currentPos;
		while (dwRemain != 0)
		{
			currentPos = (PCHAR)lpvBuf + (dwSize - dwRemain);
			int ret = ::recv(_socket, currentPos, (int)(dwRemain), 0);
			if (ret <= 0)
			{
				dwSize = 0;
				break;
			}
			dwRemain -= ret;
		}

		ret = dwSize;
	}
	else
	{
		ret = ::recv(_socket, (PCHAR)lpvBuf, (int)dwSize, 0);
	}

	return ret;
}