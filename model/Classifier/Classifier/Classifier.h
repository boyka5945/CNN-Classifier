
// Classifier.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CClassifierApp: 
// �йش����ʵ�֣������ Classifier.cpp
//

class CClassifierApp : public CWinApp
{
public:
	CClassifierApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CClassifierApp theApp;
