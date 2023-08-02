#pragma once
#include <afxsock.h>
class CChatSocket :
    public CAsyncSocket
{
public:
    CChatSocket();//构造
    virtual ~CChatSocket();//析构
    virtual void OnReceive(int nErrorCode);//接收处理
};

