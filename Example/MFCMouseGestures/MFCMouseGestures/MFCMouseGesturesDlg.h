
// MFCMouseGesturesDlg.h : ͷ�ļ�
//

#pragma once

//��������
#define RBUT_LEFT 'L'
#define RBUT_RIGHT 'R'
#define RBUT_UP 'U'
#define RBUT_DOWN 'D'

// CMFCMouseGesturesDlg �Ի���
class CMFCMouseGesturesDlg : public CDialogEx
{
// ����
public:
	CMFCMouseGesturesDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCMOUSEGESTURES_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	//��������ͺ���
	BOOL m_bIsCapture;//һ����־����
	char m_MouseGestures[4], m_SeqMG[4];//����������궯���Ĵ���U(��) D(��)��..
	int m_iMGLen;
	int m_iMouseGS, m_iMouseGE;
	POINT m_StartPoint;//���������
	BOOL MoveDirection(CPoint& point, char* Direction); //�ж����ļ򵥶���,�ĸ�,��������
	void PushMouseGesture(char gesture);//����궯���Ĵ��뱣������


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
