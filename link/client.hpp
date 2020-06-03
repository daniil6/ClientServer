#ifndef CCLIENT_HPP
#define CCLIENT_HPP

#include "baselink.hpp"

class CClient : public CBaseLink
{
public:
    CClient();
    ~CClient();

    bool Connect(const char* address, int port);
    bool Disconnect();
};

#endif // CCLIENT_HPP