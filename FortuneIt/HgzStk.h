// HgzStk.h : CHgzStk 的声明

#pragma once

#include "TimePair.h"
#include "stock_core_types.h"

// 代码生成在 2015年12月5日, 12:03

class CHgzStk : public CRecordset
{
public:
	CHgzStk(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CHgzStk)

// 字段/参数数据

// 以下字符串类型(如果存在)反映数据库字段(ANSI 数据类型的 CStringA 和 Unicode
// 数据类型的 CStringW)的实际数据类型。
//  这是为防止 ODBC 驱动程序执行可能
// 不必要的转换。如果希望，可以将这些成员更改为
// CString 类型，ODBC 驱动程序将执行所有必要的转换。
// (注意: 必须使用 3.5 版或更高版本的 ODBC 驱动程序
// 以同时支持 Unicode 和这些转换)。

	/*CTime	m_CreateDate;
	CStringA	m_RecordCreator;
	double	m_RecordVersion;
	CStringA	m_MarketLable;
	CStringA	m_SecurityType;*/
	CString	m_StkLable;
	CString	m_StkName;
	CTime	m_StkTime;
	double	m_StkOpen;
	double	m_StkHigh;
	double	m_StkLow;
	double	m_StkClose;
	double	m_StkVolume;
	double	m_StkAmount;
	double	m_StkTurnoverRate;
	/*CStringA	m_Reserved1;
	double	m_Reserved2;
	long	m_Reserved3;
	CLongBinary	m_Reserved4;*/

	// parameters
	/*CString m_StkLableParam;
	CString m_StkNameParam;
	CTime m_StkTimeStartParam;
	CTime m_StkTimeEndParam;*/

	// others
	CString m_Table;

// 重写
	// 向导生成的虚函数重写
public:
	virtual CString GetDefaultConnect();	// 默认连接字符串

	virtual CString GetDefaultSQL(); 	// 记录集的默认 SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX 支持

// 实现
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:


public:
	void print(int num = -1);
	CString& GetFieldName(int nIndex, CString& strFieldName);

	BOOL Open(const CString &lable, const CTimePair &time, const CYCLE_t cycle = DAY);
	//BOOL Requery(const CString &lable, const CTimePair &time, const CYCLE_t cycle = DAY);

	//int GetValue(CFinancialTimeSeries::STKDATA &data);
	CString SetDefaultSQL(CString &table);

	int Fetch(int num = -1);

protected:
	bool BuildSQL(CString &sql, const CString &lable, const CTimePair &time, const CYCLE_t cycle = DAY);
};


