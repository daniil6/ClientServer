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