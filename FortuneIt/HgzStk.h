// HgzStk.h : CHgzStk ������

#pragma once

#include "TimePair.h"
#include "stock_core_types.h"

// ���������� 2015��12��5��, 12:03

class CHgzStk : public CRecordset
{
public:
	CHgzStk(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHgzStk)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	/*CTime	m_CreateDate;
	CStringA	m_RecordCreator;
	double	m_RecordVersion;
	CStringA	m_MarketLable;
	CStringA	m_SecurityType;*/
	CString	m_StkLable;
	CString	m_StkName;
	CTime	m_StkTime;
	double	m_StkOpen;
	double	m_StkHigh;
	double	m_StkLow;
	double	m_StkClose;
	double	m_StkVolume;
	double	m_StkAmount;
	double	m_StkTurnoverRate;
	/*CStringA	m_Reserved1;
	double	m_Reserved2;
	long	m_Reserved3;
	CLongBinary	m_Reserved4;*/

	// parameters
	/*CString m_StkLableParam;
	CString m_StkNameParam;
	CTime m_StkTimeStartParam;
	CTime m_StkTimeEndParam;*/

	// others
	CString m_Table;

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

public:


public:
	void print(int num = -1);
	CString& GetFieldName(int nIndex, CString& strFieldName);

	BOOL Open(const CString &lable, const CTimePair &time, const CYCLE_t cycle = DAY);
	//BOOL Requery(const CString &lable, const CTimePair &time, const CYCLE_t cycle = DAY);

	//int GetValue(CFinancialTimeSeries::STKDATA &data);
	CString SetDefaultSQL(CString &table);

	int Fetch(int num = -1);

protected:
	bool BuildSQL(CString &sql, const CString &lable, const CTimePair &time, const CYCLE_t cycle = DAY);
};


