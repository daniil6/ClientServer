#ifndef CUDPCLIENT_H
#define CUDPCLIENT_H

#include "udpprocess.hpp"

class CUDPClient : public CUDPProcess
{
private:
    bool Connect(const char* address, int port) final;
    bool Disconnect() final;

public:
    CUDPClient();
    ~CUDPClient();
};

#endif // CUDPCLIENT_H