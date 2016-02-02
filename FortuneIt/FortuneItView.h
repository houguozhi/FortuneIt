
// FortuneItView.h : CFortuneItView ��Ľӿ�
//

#pragma once

#include <afxdb.h>
#include "FinancialTimeSeries.h"
#include "DlgStock.h"


class CFortuneItView : public CView
{
protected: // �������л�����
	CFortuneItView();
	DECLARE_DYNCREATE(CFortuneItView)

// ����
public:
	CFortuneItDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CFortuneItView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

public:
	CDlgStock m_dlgStk;

public:
	afx_msg void OnFortuneitTest1();
	afx_msg void OnFortuneitTest2();
};

#ifndef _DEBUG  // FortuneItView.cpp �еĵ��԰汾
inline CFortuneItDoc* CFortuneItView::GetDocument() const
   { return reinterpret_cast<CFortuneItDoc*>(m_pDocument); }
#endif

