// HgzListCtrl.cpp : 实现文件
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

// CItemEdit 消息处理程序
BOOL CItemEdit::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	// 拦截ESC键和RETURN键按下的消息，解释为WM_KILLFOCUS消息，这里也可以根据需要设置其它键作为输入结束或取消输入的标志
	if( pMsg->message == WM_KEYDOWN )
	{
		if( pMsg->wParam == VK_RETURN ) {       //回车键
			m_bEndEdit = TRUE;
			pMsg->message = WM_KILLFOCUS;
		}
		else if( pMsg->wParam == VK_ESCAPE ) {   //ESC键
			m_bEndEdit = TRUE;
			m_bInputValid = FALSE;    //此时的编辑结果无效
			pMsg->message = WM_KILLFOCUS;
		}
	}

	return CEdit::PreTranslateMessage(pMsg);
}

void CItemEdit::OnKillFocus(CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
	if( m_bEndEdit ) {
		// 得到父窗口，并通知父窗口结束编辑过程
		CHgzListCtrl *parent = (CHgzListCtrl *)GetParent();
		if( parent ) parent->EndEdit( m_bInputValid );
		m_bInputValid = TRUE;
	}
}

void CItemEdit::OnEnChange()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CEdit::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	// 得到父窗口，并通知父窗口结束编辑过程
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

// CHgzListCtrl 消息处理程序
void CHgzListCtrl::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	BOOL bSelected = FALSE;

	// 得到被点击的Item
	LVHITTESTINFO testinfo;
	testinfo.pt = point;                  //点击时的鼠标位置
	//testinfo.flags = LVHT_ONITEM;    //点击的必须不是标题
	if( SubItemHitTest(&testinfo)<0 )
		goto defalt_session;            //没有点在有效区域，不进入编辑
		
	// 检查是否有Item正被编辑
	if (m_bEditing == TRUE) { 
		if (m_nItem == testinfo.iItem && m_nSubItem == testinfo.iSubItem)
			goto defalt_session;
		else
			EndEdit(TRUE);
	}
	
	int m = m_nItem;
	int n = m_nSubItem;
	m_nItem = testinfo.iItem;            //被点击表项的行号
	m_nSubItem = testinfo.iSubItem;    //被点击表项的列号

	Update(m);

	if(m_nSubItem == 0) {
		bSelected = IsItemSelected(m_nItem) && GetSelectedCount() == 1;
		goto defalt_session;            //点中第一列，不编辑
	}

	// 开始编辑
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

	// TODO: 在此处添加消息处理程序代码
	m_edit.m_bEndEdit = TRUE;
}

BOOL CHgzListCtrl::BeginEdit(void)
{
	// 得到被编辑表项的区域
	CRect rect;
	if( GetSubItemRect(m_nItem, m_nSubItem, LVIR_LABEL, rect)==FALSE )
		return FALSE;

	// 创建编辑控件
 	if (!m_edit.GetSafeHwnd()) {
		if( m_edit.Create(WS_CHILD | WS_CLIPSIBLINGS | WS_BORDER, rect, this, ID_MYEDIT)==FALSE )
			return FALSE;
	}
	else
		m_edit.MoveWindow(&rect);

	// 取被编辑表项的文字
	CString txtItem = GetItemText( m_nItem, m_nSubItem );

	// 取出的文字填写到编辑控件
	m_edit.SetWindowText( txtItem );
	m_edit.SetFocus();
	m_edit.SetSel( 0, -1 );
	m_edit.ShowWindow( SW_SHOW );

	return TRUE;
}

void CHgzListCtrl::EndEdit(BOOL bValidate)
{
	if (m_edit.GetSafeHwnd() == NULL) return;
	// 编辑结果是有效的，重设被编辑表项的文字
	if( bValidate )
	{
		CString txtItem;
		m_edit.GetWindowText( txtItem );
		SetItemText(m_nItem, m_nSubItem, txtItem);
		GetParent()->SendMessage(WM_LVM_ITEMCHANGED, m_nItem, m_nSubItem);
	}

	// 销毁编辑窗口
	m_edit.DestroyWindow();
	m_bEditing = FALSE;
	m_edit.m_TempStr.Empty();
}

void CHgzListCtrl::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CListCtrl::OnVScroll(nSBCode, nPos, pScrollBar);

	HoldOnEditing();
}

BOOL CHgzListCtrl::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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
	// TODO: 在此添加专用代码和/或调用基类

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
	// TODO: 在此添加消息处理程序代码和/或调用默认值

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

	// TODO: 在此添加控件通知处理程序代码
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
		else if (IsItemSelected(nItem)) // 如果当前要刷新的项为选择项，则将文字设为白色，背景色设为蓝色
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
	// 还在问题！！2014.2.20


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


