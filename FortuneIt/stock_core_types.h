#pragma once
#include "stdafx.h"
#include "TimePair.h"
#include <vector>

extern void println(TCHAR *szFormat, ...);
using namespace std;

typedef enum {
	TICK = 0,				    //分笔成交
	MIN1 = 1,					//1分钟线
	MIN5 = 2,					//5分钟线					
	MIN15 = 3,					//15分钟线
	MIN30 = 4,					//30分钟线
	MIN60 = 5,					//60分钟线
	
	DAY = 6,					//日线
	WEEK = 7,					//周线
	MONTH = 8,					//月线
	SEASON = 9,                 //季线
	YEAR = 10,					//年线

	HalfDay = 11,               //半日线
	MULTISEC = 12,				//多秒线
	MULTIMIN = 13,				//多分钟线
	MULTIDAY = 14,				//多日线
} STKCYCLE;

class CStkData
{
public:
	CStkData();
	~CStkData();

	CHgzTime   time;       //时间,UCT
	double	open;		//开盘
	double	high;		//最高
	double	low;		//最低
	double	close;		//收盘
	double	volume;		//成交量(手)
	double	amount;		//成交额(元)/持仓(未平仓合约，仅期货有效)
	double  tor;        // turn_over_rate; //换手率
						//WORD	advance;		//上涨家数(仅大盘有效)
						//WORD	decline;		//下跌家数(仅大盘有效)

	bool operator<(const CStkData &stkdata)
	{
		return (time < stkdata.time);
	}

	bool operator<(const COleDateTime &t)
	{
		return (time < t);
	}

	CString ToString() { 
		CString s;
		s.Format(_T("%s %10.3f %10.3f %10.3f %10.3f %20.3f %20.3f %30.3f"), 
			time.ToString(), open, high, low, close, volume, amount, tor);
		return s;
	}

	void println() { ::println(_T("%s"), ToString()); }
};

inline bool operator < (const CStkData &stkdata, const COleDateTime &t) { return (stkdata.time < t); }

class CSplitData
{
public:
	CSplitData();
	~CSplitData();

public:
	CHgzTime	time;		//时间,UCT
	double		hg;			//红股（10送）
	double		pg;			//配股（10送）
	double		pgj;		//配股价
	double		hl;			//红利（10送）
	double		qfq;        //前复权系数，缺省应为1。RatioOfBackwardingCumDividend
	double      qfq_vol;    //成交量前复权系数，缺少应为1.
	int         idx_in_stkdata; // 除权日在 CStkData 序列中的索引。

	// 前复权：复权后价格=[(复权前价格-现金红利)+配(新)股价格×流通股份变动比例]÷(1+流通股份变动比例)
	// 前复权：除权基准价=（除权日前一天收盘价-现金股息+配股价×配股率）/（1+配股率+送股率）
	// 前复权系数：复权后价格÷复权前价格
	// Qfq=((Pclose-Hl/10)+Pgj*Pg/10)/(1+Hg/10+Pg/10)/Pclose
	void ComputeQfq(double prev_close) {
		qfq = prev_close ? ((prev_close - hl / 10) + pgj*pg / 10) / (1 + hg / 10 + pg / 10) / prev_close : 1.0;
		qfq_vol = prev_close ? 1 / (1 + hg / 10 + pg / 10) : 1.0;
	}

	CString ToString() {
		CString s;
		s.Format(_T("%s %10.3f %10.3f %10.3f %10.3f %10.3f %10.3f %d"),
			time.ToString(), hg, pg, pgj, hl, qfq, qfq_vol, idx_in_stkdata);
		return s;
	}

	void println() { ::println(_T("%s"), ToString()); }
};


