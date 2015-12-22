#include "stdafx.h"
#include "FinancialTimeSeries.h"

extern void println(TCHAR *szFormat, ...);

CFinancialTimeSeries::CFinancialTimeSeries()
{
}


CFinancialTimeSeries::~CFinancialTimeSeries()
{
}

void CFinancialTimeSeries::Requery(const CString &lable, const CTimePair &time, const CYCLE_t cycle /*= CYCLE_t::DAY*/, int print /*= 10*/)
{
	CHgzStk db;

	db.Open(lable, time, cycle);
	if (print)
		db.print(print);

	Fetch(db);
	m_cycle = cycle;
	db.Close();

	m_data.shrink_to_fit();
	if (print)
		println(_T("m_data size = %d"), m_data.size());

	// ftsplit
	Cftsplit ft;
	ft.Open(lable, time);
	ft.print();

}

int CFinancialTimeSeries::Fetch(CHgzStk &stk, int num /*= -1*/)
{
	int cnt = 0;

	if (num < 0) {
		STKDATA data;
		stk.MoveFirst();
		while (!stk.IsEOF())
		{
			data.time = stk.m_StkTime;
			data.open = stk.m_StkOpen;
			data.high = stk.m_StkHigh;
			data.close = stk.m_StkClose;
			data.volume = stk.m_StkVolume;
			data.amount = stk.m_StkAmount;
			data.tor = stk.m_StkTurnoverRate;
			m_data.push_back(data);
			stk.MoveNext();
			cnt++;
		}
	}
	else {
		STKDATA data;
		int i = num;
		while (!stk.IsEOF() && i--)
		{
			data.time = stk.m_StkTime;
			data.open = stk.m_StkOpen;
			data.high = stk.m_StkHigh;
			data.close = stk.m_StkClose;
			data.volume = stk.m_StkVolume;
			data.amount = stk.m_StkAmount;
			data.tor = stk.m_StkTurnoverRate;
			m_data.push_back(data);
			stk.MoveNext();
			cnt++;
		}
	}

	if (cnt)
	{
		stk.MovePrev();
		m_lable = stk.m_StkLable;
		m_name = stk.m_StkName;
	}
	return cnt;
}