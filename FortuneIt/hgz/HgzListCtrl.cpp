// HgzListCtrl.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "HgzListCtrl.h"


#define ID_MYEDIT 1

// CItemEdit

IMPLEMENT_DYNAMIC(CItemEdit, CEdit)

CItemEdit::CItemEdit()
	: m_TempStr(_T(""))
	, m_nStartChar(0)
	, m_nEndChar(0)
	, m_bEndEdit(false)
	, m_bEditingAndOutOfView(false)
{
}

CItemEdit::~CItemEdit()
{
}

BEGIN_MESSAGE_MAP(CItemEdit, CEdit)
	ON_WM_KILLFOCUS()
	ON_CONTROL_REFLECT(EN_CHANGE, &CItemEdit::OnEnChange)
END_MESSAGE_MAP()

// CItemEdit ��Ϣ�������
BOOL CItemEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	// ����ESC����RETURN�����µ���Ϣ������ΪWM_KILLFOCUS��Ϣ������Ҳ���Ը�����Ҫ������������Ϊ���������ȡ������ı�־
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_RETURN ) {       //�س���
			m_bEndEdit = TRUE;
			pMsg->message = WM_KILLFOCUS;
		}
		else if( pMsg->wParam == VK_ESCAPE ) {   //ESC��
			m_bEndEdit = TRUE;
			m_bInputValid = FALSE;    //��ʱ�ı༭�����Ч
			pMsg->message = WM_KILLFOCUS;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}

void CItemEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������
	if( m_bEndEdit ) {
		// �õ������ڣ���֪ͨ�����ڽ����༭����
		CHgzListCtrl *parent = (CHgzListCtrl *)GetParent();
		if( parent ) parent->EndEdit( m_bInputValid );
		m_bInputValid = TRUE;
	}
}

void CItemEdit::OnEnChange()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CEdit::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	// �õ������ڣ���֪ͨ�����ڽ����༭����
	CHgzListCtrl *parent = (CHgzListCtrl *)GetParent();

	if (parent) {
		::PostMessage(parent->GetSafeHwnd(), EN_CHANGE, (WPARAM)this, 0);
	}
}



//////////////////////////////////////////////////////
// CHgzListCtrl

IMPLEMENT_DYNAMIC(CHgzListCtrl, CListCtrl)

CHgzListCtrl::CHgzListCtrl()
{
	m_nItem = -1;
	m_nSubItem = 0;
	m_bEditing = FALSE;
}

CHgzListCtrl::~CHgzListCtrl()
{
	m_edit.DestroyWindow();
}

BEGIN_MESSAGE_MAP(CHgzListCtrl, CListCtrl)
	ON_WM_LBUTTONDOWN()
	ON_WM_VSCROLL()
	ON_WM_MOUSEWHEEL()
	ON_WM_KILLFOCUS()
	ON_WM_KEYUP()
	ON_MESSAGE(EN_CHANGE, &CHgzListCtrl::OnEnChange)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CHgzListCtrl::OnNMCustomdraw)
	ON_WM_KILLFOCUS()
//	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// CHgzListCtrl ��Ϣ�������
void CHgzListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	BOOL bSelected = FALSE;

	// �õ��������Item
	LVHITTESTINFO testinfo;
	testinfo.pt = point;                  //���ʱ�����λ��
	//testinfo.flags = LVHT_ONITEM;    //����ı��벻�Ǳ���
	if( SubItemHitTest(&testinfo)<0 )
		goto defalt_session;            //û�е�����Ч���򣬲�����༭
		
	// ����Ƿ���Item�����༭
	if (m_bEditing == TRUE) { 
		if (m_nItem == testinfo.iItem && m_nSubItem == testinfo.iSubItem)
			goto defalt_session;
		else
			EndEdit(TRUE);
	}
	
	int m = m_nItem;
	int n = m_nSubItem;
	m_nItem = testinfo.iItem;            //�����������к�
	m_nSubItem = testinfo.iSubItem;    //�����������к�

	Update(m);

	if(m_nSubItem == 0) {
		bSelected = IsItemSelected(m_nItem) && GetSelectedCount() == 1;
		goto defalt_session;            //���е�һ�У����༭
	}

	// ��ʼ�༭
	CListCtrl::OnLButtonDown(nFlags, point);
	m_bEditing = BeginEdit();
	return;

