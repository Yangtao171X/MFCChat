#pragma once

#include <afxsock.h>//CAsyncSocket���ͷ�ļ�

class CMySocket :
    public CAsyncSocket
{
public:
    CMySocket();//����
    virtual ~CMySocket();//����
    virtual void OnConnect(int nErrorCode);//��дCAsyncSocket���OnConnect()����
    virtual void OnReceive(int nErrorCode);//��дCAsyncSocket���OnReceive()����
};

