#ifndef CBASELINK_HPP
#define CBASELINK_HPP

#include <string>
#include <winsock2.h>

class CBaseLink
{
private:
protected:
    SOCKET m_socket;

    std::string m_error;
    void setError(const char* strError, int iError);

    bool CloseSocket(SOCKET& cSocket);

public:
    CBaseLink();
    virtual ~CBaseLink();

    virtual bool Send(const char* message) = 0;
    virtual bool Receive(char* message, int size) = 0;

    virtual bool Connect(const char* address, int port) = 0;
    virtual bool Disconnect() = 0;

    std::string GetError();
};

#endif // CBASELINK_HPP