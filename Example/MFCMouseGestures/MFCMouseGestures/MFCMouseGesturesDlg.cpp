
// MFCMouseGesturesDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCMouseGestures.h"
#include "MFCMouseGesturesDlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMFCMouseGesturesDlg �Ի���



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


// CMFCMouseGesturesDlg ��Ϣ�������

BOOL CMFCMouseGesturesDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	//������ʼ��
	m_bIsCapture = FALSE;
	m_StartPoint.x = 0;
	m_StartPoint.y = 0;
	m_iMouseGS = 0;
	m_iMouseGE = 0;
	m_iMGLen = 4;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCMouseGesturesDlg::OnPaint()
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
HCURSOR CMFCMouseGesturesDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCMouseGesturesDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nFlags == MK_LBUTTON)//�ж�ʱ������������
	{
		//��ȡ�豸������
		CClientDC dc(this);
		CPen p(PS_SOLID, 6, RGB(0, 60, 255));
		dc.SelectObject(p);
		//�Ӵ�ǰһ�㵽��ǰ�㻭һ����
		dc.MoveTo(m_StartPoint.x, m_StartPoint.y);
		dc.LineTo(point.x, point.y);

		if (m_bIsCapture)//��ʼ��ֵ��TRUE, ֻ�е���һ���ʱ��������Ķ���
		{
			m_bIsCapture = FALSE;
			SetCapture();//�������
			m_StartPoint = point;//��¼��ʼ�����
		}

		char dir;
		if (MoveDirection(point, &dir))//���ú���
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
	if (m_iMouseGE != 0 || m_iMouseGS != 0)//m_iMouseGS��m_iMouseGE��ʼΪ0
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (!m_bIsCapture)//����־����,�Ƿ񴥷�����궯��
	{
		m_bIsCapture = TRUE;
		ReleaseCapture();
		int i = 0;
		m_SeqMG[0] = '\0';
		while (m_iMouseGE != m_iMouseGS)//����궯�����浽m_SeqMG��,����������\0
		{
			m_SeqMG[i] = m_MouseGestures[m_iMouseGS];
			i++;
			m_SeqMG[i] = '\0';
			m_iMouseGS = (m_iMouseGS + 1) % m_iMGLen;
		}
		if (i > 0)//��ʼ�Ƚ���궯��,��������Լ����Զ���Ķ���������!
		{
			if (strcmp(m_SeqMG, "D") == 0)
				m_mouseInfo = "��(Down)";
			else if (strcmp(m_SeqMG, "L") == 0)
				m_mouseInfo = "��(Left)";
			else if (strcmp(m_SeqMG, "U") == 0)
				m_mouseInfo = "��(Up)";
			else if (strcmp(m_SeqMG, "R") == 0)
				m_mouseInfo = "��(Right)";
			else {
				m_mouseInfo = "δ֪(Unknown)";
				i = 0;
			}
			//Ϊ����������Ƶ�����
			Invalidate();
		}
		UpdateData(FALSE);
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}