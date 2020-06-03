#include "server.hpp"

CServer::CServer()
{
}

CServer::~CServer()
{
}

bool CServer::Connect(const char* address, int port)
{
    int result = 0;
    WSADATA wsaData;

    m_error.clear();

    SOCKADDR_IN serverAddr;
    SOCKADDR_IN acceptAddr;

    int lenAddr = sizeof(acceptAddr);

    ZeroMemory(&serverAddr, sizeof(sockaddr_in));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.S_un.S_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(result != NO_ERROR) {
        setError("Error WSAStartup ", result);
        return false;
    } else
        m_error.append("Success WSAStartup\n");

    m_listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(m_listenSocket == INVALID_SOCKET) {
        m_error.append("Error socket\n");
        setError("Error WSAGetLastError ", WSAGetLastError());
        WSACleanup();
        return false;
    } else
        m_error.append("Success socket\n");

    result = bind(m_listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
    if(result == SOCKET_ERROR) {
        setError("Error bind ", result);
        setError("Error WSAGetLastError ", WSAGetLastError());
        CloseSocket(m_listenSocket);
        return false;
    } else
        m_error.append("Success bind\n");

    result = listen(m_listenSocket, SOMAXCONN);
    if(result == SOCKET_ERROR) {
        setError("Error listen ", result);
        setError("Error WSAGetLastError ", WSAGetLastError());
        CloseSocket(m_listenSocket);
        return false;
    } else
        m_error.append("Success listen\n");

    m_socket = accept(m_listenSocket, (SOCKADDR*)&acceptAddr, &lenAddr);
    if(m_socket == INVALID_SOCKET) {
        m_error.append("Error accept\n");
        setError("Error WSAGetLastError ", WSAGetLastError());
        Disconnect();
        return false;
    } else
        m_error.append("Success accept\n");

    return true;
}

bool CServer::Disconnect()
{
    bool result = true;
    if(CloseSocket(m_socket) == false)
        result = false;

    if(CloseSocket(m_listenSocket) == false)
        result = false;

    return result;
}