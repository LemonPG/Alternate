/**
 @file		SocketBuilder.h
 @brief		ソケットに関するWindowsAPIを集約したクラス
 @author	kumakuma0421@gmail.com
 @date		2020.01.03
 */
#pragma once

#include "framework.h"
#include "WindowsLibrary.h"
#include "TcpConnector.h"
#include "UdpConnector.h"

namespace alt
{
	/**
	 @class	SocketBuilder
	 @brief	ソケットに関するWindowsAPIを集約したクラス
	 */
	class DLL_DECLSPEC SocketBuilder : public SocketLibrary
	{
	public:
		SocketBuilder();
		~SocketBuilder();

		virtual BOOL Startup();
		virtual UdpConnector* CreateUdpConnector(LPCTSTR lpctszIpAddr, u_short portNo);
		virtual TcpConnector* CreateTcpConnector(LPCTSTR lpctszIpAddr, u_short portNo, int retryInterval, int retryCount);
		virtual BOOL Prepare(u_short portNo, LPCTSTR lpctszIpAddr = nullptr);
		virtual TcpConnector* Wait();

	protected:
		virtual BOOL Socket(int af, int type, int protocol);
		virtual BOOL SetSockAddr(ADDRESS_FAMILY family, u_short portNo, LPCTSTR lpctszAddress);
		virtual BOOL SetSockOpt(int level, int optname, int value);
		virtual BOOL Connect();
		virtual BOOL Bind();
		virtual BOOL Listen();
		virtual BOOL Ioctl(long cmd, u_long arg);

		SOCKADDR_IN	m_SockAddrIn;
		WSADATA		_wsaData;
	};
}
