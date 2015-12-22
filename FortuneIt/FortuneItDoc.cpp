
// FortuneItDoc.cpp : CFortuneItDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FortuneIt.h"
#endif

#include "FortuneItDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFortuneItDoc

IMPLEMENT_DYNCREATE(CFortuneItDoc, CDocument)

BEGIN_MESSAGE_MAP(CFortuneItDoc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFortuneItDoc, CDocument)
END_DISPATCH_MAP()

// ע��: ��������˶� IID_IFortuneIt ��֧��
//  ��֧������ VBA �����Ͱ�ȫ�󶨡�  �� IID ����ͬ���ӵ� .IDL �ļ��е�
//  ���Ƚӿڵ� GUID ƥ�䡣

// {B598BB9B-4D55-4515-B521-EFCDA96962B8}
static const IID IID_IFortuneIt =
{ 0xB598BB9B, 0x4D55, 0x4515, { 0xB5, 0x21, 0xEF, 0xCD, 0xA9, 0x69, 0x62, 0xB8 } };

BEGIN_INTERFACE_MAP(CFortuneItDoc, CDocument)
	INTERFACE_PART(CFortuneItDoc, IID_IFortuneIt, Dispatch)
END_INTERFACE_MAP()


// CFortuneItDoc ����/����

CFortuneItDoc::CFortuneItDoc()
{
	// TODO: �ڴ����һ���Թ������

	EnableAutomation();

	AfxOleLockApp();
}

CFortuneItDoc::~CFortuneItDoc()
{
	AfxOleUnlockApp();
}

BOOL CFortuneItDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CFortuneItDoc ���л�

void CFortuneItDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CFortuneItDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// ������������֧��
void CFortuneItDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
	SetSearchContent(strSearchContent);
}

void CFortuneItDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFortuneItDoc ���

#ifdef _DEBUG
void CFortuneItDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFortuneItDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFortuneItDoc ����
