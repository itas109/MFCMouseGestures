
// MFCMouseGestures.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMFCMouseGesturesApp: 
// �йش����ʵ�֣������ MFCMouseGestures.cpp
//

class CMFCMouseGesturesApp : public CWinApp
{
public:
	CMFCMouseGesturesApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMFCMouseGesturesApp theApp;