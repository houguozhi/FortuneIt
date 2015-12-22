
// FortuneItView.cpp : CFortuneItView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFortuneItView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_FORTUNEIT_TEST1, &CFortuneItView::OnFortuneitTest1)
	ON_COMMAND(ID_FORTUNEIT_TEST2, &CFortuneItView::OnFortuneitTest2)
END_MESSAGE_MAP()

// CFortuneItView 构造/析构

CFortuneItView::CFortuneItView()
{
	// TODO: 在此处添加构造代码

}

CFortuneItView::~CFortuneItView()
{
}

BOOL CFortuneItView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CFortuneItView 绘制

void CFortuneItView::OnDraw(CDC* /*pDC*/)
{
	CFortuneItDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CFortuneItView 打印


void CFortuneItView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFortuneItView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CFortuneItView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CFortuneItView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CFortuneItView 诊断

#ifdef _DEBUG
void CFortuneItView::AssertValid() const
{
	CView::AssertValid();
}

void CFortuneItView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFortuneItDoc* CFortuneItView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFortuneItDoc)));
	return (CFortuneItDoc*)m_pDocument;
}
#endif //_DEBUG


// CFortuneItView 消息处理程序


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
