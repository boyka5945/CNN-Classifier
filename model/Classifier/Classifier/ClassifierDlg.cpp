
// ClassifierDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Classifier.h"
#include "ClassifierDlg.h"
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


// CClassifierDlg 对话框



CClassifierDlg::CClassifierDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CLASSIFIER_DIALOG, pParent)
	, m_edit(_T("")), m_edit_2(_T("")), m_edit_3(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClassifierDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT2, m_edit_2);
	DDX_Text(pDX, IDC_EDIT3, m_edit_3);
}

BEGIN_MESSAGE_MAP(CClassifierDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CClassifierDlg::OnBnClickedButton1)
	ON_EN_CHANGE(IDC_EDIT1, &CClassifierDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON2, &CClassifierDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CClassifierDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT2, &CClassifierDlg::OnEnChangeEdit2)
	ON_BN_CLICKED(IDOK, &CClassifierDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT3, &CClassifierDlg::OnEnChangeEdit3)
END_MESSAGE_MAP()


// CClassifierDlg 消息处理程序

BOOL CClassifierDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str_1 = _T("输入抓取的图片类型");
	GetDlgItem(IDC_EDIT1)->SetWindowText(str_1);

	CString str_2 = _T("输入要查看的图片类型");
	GetDlgItem(IDC_EDIT2)->SetWindowText(str_2);

	CString str_3 = _T("图片页数，每页10张");
	GetDlgItem(IDC_EDIT3)->SetWindowText(str_3);

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CClassifierDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CClassifierDlg::OnPaint()
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
HCURSOR CClassifierDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CClassifierDlg::OnBnClickedButton1(char *name)
//{
//	// TODO: 在此添加控件通知处理程序代码
//	char cmd[100];
//	sprintf_s(cmd, "C:/model/spider.py %s", name);
//	system(cmd);
//}

void CClassifierDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString cmd;
	
	cmd = _T("python C:/model/spider.py ") + m_edit + _T(" ") + m_edit_3;
	//cmd = _T("python C:/model/spider.py ") + m_edit_3;
	int len = cmd.GetLength();
	char *psendbuf = new char[len];

	for (int i = 0; i < len; i++)
		psendbuf[i] = (char)cmd.GetAt(i);
	system(psendbuf);
	
}

void CClassifierDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CClassifierDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	system("activate python3 && python C:/model/Classifier.py");
}


void CClassifierDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();

	CString CMD = _T("C:/pictureData/") + m_edit_2;
	ShellExecute(NULL, _T("open"), CMD, NULL, NULL, SW_SHOW);

}


void CClassifierDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CClassifierDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CClassifierDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
