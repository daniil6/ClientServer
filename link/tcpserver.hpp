#ifndef CSERVER_HPP
#define CSERVER_HPP

#include "tcpprocess.hpp"

class CTCPServer : public CTCPProcess
{
private:
    SOCKET m_listenSocket;

public:
    CTCPServer();
    ~CTCPServer();

    bool Connect(const char* address, int port) final;
    bool Disconnect() final;
};

#endif // CSERVER_HPP