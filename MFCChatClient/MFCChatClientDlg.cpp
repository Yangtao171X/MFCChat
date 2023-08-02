
// MFCChatClientDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatClient.h"
#include "MFCChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCChatClientDlg 对话框



CMFCChatClientDlg::CMFCChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_listBox);
	DDX_Control(pDX, IDC_MSG_EDIT, m_inputEdit);
}

BEGIN_MESSAGE_MAP(CMFCChatClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT_BUTTON, &CMFCChatClientDlg::OnBnClickedConnectButton)
	ON_BN_CLICKED(IDC_SEND_BUTTON, &CMFCChatClientDlg::OnBnClickedSendButton)
END_MESSAGE_MAP()


// CMFCChatClientDlg 消息处理程序

BOOL CMFCChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//【设置客户端界面的默认端口号、默认IP地址】
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));
	GetDlgItem(IDC_IPADDRESS)->SetWindowText(_T("127.0.0.1"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCChatClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatClientDlg::OnBnClickedConnectButton()
{
	// 【连接按钮】
	TRACE("---OnBnClickedConnectButton---");

	CString cstrPort, cstrIP;//分别保存用户输入的端口号和IP
	//从控件中获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(cstrPort);//获取端口号
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(cstrIP);//获取IP
	//将CString转为char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(cstrPort);
	LPCSTR szIP = (LPSTR)T2A(cstrIP);
	
	//创建客户端套接字对象
	m_clientSocket = new CMySocket();
	//创建套接字，并设置合法性检查
	if (!m_clientSocket->Create()) {//若创建失败
		TRACE("---【error】：客户端套接字创建失败，错误码：%d---", GetLastError());
		return;
	}
	else {
		TRACE("---客户端套接字创建成功！---");
	}
	//连接套接字
	int iPort = _ttoi(cstrPort);//将CString转为int
	if (m_clientSocket->Connect(cstrIP, iPort) != 0) {//CAsyncSocket::Connect()函数，连接成功返回非0，连接失败返回0
		TRACE("---【error】：客户端连接服务器失败，错误码：%d---", GetLastError());
		return;
	}

	TRACE("---szPort = %s，szIP = %s---", szPort, szIP);
}


void CMFCChatClientDlg::OnBnClickedSendButton()
{
	TRACE("---CMFCChatClientDlg::OnBnClickedSendButton---");
	//【客户端发送按钮】

	//获取编辑框要发送的内容
	CString strSendMsg;
	GetDlgItem(IDC_MSG_EDIT)->GetWindowText(strSendMsg);
	//将发送内容从CString转为char*的发送缓冲区
	USES_CONVERSION;
	LPCSTR szSendBuffer = T2A(strSendMsg);
	TRACE("---客户端要发送的信息：%s---", szSendBuffer);

	//发送到服务器端
	m_clientSocket->Send(szSendBuffer, 200, 0);
	//获取当前时间，并拼接发送内容
	CString strTime;
	m_time = CTime::GetCurrentTime();
	strTime = m_time.Format("%X");
	CString strShow = strTime + _T(" 【客户端】：") + strSendMsg;
	//将拼接好的发送内容显示到历史记录列表框
	m_listBox.AddString(strShow);
	//更新列表框控件变量值
	m_listBox.UpdateData(FALSE);
	//发送后清空编辑框
	GetDlgItem(IDC_MSG_EDIT)->SetWindowText(_T(""));
}
