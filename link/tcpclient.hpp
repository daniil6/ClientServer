#ifndef CCLIENT_HPP
#define CCLIENT_HPP

#include "baselink.hpp"

class CTCPClient : public CBaseLink
{
public:
    CTCPClient();
    ~CTCPClient();

    bool Connect(const char* address, int port);
    bool Disconnect();
};

#endif // CCLIENT_HPP