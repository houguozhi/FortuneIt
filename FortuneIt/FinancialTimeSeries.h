#pragma once

#include <vector>
#include <algorithm>
#include "stock_core_types.h"
#include "HgzStk.h"
#include "ftsplit.h"


using namespace std;

class CTimePair;

class CFinancialTimeSeries
{
public:
	CFinancialTimeSeries();
	~CFinancialTimeSeries();

	const vector<CStkData>* Data() const { return &m_data; }
	void Data(vector<CStkData> val) { m_data = val; }
	
public:
	

protected:
	CString m_lable;
	CString m_name;
	CString m_desc;
	STKCYCLE m_cycle;

	vector<CStkData> m_data;
	vector<CSplitData> m_split_data;

private:
	bool m_bCumDividendPrice;

public:
	// overload operator < to be comaring of time
	

public:
	// Interface to Database
	void Requery(const CString &lable, const CTimePair &time, const STKCYCLE cycle = STKCYCLE::DAY, const bool bCumDividend = true, int print = 10);
	void PerformBackwardingCumDividend(BOOL bYes = TRUE);
	bool ConvertCycle(STKCYCLE cyc);


	void SearchXDDateInStkData(CSplitData &var);

public:
	// �������õĺ���
	/* ����ָ������ʱ��Ĺ�Ʊ���ݣ���������
	 * direction = 0�����Ҿ�ȷ���ڣ�= -1������С�ڵ��ڸ�ʱ���1����= 1�����Ҵ��ڵ��ڸ�ʱ���1����
	 * ����ֵ���ҵ���������ֵ���Ҳ������� -1��
	 */
	vector<CStkData>::iterator  Find(CTime &time, int direction = 0);
	// ����ָ�����������
	CFinancialTimeSeries SelectSpan(CTimePair &time);

protected:
	int Fetch(CHgzStk &stk, int num = -1);
	int Fetch(Cftsplit &split, int num = -1);
	CString GetTable(CTimePair &time, STKCYCLE cycle = STKCYCLE::DAY);

	//bool CompByTime(STKDATA &stkdata, CTime &t);
};

typedef CFinancialTimeSeries CStock;




