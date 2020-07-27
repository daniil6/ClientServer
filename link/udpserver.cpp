#include "udpserver.hpp"

CUDPServer::CUDPServer()
{
}

CUDPServer::~CUDPServer()
{
}

bool CUDPServer::Connect(const char* address, int port)
{
    int result = 0;
    WSADATA wsaData;

    ZeroMemory(&m_serverAddr, sizeof(SOCKADDR_IN));
    m_serverAddr.sin_family = AF_INET;
    m_serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
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

    result = bind(m_socket, (SOCKADDR*)&m_serverAddr, sizeof(m_serverAddr));
    if(result == SOCKET_ERROR) {
        setError("Error bind ", result);
        setError("Error WSAGetLastError ", WSAGetLastError());
        CloseSocket(m_socket);
        return false;
    } else
        m_error.append("Success bind\n");

    return true;
}

bool CUDPServer::Disconnect()
{
    bool result = true;
    if(CloseSocket(m_socket) == false)
        result = false;

    WSACleanup();

    return result;
}