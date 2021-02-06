//! @file	SocketBuilder.cpp
//! @brief	�\�P�b�g�Ɋւ���WindowsAPI���W�񂵂��N���X
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

	WSACleanup(); //! @todo TCPConnector��������������ꍇ���l���ł��Ă��Ȃ�
}

BOOL SocketBuilder::Startup()
{
	BOOL ret = FALSE;

	int result = WSAStartup(MAKEWORD(2, 0), &_wsaData);
	switch (result)
	{
		case 0:
			ret = TRUE;
			//LogInfo(_T("WSAStartup() ����"));
			break;

		case WSASYSNOTREADY:
			//LogInfo(_T("�l�b�g���[�N�T�u�V�X�e�����l�b�g���[�N�ւ̐ڑ��������ł��Ă��Ȃ�"));
			break;

		case WSAVERNOTSUPPORTED:
			//LogInfo(_T("�v�����ꂽwinsock�̃o�[�W�������T�|�[�g����Ă��Ȃ�"));
			break;

		case WSAEINPROGRESS:
			//LogInfo(_T("�u���b�L���O����̎��s���ł��邩�A �܂��̓T�[�r�X�v���o�C�_���R�[���o�b�N�֐����������Ă���"));
			break;

		case WSAEPROCLIM:
			//LogInfo(_T("winsock�������ł���ő�v���Z�X���ɒB����"));
			break;

		case WSAEFAULT:
			//LogInfo(_T("�������ł���lpWSAData �͗L���ȃ|�C���^�ł͂Ȃ�"));
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

		// KeepAlive�̓\�t�g�ł̐ݒ��ON/OFF�����ł��B
		// ���ۂ̐ݒ�l�̓��W�X�g������擾����܂��B
		// HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Tcpip\Parameters
		// KeepAliveTime(ms) ����l:7,200,000�~���b(2����)
		// KeepAliveInterval(ms) ����l:1,000�~���b(1�b)
		ret = this->SetSockOpt(SOL_SOCKET, SO_KEEPALIVE, 1);
		if (ret == FALSE) break;

		ret = this->SetSockAddr(AF_INET, portNo, lpctszIpAddr);
		if (ret == FALSE) break;

		// connect()�͑Ό��T�[�o�[���ʂ̃}�V���ɂ���ꍇ�A
		// 21�b�̃u���b�L���O���ԂƂȂ�܂�(�Ό������Ȃ��ꍇ�Ȃ�)�B
		// ���̂��߁Aconnect()���Ăяo���O�ɁA�\�P�b�g�֐���񓯊�
		// (�m���u���b�L���O)���[�h�ɕύX���܂��B
		ret = this->Ioctl(FIONBIO, 1);
		if (ret == FALSE) break;

		while (retryCount--)
		{
			ret = this->Connect();
			if (ret == TRUE || this->GetErrNo() == WSAEISCONN)
			{
				// connect()�ɐ��������ꍇ�A�񓯊�(�m���u���b�L���O)
				// ���[�h��ʏ�̃u���b�L���O���[�h�ɖ߂��܂��B
				// ���s�����ꍇ�́A���̂܂܃N���[�Y����܂��B
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

		// �\�P�b�g�ɑ΂���SO_REUSEADDR��ݒ肷��ƁA
		// TIME_WAIT��Ԃ̃|�[�g�����݂��Ă�bind()��
		// �ł���悤�ɂȂ�܂��B
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

		// KeepAlive�̓\�t�g�ł̐ݒ��ON/OFF�����ł��B
		// ���ۂ̐ݒ�l�̓��W�X�g������擾����܂��B
		// HKEY_LOCAL_MACHINE\System\CurrentControlSet\Services\Tcpip\Parameters
		// KeepAliveTime(ms) ����l:7,200,000�~���b(2����)
		// KeepAliveInterval(ms) ����l:1,000�~���b(1�b)
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
			//! @todo �Ȃ�炩�̌`���Őڑ������o�͂��悤�B
			OutputDebugString(tszMsg);

			response = new TcpConnector(mySocket);
		}
	}

	return response;
}