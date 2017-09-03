
// MFCMouseGesturesDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCMouseGestures.h"
#include "MFCMouseGesturesDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCMouseGesturesDlg 对话框



CMFCMouseGesturesDlg::CMFCMouseGesturesDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCMouseGesturesDlg::IDD, pParent)
	, m_mouseInfo(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMouseGesturesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_MOUSE_INFO, m_mouseInfo);
}

BEGIN_MESSAGE_MAP(CMFCMouseGesturesDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMFCMouseGesturesDlg 消息处理程序

BOOL CMFCMouseGesturesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// TODO:  在此添加额外的初始化代码
	//变量初始化
	m_bIsCapture = FALSE;
	m_StartPoint.x = 0;
	m_StartPoint.y = 0;
	m_iMouseGS = 0;
	m_iMouseGE = 0;
	m_iMGLen = 4;

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCMouseGesturesDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCMouseGesturesDlg::OnPaint()
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
HCURSOR CMFCMouseGesturesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCMouseGesturesDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (nFlags == MK_LBUTTON)//判断时候鼠标左键按下
	{
		//获取设备上下文
		CClientDC dc(this);
		CPen p(PS_SOLID, 6, RGB(0, 60, 255));
		dc.SelectObject(p);
		//从从前一点到当前点画一条线
		dc.MoveTo(m_StartPoint.x, m_StartPoint.y);
		dc.LineTo(point.x, point.y);

		if (m_bIsCapture)//初始的值的TRUE, 只有当第一点的时候发生里面的动作
		{
			m_bIsCapture = FALSE;
			SetCapture();//捕获鼠标
			m_StartPoint = point;//记录初始坐标点
		}

		char dir;
		if (MoveDirection(point, &dir))//调用函数
		{
			PushMouseGesture(dir);
			m_StartPoint = point;
		}
	}


	CDialogEx::OnMouseMove(nFlags, point);
}

BOOL CMFCMouseGesturesDlg::MoveDirection(CPoint &point, char *Direction)
{
	int x = point.x - m_StartPoint.x;
	int y = point.y - m_StartPoint.y;
	int dist = x*x + y*y;
	if (dist > 64)
	{
		if (x > abs(y) && x > 0)
			*Direction = RBUT_RIGHT;
		else if (abs(x) > abs(y) && x<0)
			*Direction = RBUT_LEFT;
		else if (y>abs(x) && y > 0)
			*Direction = RBUT_DOWN;
		else if (abs(y) > abs(x) && y < 0)
			*Direction = RBUT_UP;
		else
			return FALSE;
		return TRUE;
	}
	else
		return FALSE;
}

void CMFCMouseGesturesDlg::PushMouseGesture(char gesture)
{
	if (m_iMouseGE != 0 || m_iMouseGS != 0)//m_iMouseGS和m_iMouseGE初始为0
	{
		int pre = (m_iMouseGE - 1 + m_iMGLen) % m_iMGLen;
		if (m_MouseGestures[pre] == gesture)
			return;
	}
	m_MouseGestures[m_iMouseGE] = gesture;
	m_iMouseGE = (m_iMouseGE + 1) % m_iMGLen;
	if (m_iMouseGS == m_iMouseGE)
		m_iMouseGS = (m_iMouseGS + 1) % m_iMGLen;
}

void CMFCMouseGesturesDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SetCapture();
	m_bIsCapture = TRUE;
	//m_StartPoint.x = LOWORD((DWORD)lParam);
	//m_StartPoint.y = HIWORD((DWORD)lParam);
	m_StartPoint = point;
	m_iMouseGS = 0;
	m_iMouseGE = 0;

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCMouseGesturesDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	if (!m_bIsCapture)//看标志变量,是否触发了鼠标动作
	{
		m_bIsCapture = TRUE;
		ReleaseCapture();
		int i = 0;
		m_SeqMG[0] = '\0';
		while (m_iMouseGE != m_iMouseGS)//将鼠标动作保存到m_SeqMG中,并在最后加上\0
		{
			m_SeqMG[i] = m_MouseGestures[m_iMouseGS];
			i++;
			m_SeqMG[i] = '\0';
			m_iMouseGS = (m_iMouseGS + 1) % m_iMGLen;
		}
		if (i > 0)//开始比较鼠标动作,在这里可以加上自定义的动作和命令!
		{
			if (strcmp(m_SeqMG, "D") == 0)
				m_mouseInfo = "下(Down)";
			else if (strcmp(m_SeqMG, "L") == 0)
				m_mouseInfo = "左(Left)";
			else if (strcmp(m_SeqMG, "U") == 0)
				m_mouseInfo = "上(Up)";
			else if (strcmp(m_SeqMG, "R") == 0)
				m_mouseInfo = "右(Right)";
			else {
				m_mouseInfo = "未知(Unknown)";
				i = 0;
			}
			//为了清空所绘制的曲线
			Invalidate();
		}
		UpdateData(FALSE);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}