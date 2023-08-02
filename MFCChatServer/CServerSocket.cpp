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
	//��ȡDlg���ڶ���
	CMFCChatServerDlg* dlg = (CMFCChatServerDlg*) AfxGetApp()->GetMainWnd();
	//������ʱ���ӵ��׽��ֶ���
	dlg->m_chatSocket = new CChatSocket;
	//ʹ�ûص�������������ʱ�����׽��ֵ�����
	CAsyncSocket::Accept(*(dlg->m_chatSocket));
	//��ȡ����ʽ����ǰʱ�䣬��ƴ�ӳ���ʾ��Ϣ������CString
	CString str;
	dlg->m_time = CTime::GetCurrentTime();//��ȡ��ǰʱ��
	str = dlg->m_time.Format("%X");
	str += _T("�ͻ������ӳɹ���");
	//��CString��ʾ��Ϣ������ʷ��¼��ListBox��
	dlg->m_listBox.AddString(str);
	//���¿ؼ�����ֵ
	dlg->m_listBox.UpdateData(FALSE);
	//�ص������OnAccept()����
	CAsyncSocket::OnAccept(nErrorCode);
}
