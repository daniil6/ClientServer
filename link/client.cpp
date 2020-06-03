#include "client.hpp"

CClient::CClient()
{
}

CClient::~CClient()
{
}

// "192.168.1.34"
// 55213

bool CClient::Connect(const char* address, int port)
{
    int result = 0;
    WSADATA wsaData;
    sockaddr_in clientService;

    m_error.clear();

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != NO_ERROR) {
        setError("Error WSAStartup=", result);
        return false;
    } else
        m_error.append("Success WSAStartup\n");

    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_socket == INVALID_SOCKET) {
        m_error.append("Error socket\n");
        setError("Error WSAGetLastError=", WSAGetLastError());
        WSACleanup();
        return false;
    } else
        m_error.append("Success socket\n");

    ZeroMemory(&clientService, sizeof(sockaddr_in));
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(address);
    clientService.sin_port = htons(port);

    result = connect(m_socket, (SOCKADDR*)&clientService, sizeof(clientService));
    if(result == SOCKET_ERROR) {
        setError("Error connect result=", result);
        setError("Error WSAGetLastError=", WSAGetLastError());
        CloseSocket(m_socket);
        return false;
    } else
        m_error.append("Success connect\n");

    return true;
}

bool CClient::Disconnect()
{
    return CloseSocket(m_socket);
}