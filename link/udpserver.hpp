#ifndef CUDPSERVER_H
#define CUDPSERVER_H

#include "udpprocess.hpp"

class CUDPServer : public CUDPProcess
{
private:
    bool Connect(const char* address, int port) final;
    bool Disconnect() final;

public:
    CUDPServer();
    ~CUDPServer();
};

#endif // CUDPSERVER_H