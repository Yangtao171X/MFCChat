
// MFCChatServerDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCChatServer.h"
#include "MFCChatServerDlg.h"
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


// CMFCChatServerDlg 对话框



CMFCChatServerDlg::CMFCChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MSG_LIST, m_listBox);
}

BEGIN_MESSAGE_MAP(CMFCChatServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START_BTN, &CMFCChatServerDlg::OnBnClickedStartBtn)
	ON_BN_CLICKED(IDC_SEND_BTN, &CMFCChatServerDlg::OnBnClickedSendBtn)
END_MESSAGE_MAP()


// CMFCChatServerDlg 消息处理程序

BOOL CMFCChatServerDlg::OnInitDialog()
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

	//【设置默认端口号的值】
	GetDlgItem(IDC_PORT_EDIT)->SetWindowText(_T("5000"));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCChatServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCChatServerDlg::OnPaint()
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
HCURSOR CMFCChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCChatServerDlg::OnBnClickedStartBtn()
{
	// 【启动按钮】
	TRACE("---OnBnClickedStartBtn---");
	CString cstrPort;//保存输入的端口号

	//从控件中获取内容
	GetDlgItem(IDC_PORT_EDIT)->GetWindowText(cstrPort);//获取控件中的端口号
	//将CString转为char*
	USES_CONVERSION;
	LPCSTR szPort = (LPCSTR)T2A(cstrPort);
	TRACE("---szPort = %s---", szPort);

	//创建服务器端套接字对象
	m_serverSocket = new CServerSocket();
	//创建服务器端套接字
	int iPort = _ttoi(cstrPort);//CString转为int
	if (!m_serverSocket->Create(iPort)) {
		TRACE("---【error】：服务器端套接字创建失败，错误码：%d---", GetLastError());
		return;
	}
	else {
		TRACE("---服务器端套接字创建成功！---");
	}
	//使用套接字进行监听
	if (!m_serverSocket->Listen()) {
		TRACE("---【error】：服务器端监听错误，错误码：%d---", GetLastError());
		return;
	}

	//Listen()后自动跳到CServerSocket::OnAccept()

	//获取并格式化当前时间，再拼接成提示信息，存入CString
	CString str;
	m_time = CTime::GetCurrentTime();//获取当前时间
	str = m_time.Format("%X");//格式化
	str += _T("建立服务！");//拼接
	//将CString提示信息放入历史记录的ListBox中
	m_listBox.AddString(str);
	//更新ListBox控件变量值
	UpdateData(FALSE);
}


void CMFCChatServerDlg::OnBnClickedSendBtn()
{
	// 【服务端发送按钮】
	TRACE("---CMFCChatServerDlg::OnBnClickedSendBtn---");
	//获取发送编辑框要发送的内容
	CString strSendMsg;
	GetDlgItem(IDC_MSG_EDIT)->GetWindowText(strSendMsg);
	//将发送的内容从CString转为char*
	USES_CONVERSION;
	LPCSTR szSendBuffer = T2A(strSendMsg);
	TRACE("---客户端要发送的信息：%s---", szSendBuffer);

	//发送到客户端
	m_chatSocket->Send(szSendBuffer, 200, 0);
	//将要发送的内容拼接额外信息
	m_time = CTime::GetCurrentTime();
	CString strTime = m_time.Format("%X");
	CString strShow = strTime + _T(" 【服务器端】：") + strSendMsg;
	//将拼接好的发送内容放入记录列表框中
	m_listBox.AddString(strShow);
	//更新列表框控件变量的值
	m_listBox.UpdateData(FALSE);
	//发送后清空编辑框
	GetDlgItem(IDC_MSG_EDIT)->SetWindowText(_T(""));
}
