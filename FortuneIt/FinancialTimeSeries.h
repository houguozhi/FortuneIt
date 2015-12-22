#pragma once

#include <vector>
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

public:
	

protected:
	CString m_lable;
	CString m_name;
	CString m_desc;
	CYCLE_t m_cycle;

	vector<STKDATA> m_data;
	vector<SPLITDATA> m_split_data;

public:
	// Interface to Database
	void Requery(const CString &lable, const CTimePair &time, const CYCLE_t cycle = CYCLE_t::DAY, int print = 10);

protected:
	int Fetch(CHgzStk &stk, int num = -1);
	CString GetTable(CTimePair &time, CYCLE_t cycle = CYCLE_t::DAY);

};

typedef CFinancialTimeSeries CStock;




