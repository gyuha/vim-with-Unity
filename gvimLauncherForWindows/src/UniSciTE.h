
// UniSciTE.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CUniSciTEApp:
// �� Ŭ������ ������ ���ؼ��� UniSciTE.cpp�� �����Ͻʽÿ�.
//

class CUniSciTEApp : public CWinApp
{
public:
	CUniSciTEApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CUniSciTEApp theApp;