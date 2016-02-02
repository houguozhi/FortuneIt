#pragma once
#include "afxdtctl.h"
#include "atltime.h"
#include "TimePair.h"
#include "stock_core_types.h"
#include "FinancialTimeSeries.h"

#include "exsources/HighSpeedChartingControl/ChartCtrl_source/ChartCtrl.h"
#include "exsources/HighSpeedChartingControl/ChartCtrl_source/ChartCtrlHeaders.h"





// CDlgStock �Ի���

class CDlgStock : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgStock)

public:
	CDlgStock(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgStock();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strMarket;
	CString m_strLable;
	STKCYCLE m_Cycle;
	BOOL m_bCumDividendPrice;
	CTimePair m_Time;
	CChartCtrl m_ChartCtrl;
	
	virtual BOOL OnInitDialog();

	void test1();
	
	afx_msg void OnBnClickedButton1();
};
