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
	char recvBuffer[200];
	//���տͻ��˷���������Ϣ��������
	CAsyncSocket::Receive(recvBuffer, 200, 0);
	TRACE("---�������˽��յ��Ŀͻ�����Ϣ��%s---",recvBuffer);

	//��������תΪCString��
	USES_CONVERSION;
	CString strRecvBuffer = A2W(recvBuffer);
	//������������ƴ�Ӷ�����Ϣ����ʾ����¼�б��
	CString strTime;
	dlg->m_time = CTime::GetCurrentTime();
	strTime = dlg->m_time.Format("%X");
	CString strShow = strTime + _T(" ���ͻ��ˡ���") + strRecvBuffer;
	dlg->m_listBox.AddString(strShow);
	//�ص�����OnReceive()����
	CAsyncSocket::OnReceive(nErrorCode);
}