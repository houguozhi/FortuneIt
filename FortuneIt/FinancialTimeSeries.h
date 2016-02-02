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
	// 部分有用的函数
	/* 查找指定日期时间的股票数据，返回索引
	 * direction = 0，查找精确日期；= -1，查找小于等于该时间第1个；= 1，查找大于等于该时间第1个。
	 * 返回值：找到返回索引值，找不到返回 -1。
	 */
	vector<CStkData>::iterator  Find(CTime &time, int direction = 0);
	// 返回指定区间的序列
	CFinancialTimeSeries SelectSpan(CTimePair &time);

protected:
	int Fetch(CHgzStk &stk, int num = -1);
	int Fetch(Cftsplit &split, int num = -1);
	CString GetTable(CTimePair &time, STKCYCLE cycle = STKCYCLE::DAY);

	//bool CompByTime(STKDATA &stkdata, CTime &t);
};

typedef CFinancialTimeSeries CStock;




