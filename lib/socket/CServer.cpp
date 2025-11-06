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
			switch(errno)
			{
				case ECONNRESET:
					success = false;
					break;
				default:
					sAssertion(retVal >= 0,
							"(CServer::receiveMessage()): Failed to read from the socket", true);
					break;
			}
			break;
		}
		else if(retVal == 0)
		{
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
		if((retVal < 0) && (errno == EPIPE))
		{
			std::cout << "[*] Server: Connection was terminated" << std::endl;
			success = false;
			break;
		}
		else if(retVal < 0)
		{
			std::cout << "CServer::transmitMessage(): Failed to send the message, errno: " << errno << std::endl;
		}
		success = true;
		writtenByte += retVal;
	}while(writtenByte < sizeof(content));
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
	mConnectedSocketFD = accept(mSocketFD,
					   	   	    reinterpret_cast<struct sockaddr*>(&mClientAddr),
								&mClientLen);
	sAssertion(mConnectedSocketFD >= 0, "(CServer::CServer()): Failed to accept the client connection.", true);
	return true;
}
CServer::CServer() : mSocketFD(-1),
					 mConnectedSocketFD(-1),
					 mClientLen(0U)
{

}
CServer::~CServer()
{
	Int32 retVal = shutdown(mConnectedSocketFD, SHUT_RDWR);
	sAssertion(retVal >= 0, "(CServer::~CServer()): Failed to shutdown socket.", true);

	retVal = close(mConnectedSocketFD);
	sAssertion(retVal >= 0, "(CServer::~CServer()): Failed to close connected socket.", true);

	retVal = close(mSocketFD);
	sAssertion(retVal >= 0, "(CServer::~CServer()): Failed to close socket.", true);
}
