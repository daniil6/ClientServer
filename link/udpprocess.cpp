#include "udpprocess.hpp"

CUDPProcess::CUDPProcess()
{
}

CUDPProcess::~CUDPProcess()
{
}

bool CUDPProcess::Send(const char* message)
{
    int result = sendto(m_socket, message, (int)strlen(message), 0, (struct sockaddr*)&m_serverAddr, m_sizeSockAddr);
    if(result == SOCKET_ERROR) {
        setError("Error recvfrom result=", result);
        setError("Error WSAGetLastError=", WSAGetLastError());
        return false;
    } else
        m_error.append("Success recvfrom\n");

    return true;
}

bool CUDPProcess::Receive(char* message, int size)
{
    int result = recvfrom(m_socket, message, size, 0, (struct sockaddr*)&m_serverAddr, &m_sizeSockAddr);
    if(result == SOCKET_ERROR) {
        setError("Error recvfrom result=", result);
        setError("Error WSAGetLastError=", WSAGetLastError());
        return false;
    } else
        m_error.append("Success recvfrom\n");

    return true;
}