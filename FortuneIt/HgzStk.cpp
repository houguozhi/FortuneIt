// HgzStk.h : CHgzStk 类的实现



// CHgzStk 实现

// 代码生成在 2015年12月5日, 12:03

#include "stdafx.h"
#include "HgzStk.h"

extern void println(TCHAR *szFormat, ...);

IMPLEMENT_DYNAMIC(CHgzStk, CRecordset)

CHgzStk::CHgzStk(CDatabase* pdb)
	: CRecordset(pdb)
	, m_StkLable(_T(""))
	, m_StkName(_T(""))
	, m_StkData()
{
	//m_StkLable = _T("");
	//m_StkName = _T("");
	//m_StkData = CStkData();
	m_nFields = 10;// 19;
	m_nDefaultType = snapshot;
	m_nParams = 0;// 3;

	/*m_strFilter = _T("StkLable = ? AND StkTime BETWEEN ? AND ?");
	//m_strSort = _T("");*/
	m_Table = _T("[dbo].[StkDay_2009_2010]");
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CHgzStk::GetDefaultConnect()
{
	return _T("DSN=hgzStk64;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=DESKTOP-863BSVD;DATABASE=hgzStkDB");
}

CString CHgzStk::GetDefaultSQL()
{
	return m_Table;
}

void CHgzStk::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX,   _T("[StkLable]"),        m_StkLable);
	RFX_Text(pFX,   _T("[StkName]"),         m_StkName);
	RFX_Date(pFX, _T("[StkTime]"),			m_StkData.time);
	RFX_Double(pFX, _T("[StkOpen]"),		m_StkData.open);
	RFX_Double(pFX, _T("[StkHigh]"),		m_StkData.high);
	RFX_Double(pFX, _T("[StkLow]"),			m_StkData.low);
	RFX_Double(pFX, _T("[StkClose]"),		m_StkData.close);
	RFX_Double(pFX, _T("[StkVolume]"),		m_StkData.volume);
	RFX_Double(pFX, _T("[StkAmount]"),		m_StkData.amount);
	RFX_Double(pFX, _T("[StkTurnoverRate]"), m_StkData.tor);

	/*pFX->SetFieldType(CFieldExchange::param);
	// RFX calls for parameter data members
	RFX_Text(pFX, _T("Param"), m_StkLableParam);
	//RFX_Text(pFX, _T("Param"), m_StkNameParam);
	RFX_Date(pFX, _T("Param"), m_StkTimeStartParam);
	RFX_Date(pFX, _T("Param"), m_StkTimeEndParam);*/


}
/////////////////////////////////////////////////////////////////////////////
// CHgzStk 诊断

#ifdef _DEBUG
void CHgzStk::AssertValid() const
{
	CRecordset::AssertValid();
}

void CHgzStk::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG

CString& CHgzStk::GetFieldName(int nIndex, CString& strFieldName)
{
		CODBCFieldInfo fieldinfo;
		GetODBCFieldInfo(nIndex, fieldinfo);
		strFieldName = fieldinfo.m_strName;
		return strFieldName;
}

CString CHgzStk::SetDefaultSQL(CString &table)
{
	CString old(m_Table); 
	m_Table = table; 
	return old;
}


int CHgzStk::Fetch(int num /*= -1*/)
{
//#error
	return 0;
}


