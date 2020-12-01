//! @file	SocketBuilder.cpp
//! @brief	ソケットに関するWindowsAPIを集約したクラス
//! @author	kumakuma0421@gmail.com
//! @date	2020.01.03

#include "pch.h"
#include "SocketBuilder.h"

using namespace alt;

SocketBuilder::SocketBuilder()
{
	ZeroMemory(&_wsaData, sizeof(_wsaData));
	ZeroMemory(&m_SockAddrIn, sizeof(m_SockAddrIn));
}

SocketBuilder::~SocketBuilder()
{
	this->Close();

	WSACleanup(); //! @todo TCPConnectorだけ存続させる場合を考慮できていない
}

BOOL SocketBuilder::Startup()
{
	BOOL ret = FALSE;

	int result = WSAStartup(MAKEWORD(2, 0), &_wsaData);
	switch (result)
	{
		case 0:
			ret = TRUE;
			//LogInfo(_T("WSAStartup() 成功"));
			break;

		case WSASYSNOTREADY:
			//LogInfo(_T("ネットワークサブシステムがネットワークへの接続を準備できていない"));
			break;

		case WSAVERNOTSUPPORTED:
			//LogInfo(_T("要求されたwinsockのバージョンがサポートされていない"));
			break;

		case WSAEINPROGRESS:
			//LogInfo(_T("ブロッキング操作の実行中であるか、 またはサービスプロバイダがコールバック関数を処理している"));
			break;

		case WSAEPROCLIM:
			//LogInfo(_T("winsockが処理できる最大プロセス数に達した"));
			break;

		case WSAEFAULT:
			//LogInfo(_T("第二引数であるlpWSAData は有効なポインタではない"));
			break;

		default:
			break;
	}

	if (ret != TRUE)
	{
		WSACleanup();
	}

	return ret;
}

BOOL SocketBuilder::Socket(int af, int type, int protocol)
{
	BOOL response = TRUE;

	_socket = ::socket(af, type, protocol);
	if (_socket == INVALID_SOCKET)
	{
		response = FALSE;
	}

	return response;
}

BOOL SocketBuilder::SetSockAddr(ADDRESS_FAMILY family, u_short portNo, LPCTSTR lpctszAddress)
{
	BOOL response = TRUE;

	m_SockAddrIn.sin_family = family;
	m_SockAddrIn.sin_port = htons(portNo);
	if (lpctszAddress != nullptr)
	{
		INT ret = ::InetPton(family, lpctszAddress, &(m_SockAddrIn.sin_addr));
		if (ret != 1)
		{
			response = FALSE;
		}
	}

	return response;
}

BOOL SocketBuilder::SetSockOpt(int level, int optname, int value)
{
	BOOL response = TRUE;

	int ret = ::setsockopt(_socket, level, optname, (const char*)&value, sizeof(value));
	if (ret != 0)
	{
		this->Close();
		ret = FALSE;
	}

	return response;
}

BOOL SocketBuilder::Connect()
{
	BOOL response = TRUE;

	int ret = ::connect(_socket, (PSOCKADDR)&m_SockAddrIn, sizeof(m_SockAddrIn));
	if (ret != 0)
	{
		response = FALSE;
	}

	return response;
}

BOOL SocketBuilder::Bind()
{
	BOOL response = TRUE;

	int ret = ::bind(_socket, (PSOCKADDR)&m_SockAddrIn, sizeof(m_SockAddrIn));
	if (ret != 0)
	{
		response = FALSE;
	}

	return response;
}

BOOL SocketBuilder::Listen()
{
	BOOL response = TRUE;

	int ret = ::listen(_socket, 5);
	if (ret != 0)
	{
		response = FALSE;
	}

	return response;
}

//! @sa https://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-ioctlsocket
BOOL SocketBuilder::Ioctl(long cmd, u_long arg)
{
	u_long value = arg;
	BOOL response = TRUE;

	int ret = ::ioctlsocket(_socket, cmd, &value);
	if (ret != 0)
	{
		response = FALSE;
	}

	return response;
}

UdpConnector* SocketBuilder::CreateUdpConnector(LPCTSTR lpctszIpAddr, u_short portNo)
{
	UdpConnector* response = nullptr;
	BOOL ret = FALSE;

	do
	{
		ret = this->Socket(AF_INET, SOCK_DGRAM, 0);
		if (ret == FALSE) break;

		ret = this->SetSockAddr(AF_INET, portNo, lpctszIpAddr);
		if (ret == FALSE) break;

		ret = this->Bind();
		if (ret == FALSE) break;

		response = new UdpConnector(_socket);
		_socket = INVALID_SOCKET;
		return response;

	} while (FALSE);

	this->Close();

	return response;
}

