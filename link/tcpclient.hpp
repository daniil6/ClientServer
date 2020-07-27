#ifndef CCLIENT_HPP
#define CCLIENT_HPP

#include "tcpprocess.hpp"

class CTCPClient : public CTCPProcess
{
public:
    CTCPClient();
    ~CTCPClient();

    bool Connect(const char* address, int port) final;
    bool Disconnect() final;
};

#endif // CCLIENT_HPP