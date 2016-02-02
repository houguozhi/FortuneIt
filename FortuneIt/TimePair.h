#pragma once
#include "atltime.h"

class CTimePair 
{
public:
	CTimePair();
	CTimePair(COleDateTime &_start, COleDateTime &_end);
	~CTimePair ();


public:
	COleDateTime start;
	COleDateTime end;

public:
	COleDateTimeSpan GetSpan() { return end - start; }


};

class CHgzTime :
	public COleDateTime
{
public:
	CHgzTime();
	~CHgzTime();

	CHgzTime(
		_In_ int nYear,
		_In_ int nMonth,
		_In_ int nDay,
		_In_ int nHour,
		_In_ int nMin,
		_In_ int nSec) :
		COleDateTime(
			nYear,
			nMonth,
			nDay,
			nHour,
			nMin,
			nSec){}



public:
	CString ToString() { return Format(_T("%Y%m%d %H:%M:%S %w %W")); }


	int GetWeek() {	return _ttoi(Format(_T("%W")));	}
	int GetSeason() { return ((GetMonth() - 1) / 3 + 1); } // SEASON = 1, 2, 3, 4

	// forwarding parent class member function, so that can be called by child class function pointer
	int GetMonth() { return COleDateTime::GetMonth(); }
	int GetYear() { return COleDateTime::GetYear(); }

	int GetM5OfDay() { return (GetHour() * 60 + GetMinute() - 1) / 5; } // Min5 serial no. of the day
	int GetM15OfDay() { return (GetHour() * 60 + GetMinute() - 1) / 15; } // Min15 serial no. of the day
	int GetM30OfDay() { return (GetHour() * 60 + GetMinute() - 1) / 30; } // Min30 serial no. of the day
	int GetM60OfDay() { return (GetHour() * 60 + GetMinute() - 1) / 60; } // Min60 serial no. of the day
	int GetTradingM60OfDay() { 
		const int t1030 = 10 * 60 + 30;
		const int t1130 = 11 * 60 + 30;
		const int t1400 = 14 * 60 + 00;
		const int t1500 = 15 * 60 + 00;

		int t = GetHour() * 60 + GetMinute();
		if (t <= t1030)
			return 0;
		if (t <= t1130)
			return 1;
		if (t <= t1400)
			return 2;
		if (t <= t1500)
			return 3;

	} // trading Min60 serial no. of the day
	int GetM120OfDay() { return (GetHour() * 60 + GetMinute() - 1) / 120; } // Min120 serial no. of the day
	int GetHalfDay() {
		const int t1200 = 12 * 60 + 00;
		
		int t = GetHour() * 60 + GetMinute();
		if (t <= t1200)
			return 0;
		else
			return 1;
	} // HalfDay serial no. of the day

	int GetM5OfYear() { return GetDay() * 24 * 60 + GetM5OfDay(); } // Min5 serial no. of the year
	int GetM15OfYear() { return GetDay() * 24 * 60 + GetM15OfDay(); } // Min15 serial no. of the year
	int GetM30OfYear() { return GetDay() * 24 * 60 + GetM30OfDay(); } // Min30 serial no. of the year
	int GetM60OfYear() { return GetDay() * 24 * 60 + GetM60OfDay(); } // Min60 serial no. of the year
	int GetM120OfYear() { return GetDay() * 24 * 60 + GetM120OfDay(); } // Min120 serial no. of the year
	int GetTradingM60OfYear() { return GetDay() * 24 * 60 + GetTradingM60OfDay(); } // trading Min60 serial no. of the year
	int GetHalfDayOfYear() { return GetDay() * 24 * 60 + GetHalfDay(); } // HalfDay serial no. of the year

};



