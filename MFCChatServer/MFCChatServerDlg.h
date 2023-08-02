
// MFCChatServerDlg.h: 头文件
//

#pragma once

#include "CServerSocket.h"
#include "CChatSocket.h"

#define SERVER_MAX_BUF 1024 //服务器端发送/接收缓冲区最大值
// CMFCChatServerDlg 对话框
class CMFCChatServerDlg : public CDialogEx
{
// 构造
public:
	CMFCChatServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCHATSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStartBtn();
public:
	CServerSocket* m_serverSocket;//服务器端套接字对象
	CChatSocket* m_chatSocket;//连接后的临时套接字
	CListBox m_listBox;//历史记录列表框
	CTime m_time;//时间

	afx_msg void OnBnClickedSendBtn();
	//自定义的拼接数据函数（拼接规则：时间+昵称+发送信息，内部获取当前时间）
	CString CatShowMessage(CString strNickName, CString strSendMsg);
};
