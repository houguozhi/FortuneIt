#pragma once
#include "stdafx.h"
#include "TimePair.h"
#include <vector>

extern void println(TCHAR *szFormat, ...);
using namespace std;

typedef enum {
	TICK = 0,				    //�ֱʳɽ�
	MIN1 = 1,					//1������
	MIN5 = 2,					//5������					
	MIN15 = 3,					//15������
	MIN30 = 4,					//30������
	MIN60 = 5,					//60������
	
	DAY = 6,					//����
	WEEK = 7,					//����
	MONTH = 8,					//����
	SEASON = 9,                 //����
	YEAR = 10,					//����

	HalfDay = 11,               //������
	MULTISEC = 12,				//������
	MULTIMIN = 13,				//�������
	MULTIDAY = 14,				//������
} STKCYCLE;

class CStkData
{
public:
	CStkData();
	~CStkData();

	CHgzTime   time;       //ʱ��,UCT
	double	open;		//����
	double	high;		//���
	double	low;		//���
	double	close;		//����
	double	volume;		//�ɽ���(��)
	double	amount;		//�ɽ���(Ԫ)/�ֲ�(δƽ�ֺ�Լ�����ڻ���Ч)
	double  tor;        // turn_over_rate; //������
						//WORD	advance;		//���Ǽ���(��������Ч)
						//WORD	decline;		//�µ�����(��������Ч)

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
	CHgzTime	time;		//ʱ��,UCT
	double		hg;			//��ɣ�10�ͣ�
	double		pg;			//��ɣ�10�ͣ�
	double		pgj;		//��ɼ�
	double		hl;			//������10�ͣ�
	double		qfq;        //ǰ��Ȩϵ����ȱʡӦΪ1��RatioOfBackwardingCumDividend
	double      qfq_vol;    //�ɽ���ǰ��Ȩϵ����ȱ��ӦΪ1.
	int         idx_in_stkdata; // ��Ȩ���� CStkData �����е�������

	// ǰ��Ȩ����Ȩ��۸�=[(��Ȩǰ�۸�-�ֽ����)+��(��)�ɼ۸����ͨ�ɷݱ䶯����]��(1+��ͨ�ɷݱ䶯����)
	// ǰ��Ȩ����Ȩ��׼��=����Ȩ��ǰһ�����̼�-�ֽ��Ϣ+��ɼۡ�����ʣ�/��1+�����+�͹��ʣ�
	// ǰ��Ȩϵ������Ȩ��۸�¸�Ȩǰ�۸�
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


