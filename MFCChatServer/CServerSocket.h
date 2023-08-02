#pragma once

#include <afxSock.h>//引入CAsyncSocket类头文件

class CServerSocket :
    public CAsyncSocket
{
public:
    CServerSocket();//构造
    virtual ~CServerSocket();//析构
    virtual void OnAccept(int nErrorCode);
};

