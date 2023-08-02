#pragma once

#include <afxsock.h>//CAsyncSocket类的头文件

class CMySocket :
    public CAsyncSocket
{
public:
    CMySocket();//构造
    virtual ~CMySocket();//析构
    virtual void OnConnect(int nErrorCode);//重写CAsyncSocket类的OnConnect()函数
    virtual void OnReceive(int nErrorCode);//重写CAsyncSocket类的OnReceive()函数
};

