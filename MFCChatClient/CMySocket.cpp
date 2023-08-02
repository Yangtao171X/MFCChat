#include "pch.h"
#include "CMySocket.h"

#include "MFCChatClientDlg.h"//引入Dlg窗口的头文件

CMySocket::CMySocket() {

}
CMySocket:: ~CMySocket() {

}
void	CMySocket::OnConnect(int nErrorCode) {
	TRACE("---CMySocket::OnConnect---");
	//获取Dlg窗口对象
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	//获取当前时间并格式化，拼接成一个提示信息存入CString中
	CString str;
	dlg->m_time = CTime::GetCurrentTime();//获取当前时间
	str = dlg->m_time.Format("%X");//格式化时间
	str += _T("与服务器端连接成功！");//拼接
	//将存有提示信息的CString放入历史记录的ListBox中
	dlg->m_listBox.AddString(str);
	//回调父类CAsyncSocket的OnConnect()函数
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode) {
	TRACE("---CMySocket::OnReceive---");
}