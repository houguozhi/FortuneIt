// StkSet.h : CStkSet 类的实现



// CStkSet 实现

// 代码生成在 2015年12月14日, 00:39

#include "stdafx.h"
#include "StkSet.h"
IMPLEMENT_DYNAMIC(CStkSet, CRecordset)

CStkSet::CStkSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nFields = 0;
	m_nDefaultType = snapshot;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CStkSet::GetDefaultConnect()
{
	return _T("DSN=hgzStk32;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2015;WSID=DESKTOP-863BSVD;DATABASE=hgzStkDB");
}

CString CStkSet::GetDefaultSQL()
{
	return _T("");
}

void CStkSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型

}
/////////////////////////////////////////////////////////////////////////////
// CStkSet 诊断

#ifdef _DEBUG
void CStkSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStkSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


