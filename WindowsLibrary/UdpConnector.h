/**
 @file		UdpConnector.h
 @brief		UDP�ʐM�Ɋւ���WindowsAPI���W�񂵂��N���X
 @author	kumakuma0421@gmail.com
 @date		2020.01.03
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"

namespace alt
{
	/**
	 @class	UdpConnector
	 @brief	UDP�ʐM�Ɋւ���WindowsAPI���W�񂵂��N���X
	 */
	class DLL_DECLSPEC UdpConnector : public SocketLibrary
	{
	public:
		UdpConnector(SOCKET socket);

		virtual BOOL SetSockAddr(LPCTSTR lpctszAddress, u_short portNo);
		virtual INT Send(LPVOID lpvBuf, DWORD dwSize);
		virtual INT Recv(LPVOID lpvBuf, DWORD dwSize);

	protected:
		UdpConnector();
		SOCKADDR_IN	_sockAddrIn;
	};
}