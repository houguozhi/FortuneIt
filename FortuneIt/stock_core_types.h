#pragma once
#include "stdafx.h"

typedef enum {
	TICK = 11,				    //�ֱʳɽ�
	MIN1 = 1,					//1������
	MIN5 = 2,					//5������					
	MIN15 = 3,					//15������
	MIN30 = 4,					//30������
	MIN60 = 5,					//60������
	HalfDay = 12,               //������
	DAY = 6,					//����
	WEEK = 7,					//����
	MONTH = 8,					//����
	SEASON = 9,                 //����
	YEAR = 10,					//����

	MULTISEC = 13,				//������
	MULTIMIN = 14,				//�������
	MULTIDAY = 15,				//������
} CYCLE_t;

typedef struct tagSTKDATA
{
	CTime   time;       //ʱ��,UCT
	float	open;		//����
	float	high;		//���
	float	low;			//���
	float	close;		//����
	float	volume;		//�ɽ���(��)
	float	amount;		//�ɽ���(Ԫ)/�ֲ�(δƽ�ֺ�Լ�����ڻ���Ч)
	float   tor;        // turn_over_rate; //������
						//WORD	advance;		//���Ǽ���(��������Ч)
						//WORD	decline;		//�µ�����(��������Ч)
} STKDATA;

typedef struct tagSPLITDATA
{
	CTime	time;			//ʱ��,UCT
	float	fHg;			//���
	float	fPg;			//���
	float	fPgj;			//��ɼ�
	float	fHl;			//����
} SPLITDATA;


