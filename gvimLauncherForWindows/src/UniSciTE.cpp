
// UniSciTE.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "UniSciTE.h"
#include <windows.h>
#include <stdio.h>
#include <shellapi.h>
#include <comdef.h>
#include <afxpriv.h> 

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CUniSciTEApp

BEGIN_MESSAGE_MAP(CUniSciTEApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CUniSciTEApp ����

CUniSciTEApp::CUniSciTEApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CUniSciTEApp ��ü�Դϴ�.

CUniSciTEApp theApp;

BOOL get_module_directory(TCHAR *obuf, size_t osize)
{
	if ( ! GetModuleFileName(0, obuf, osize) )
	{
		*obuf = '\0';// insure it's NUL terminated
		return FALSE;
	}

	TCHAR*lastslash = 0;

	for ( ; *obuf; obuf ++)
	{
		if ( *obuf == '\\' || *obuf == '/' )
			lastslash = obuf;
	}

	if ( lastslash ) *lastslash = '\0';

	return TRUE;
}


// CUniSciTEApp �ʱ�ȭ

BOOL CUniSciTEApp::InitInstance()
{
//	CWinApp::InitInstance();

	LPWSTR *szArglist;
	int nArgs;

	szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
	if( NULL == szArglist )
	{
		wprintf(L"CommandLineToArgvW failed\n");
		return 0;
	}

	if (nArgs < 3)
	{
		AfxMessageBox("Need more parameters.");
		return 0;
	}

	// INI ���� �б�
	char szCurDir[256] = {NULL,};
	get_module_directory(szCurDir, sizeof(szCurDir));
	strcat_s(szCurDir, "\\wrapper.ini");

	char strBuf[256] = {NULL,};

	GetPrivateProfileString("Init", "Application", NULL, strBuf, sizeof(strBuf), szCurDir);
	CString strApplication;
	strApplication.Format("%s", strBuf);

	GetPrivateProfileString("Init", "LineOption", NULL, strBuf, sizeof(strBuf), szCurDir);
	CString strLineOption;
	strLineOption.Format("%s", strBuf);
	USES_CONVERSION;

	CString strGotoLine;
	strGotoLine.Format("%s", W2A(szArglist[2]));
	strGotoLine.Replace("-goto:", strLineOption);

	GetPrivateProfileString("Init", "OtherOption", NULL, strBuf, sizeof(strBuf), szCurDir);
	CString strOtherOption;
	strOtherOption.Format("%s", strBuf);

	CString param;
	param.Format("%s %s \"%s\"", 
		strOtherOption,
		strGotoLine,
		W2A(szArglist[1])
		);

	HINSTANCE hInstance = ShellExecute(NULL, _T("open"), strApplication, param, NULL, SW_SHOWNORMAL);  
	if (hInstance <= (HINSTANCE) 32)
	{
		CString erroMsg;
		erroMsg.Format("Failed to run \"%s\", Error: %d", strApplication, GetLastError());
		AfxMessageBox(erroMsg);
	}
	return FALSE;
}

