// ftsplit.h : Cftsplit ������

#pragma once
#include "TimePair.h"
#include "stock_core_types.h"

// ���������� 2015��12��23��, 01:48

class Cftsplit : public CRecordset
{
public:
	Cftsplit(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(Cftsplit)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	/*CTime	m_CreateDate;
	CString	m_RecordCreator;
	double	m_RecordVersion;
	CString	m_MarketLable;
	CString	m_SecurityType;*/
	CString	m_StkLable;
	CTime	m_StkTime;
	double	m_Hg;
	double	m_Pg;
	double	m_Pgj;
	double	m_Hl;
	//CString	m_Reserved1;

	// parameters
	CString m_StkLableParam;
	CTimePair m_StkTimeParam;
	


// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


public:
	BOOL Open(const CString &lable, const CTimePair &time);
	BOOL Requery(const CString &lable, const CTimePair &time);
	void print(int num = -1);


};


