#include "stdafx.h"
#include "stock_core_types.h"


CStkData::CStkData()
	: time()
	, open(0.0)
	, high(0.0)
	, low(0.0)
	, close(0.0)
	, volume(0.0)
	, amount(0.0)
	, tor(0.0)
{

}

CStkData::~CStkData()
{

}


CSplitData::CSplitData()
	: time()
	, hg(0.0)
	, pg(0.0)
	, pgj(0.0)
	, hl(0.0)
	, qfq(1.0)
	, qfq_vol(1.0)
	, idx_in_stkdata(-1)
{

}

CSplitData::~CSplitData()
{

}
