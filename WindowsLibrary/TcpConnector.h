/**
 @file		TcpConnector.h
 @brief		TCP�ʐM�Ɋւ���WindowsAPI���W�񂵂��N���X
 @author	kumakuma0421@gmail.com
 @date		2019.12.21
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
    /**
     @class	TcpConnector
     @brief	TCP�ʐM�Ɋւ���WindowsAPI���W�񂵂��N���X
     */
    class DLL_DECLSPEC TcpConnector : public SocketLibrary
	{
	public:
		TcpConnector(SOCKET socket) { _socket = socket; };

		virtual INT Send(LPVOID lpvBuf, DWORD dwSize);
		virtual INT Recv(LPVOID lpvBuf, DWORD dwSize, BOOL isBlocking = TRUE);

	protected:
		TcpConnector() { _socket = INVALID_SOCKET; };
	};
}