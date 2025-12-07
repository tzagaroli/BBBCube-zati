/**
 * @file	CServer.cpp
 * @author	Michael Meindl
 * @date	28.9.2016
 * @brief	Class defintions for CServer.
 */
#include "CServer.h"
#include <unistd.h>		//close()
#include <strings.h>	//bzero()
#include <iostream>
#include <errno.h>
#include <sys/select.h>
#include <fcntl.h>

extern int errno;

bool CServer::receiveMessage(SContent& content)
{
	bool success = false;
	Int32 retVal = -1;
	size_t bytesReceived = 0;
	UInt8* buffer = reinterpret_cast<UInt8*>(&content);
	do
	{
		retVal = read(mConnectedSocketFD, (buffer+bytesReceived), sizeof(content)-bytesReceived);

		if(retVal < 0)
		{
			if(errno == ECONNRESET || errno == EPIPE)
			{
				std::cout << "[*] Server: Connection was reset" << std::endl;
				success = false;
				break;
			}
			else if(errno == EAGAIN || errno == EWOULDBLOCK)
			{
				// Timeout on receive
				std::cout << "[*] Server: Receive timeout" << std::endl;
				success = false;
				break;
			}
			else
			{
				std::cerr << "(CServer::receiveMessage()): Failed to read from the socket, errno: " << errno << std::endl;
				success = false;
				break;
			}
		}
		else if(retVal == 0)
		{
			// Connection closed gracefully
			success = false;
			break;
		}
		else
		{
			bytesReceived += retVal;
		}
	}while(bytesReceived < sizeof(content));

	if(bytesReceived == sizeof(content))
	{
		success = true;
	}
	return success;
}
bool CServer::transmitMessage(SContent& content)
{
	bool success = false;
	Int32 retVal = -1;
	size_t writtenByte = 0;
	UInt8* buffer = reinterpret_cast<UInt8*>(&content);
	do
	{
		retVal = send(mConnectedSocketFD, (buffer+writtenByte), (sizeof(content) - writtenByte), MSG_NOSIGNAL);
		if(retVal < 0)
		{
			if(errno == EPIPE || errno == ECONNRESET)
			{
				std::cout << "[*] Server: Connection was terminated" << std::endl;
				success = false;
				break;
			}
			else if(errno == EAGAIN || errno == EWOULDBLOCK)
			{
				// Timeout - client not reading data fast enough
				std::cout << "[*] Server: Send timeout, client not responding" << std::endl;
				success = false;
				break;
			}
			else
			{
				std::cout << "CServer::transmitMessage(): Failed to send the message, errno: " << errno << std::endl;
				success = false;
				break;
			}
		}
		else
		{
			writtenByte += retVal;
		}
	}while(writtenByte < sizeof(content));

	if(writtenByte == sizeof(content))
	{
		success = true;
	}
	return success;
}
void CServer::init()
{
	mSocketFD = socket(AF_INET, SOCK_STREAM, 0);
	sAssertion(mSocketFD >= 0, "(CServer::CServer()): Failed to open socket.", true);

	// karim's socket fix
	int enable = 1;
	setsockopt(mSocketFD, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int));

	//Bind the socket to an address
	struct sockaddr_in server_addr;
	bzero(reinterpret_cast<Int8*>(&server_addr), sizeof(server_addr));
	server_addr.sin_family		= AF_INET;
	server_addr.sin_port		= htons(sPort);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	Int32 retVal = bind(mSocketFD,
						reinterpret_cast<struct sockaddr*>(&server_addr),
						sizeof(server_addr));
	sAssertion(retVal >= 0, "(CServer::CServer()): Failed to bind the socket.", true);

	retVal = listen(mSocketFD, 1);
	sAssertion(retVal >= 0, "(CServer::CServer()): Failed to listen().", true);
}
bool CServer::waitForClient()
{
	// Use select() with timeout to make accept() interruptible
	fd_set readfds;
	struct timeval timeout;

	// Initialize client address length (critical for accept())
	mClientLen = sizeof(mClientAddr);

	while(true)
	{
		FD_ZERO(&readfds);
		FD_SET(mSocketFD, &readfds);

		// Set timeout to 1 second to periodically check for shutdown
		timeout.tv_sec = 1;
		timeout.tv_usec = 0;

		int ret = select(mSocketFD + 1, &readfds, NULL, NULL, &timeout);

		if(ret < 0)
		{
			// Error in select
			if(errno == EINTR)
			{
				// Interrupted by signal, return false to allow checking g_stop
				return false;
			}
			sAssertion(false, "(CServer::waitForClient()): select() failed.", true);
		}
		else if(ret == 0)
		{
			// Timeout - return false to allow caller to check g_stop flag
			return false;
		}
		else
		{
			// Socket is ready, try to accept
			mConnectedSocketFD = accept(mSocketFD,
										reinterpret_cast<struct sockaddr*>(&mClientAddr),
										&mClientLen);
			if(mConnectedSocketFD >= 0)
			{
				// Set send/receive timeouts on the connected socket
				struct timeval sockTimeout;
				sockTimeout.tv_sec = 1;  // 1 second timeout
				sockTimeout.tv_usec = 0;

				setsockopt(mConnectedSocketFD, SOL_SOCKET, SO_SNDTIMEO, &sockTimeout, sizeof(sockTimeout));
				setsockopt(mConnectedSocketFD, SOL_SOCKET, SO_RCVTIMEO, &sockTimeout, sizeof(sockTimeout));

				return true;
			}
			else if(errno == EINTR)
			{
				// accept interrupted by signal
				return false;
			}
			// Other errors, assert
			sAssertion(false, "(CServer::waitForClient()): Failed to accept the client connection.", true);
		}
	}
	return false;
}
CServer::CServer() : mSocketFD(-1),
					 mConnectedSocketFD(-1),
					 mClientLen(0U)
{

}
CServer::~CServer()
{
	// Only shutdown/close if socket is valid
	if(mConnectedSocketFD >= 0)
	{
		Int32 retVal = shutdown(mConnectedSocketFD, SHUT_RDWR);
		if(retVal < 0 && errno != ENOTCONN)
		{
			std::cerr << "(CServer::~CServer()): Warning: Failed to shutdown connected socket, errno: " << errno << std::endl;
		}

		retVal = close(mConnectedSocketFD);
		if(retVal < 0)
		{
			std::cerr << "(CServer::~CServer()): Warning: Failed to close connected socket, errno: " << errno << std::endl;
		}
	}

	if(mSocketFD >= 0)
	{
		Int32 retVal = close(mSocketFD);
		if(retVal < 0)
		{
			std::cerr << "(CServer::~CServer()): Warning: Failed to close socket, errno: " << errno << std::endl;
		}
	}
}