defalt_session:
	CListCtrl::OnLButtonDown(nFlags, point);

	if (m_nSubItem == 0 && bSelected) {
		SetItemState(m_nItem, 0, LVIS_SELECTED);
		SetItemState(m_nItem, 0, LVIS_FOCUSED);
	}
}

void CHgzListCtrl::OnKillFocus(CWnd* pNewWnd)
{
	CListCtrl::OnKillFocus(pNewWnd);

	// TODO: �ڴ˴������Ϣ����������
	m_edit.m_bEndEdit = TRUE;
}

BOOL CHgzListCtrl::BeginEdit(void)
{
	// �õ����༭���������
	CRect rect;
	if( GetSubItemRect(m_nItem, m_nSubItem, LVIR_LABEL, rect)==FALSE )
		return FALSE;

	// �����༭�ؼ�
 	if (!m_edit.GetSafeHwnd()) {
		if( m_edit.Create(WS_CHILD | WS_CLIPSIBLINGS | WS_BORDER, rect, this, ID_MYEDIT)==FALSE )
			return FALSE;
	}
	else
		m_edit.MoveWindow(&rect);

	// ȡ���༭���������
	CString txtItem = GetItemText( m_nItem, m_nSubItem );

	// ȡ����������д���༭�ؼ�
	m_edit.SetWindowText( txtItem );
	m_edit.SetFocus();
	m_edit.SetSel( 0, -1 );
	m_edit.ShowWindow( SW_SHOW );

	return TRUE;
}

void CHgzListCtrl::EndEdit(BOOL bValidate)
{
	if (m_edit.GetSafeHwnd() == NULL) return;
	// �༭�������Ч�ģ����豻�༭���������
	if( bValidate )
	{
		CString txtItem;
		m_edit.GetWindowText( txtItem );
		SetItemText(m_nItem, m_nSubItem, txtItem);
		GetParent()->SendMessage(WM_LVM_ITEMCHANGED, m_nItem, m_nSubItem);
	}

	// ���ٱ༭����
	m_edit.DestroyWindow();
	m_bEditing = FALSE;
	m_edit.m_TempStr.Empty();
}

void CHgzListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

	HoldOnEditing();
}

BOOL CHgzListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	BOOL b = CListCtrl::OnMouseWheel(nFlags, zDelta, pt);
	HoldOnEditing();
	return b;
}

void CHgzListCtrl::HoldOnEditing()
{
	m_edit.m_bEndEdit = FALSE;
	if (m_bEditing) {
		if (IsItemVisible(m_nItem)) {
			CRect rect;
			if( GetSubItemRect(m_nItem, m_nSubItem, LVIR_LABEL, rect)==FALSE )
				return;
			m_edit.MoveWindow(&rect);
			m_edit.RedrawWindow();
			if (m_edit.m_bEditingAndOutOfView) {
				m_edit.m_bEditingAndOutOfView = FALSE;
				m_edit.SetWindowText(m_edit.m_TempStr);
				m_edit.m_TempStr.Empty();
				m_edit.ShowWindow(SW_SHOW);
				m_edit.SetFocus();
				m_edit.SetActiveWindow();
				m_edit.CreateSolidCaret(1, rect.Height());
				m_edit.SetSel(m_edit.m_nStartChar, m_edit.m_nEndChar);
				m_edit.ShowCaret();
			}
			m_edit.m_bEndEdit = TRUE;
		}
		else {
			m_edit.GetWindowText(m_edit.m_TempStr);
			m_edit.GetSel(m_edit.m_nStartChar, m_edit.m_nEndChar);
			m_edit.m_bEditingAndOutOfView = TRUE;
			m_edit.ShowWindow(SW_HIDE);
		}
	}
}

BOOL CHgzListCtrl::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if( pMsg->message == WM_KEYDOWN ) {
		if (m_bEditing) {
			EnsureVisible(m_nItem, FALSE);
			HoldOnEditing();
			HWND hWnd = m_edit.GetSafeHwnd();
			pMsg->hwnd = hWnd;
			return m_edit.PreTranslateMessage(pMsg);
		}
	}

	return CListCtrl::PreTranslateMessage(pMsg);
}

void CHgzListCtrl::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CListCtrl::OnKeyUp(nChar, nRepCnt, nFlags);
}

