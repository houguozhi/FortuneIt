
// FortuneIt.h : FortuneIt Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������
#include "MainFrm.h"

// CFortuneItApp:
// �йش����ʵ�֣������ FortuneIt.cpp
//

class CFortuneItApp : public CWinAppEx
{
public:
	CFortuneItApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	COleTemplateServer m_server;
		// �����ĵ������ķ���������
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFortuneItApp theApp;
extern CMainFrame *g_mf;
extern void println(TCHAR *szFormat, ...);