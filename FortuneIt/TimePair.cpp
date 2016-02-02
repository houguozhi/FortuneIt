#include "stdafx.h"
#include "TimePair.h"

CTimePair::CTimePair()
{
	start = end = COleDateTime(0.0);
}

CTimePair::CTimePair(COleDateTime &_start, COleDateTime &_end)
{
	start = _start;
	end = _end;	
}

CTimePair::~CTimePair()
{

}




CHgzTime::CHgzTime()
{
}


CHgzTime::~CHgzTime()
{
}
