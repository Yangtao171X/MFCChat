#include "pch.h"
#include "CChatSocket.h"
#include "MFCChatServerDlg.h"
CChatSocket::CChatSocket() {

}
CChatSocket::~CChatSocket() {

}
void CChatSocket::OnReceive(int nErrorCode) {
	TRACE("---CChatSocket::OnReceive---");
	//��ȡDlg���ڶ���
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*)AfxGetApp()->GetMainWnd();
	//�������ջ�����
	char recvBuffer[SERVER_MAX_BUF];
	//���տͻ��˷���������Ϣ��������
	CAsyncSocket::Receive(recvBuffer, SERVER_MAX_BUF, 0);
	TRACE("---�������˽��յ��Ŀͻ�����Ϣ��%s---",recvBuffer);

	//��������תΪCString��
	USES_CONVERSION;
	CString strRecvBuffer = A2W(recvBuffer);
	//������������ƴ�Ӷ�����Ϣ
	/*
	CString strTime;
	dlg->m_time = CTime::GetCurrentTime();
	strTime = dlg->m_time.Format("%X");
	CString strShow = strTime + _T(" ���ͻ��ˡ���") + strRecvBuffer;
	*/
	CString strShow = dlg->CatShowMessage(_T(" ���ͻ��ˡ���"), strRecvBuffer);
	//��ƴ�Ӻõ���Ϣ�ŵ���¼�б��
	dlg->m_listBox.AddString(strShow);
	//�ص�����OnReceive()����
	CAsyncSocket::OnReceive(nErrorCode);
}