
// Push_Box.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPush_BoxApp:
// �йش����ʵ�֣������ Push_Box.cpp
//

class CPush_BoxApp : public CWinApp
{
public:
	CPush_BoxApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	afx_msg void OnAboutUs();
};

extern CPush_BoxApp theApp;