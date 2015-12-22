#pragma once

//#include "stdafx.h"
#include <string>

using namespace std;

#define uchar unsigned char
//////////////////////////////
#ifdef _UNICODE
	#define tstring		wstring
	#define tregex		wregex
	#define tcout		wcout
	#define tcmatch		wcmatch
	#define tsmatch		wsmatch
#else
	#define tstring		string
	#define tregex		regex
	#define tcout		cout
	#define tcmatch		cmatch
	#define tsmatch		smatch
#endif
/////////////////////////////

#pragma warning(disable : 4996)


extern BOOL hgzExtractSubString(	// 成功返回 TRUE
	CString& rString,				// 本序号（iSubString）提取到的子字符串
    const CString& cstrFullString,	// 原字符串
    int iSubString,					// 子串序号
    const CString& regexSep			// 分隔符
	);

extern int hgzExtractSubStrings(	// 成功返回 TRUE
	CStringArray& arr,				// 提取到的子串数组
    const CString& cstrFullString,	// 原字符串
    const CString& regexSep			// 分隔符字符串
	);

extern BOOL hgzExtractSubString1(	// 成功返回 TRUE
	CString& rString,				// 本序号（iSubString）提取到的子字符串
	const CString& cstrFullString,	// 原字符串
	int iSubString,					// 子串序号
	const CString& regexSep			// 分隔符
	);

extern int hgzExtractSubStrings1(	// 成功返回 TRUE
	CStringArray& arr,				// 提取到的子串数组
	const CString& cstrFullString,	// 原字符串
	const CString& regexSep			// 分隔符字符串
	);

extern int hgzSubStringCount(
	const CString& s,				// 原字符串
	const CString& regexSep			// 分隔符字符串
	);

extern int hgzDeleteSepFromString(CString &s, const CString &regexSep);
//extern void regex_test(CString str);
extern void ExtractString(CStringArray& arr, const CString& strSrc, const CString& sep);
//
// 向组合框追加字符串
//
extern bool AddStrToComboBox(CString &str, CComboBox &cb);
extern void splitfloat(float x, int &intpart, float &fracpart);
extern int CStringSplit(CStringArray& dest, const CString& source, const CString& divKey);
extern int count_ones(unsigned int x, int length);
extern int RandRange( int range_min, int range_max );

//
extern void DeleteSpaceFromString( CString &s );
extern __int64 BinCString2HexInt( const CString &s );
extern unsigned __int64 BinCString2UInt( const CString &s );
extern BOOL hgzOpenConsole();
extern BOOL hgzCloseConsole();

// BigEnding <-> LittleEnding
extern void hgzRevertByteOrder(UINT8 *addr, UINT length);
extern void hgzRevertByteOrder( UINT8 *out, const UINT8 *in, UINT bytes );
extern unsigned __int32 hgzRevertByteOrder32( unsigned __int32 x );
extern unsigned __int16 hgzRevertByteOrder16( unsigned __int16 x );extern UINT64 hgzMaskBits( UINT64 val, int validBits );

extern CString GetProductVersion(LPCTSTR lpszFileName);

extern bool hgzIsBigEndian(void);

extern CString hgzGetFolderPath(const CString &filePath);
extern CString hgzGetFileName(const CString &filePath);
extern CString hgzGetFileTitle(const CString &filePath);