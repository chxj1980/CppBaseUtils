
// CharsetDetectDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCharsetDetectDemoApp: 
// �йش����ʵ�֣������ CharsetDetectDemo.cpp
//

class CCharsetDetectDemoApp : public CWinApp
{
public:
	CCharsetDetectDemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCharsetDetectDemoApp theApp;