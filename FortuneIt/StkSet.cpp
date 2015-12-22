// StkSet.h : CStkSet ���ʵ��



// CStkSet ʵ��

// ���������� 2015��12��14��, 00:39

#include "stdafx.h"
#include "StkSet.h"
IMPLEMENT_DYNAMIC(CStkSet, CRecordset)

CStkSet::CStkSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nFields = 0;
	m_nDefaultType = snapshot;
}
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������

}
/////////////////////////////////////////////////////////////////////////////
// CStkSet ���

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