//
// @sa http://chokuto.ifdef.jp/advanced/function/connect.html
//
TcpConnector* SocketBuilder::CreateTcpConnector(LPCTSTR lpctszIpAddr, u_short portNo, int retryInterval, int retryCount)
{
	TcpConnector* response = nullptr;
	BOOL ret = FALSE;

	do
	{
		ret = this->Socket(AF_INET, SOCK_STREAM, 0);
		if (ret == FALSE) break;

		// KeepAliveはソフトでの設定はON/OFFだけです。
		// 実際の設定値はレジストリから取得されます。
		// HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Tcpip\Parameters
		// KeepAliveTime(ms) 既定値:7,200,000ミリ秒(2時間)
		// KeepAliveInterval(ms) 既定値:1,000ミリ秒(1秒)
		ret = this->SetSockOpt(SOL_SOCKET, SO_KEEPALIVE, 1);
		if (ret == FALSE) break;

		ret = this->SetSockAddr(AF_INET, portNo, lpctszIpAddr);
		if (ret == FALSE) break;

		// connect()は対向サーバーが別のマシンにある場合、
		// 21秒のブロッキング時間となります(対向がいない場合など)。
		// そのため、connect()を呼び出す前に、ソケット関数を非同期
		// (ノンブロッキング)モードに変更します。
		ret = this->Ioctl(FIONBIO, 1);
		if (ret == FALSE) break;

		while (retryCount--)
		{
			ret = this->Connect();
			if (ret == TRUE || this->GetErrNo() == WSAEISCONN)
			{
				// connect()に成功した場合、非同期(ノンブロッキング)
				// モードを通常のブロッキングモードに戻します。
				// 失敗した場合は、そのままクローズされます。
				ret = this->Ioctl(FIONBIO, 0);
				if (ret == TRUE)
				{
					response = new TcpConnector(_socket);
					_socket = INVALID_SOCKET;
					return response;
				}
			}
			else
			{
				_tprintf(_T(" connect() error. reason=%d\n"), this->GetErrNo());
				Sleep(retryInterval);
			}
		}
	} while (FALSE);

	this->Close();

	return response;
}

BOOL SocketBuilder::Prepare(u_short portNo, LPCTSTR lpctszIpAddr)
{
	BOOL response = FALSE;

	do
	{
		response = this->Socket(AF_INET, SOCK_STREAM, 0);
		if (response == FALSE)
		{
			break;
		}

		// ソケットに対してSO_REUSEADDRを設定すると、
		// TIME_WAIT状態のポートが存在してもbind()が
		// できるようになります。
		// @sa also www.geekpage.jp/programming/linux-network/so_reuseaddr.php
		response = this->SetSockOpt(SOL_SOCKET, SO_REUSEADDR, 1);
		if (response == FALSE)
		{
			break;
		}

		response = this->SetSockAddr(AF_INET, portNo, lpctszIpAddr);
		if (response == FALSE)
		{
			break;
		}

		response = this->Bind();
		if (response == FALSE)
		{
			break;
		}

		// KeepAliveはソフトでの設定はON/OFFだけです。
		// 実際の設定値はレジストリから取得されます。
		// HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Tcpip\Parameters
		// KeepAliveTime(ms) 既定値:7,200,000ミリ秒(2時間)
		// KeepAliveInterval(ms) 既定値:1,000ミリ秒(1秒)
		response = this->SetSockOpt(SOL_SOCKET, SO_KEEPALIVE, 1);
		if (response == FALSE)
		{
			break;
		}

		response = this->Listen();
		if (response == FALSE)
		{
			break;
		}

	} while (FALSE);

	return response;
}

TcpConnector* SocketBuilder::Wait()
{
	TcpConnector* response = nullptr;
	BOOL ret = FALSE;

	SOCKADDR_IN mySockAddrIn;
	int length = sizeof(mySockAddrIn);
	SOCKET mySocket = ::accept(_socket, (PSOCKADDR)&mySockAddrIn, &length);
	if (mySocket != INVALID_SOCKET)
	{
		TCHAR tszAcceptIPAddress[INET_ADDRSTRLEN];
		PCWSTR ret = InetNtop(AF_INET, &mySockAddrIn.sin_addr, tszAcceptIPAddress, INET_ADDRSTRLEN);
		if (ret != nullptr)
		{
			int iAcceptPort = ntohs(mySockAddrIn.sin_port);

			TCHAR tszMsg[80];
			wsprintf(tszMsg, _T("Accepted (%s,%d)\n"), tszAcceptIPAddress, iAcceptPort);
			//! @todo なんらかの形式で接続情報を出力しよう。
			OutputDebugString(tszMsg);

			response = new TcpConnector(mySocket);
		}
	}

	return response;
}