#ifndef CSERVER_HPP
#define CSERVER_HPP

#include "baselink.hpp"

class CServer : public CBaseLink
{
private:
    SOCKET m_listenSocket;

public:
    CServer();
    ~CServer();

    bool Connect(const char* address, int port);
    bool Disconnect();
};

#endif // CSERVER_HPP