afx_msg LRESULT CHgzListCtrl::OnEnChange(WPARAM wParam, LPARAM lParam)
{
	CWnd *parent = GetParent();
	if (parent) {
		::PostMessage(parent->GetSafeHwnd(), EN_CHANGE, wParam, lParam);
	}

	return 0;
}

void CHgzListCtrl::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	/*LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;*/

	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );
	*pResult = CDRF_DODEFAULT;

	if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYITEMDRAW;
	}
	else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
	{
		*pResult = CDRF_NOTIFYSUBITEMDRAW;
	}
	else if ( (CDDS_ITEMPREPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage )
	{
		int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );
		
		if (m_nItem == nItem) {
			if (IsItemSelected(nItem)) {
				pLVCD->clrText = RGB(0, 0, 0);        //Set the text to Red
				pLVCD->clrTextBk = RGB(0, 255, 0); //leave the background color white
			}
			else {
				pLVCD->clrText = RGB(255, 0, 255);        //Set the text to Red
				pLVCD->clrTextBk = RGB(255, 255, 255); //leave the background color white
			}
		}
		else if (IsItemSelected(nItem)) // �����ǰҪˢ�µ���Ϊѡ�����������Ϊ��ɫ������ɫ��Ϊ��ɫ
		{
			pLVCD->clrText = RGB(255, 255, 255);        //Set the text to white
			pLVCD->clrTextBk = RGB(51, 153, 255);        //Set the background color to blue

			//*pResult = CDRF_NOTIFYPOSTPAINT;
		}
		else
		{
			pLVCD->clrText = RGB(0, 0, 0);        //set the text black
			pLVCD->clrTextBk = RGB(255, 255, 255);    //leave the background color white
		}

		//*pResult = CDRF_DODEFAULT;
	}
	//else if ( (CDDS_ITEMPOSTPAINT | CDDS_SUBITEM) == pLVCD->nmcd.dwDrawStage ) 
	//{
	//	int nItem = static_cast<int>( pLVCD->nmcd.dwItemSpec );

	//	COLORREF clr1 = pLVCD->clrTextBk;
	//	TRACE(_T("pLVCD->clrTextBk = RGB(%d, %d, %d)"), GetRValue(clr1), GetGValue(clr1), GetBValue(clr1));

	//	if (m_nItem == nItem) {
	//		pLVCD->clrText = RGB(255, 0, 0);        //Set the text to Red
	//		if (IsItemSelected(nItem)) {
	//			pLVCD->clrTextBk = RGB(51, 153, 255); //leave the background color white
	//		}
	//		else {
	//			pLVCD->clrTextBk = RGB(255, 255, 255); //leave the background color white
	//		}

	//		//*pResult = CDRF_NOTIFYPOSTPAINT;
	//		Update(nItem);
	//	}
	//}
}

bool CHgzListCtrl::IsItemSelected( int nItem )
{
	return (GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED);
}

CHgzListCtrl * CHgzListCtrl::NewHgzListCtrlRegs( CWnd * pParentWnd, int nID, CRect &rect, int nRow /*= 16*/, int nCol /*= 2*/, unsigned int nExStyle /*= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES */ )
{
	// �������⣡��2014.2.20


	CHgzListCtrl *pListCtrlRegs = new CHgzListCtrl();
	ASSERT_VALID(pListCtrlRegs);
	pListCtrlRegs->Create(LVS_REPORT, rect, pParentWnd, nID);
	/*pListCtrlRegs->ModifyStyle(0, LVS_REPORT);
	pListCtrlRegs->MoveWindow(&rect);*/
	pListCtrlRegs->SetExtendedStyle(nExStyle);
	pListCtrlRegs->ModifyStyleEx(0, WS_EX_CLIENTEDGE, SWP_DRAWFRAME); // display border

	pListCtrlRegs->InsertColumn(0, _T("RegName"), 0, 120);
	pListCtrlRegs->InsertColumn(1, _T("RegValue"), 0, 280);

	CString s;
	pListCtrlRegs->SetItemCount(nRow);
	for (int i = 0; i < nRow; i++) {
		s.Format(_T("Reg%d"), i);
		pListCtrlRegs->InsertItem(i, s);
	}

	return pListCtrlRegs;
}


