#include "stdafx.h"
#include "FinancialTimeSeries.h"
#include <functional>

extern void println(TCHAR *szFormat, ...);

CFinancialTimeSeries::CFinancialTimeSeries()
{
}


CFinancialTimeSeries::~CFinancialTimeSeries()
{
}

void CFinancialTimeSeries::Requery(const CString &lable, const CTimePair &time, const STKCYCLE cycle /*= STKCYCLE::DAY*/, const bool bCumDividend /*= true*/, int print /*= 10*/)
{
	CHgzStk db;

	db.Open(lable, time, cycle);
	if (print)
		db.print(print);

	Fetch(db);
	m_cycle = (cycle < DAY || cycle == HalfDay) ? MIN5 : DAY;
	db.Close();
	m_data.shrink_to_fit();
	//sort(m_data.begin(), m_data.end(), [&](auto &var1, auto &var2) { return var1.time < var2.time; });
	sort(m_data.begin(), m_data.end());

	println(_T("Top 10:"));
	int i = 0;
	for (auto var = m_data.begin(); var != m_data.end() && i < 10; var++, i++) var->println();
	println(_T("Bottom 10:"));
	i = 0;
	for (auto var = m_data.rbegin(); var != m_data.rend() && i < 10; var++, i++) var->println();
	
	
	if (print)
		println(_T("m_data size = %d"), m_data.size());

	// ftsplit
	if (bCumDividend)
	{
		Cftsplit ft;
		ft.Open(lable, time);
		if (print)
			ft.print(print);

		Fetch(ft);
		ft.Close();
		m_split_data.shrink_to_fit();
		if (print)
			println(_T("m_split_data size = %d"), m_split_data.size());

		PerformBackwardingCumDividend();
	}

	ConvertCycle(cycle);

}

void CFinancialTimeSeries::PerformBackwardingCumDividend(BOOL bYes /*= TRUE*/)
{
	// ǰ��Ȩ����Ȩ��۸�=[(��Ȩǰ�۸�-�ֽ����)+��(��)�ɼ۸����ͨ�ɷݱ䶯����]��(1+��ͨ�ɷݱ䶯����)
	// ǰ��Ȩ����Ȩ��׼��=����Ȩ��ǰһ�����̼�-�ֽ��Ϣ+��ɼۡ�����ʣ�/��1+�����+�͹��ʣ�
	// ǰ��Ȩϵ������Ȩ��۸�¸�Ȩǰ�۸�
	// Qfq=((Pclose-Hl/10)+Pgj*Pg/10)/(1+Hg/10+Pg/10)/Pclose

	// �����ҳ���Ȩǰһ�����̼ۣ�Pclose
	// �����ҳ���Ȩǰһ��Ԫ�ء�
	// 1���ҳ���Ȩ�Ǽ���
	// 2����¼ÿ��ȨϢ����Ӧ�Ĺ�Ȩ�Ǽ��գ���������ۼ�ǰ��Ȩϵ����

	if (bYes == m_bCumDividendPrice)
		return;

	if (!m_split_data.size())
		return;

	for (auto &var : m_split_data)
	{
		SearchXDDateInStkData(var);
		var.println();
	}

	println(_T(""));
	// 3������ÿ��ȨϢ����ۼ�ǰ��Ȩϵ�����ۼƻ��ڵ�ǰȨϢ������
	for (auto &var = m_split_data.rbegin() + 1; var != m_split_data.rend(); var++)
	{
		var->qfq *= (var - 1)->qfq;
		var->qfq_vol *= (var - 1)->qfq_vol;
	}

	for (auto &var : m_split_data)
	{
		var.println();
	}

	// 4�������ۼ�ǰ��Ȩϵ�����Թ�Ʊ���ݽ���ǰ��Ȩ����
	// 4.1 ÿ��ȨϢ��ֻ���������ȨϢ���ǰһȨϢ��֮������ݡ�
	if (!m_bCumDividendPrice)
	{
		for (auto var = m_split_data.begin(); var != m_split_data.end(); var++)
		{
			if (var->idx_in_stkdata == -1)
				break;

			for (int i = (var == m_split_data.begin() ? 0 : (var - 1)->idx_in_stkdata); i < var->idx_in_stkdata; i++)
			{
				//m_data[i] *= var->qfq; // need to define *= operator of CStkData
				m_data[i].open *= var->qfq;
				m_data[i].high *= var->qfq;
				m_data[i].low *= var->qfq;
				m_data[i].close *= var->qfq;
				m_data[i].volume *= var->qfq_vol;
				m_data[i].amount *= (var->qfq * var->qfq_vol);

			}
		}
		m_bCumDividendPrice = true;
	}

	println(_T(""));
	for_each(m_data.begin(), m_data.size() < 10 ? m_data.end() : m_data.begin() + 10, [&](auto &var) { var.println(); });

}

