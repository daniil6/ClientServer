#ifndef CTCPSENDRECEIVE_H
#define CTCPSENDRECEIVE_H

#include "baselink.hpp"

class CTCPProcess : public CBaseLink
{
public:
    CTCPProcess();
    ~CTCPProcess();

    bool Send(const char* message) final;
    bool Receive(char* message, int size) final;
};

#endif // CTCPSENDRECEIVE_H