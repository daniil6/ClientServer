#include "udpclient.hpp"

CUDPClient::CUDPClient()
{
}

CUDPClient::~CUDPClient()
{
}

bool CUDPClient::Connect(const char* address, int port)
{
    int result = 0;
    WSADATA wsaData;

    ZeroMemory(&m_serverAddr, sizeof(SOCKADDR_IN));
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_addr.S_un.S_addr = inet_addr(address);
    m_serverAddr.sin_port = htons(port);

    m_sizeSockAddr = sizeof(SOCKADDR_IN);

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != NO_ERROR) {
        setError("Error WSAStartup ", result);
        return false;
    } else
        m_error.append("Success WSAStartup\n");

    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if(m_socket == INVALID_SOCKET) {
        m_error.append("Error socket\n");
        setError("Error WSAGetLastError ", WSAGetLastError());
        WSACleanup();
        return false;
    } else
        m_error.append("Success socket\n");

    return true;
}

bool CUDPClient::Disconnect()
{
    bool result = true;
    if(CloseSocket(m_socket) == false)
        result = false;

    WSACleanup();

    return result;
}