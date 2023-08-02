#include "pch.h"
#include "CMySocket.h"

#include "MFCChatClientDlg.h"//����Dlg���ڵ�ͷ�ļ�
CMySocket::CMySocket() {

}
CMySocket:: ~CMySocket() {

}
void	CMySocket::OnConnect(int nErrorCode) {
	TRACE("---CMySocket::OnConnect---");
	//��ȡDlg���ڶ���
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	//��ȡ��ǰʱ�䲢��ʽ����ƴ�ӳ�һ����ʾ��Ϣ����CString��
	/*
	dlg->m_time = CTime::GetCurrentTime();//��ȡ��ǰʱ��
	CString strShow = dlg->m_time.Format("%X");//��ʽ��ʱ��
	strShow += _T("������������ӳɹ���");//ƴ��
	*/
	CString strShow = dlg->CatShowMessage(_T("������������ӳɹ���"), _T(""));
	//��������ʾ��Ϣ��CString������ʷ��¼��ListBox��
	dlg->m_listBox.AddString(strShow);
	//�ص�����CAsyncSocket��OnConnect()����
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode) {
	TRACE("---CMySocket::OnReceive---");
	//��ȡDlg���ڶ���
	CMFCChatClientDlg* dlg = (CMFCChatClientDlg*)AfxGetApp()->GetMainWnd();
	//�������ջ�����
	char recvBuffer[CLIENT_MAX_BUF];
	//���շ������˷��͹��������ݵ����ջ�����
	dlg->m_clientSocket->Receive(recvBuffer, CLIENT_MAX_BUF, 0);
	//�����ջ���������תΪCString
	USES_CONVERSION;
	CString strRecvBuffer = A2W(recvBuffer);
	//������������ƴ�Ӷ������ݺ�
	/*
	dlg->m_time = CTime::GetCurrentTime();
	CString strTime = dlg->m_time.Format("%X");
	CString strShow = strTime + _T(" ���������ˡ���") + strRecvBuffer;
	*/
	CString strShow = dlg->CatShowMessage(_T(" ���������ˡ���"), strRecvBuffer);
	//��ƴ�ӺõĻ�����������ʾ����¼�б��
	dlg->m_listBox.AddString(strShow);
	//�ص�����OnReceive()����
	CAsyncSocket::OnReceive(nErrorCode);

}