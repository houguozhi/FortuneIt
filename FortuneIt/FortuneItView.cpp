
// FortuneItView.cpp : CFortuneItView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FortuneIt.h"
#endif

#include "FortuneItDoc.h"
#include "FortuneItView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MainFrm.h"

// CFortuneItView

IMPLEMENT_DYNCREATE(CFortuneItView, CView)

BEGIN_MESSAGE_MAP(CFortuneItView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFortuneItView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FORTUNEIT_TEST1, &CFortuneItView::OnFortuneitTest1)
	ON_COMMAND(ID_FORTUNEIT_TEST2, &CFortuneItView::OnFortuneitTest2)
END_MESSAGE_MAP()

// CFortuneItView ����/����

CFortuneItView::CFortuneItView()
{
	// TODO: �ڴ˴���ӹ������

}

CFortuneItView::~CFortuneItView()
{
}

BOOL CFortuneItView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFortuneItView ����

void CFortuneItView::OnDraw(CDC* /*pDC*/)
{
	CFortuneItDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CFortuneItView ��ӡ


void CFortuneItView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFortuneItView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFortuneItView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFortuneItView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CFortuneItView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFortuneItView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFortuneItView ���

#ifdef _DEBUG
void CFortuneItView::AssertValid() const
{
	CView::AssertValid();
}

void CFortuneItView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFortuneItDoc* CFortuneItView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFortuneItDoc)));
	return (CFortuneItDoc*)m_pDocument;
}
#endif //_DEBUG


// CFortuneItView ��Ϣ�������


void CFortuneItView::OnFortuneitTest1()
{
	CDatabase db;
	db.Open(_T("hgzStk32"));
	CRecordset set1(&db);
	db.Close();
}


void CFortuneItView::OnFortuneitTest2()
{
	CStock stk;
	stk.Requery(_T("SZ000002"), CTimePair(CTime(2007, 1, 1, 0, 0, 0), CTime(2007, 5, 31, 23, 59, 59)), CYCLE_t::DAY);
	
}
