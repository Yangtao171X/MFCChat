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
	CString str;
	dlg->m_time = CTime::GetCurrentTime();//��ȡ��ǰʱ��
	str = dlg->m_time.Format("%X");//��ʽ��ʱ��
	str += _T("������������ӳɹ���");//ƴ��
	//��������ʾ��Ϣ��CString������ʷ��¼��ListBox��
	dlg->m_listBox.AddString(str);
	//�ص�����CAsyncSocket��OnConnect()����
	CAsyncSocket::OnConnect(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode) {
	TRACE("---CMySocket::OnReceive---");
}