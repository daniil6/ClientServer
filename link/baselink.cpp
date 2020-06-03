#include "baselink.hpp"

CBaseLink::CBaseLink()
{
}

CBaseLink::~CBaseLink()
{
}

void CBaseLink::setError(const char* strError, int iError)
{
    m_error.append(strError);
    m_error.append(std::to_string(iError));
    m_error.append("\n");
}

std::string CBaseLink::GetError()
{
    return m_error;
}

bool CBaseLink::CloseSocket(SOCKET& cSocket)
{
    int result = closesocket(cSocket);
    if(result == SOCKET_ERROR) {
        setError("Error closesocket result=", result);
        setError("Error WSAGetLastError=", WSAGetLastError());
        WSACleanup();
    }

    m_error.append("Success closesocket\n");
    return true;
}

bool CBaseLink::Send(const char* message)
{
    m_error.clear();
    int result = send(m_socket, message, (int)strlen(message), 0);
    if(result == SOCKET_ERROR) {
        setError("Error send result=", result);
        setError("Error WSAGetLastError=", WSAGetLastError());
        return false;
    } else
        m_error.append("Success send\n");

    // result = shutdown(m_socket, SD_SEND);
    // if(result == SOCKET_ERROR) {
    //    setError("Error shutdown result=", result);
    //    setError("Error WSAGetLastError=", WSAGetLastError());
    //    return false;
    //} else
    //    m_error.append("Success shutdown\n");

    return true;
}

bool CBaseLink::Receive(char* message, int size)
{
    m_error.clear();

    int result = recv(m_socket, message, size, 0);
    if(result > 0) {
        setError("Bytes received: ", result);
    } else {
        if(result != 0) {
            setError("Error recv result=", result);
            setError("Error WSAGetLastError=", WSAGetLastError());
            return false;
        } else
            m_error.append("Connection closed\n");
    }

    return true;
}