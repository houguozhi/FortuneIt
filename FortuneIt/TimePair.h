#pragma once

class CTimePair 
{
public:
	CTimePair ();
	CTimePair(CTime &_start, CTime &_end) {
		start = _start;
		end = _end;
	}
	~CTimePair ();


public:
	CTime start;
	CTime end;

public:
	CTimeSpan GetSpan() { return end - start; }


};

