
// ClassifierDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Classifier.h"
#include "ClassifierDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CClassifierDlg �Ի���



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


// CClassifierDlg ��Ϣ�������

BOOL CClassifierDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString str_1 = _T("����ץȡ��ͼƬ����");
	GetDlgItem(IDC_EDIT1)->SetWindowText(str_1);

	CString str_2 = _T("����Ҫ�鿴��ͼƬ����");
	GetDlgItem(IDC_EDIT2)->SetWindowText(str_2);

	CString str_3 = _T("ͼƬҳ����ÿҳ10��");
	GetDlgItem(IDC_EDIT3)->SetWindowText(str_3);

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CClassifierDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CClassifierDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//void CClassifierDlg::OnBnClickedButton1(char *name)
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	char cmd[100];
//	sprintf_s(cmd, "C:/model/spider.py %s", name);
//	system(cmd);
//}

void CClassifierDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CClassifierDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	system("activate python3 && python C:/model/Classifier.py");
}


void CClassifierDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	CString CMD = _T("C:/pictureData/") + m_edit_2;
	ShellExecute(NULL, _T("open"), CMD, NULL, NULL, SW_SHOW);

}


void CClassifierDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CClassifierDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CClassifierDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
