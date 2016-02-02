// DlgStock.cpp : 实现文件
//

#include "stdafx.h"
#include "FortuneIt.h"
#include "DlgStock.h"
#include "afxdialogex.h"


// CDlgStock 对话框

IMPLEMENT_DYNAMIC(CDlgStock, CDialogEx)

CDlgStock::CDlgStock(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	m_strMarket = _T("SZ");
	m_strLable = _T("000002");
	m_Cycle = STKCYCLE::DAY;
	m_bCumDividendPrice = TRUE;
	m_Time.start = COleDateTime(2004, 5, 19, 0, 0, 0);
	m_Time.end = COleDateTime(2004, 5, 31, 23, 59, 59);
}

CDlgStock::~CDlgStock()
{
}

void CDlgStock::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBString(pDX, IDC_COMBO2, m_strMarket);
	DDX_CBString(pDX, IDC_COMBO1, m_strLable);
	DDX_CBIndex(pDX, IDC_COMBO3, *(int*)&m_Cycle);
	DDX_Check(pDX, IDC_CHECK1, m_bCumDividendPrice);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_Time.start);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER2, m_Time.end);

	DDX_Control(pDX, IDC_CHARTCTRL1, m_ChartCtrl);
}


BEGIN_MESSAGE_MAP(CDlgStock, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgStock::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgStock 消息处理程序


BOOL CDlgStock::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("TICK"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MIN1"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MIN5"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MIN15"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MIN30"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MIN60"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("DAY"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("WEEK"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MONTH"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("SEASON"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("YEAR"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("HalfDay"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MULTISEC"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MULTIMIN"));
	((CComboBox*)GetDlgItem(IDC_COMBO3))->AddString(_T("MULTIDAY"));

	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1))->SetFormat(_T("yyyy-MM-dd HH:mm:ss ddd"));
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER2))->SetFormat(_T("yyyy-MM-dd HH:mm:ss ddd"));
	
	UpdateData(FALSE);



	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CDlgStock::test1()
{
	UpdateData(true);

	CFinancialTimeSeries stk;
	stk.Requery(m_strMarket + m_strLable, m_Time, m_Cycle, m_bCumDividendPrice, 10);

	// Charting
	m_ChartCtrl.EnableRefresh(FALSE);
	m_ChartCtrl.RemoveAllSeries();
	CChartStandardAxis* pBottomAxis = m_ChartCtrl.CreateStandardAxis(CChartCtrl::BottomAxis);
	CChartLogarithmicAxis* pLeftAxis = m_ChartCtrl.CreateLogarithmicAxis(CChartCtrl::LeftAxis);
	pBottomAxis->SetAutomatic(true);
	pBottomAxis->SetMinTickIncrement(1.0);
	pBottomAxis->SetTickLabelOrientationInDegree(45);
	pBottomAxis->SetMarginSize(false, 100);
	pLeftAxis->SetAutomatic(true);

	CChartCandlestickSerie *pCandles = m_ChartCtrl.CreateCandlestickSerie();
	for (auto &var : *stk.Data()) pCandles->AddPoint(var.time, var.open, var.high, var.low, var.close);

	pCandles->SetColor(RGB(0, 155, 100));
	pCandles->EnableShadow(false);
	
	m_ChartCtrl.EnableRefresh(TRUE);
	
	
}


void CDlgStock::OnBnClickedButton1()
{
	test1();
}
