#pragma once
#include "stdafx.h"

typedef enum {
	TICK = 11,				    //分笔成交
	MIN1 = 1,					//1分钟线
	MIN5 = 2,					//5分钟线					
	MIN15 = 3,					//15分钟线
	MIN30 = 4,					//30分钟线
	MIN60 = 5,					//60分钟线
	HalfDay = 12,               //半日线
	DAY = 6,					//日线
	WEEK = 7,					//周线
	MONTH = 8,					//月线
	SEASON = 9,                 //季线
	YEAR = 10,					//年线

	MULTISEC = 13,				//多秒线
	MULTIMIN = 14,				//多分钟线
	MULTIDAY = 15,				//多日线
} CYCLE_t;

typedef struct tagSTKDATA
{
	CTime   time;       //时间,UCT
	float	open;		//开盘
	float	high;		//最高
	float	low;			//最低
	float	close;		//收盘
	float	volume;		//成交量(手)
	float	amount;		//成交额(元)/持仓(未平仓合约，仅期货有效)
	float   tor;        // turn_over_rate; //换手率
						//WORD	advance;		//上涨家数(仅大盘有效)
						//WORD	decline;		//下跌家数(仅大盘有效)
} STKDATA;

typedef struct tagSPLITDATA
{
	CTime	time;			//时间,UCT
	float	fHg;			//红股
	float	fPg;			//配股
	float	fPgj;			//配股价
	float	fHl;			//红利
} SPLITDATA;


