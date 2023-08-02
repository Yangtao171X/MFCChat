#include "pch.h"
#include "CServerSocket.h"
#include "MFCChatServerDlg.h"
#include "CChatSocket.h"
CServerSocket::CServerSocket() {

}
CServerSocket::~CServerSocket() {

}
void CServerSocket::OnAccept(int nErrorCode) {
	TRACE("---CServerSocket::OnAccept---");
	//获取Dlg窗口对象
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*) AfxGetApp()->GetMainWnd();
	//创建临时连接的套接字对象
	dlg->m_chatSocket = new CChatSocket;
	//使用回调函数，接受临时连接套接字的连接
	CAsyncSocket::Accept(*(dlg->m_chatSocket));
	//获取并格式化当前时间，再拼接成提示信息，存入CString
	CString str;
	dlg->m_time = CTime::GetCurrentTime();//获取当前时间
	str = dlg->m_time.Format("%X");
	str += _T("客户端连接成功！");
	//将CString提示信息放入历史记录的ListBox中
	dlg->m_listBox.AddString(str);
	//更新控件变量值
	dlg->m_listBox.UpdateData(FALSE);
	//回调父类的OnAccept()函数
	CAsyncSocket::OnAccept(nErrorCode);
}
