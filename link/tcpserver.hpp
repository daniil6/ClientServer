#ifndef CSERVER_HPP
#define CSERVER_HPP

#include "baselink.hpp"

class CTCPServer : public CBaseLink
{
private:
    SOCKET m_listenSocket;

public:
    CTCPServer();
    ~CTCPServer();

    bool Connect(const char* address, int port);
    bool Disconnect();
};

#endif // CSERVER_HPP