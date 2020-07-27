#ifndef CUDPPROCESS_H
#define CUDPPROCESS_H

#include "baselink.hpp"

class CUDPProcess : public CBaseLink
{
protected:
    SOCKADDR_IN m_serverAddr;
    int m_sizeSockAddr;

public:
    CUDPProcess();
    ~CUDPProcess();

    bool Send(const char* message) final;
    bool Receive(char* message, int size) final;
};

#endif // CUDPPROCESS_H