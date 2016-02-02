// ftsplit.h : Cftsplit 类的实现



// Cftsplit 实现

// 代码生成在 2015年12月23日, 01:48

#include "stdafx.h"
#include "ftsplit.h"
extern void println(TCHAR *szFormat, ...);

IMPLEMENT_DYNAMIC(Cftsplit, CRecordset)

Cftsplit::Cftsplit(CDatabase* pdb)
	: CRecordset(pdb)
	, m_lable(_T(""))
	, m_SplitData()
{
	//m_lable = _T("");
	//m_SplitData = CSplitData();
	m_nFields = 6;// 12;
	m_nDefaultType = snapshot;
	
	m_StkLableParam = _T("");
	m_StkTimeParam;
	m_nParams = 3;

	m_strFilter = _T("StkLable = ? AND StkTime BETWEEN ? AND ?");
	//m_strSort = _T("");

}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString Cftsplit::GetDefaultConnect()
{
	return _T("DSN=hgzStk64;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=DESKTOP-863BSVD;DATABASE=hgzStkDB");
}

CString Cftsplit::GetDefaultSQL()
{
	return _T("[dbo].[ftsplit]");
}

void Cftsplit::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[StkLable]"), m_lable);
	RFX_Date(pFX, _T("[StkTime]"), m_SplitData.time);
	RFX_Double(pFX, _T("[Hg]"), m_SplitData.hg);
	RFX_Double(pFX, _T("[Pg]"), m_SplitData.pg);
	RFX_Double(pFX, _T("[Pgj]"), m_SplitData.pgj);
	RFX_Double(pFX, _T("[Hl]"), m_SplitData.hl);

	// parameters
	pFX->SetFieldType(CFieldExchange::param);
	// RFX calls for parameter data members
	RFX_Text(pFX, _T("Param"), m_StkLableParam);
	RFX_Date(pFX, _T("Param"), m_StkTimeParam.start);
	RFX_Date(pFX, _T("Param"), m_StkTimeParam.end);

}
/////////////////////////////////////////////////////////////////////////////
// Cftsplit 诊断

#ifdef _DEBUG
void Cftsplit::AssertValid() const
{
	CRecordset::AssertValid();
}

void Cftsplit::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

BOOL Cftsplit::Open(const CString &lable, const CTimePair &time)
{
	m_StkLableParam = lable;
	m_StkTimeParam = time;
	return CRecordset::Open();
}

BOOL Cftsplit::Requery(const CString &lable, const CTimePair &time)
{
	m_StkLableParam = lable;
	m_StkTimeParam = time;
	return CRecordset::Requery();
}

void Cftsplit::print(int num /*= -1*/)
{
	if (IsEmpty())
		return;
	
	// print title
	println(_T("\n-------------------------------------------------------------------------------------------"));
	println(_T("[Lable]\t      [Time]\t                                       [Hg]\t [Pg]\t [Pgj]\t [Hl]"));
	// print data
	int cnt = 0;
	MoveFirst();
	for (cnt = 0; (num == -1 ? true : (cnt < num)) && !IsEOF(); )
	{
		cnt++;
		println(_T("%s %s"), m_lable, m_SplitData.ToString());
		MoveNext();
	}
	println(_T("\n-------------------------------------------------------------------------------------------"));
	println(_T("Total count: %d"), cnt);
}