#define SQL_CLAUSE(lable, time, table) CString(_T("SELECT [StkLable], [StkName], [StkTime], [StkOpen], [StkHigh], [StkLow], [StkClose], [StkVolume], [StkAmount], [StkTurnoverRate]")) + CString(_T(" FROM ")) + table + CString(_T(" WHERE StkLable = '")) + lable + CString(_T("' AND StkTime BETWEEN ")) + time.start.Format(_T("'%Y-%m-%d %H:%M:%S'")) + CString(_T(" AND ")) + time.end.Format(_T("'%Y-%m-%d %H:%M:%S'"))
#define SQL_CLAUSEX(lable, start, end, table) CString(_T("SELECT [StkLable], [StkName], [StkTime], [StkOpen], [StkHigh], [StkLow], [StkClose], [StkVolume], [StkAmount], [StkTurnoverRate]")) + CString(_T(" FROM ")) + table + CString(_T(" WHERE StkLable = '")) + lable + CString(_T("' AND StkTime BETWEEN ")) + start.Format(_T("'%Y-%m-%d %H:%M:%S'")) + CString(_T(" AND ")) + end.Format(_T("'%Y-%m-%d %H:%M:%S'"))
bool CHgzStk::BuildSQL(CString &sql, const CString &lable, const CTimePair &time, const STKCYCLE cycle /*= DAY*/)
{
	/*TCHAR sql1[] = _T("SELECT \
			  [CreateDate]\
			, [RecordCreator]\
			, [RecordVersion]\
			, [MarketLable]\
			, [SecurityType]\
			, [StkLable]\
			, [StkName]\
			, [StkTime]\
			, [StkOpen]\
			, [StkHigh]\
			, [StkLow]\
			, [StkClose]\
			, [StkVolume]\
			, [StkAmount]\
			, [StkTurnoverRate]\
			, [Reserved1]\
			, [Reserved2]\
			, [Reserved3]\
			, [Reserved4]\
			FROM[hgzStkDB].[dbo].[StkDay_2009_2010]\
			WHERE StkLable = 'SZ000001'");

	TCHAR sql2[] = _T("SELECT \
			  [StkLable]\
			, [StkName]\
			, [StkTime]\
			, [StkOpen]\
			, [StkHigh]\
			, [StkLow]\
			, [StkClose]\
			, [StkVolume]\
			, [StkAmount]\
			, [StkTurnoverRate]\
			FROM[hgzStkDB].[dbo].[StkDay_2009_2010]\
			WHERE StkLable = 'SZ000001'");*/

	CString comma(_T(", "));
	// DAY 
	CString table_StkDay_1990_2000(_T("StkDay_1990_2000"));
	CString table_StkDay_2001_2005(_T("StkDay_2001_2005"));
	CString table_StkDay_2006_2008(_T("StkDay_2006_2008"));
	CString table_StkDay_2009_2010(_T("StkDay_2009_2010"));
	CString table_StkDay_2011_2012(_T("StkDay_2011_2012"));
	CString table_StkDay_HalfDay(_T("StkDay_HalfDay"));
	CString table_StkDay = table_StkDay_1990_2000 + comma + table_StkDay_2001_2005 + comma + table_StkDay_2006_2008 + comma + table_StkDay_2009_2010 + comma + table_StkDay_2011_2012 + comma + table_StkDay_HalfDay;

	// MIN5 
	CString table_StkM5_200312(_T("StkM5_200312"));
	CString table_StkM5_2003 = table_StkM5_200312;

	CString table_StkM5_200401u02(_T("StkM5_200401u02"));
	CString table_StkM5_200403u04(_T("StkM5_200403u04"));
	CString table_StkM5_200405u06(_T("StkM5_200405u06"));
	CString table_StkM5_200407u08(_T("StkM5_200407u08"));
	CString table_StkM5_200409u10(_T("StkM5_200409u10"));
	CString table_StkM5_200411u12(_T("StkM5_200411u12"));
	CString table_StkM5_2004 = table_StkM5_200401u02 + comma + table_StkM5_200403u04 + comma + table_StkM5_200405u06 + comma + table_StkM5_200407u08 + comma + table_StkM5_200409u10 + comma + table_StkM5_200411u12;

	CString table_StkM5_200501u02(_T("StkM5_200501u02"));
	CString table_StkM5_200503u04(_T("StkM5_200503u04"));
	CString table_StkM5_200505u06(_T("StkM5_200505u06"));
	CString table_StkM5_200507u08(_T("StkM5_200507u08"));
	CString table_StkM5_200509u10(_T("StkM5_200509u10"));
	CString table_StkM5_200511u12(_T("StkM5_200511u12"));
	CString table_StkM5_2005 = table_StkM5_200501u02 + comma + table_StkM5_200503u04 + comma + table_StkM5_200505u06 + comma + table_StkM5_200507u08 + comma + table_StkM5_200509u10 + comma + table_StkM5_200511u12;

	CString table_StkM5_200601u02(_T("StkM5_200601u02"));
	CString table_StkM5_200603u04(_T("StkM5_200603u04"));
	CString table_StkM5_200605u06(_T("StkM5_200605u06"));
	CString table_StkM5_200607u08(_T("StkM5_200607u08"));
	CString table_StkM5_200609u10(_T("StkM5_200609u10"));
	CString table_StkM5_200611u12(_T("StkM5_200611u12"));
	CString table_StkM5_2006 = table_StkM5_200601u02 + comma + table_StkM5_200603u04 + comma + table_StkM5_200605u06 + comma + table_StkM5_200607u08 + comma + table_StkM5_200609u10 + comma + table_StkM5_200611u12;

	CString table_StkM5_200701u02(_T("StkM5_200701u02"));
	CString table_StkM5_200703u04(_T("StkM5_200703u04"));
	CString table_StkM5_200705u06(_T("StkM5_200705u06"));
	CString table_StkM5_200707u08(_T("StkM5_200707u08"));
	CString table_StkM5_200709u10(_T("StkM5_200709u10"));
	CString table_StkM5_200711u12(_T("StkM5_200711u12"));
	CString table_StkM5_2007 = table_StkM5_200701u02 + comma + table_StkM5_200703u04 + comma + table_StkM5_200705u06 + comma + table_StkM5_200707u08 + comma + table_StkM5_200709u10 + comma + table_StkM5_200711u12;

	CString table_StkM5_200801u02(_T("StkM5_200801u02"));
	CString table_StkM5_200803u04(_T("StkM5_200803u04"));
	CString table_StkM5_200805u06(_T("StkM5_200805u06"));
	CString table_StkM5_200807u08(_T("StkM5_200807u08"));
	CString table_StkM5_200809u10(_T("StkM5_200809u10"));
	CString table_StkM5_200811u12(_T("StkM5_200811u12"));
	CString table_StkM5_2008 = table_StkM5_200801u02 + comma + table_StkM5_200803u04 + comma + table_StkM5_200805u06 + comma + table_StkM5_200807u08 + comma + table_StkM5_200809u10 + comma + table_StkM5_200811u12;

	CString table_StkM5_200901(_T("StkM5_200901"));
	CString table_StkM5_200902(_T("StkM5_200902"));
	CString table_StkM5_200903(_T("StkM5_200903"));
	CString table_StkM5_200904(_T("StkM5_200904"));
	CString table_StkM5_200905(_T("StkM5_200905"));
	CString table_StkM5_200906(_T("StkM5_200906"));
	CString table_StkM5_200907(_T("StkM5_200907"));
	CString table_StkM5_200908(_T("StkM5_200908"));
	CString table_StkM5_200909(_T("StkM5_200909"));
	CString table_StkM5_200910(_T("StkM5_200910"));
	CString table_StkM5_200911(_T("StkM5_200911"));
	CString table_StkM5_200912(_T("StkM5_200912"));
	CString table_StkM5_2009 = table_StkM5_200901 + comma + table_StkM5_200902 + comma + table_StkM5_200903 + comma + table_StkM5_200904 + comma + table_StkM5_200905 + comma + table_StkM5_200906 + comma + table_StkM5_200907 + comma + table_StkM5_200908 + comma + table_StkM5_200909 + comma + table_StkM5_200910 + comma + table_StkM5_200911 + comma + table_StkM5_200912;

	CString table_StkM5_201001(_T("StkM5_201001"));
	CString table_StkM5_201002(_T("StkM5_201002"));
	CString table_StkM5_201003(_T("StkM5_201003"));
	CString table_StkM5_201004(_T("StkM5_201004"));
	CString table_StkM5_201005(_T("StkM5_201005"));
	CString table_StkM5_201006(_T("StkM5_201006"));
	CString table_StkM5_201007(_T("StkM5_201007"));
	CString table_StkM5_201008(_T("StkM5_201008"));
	CString table_StkM5_201009(_T("StkM5_201009"));
	CString table_StkM5_201010(_T("StkM5_201010"));
	CString table_StkM5_201011(_T("StkM5_201011"));
	CString table_StkM5_201012(_T("StkM5_201012"));
	CString table_StkM5_2010 = table_StkM5_201001 + comma + table_StkM5_201002 + comma + table_StkM5_201003 + comma + table_StkM5_201004 + comma + table_StkM5_201005 + comma + table_StkM5_201006 + comma + table_StkM5_201007 + comma + table_StkM5_201008 + comma + table_StkM5_201009 + comma + table_StkM5_201010 + comma + table_StkM5_201011 + comma + table_StkM5_201012;

	CString table_StkM5_201101(_T("StkM5_201101"));
	CString table_StkM5_201102(_T("StkM5_201102"));
	CString table_StkM5_201103(_T("StkM5_201103"));
	CString table_StkM5_201104(_T("StkM5_201104"));
	CString table_StkM5_201105(_T("StkM5_201105"));
	CString table_StkM5_201106(_T("StkM5_201106"));
	CString table_StkM5_201107(_T("StkM5_201107"));
	CString table_StkM5_201108(_T("StkM5_201108"));
	CString table_StkM5_201109(_T("StkM5_201109"));
	CString table_StkM5_201110(_T("StkM5_201110"));
	CString table_StkM5_201111(_T("StkM5_201111"));
	CString table_StkM5_201112(_T("StkM5_201112"));
	CString table_StkM5_2011 = table_StkM5_201101 + comma + table_StkM5_201102 + comma + table_StkM5_201103 + comma + table_StkM5_201104 + comma + table_StkM5_201105 + comma + table_StkM5_201106 + comma + table_StkM5_201107 + comma + table_StkM5_201108 + comma + table_StkM5_201109 + comma + table_StkM5_201110 + comma + table_StkM5_201111 + comma + table_StkM5_201112;

	CString table_StkM5_201201(_T("StkM5_201201"));
	CString table_StkM5_201202(_T("StkM5_201202"));
	CString table_StkM5_201203(_T("StkM5_201203"));
	CString table_StkM5_201204(_T("StkM5_201204"));
	CString table_StkM5_201205(_T("StkM5_201205"));
	CString table_StkM5_201206(_T("StkM5_201206"));
	CString table_StkM5_201207(_T("StkM5_201207"));
	CString table_StkM5_201208(_T("StkM5_201208"));
	CString table_StkM5_201209(_T("StkM5_201209"));
	CString table_StkM5_201210(_T("StkM5_201210"));
	CString table_StkM5_201211(_T("StkM5_201211"));
	CString table_StkM5_201212(_T("StkM5_201212"));
	CString table_StkM5_2012 = table_StkM5_201201 + comma + table_StkM5_201202 + comma + table_StkM5_201203 + comma + table_StkM5_201204 + comma + table_StkM5_201205 + comma + table_StkM5_201206 + comma + table_StkM5_201207 + comma + table_StkM5_201208 + comma + table_StkM5_201209 + comma + table_StkM5_201210 + comma + table_StkM5_201211 + comma + table_StkM5_201212;

	CString table_StkM5_HalfDay(_T("StkM5_HalfDay"));
	CString table_StkM5 = table_StkM5_2003 + comma + table_StkM5_2004 + comma + table_StkM5_2005 + comma + table_StkM5_2006 + comma + table_StkM5_2007 + comma + table_StkM5_2008 + comma + table_StkM5_2009 + comma + table_StkM5_2010 + comma + table_StkM5_2011 + comma + table_StkM5_2012 + comma + table_StkM5_HalfDay;


	sql.Empty();
	//sql = _T("SELECT * FROM (");
	switch (cycle)
	{
	case STKCYCLE::DAY:
	case STKCYCLE::WEEK:
	case STKCYCLE::MONTH:
	case STKCYCLE::SEASON:
	case STKCYCLE::YEAR:
	case STKCYCLE::MULTIDAY:
	default:
	{
		/*sql =                 SQL_CLAUSE(lable, time, table_StkDay_1990_2000)
				+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_2001_2005)
				+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_2006_2008)
				+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_2009_2010)
				+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_2011_2012)
				+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_HalfDay);*/

		if      (time.start < COleDateTime(2001, 01, 01, 00, 00, 00)) sql += SQL_CLAUSE(lable, time, table_StkDay_1990_2000);
		else if (time.start < COleDateTime(2006, 01, 01, 00, 00, 00)) sql += SQL_CLAUSE(lable, time, table_StkDay_2001_2005);
		else if (time.start < COleDateTime(2009, 01, 01, 00, 00, 00)) sql += SQL_CLAUSE(lable, time, table_StkDay_2006_2008);
		else if (time.start < COleDateTime(2011, 01, 01, 00, 00, 00)) sql += SQL_CLAUSE(lable, time, table_StkDay_2009_2010);
		else if (time.start < COleDateTime(2013, 01, 01, 00, 00, 00)) sql += SQL_CLAUSE(lable, time, table_StkDay_2011_2012);
		else                                                   sql += SQL_CLAUSE(lable, time, table_StkDay_HalfDay);

		if (time.end >= COleDateTime(2001, 01, 01, 00, 00, 00)) { if (time.start < COleDateTime(2001, 01, 01, 00, 00, 00)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_2001_2005); } else break;
		if (time.end >= COleDateTime(2006, 01, 01, 00, 00, 00)) { if (time.start < COleDateTime(2006, 01, 01, 00, 00, 00)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_2006_2008); } else break;
		if (time.end >= COleDateTime(2009, 01, 01, 00, 00, 00)) { if (time.start < COleDateTime(2009, 01, 01, 00, 00, 00)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_2009_2010); } else break;
		if (time.end >= COleDateTime(2011, 01, 01, 00, 00, 00)) { if (time.start < COleDateTime(2011, 01, 01, 00, 00, 00)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_2011_2012); } else break;
		if (time.end >= COleDateTime(2013, 01, 01, 00, 00, 00)) { if (time.start < COleDateTime(2013, 01, 01, 00, 00, 00)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkDay_HalfDay); } else break;

		break;
	}
	case STKCYCLE::MIN5:
	case STKCYCLE::MIN15:
	case STKCYCLE::MIN30:
	case STKCYCLE::MIN60:
	case STKCYCLE::HalfDay:
	{
		/*sql =                 SQL_CLAUSE(lable, time, table_StkM5_200312)
		    + _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200401u02)
		    + _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200403u04)
		    + _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200405u06)
		    + _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200407u08)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200409u10)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200411u12)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200501u02)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200503u04)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200505u06)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200507u08)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200509u10)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200511u12)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200601u02)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200603u04)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200605u06)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200607u08)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200609u10)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200611u12)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200701u02)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200703u04)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200705u06)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200707u08)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200709u10)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200711u12)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200801u02)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200803u04)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200805u06)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200807u08)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200809u10)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200811u12)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200901)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200902)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200903)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200904)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200905)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200906)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200907)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200908)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200909)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200910)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200911)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200912)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201001)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201002)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201003)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201004)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201005)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201006)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201007)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201008)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201009)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201010)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201011)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201012)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201101)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201102)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201103)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201104)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201105)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201106)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201107)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201108)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201109)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201110)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201111)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201112)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201201)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201202)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201203)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201204)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201205)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201206)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201207)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201208)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201209)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201210)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201211)
			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201212)

			+ _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_HalfDay);*/


		if      (time.start < COleDateTime(2004,  1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200312);

		else if (time.start < COleDateTime(2004, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200401u02);
		else if (time.start < COleDateTime(2004, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200403u04);
		else if (time.start < COleDateTime(2004, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200405u06);
		else if (time.start < COleDateTime(2004, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200407u08);
		else if (time.start < COleDateTime(2004, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_200409u10);
		else if (time.start < COleDateTime(2005, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200411u12);

		else if (time.start < COleDateTime(2005, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200501u02);
		else if (time.start < COleDateTime(2005, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200503u04);
		else if (time.start < COleDateTime(2005, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200505u06);
		else if (time.start < COleDateTime(2005, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200507u08);
		else if (time.start < COleDateTime(2005, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_200509u10);
		else if (time.start < COleDateTime(2006, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200511u12);

		else if (time.start < COleDateTime(2006, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200601u02);
		else if (time.start < COleDateTime(2006, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200603u04);
		else if (time.start < COleDateTime(2006, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200605u06);
		else if (time.start < COleDateTime(2006, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200607u08);
		else if (time.start < COleDateTime(2006, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_200609u10);
		else if (time.start < COleDateTime(2007, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200611u12);

		else if (time.start < COleDateTime(2007, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200701u02);
		else if (time.start < COleDateTime(2007, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200703u04);
		else if (time.start < COleDateTime(2007, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200705u06);
		else if (time.start < COleDateTime(2007, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200707u08);
		else if (time.start < COleDateTime(2007, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_200709u10);
		else if (time.start < COleDateTime(2008, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200711u12);

		else if (time.start < COleDateTime(2008, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200801u02);
		else if (time.start < COleDateTime(2008, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200803u04);
		else if (time.start < COleDateTime(2008, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200805u06);
		else if (time.start < COleDateTime(2008, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200807u08);
		else if (time.start < COleDateTime(2008, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_200809u10);
		else if (time.start < COleDateTime(2009, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200811u12);

		else if (time.start < COleDateTime(2009, 2, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200901);
		else if (time.start < COleDateTime(2009, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200902);
		else if (time.start < COleDateTime(2009, 4, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200903);
		else if (time.start < COleDateTime(2009, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200904);
		else if (time.start < COleDateTime(2009, 6, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200905);
		else if (time.start < COleDateTime(2009, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200906);
		else if (time.start < COleDateTime(2009, 8, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200907);
		else if (time.start < COleDateTime(2009, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200908);
		else if (time.start < COleDateTime(2009, 10, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_200909);
		else if (time.start < COleDateTime(2009, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_200910);
		else if (time.start < COleDateTime(2009, 12, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_200911);
		else if (time.start < COleDateTime(2010, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_200912);

		else if (time.start < COleDateTime(2010, 2, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201001);
		else if (time.start < COleDateTime(2010, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201002);
		else if (time.start < COleDateTime(2010, 4, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201003);
		else if (time.start < COleDateTime(2010, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201004);
		else if (time.start < COleDateTime(2010, 6, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201005);
		else if (time.start < COleDateTime(2010, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201006);
		else if (time.start < COleDateTime(2010, 8, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201007);
		else if (time.start < COleDateTime(2010, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201008);
		else if (time.start < COleDateTime(2010, 10, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201009);
		else if (time.start < COleDateTime(2010, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201010);
		else if (time.start < COleDateTime(2010, 12, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201011);
		else if (time.start < COleDateTime(2011, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201012);

		else if (time.start < COleDateTime(2011, 2, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201101);
		else if (time.start < COleDateTime(2011, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201102);
		else if (time.start < COleDateTime(2011, 4, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201103);
		else if (time.start < COleDateTime(2011, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201104);
		else if (time.start < COleDateTime(2011, 6, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201105);
		else if (time.start < COleDateTime(2011, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201106);
		else if (time.start < COleDateTime(2011, 8, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201107);
		else if (time.start < COleDateTime(2011, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201108);
		else if (time.start < COleDateTime(2011, 10, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201109);
		else if (time.start < COleDateTime(2011, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201110);
		else if (time.start < COleDateTime(2011, 12, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201111);
		else if (time.start < COleDateTime(2012, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201112);

		else if (time.start < COleDateTime(2012, 2, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201201);
		else if (time.start < COleDateTime(2012, 3, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201202);
		else if (time.start < COleDateTime(2012, 4, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201203);
		else if (time.start < COleDateTime(2012, 5, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201204);
		else if (time.start < COleDateTime(2012, 6, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201205);
		else if (time.start < COleDateTime(2012, 7, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201206);
		else if (time.start < COleDateTime(2012, 8, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201207);
		else if (time.start < COleDateTime(2012, 9, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201208);
		else if (time.start < COleDateTime(2012, 10, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201209);
		else if (time.start < COleDateTime(2012, 11, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201210);
		else if (time.start < COleDateTime(2012, 12, 1, 0, 0, 0))sql = SQL_CLAUSE(lable, time, table_StkM5_201211);
		else if (time.start < COleDateTime(2013, 1, 1, 0, 0, 0)) sql = SQL_CLAUSE(lable, time, table_StkM5_201212);

		else                                              sql = SQL_CLAUSE(lable, time, table_StkM5_HalfDay);


		if (time.end >= COleDateTime(2004, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2004, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200401u02); }	else break;
		if (time.end >= COleDateTime(2004, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2004, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200403u04); } else break;
		if (time.end >= COleDateTime(2004, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2004, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200405u06); } else break;
		if (time.end >= COleDateTime(2004, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2004, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200407u08); } else break;
		if (time.end >= COleDateTime(2004, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2004, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200409u10); } else break;
		if (time.end >= COleDateTime(2004, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2004, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200411u12); } else break;
		
		if (time.end >= COleDateTime(2005, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2005, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200501u02); } else break;
		if (time.end >= COleDateTime(2005, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2005, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200503u04); } else break;
		if (time.end >= COleDateTime(2005, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2005, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200505u06); } else break;
		if (time.end >= COleDateTime(2005, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2005, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200507u08); } else break;
		if (time.end >= COleDateTime(2005, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2005, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200509u10); } else break;
		if (time.end >= COleDateTime(2005, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2005, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200511u12); } else break;

		if (time.end >= COleDateTime(2006, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2006, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200601u02); } else break;
		if (time.end >= COleDateTime(2006, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2006, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200603u04); } else break;
		if (time.end >= COleDateTime(2006, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2006, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200605u06); } else break;
		if (time.end >= COleDateTime(2006, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2006, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200607u08); } else break;
		if (time.end >= COleDateTime(2006, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2006, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200609u10); } else break;
		if (time.end >= COleDateTime(2006, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2006, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200611u12); } else break;

		if (time.end >= COleDateTime(2007, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2007, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200701u02); } else break;
		if (time.end >= COleDateTime(2007, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2007, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200703u04); } else break;
		if (time.end >= COleDateTime(2007, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2007, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200705u06); } else break;
		if (time.end >= COleDateTime(2007, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2007, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200707u08); } else break;
		if (time.end >= COleDateTime(2007, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2007, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200709u10); } else break;
		if (time.end >= COleDateTime(2007, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2007, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200711u12); } else break;

		if (time.end >= COleDateTime(2008, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2008, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200801u02); } else break;
		if (time.end >= COleDateTime(2008, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2008, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200803u04); } else break;
		if (time.end >= COleDateTime(2008, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2008, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200805u06); } else break;
		if (time.end >= COleDateTime(2008, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2008, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200807u08); } else break;
		if (time.end >= COleDateTime(2008, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2008, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200809u10); } else break;
		if (time.end >= COleDateTime(2008, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2008, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200811u12); } else break;

		if (time.end >= COleDateTime(2009, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200901); } else break;
		if (time.end >= COleDateTime(2009, 2, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 2, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200902); } else break;
		if (time.end >= COleDateTime(2009, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200903); } else break;
		if (time.end >= COleDateTime(2009, 4, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 4, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200904); } else break;
		if (time.end >= COleDateTime(2009, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200905); } else break;
		if (time.end >= COleDateTime(2009, 6, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 6, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200906); } else break;
		if (time.end >= COleDateTime(2009, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200907); } else break;
		if (time.end >= COleDateTime(2009, 8, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 8, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200908); } else break;
		if (time.end >= COleDateTime(2009, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200909); } else break;
		if (time.end >= COleDateTime(2009, 10, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 10, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200910); } else break;
		if (time.end >= COleDateTime(2009, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200911); } else break;
		if (time.end >= COleDateTime(2009, 12, 1, 0, 0, 0)) { if (time.start < COleDateTime(2009, 12, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_200912); } else break;

		if (time.end >= COleDateTime(2010, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201001); } else break;
		if (time.end >= COleDateTime(2010, 2, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 2, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201002); } else break;
		if (time.end >= COleDateTime(2010, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201003); } else break;
		if (time.end >= COleDateTime(2010, 4, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 4, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201004); } else break;
		if (time.end >= COleDateTime(2010, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201005); } else break;
		if (time.end >= COleDateTime(2010, 6, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 6, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201006); } else break;
		if (time.end >= COleDateTime(2010, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201007); } else break;
		if (time.end >= COleDateTime(2010, 8, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 8, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201008); } else break;
		if (time.end >= COleDateTime(2010, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201009); } else break;
		if (time.end >= COleDateTime(2010, 10, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 10, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201010); } else break;
		if (time.end >= COleDateTime(2010, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201011); } else break;
		if (time.end >= COleDateTime(2010, 12, 1, 0, 0, 0)) { if (time.start < COleDateTime(2010, 12, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201012); } else break;

		if (time.end >= COleDateTime(2011, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201101); } else break;
		if (time.end >= COleDateTime(2011, 2, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 2, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201102); } else break;
		if (time.end >= COleDateTime(2011, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201103); } else break;
		if (time.end >= COleDateTime(2011, 4, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 4, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201104); } else break;
		if (time.end >= COleDateTime(2011, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201105); } else break;
		if (time.end >= COleDateTime(2011, 6, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 6, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201106); } else break;
		if (time.end >= COleDateTime(2011, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201107); } else break;
		if (time.end >= COleDateTime(2011, 8, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 8, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201108); } else break;
		if (time.end >= COleDateTime(2011, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201109); } else break;
		if (time.end >= COleDateTime(2011, 10, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 10, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201110); } else break;
		if (time.end >= COleDateTime(2011, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201111); } else break;
		if (time.end >= COleDateTime(2011, 12, 1, 0, 0, 0)) { if (time.start < COleDateTime(2011, 12, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201112); } else break;

		if (time.end >= COleDateTime(2012, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 1, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201201); } else break;
		if (time.end >= COleDateTime(2012, 2, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 2, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201202); } else break;
		if (time.end >= COleDateTime(2012, 3, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 3, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201203); } else break;
		if (time.end >= COleDateTime(2012, 4, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 4, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201204); } else break;
		if (time.end >= COleDateTime(2012, 5, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 5, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201205); } else break;
		if (time.end >= COleDateTime(2012, 6, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 6, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201206); } else break;
		if (time.end >= COleDateTime(2012, 7, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 7, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201207); } else break;
		if (time.end >= COleDateTime(2012, 8, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 8, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201208); } else break;
		if (time.end >= COleDateTime(2012, 9, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 9, 1, 0, 0, 0)) sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201209); } else break;
		if (time.end >= COleDateTime(2012, 10, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 10, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201210); } else break;
		if (time.end >= COleDateTime(2012, 11, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 11, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201211); } else break;
		if (time.end >= COleDateTime(2012, 12, 1, 0, 0, 0)) { if (time.start < COleDateTime(2012, 12, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_201212); } else break;
		
		if (time.end >= COleDateTime(2013, 1, 1, 0, 0, 0)) { if (time.start < COleDateTime(2013, 1, 1, 0, 0, 0))sql += _T(" UNION ALL ") + SQL_CLAUSE(lable, time, table_StkM5_HalfDay); } else break;


		break;
	}
	
	}

	//sql += _T(") ORDER BY StkTime");
	//m_strSort = _T("StkTime");

	return true;
}

BOOL CHgzStk::Open(const CString &lable, const CTimePair &time, const STKCYCLE cycle /*= DAY*/)
{
	CString sql;
	BuildSQL(sql, lable, time, cycle);
	return CRecordset::Open(AFX_DB_USE_DEFAULT_TYPE, sql, none);	
}

void CHgzStk::print(int num /*= -1*/)
{
	if (IsEmpty())
		return;
	
	// print title
	println(_T("\n-------------------------------------------------------------------------------------------"));
	println(_T("[Lable]\t      [Name]\t      [Time]\t                            [Open]\t [High]\t [Low]\t [Close]\t [Volume]\t [Amount]\t [TurnoverRate]"));
	// print data
	int cnt = 0;
	MoveFirst();
	for (cnt = 0; (num == -1 ? true : (cnt < num)) && !IsEOF(); )
	{
		cnt++;
		println(_T("%s %s %s"), m_StkLable, m_StkName, m_StkData.ToString());
		MoveNext();
	}
	println(_T("\n-------------------------------------------------------------------------------------------"));
	println(_T("Total count: %d"), cnt);

}


