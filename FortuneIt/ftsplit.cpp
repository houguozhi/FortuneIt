// ftsplit.h : Cftsplit ���ʵ��



// Cftsplit ʵ��

// ���������� 2015��12��23��, 01:48

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
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
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
// Cftsplit ���

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




