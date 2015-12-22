#pragma once
#include "atltypes.h"


#define WM_LVM_ITEMCHANGED (WM_USER + 1)

// CItemEdit

class CItemEdit : public CEdit
{
	DECLARE_DYNAMIC(CItemEdit)

public:
	CItemEdit();
	virtual ~CItemEdit();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	bool m_bInputValid;
public:
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	// 用于在暂时失去焦点时保存字符串。
	CString m_TempStr;
	int m_nStartChar;
	int m_nEndChar;
	bool m_bEndEdit;
	bool m_bEditingAndOutOfView;
	afx_msg void OnEnChange();
};

// CHgzListCtrl

class CHgzListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CHgzListCtrl)

public:
	CHgzListCtrl();
	virtual ~CHgzListCtrl();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CItemEdit m_edit;
	bool m_bEditing;
public:
	bool Editing() const { return m_bEditing; }
	void Editing(bool val) { m_bEditing = val; }
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	BOOL BeginEdit(void);
	void EndEdit(BOOL bValidate);
	int m_nItem;
	int m_nSubItem;

	UINT m_nFlags;
	CPoint m_point;
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);

	afx_msg void HoldOnEditing();

	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
protected:
	afx_msg LRESULT OnEnChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);
	bool IsItemSelected( int nItem);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
//	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	CHgzListCtrl * NewHgzListCtrlRegs( CWnd * pParentWnd, int nID, CRect &rect, int nRow = 16, int nCol = 2, unsigned int nExStyle = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES );
	afx_msg void OnKillFocus(CWnd* pNewWnd);
//	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