void CFinancialTimeSeries::SearchXDDateInStkData(CSplitData &var)
{
	auto xd = lower_bound(m_data.begin(), m_data.end(), var.time);
	if (xd == m_data.end()) // all less than
	{
		var.qfq = 1;
		var.idx_in_stkdata = -1;
	}
	else if (xd == m_data.begin()) // all large than or equal to
	{
		var.qfq = 1;
		var.idx_in_stkdata = -1;
	}
	else // some less than, some large than or equal to
	{
		var.ComputeQfq((xd - 1)->close);
		var.idx_in_stkdata = xd - m_data.begin();
	}
}

bool CFinancialTimeSeries::ConvertCycle(STKCYCLE cyc)
{
	if (m_cycle > cyc)
		return false;
	if (m_cycle == cyc)
		return true;

	vector<CStkData> vn;

	auto f = [&](STKCYCLE cycle)
	{
		int (CHgzTime::*pmf)() = NULL;
		switch (cyc)
		{
		case MIN15:		pmf = &CHgzTime::GetM15OfYear; break;
		case MIN30:		pmf = &CHgzTime::GetM30OfYear; break;
		case MIN60:		pmf = &CHgzTime::GetTradingM60OfYear; break;
		case HalfDay:	pmf = &CHgzTime::GetHalfDayOfYear; break;
		
		case WEEK:		pmf = &CHgzTime::GetWeek; break;
		case MONTH:		pmf = &CHgzTime::GetMonth; break;
		case SEASON:	pmf = &CHgzTime::GetSeason; break;
		case YEAR:		pmf = &CHgzTime::GetYear; break;
		default:		return false;
		}

		auto f1 = [&](int n) { return m_data[n].time.GetYear() * 1000000 + (m_data[n].time.*pmf)(); };
		int prev = f1(0);
		vn.push_back(m_data[0]);
		for (int i = 1; i < m_data.size(); i++)
		{
			int curr = f1(i);
			if ((pmf == &CHgzTime::GetWeek) && (m_data[i].time.GetWeek() == 0) && ((m_data[i].time - vn.back().time).GetDays() <= 7))
			{ // ���괦����ǰ����Ƿ�ͬһ�ܣ����ǣ��ϲ���ǰһ�ꡣ
			}
			else if (curr != prev)
			{
				prev = curr;
				vn.back().time = m_data[i - 1].time;
				vn.back().close = m_data[i - 1].close;
				vn.push_back(m_data[i]);
			}

			vn.back().high = max(vn.back().high, m_data[i].high);
			vn.back().low = min(vn.back().low, m_data[i].low);
			vn.back().volume += m_data[i].volume;
			vn.back().amount += m_data[i].amount;
			vn.back().tor += m_data[i].tor;

		}
		vn.back().time = m_data.back().time;
		vn.back().close = m_data.back().close;

	} (cyc);

	for (auto &var : vn) var.println();

	return true;
}

//vector<CStkData>::iterator CFinancialTimeSeries::Find(CTime &time, int direction /*= 0*/)
//{
//	// ���ķ����Ƕ��ַ�
//	if (direction == -1)
//		return upper_bound(m_data.begin(), m_data.end(), time);
//	else if (direction == 1)
//		return lower_bound(m_data.begin(), m_data.end(), time);
//	else if (direction == 0)
//		return find_if(m_data.begin(), m_data.end(), time);
//}

int CFinancialTimeSeries::Fetch(CHgzStk &stk, int num /*= -1*/)
{
	if (stk.IsEmpty())
		return 0;

	if (num == -1)
		stk.MoveFirst();
	
	int cnt = 0;
	while (!stk.IsEOF() && (cnt != num))
	{
		m_data.push_back(stk.m_StkData);
		stk.MoveNext();
		cnt++;
	}
	
	if (cnt)
	{
		stk.MovePrev();
		m_lable = stk.m_StkLable;
		m_name = stk.m_StkName;
		stk.MoveNext();
	}
	return cnt;
}

int CFinancialTimeSeries::Fetch(Cftsplit &split, int num /*= -1*/)
{
	if (split.IsEmpty())
		return 0;

	if (num == -1)
		split.MoveFirst();

	int cnt = 0;
	while (!split.IsEOF() && (cnt != num))
	{
		m_split_data.push_back(split.m_SplitData);
		split.MoveNext();
		cnt++;
	}

	return cnt;
}



