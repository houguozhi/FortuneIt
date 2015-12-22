
// FortuneIt.h : FortuneIt 应用程序的主头文件
//
#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"       // 主符号
#include "MainFrm.h"

// CFortuneItApp:
// 有关此类的实现，请参阅 FortuneIt.cpp
//

class CFortuneItApp : public CWinAppEx
{
public:
	CFortuneItApp();


// 重写
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// 实现
	COleTemplateServer m_server;
		// 用于文档创建的服务器对象
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