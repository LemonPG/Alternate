/**
 @file		UdpConnector.h
 @brief		UDP通信に関するWindowsAPIを集約したクラス
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
	 @brief	UDP通信に関するWindowsAPIを集約したクラス
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