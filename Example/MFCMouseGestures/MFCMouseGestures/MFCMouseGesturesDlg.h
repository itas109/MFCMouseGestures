
// MFCMouseGesturesDlg.h : 头文件
//

#pragma once

//定义命令
#define RBUT_LEFT 'L'
#define RBUT_RIGHT 'R'
#define RBUT_UP 'U'
#define RBUT_DOWN 'D'

// CMFCMouseGesturesDlg 对话框
class CMFCMouseGesturesDlg : public CDialogEx
{
// 构造
public:
	CMFCMouseGesturesDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCMOUSEGESTURES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

	//定义变量和函数
	BOOL m_bIsCapture;//一个标志变量
	char m_MouseGestures[4], m_SeqMG[4];//用来保存鼠标动作的代码U(上) D(下)等..
	int m_iMGLen;
	int m_iMouseGS, m_iMouseGE;
	POINT m_StartPoint;//鼠标的坐标点
	BOOL MoveDirection(CPoint& point, char* Direction); //判断鼠标的简单动作,四个,上下左右
	void PushMouseGesture(char gesture);//把鼠标动作的代码保存起来


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
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	CString m_mouseInfo;
};
