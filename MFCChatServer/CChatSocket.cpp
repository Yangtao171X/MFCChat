#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"
CChatSocket::CChatSocket() {

}
CChatSocket::~CChatSocket() {

}
void CChatSocket::OnReceive(int nErrorCode) {
	TRACE("---CChatSocket::OnReceive---");
	//获取Dlg窗口对象
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	//创建接收缓冲区
	char recvBuffer[SERVER_MAX_BUF];
	//接收客户端发过来的信息到缓冲区
	CAsyncSocket::Receive(recvBuffer, SERVER_MAX_BUF, 0);
	TRACE("---服务器端接收到的客户端信息：%s---",recvBuffer);

	//将缓冲区转为CString型
	USES_CONVERSION;
	CString strRecvBuffer = A2W(recvBuffer);
	//将缓冲区数据拼接额外信息
	/*
	CString strTime;
	dlg->m_time = CTime::GetCurrentTime();
	strTime = dlg->m_time.Format("%X");
	CString strShow = strTime + _T(" 【客户端】：") + strRecvBuffer;
	*/
	CString strShow = dlg->CatShowMessage(_T(" 【客户端】："), strRecvBuffer);
	//将拼接好的信息放到记录列表框
	dlg->m_listBox.AddString(strShow);
	//回调父类OnReceive()函数
	CAsyncSocket::OnReceive(nErrorCode);
}