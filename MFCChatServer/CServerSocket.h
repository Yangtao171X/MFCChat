#pragma once

#include <afxSock.h>//����CAsyncSocket��ͷ�ļ�

class CServerSocket :
    public CAsyncSocket
{
public:
    CServerSocket();//����
    virtual ~CServerSocket();//����
    virtual void OnAccept(int nErrorCode);
};

