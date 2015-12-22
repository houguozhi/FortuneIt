#include "stdafx.h"
#include <iostream>
#include <iomanip>
#include <regex>
#include "hgz.h"

using namespace std;
//using std::tcout;
//using namespace std::tr1;



/////////////////////////////////////////////////////////////////////

// 提取单个字符串
// ****BUG: 当分隔符不为空格，而字符串内含有空格时，不能正确分开，原因在于我的内部实现是先把指定分隔符转成了空格来处理的，待以后完善。
BOOL hgzExtractSubString(				// 成功返回 TRUE
		CString& rString,				// 本序号（iSubString）提取到的子字符串
		const CString& cstrFullString,	// 原字符串
		int iSubString,					// 子串序号
		const CString& regexSep )		// 分隔符字符串
{
	CString strSrc(cstrFullString);
	// 先去掉首尾空格
	strSrc.TrimLeft(regexSep);
	strSrc.TrimRight(regexSep);
	
	// regex_constants::syntax_option_type fl = std::regex_constants::icase; // 设置正则表达式选项 - 忽略大小写 
	tregex regExpress(regexSep, std::regex_constants::icase);	// 定义正则表达式对象

	// 将分隔符替换为单个空格
	std::tstring tmp =								// 返回替换后的字符串
	regex_replace(
		(std::tstring)strSrc.GetString(),	// 原字符串
		regExpress,									// 正则表达式
		(std::tstring)_T(" "),						// 替换字符串
		std::regex_constants::match_any				// 查找及替换规则
		);
	//const TCHAR *tmp1 = new TCHAR[32];
	const TCHAR *tmp1;
		
	// 如何判断 std::tstring 为空？
	// NULL 和 "" （空字符串）的区别？
	// str.c_str() == "" 不行。
	// 暂以长度是否为 0 来判断。
	tmp1 = tmp.length() == 0 ? NULL : tmp.c_str();
	BOOL x = AfxExtractSubString(rString, tmp1, iSubString, _T(' '));
	//delete [] tmp1;
	return x;
}

// 提取所有字符串
int hgzExtractSubStrings(				// 成功返回提取的子串数，不成功返回 0
	CStringArray& arr,				// 提取到的子串数组
	const CString& cstrFullString,	// 原字符串
	const CString& regexSep )		// 分隔符字符串
{
	int size = arr.GetSize();
	CString str(cstrFullString);
	CString subStr;
	int i = 0;
	while (hgzExtractSubString(subStr, str, i,	regexSep))
	{
		arr.Add(subStr);
		i++;
	}

	return arr.GetSize() - size;
}

//-----------------------------------------
//  [11/29/2013 hgz]
// 提取单个字符串
BOOL hgzExtractSubString1(				// 成功返回 TRUE
	CString& rString,				// 本序号（iSubString）提取到的子字符串
	const CString& cstrFullString,	// 原字符串
	int iSubString,					// 子串序号
	const CString& regexSep )		// 分隔符字符串
{
	CString strSrc(cstrFullString);
	// 先去掉首尾空格
	strSrc.TrimLeft(regexSep);
	strSrc.TrimRight(regexSep);

	// regex_constants::syntax_option_type fl = std::regex_constants::icase; // 设置正则表达式选项 - 忽略大小写 
	tregex e(regexSep, std::regex_constants::icase);	// 定义正则表达式对象

	tsmatch m;
	std::tstring s((std::tstring)strSrc.GetString());
	int i = 0;
	for (; regex_search( s, m,	e ); i++ ) {
		if (i == iSubString) {
			rString = m.prefix().str().c_str();
			return TRUE;
		}
		s = m.suffix().str();
	}
	if (i == iSubString/* the last suffix is the Sub String */ || iSubString == 0 /* the whole string is the 0th sub string */) {
		rString = s.c_str();
		return TRUE;
	}

	return FALSE;

}
// 提取所有字符串
int hgzExtractSubStrings1(			// 成功返回提取的子串数，不成功返回 0
	CStringArray& arr,				// 提取到的子串数组
	const CString& cstrFullString,	// 原字符串
	const CString& regexSep )		// 分隔符字符串
{
	//int size = arr.GetSize();
	arr.RemoveAll();
	// first of all, trim the preceding and ending regexSep strings.
	// use CString since it has trim functions.
	if (cstrFullString.GetLength() == 0) return 0;
	CString strSrc(cstrFullString);
	strSrc.TrimLeft(regexSep);
	strSrc.TrimRight(regexSep);
	if (strSrc.GetLength() == 0) return 0;

	// construct the regex object
	// regex_constants::syntax_option_type fl = std::regex_constants::icase; // 设置正则表达式选项 - 忽略大小写 
	tregex e(regexSep, std::regex_constants::icase);	// 定义正则表达式对象

	// m is the search result
	tsmatch m;
	// s is a std string, because regex_search can use only std string as its operands.
	std::tstring s((std::tstring)strSrc.GetString());
	while ( regex_search( s, m,	e ) ) {
		arr.Add(m.prefix().str().c_str());
		s = m.suffix().str();
	}
	arr.Add(s.c_str());

	//return arr.GetSize() - size;
	return arr.GetSize();
}


int hgzSubStringCount(
	const CString& s,				// 原字符串
	const CString& regexSep )		// 分隔符字符串
{
	CStringArray arr;
	return hgzExtractSubStrings1(arr, s,regexSep);
}

int hgzDeleteSepFromString(CString &s, const CString &regexSep)
{
    CStringArray arr;

    int x = hgzExtractSubStrings1(arr, s, regexSep);
    s.Format(_T(""));
    for (int i = 0; i < arr.GetSize(); i++) {
        s.Append(arr[i]);
    }
    return x;
}

//void regex_test(CString str)
//{
//	
//	//
//	// 正则表达式
//	//
//	tcout << _T("-------------------------") << endl;
//
//	// 注意 syntax_option_type 和 match_flag_type 的不同
//	regex_constants::syntax_option_type fl = std::regex_constants::icase; // 设置正则表达式选项 - 忽略大小写 
//	regex_constants::match_flag_type fl1   = std::regex_constants::match_default;
//    CString regStr(_T(" +"));       // 定义正则表达式字符串
//	// tregex regExpress(regStr, fl);   // 定义正则表达式对象
//	 tregex regExpress(regStr.GetString());    // 定义正则表达式对象
//    // tregex regExpress(_T(" +"));  // 定义正则表达式对象
//
//    // 保存查找的结果   
//    //cmatch mr;  
//	match_results<std::string::const_iterator> mr;
//	/*
//	template<class IOtraits, class IOalloc, class Alloc, class Elem, class RXtraits, class Alloc2>
//	bool regex_search(
//		const basic_string<Elem, IOtraits, IOalloc>& str,
//		match_results<typename basic_string<Elem, IOtraits, IOalloc>::const_iterator, Alloc>& match,
//		const basic_regex<Elem, RXtraits, Alloc2>& re,
//		match_flag_type flags = match_default);
//	*/
//
//
//	// search
//	if(regex_search(tstring(str.GetString()), mr, regExpress, fl1))  
//    {  
//        tcout<<_T("正则表达式: \"")<<regStr<<_T("\"")<<endl;
//		tcout<<_T("查找: \"")<<str<<_T("\"")<<endl;
//		tcout<<_T("-- 成功!")<<std::endl;  
//        for(size_t i= 0; i < mr.size(); ++i)  
//        {  
//            tcout<<_T("第")<<i<<_T("个结果:\"")<<mr.str(i)<<_T("\"")<<endl;  
//            tcout<<_T("起始位置:")<<mr.position(i);
//			tcout<<endl<<_T("长度")<<mr.length(i)<<std::endl;  
//        }  
//        std::tcout<<std::endl;  
//	}
//	
//	// 注意：regex_replace 里的字符串必须转换为 std::tstring 类型方可使用，而 regex_search 则不必。
//	CString fmt = _T(" ");
//	// replace
//
//
//	/*
//	// 方式 2：
//	template<class RXtraits, class Alloc, class Elem>
//      basic_string<Elem> regex_replace(
//			const basic_string<Elem>& str,
//			const basic_regex<Elem, RXtraits, Alloc>& re,
//			const basic_string<Elem>& fmt,
//			match_flag_type flags = match_default
//			);
//	*/
//
//	//regex_replace((std::tstring)str.GetString(), regExpress, (std::tstring)fmt.GetString());
//	std::tstring tmp =					// 返回替换后的字符串
//	regex_replace(
//		(std::tstring)str.GetString(),	// 原字符串
//		regExpress,						// 正则表达式
//		(std::tstring)_T(" "),			// 替换字符串
//		std::regex_constants::match_any	// 查找及替换规则
//		);
//
//	tcout<<endl<<tmp<<endl;
//	tcout << _T("-------------------------") << endl;
//
//}


// ExtractString 测试：有 BUG，如下，不能把 01 00 06 00 00 ab 10 3 6 从 a 处分开。
void ExtractString(
		CStringArray& arr, 
		const CString& strSrc, 
		const CString& sep = _T("\r\n") )
{
 // 预处理: 可根据需要决定是否需要Trim，以及是Trim掉空格/还是分隔符/还是其它
 CString str(strSrc);
 str.TrimLeft(); 
 str.TrimRight();
  
 if(str.IsEmpty())
  return;
 
 // 开始分解
 int pos = str.Find(sep);
 while (pos != -1)
 {
  //if(!str.Left(pos).IsEmpty()) // 如有必要也可在此Trim后再判断是否为空，为空则舍弃
  arr.Add(str.Left(pos));
 
  str = str.Mid(pos + sep.GetLength());
  pos = str.Find(sep);
 }
 
 arr.Add(str); // think
}

//
// 向组合框追加字符串
//
bool AddStrToComboBox(CString &str, CComboBox &cb)
{
	if (!str.IsEmpty() && (cb.FindStringExact(-1, str)) == CB_ERR) // 1、大小写不敏感；2、首尾空格有效。
	{
		cb.AddString(str);
		return TRUE;
	}

	return FALSE;

}

//
//
//
void splitfloat(float x, int &intpart, float &fracpart)
{  
   intpart=int(x); 
   fracpart=x-intpart; 
}


int CStringSplit(CStringArray& dest, const CString& source, const CString& divKey)
{
     dest.RemoveAll();
     int pos = 0;
     int pre_pos = -1;

     int sl = source.GetLength();
	 while( sl != pos )
	 {
         pos = source.Find(divKey, (pos+1));
		 if (pos == -1) pos = sl;
         if (pos != (pre_pos + 1)) // 子串空则略过
			dest.Add(source.Mid((pre_pos + 1), (pos - (pre_pos + 1))));
		 
		 pre_pos = pos;
     }

	 //for (int i = 0; i < dest.GetSize(); i++)
		// _tprintf_s("%s\n", dest[i]); 

	 return dest.GetSize();
}


int count_ones(unsigned int x, int length)
{
	int ones = 0;

	for (int i = 0; i < length; i++)
	{
		ones += (x>>i) & 0x01;
	}

	return ones;
}


int RandRange( int range_min, int range_max )
{
	// Generate random numbers in the closed interval
	// [range_min, range_max]. In other words,
	// range_min <= random number <= range_max
	return rand() % (range_max - range_min + 1) + range_min;
}

void DeleteSpaceFromString( CString &s )
{
	CStringArray arr;

	ExtractString(arr, s, _T(" "));
	s.Format(_T(""));
	for (int i = 0; i < arr.GetSize(); i++) {
		s.Append(arr[i]);
	}
}

__int64 BinCString2HexInt( const CString &s )
{
	__int64 h = 0;

	int len = s.GetLength();
	for (int i = 0; i < len; i++) {
		h += (s[len-1-i] == _T('1')) ? (1<<i) : 0;
		//_tprintf_s(_T("\n%x"), h);
	}

	return h;
}

unsigned __int64 BinCString2UInt( const CString &s )
{
	unsigned __int64 h = 0;

	int len = s.GetLength();
	for (int i = 0; i < len; i++) {
		h += (s[len-1-i] == _T('1')) ? (1<<i) : 0;
		//_tprintf_s(_T("\n%x"), h);
	}
	return h;
}
BOOL hgzOpenConsole()
{
	AllocConsole();  
	_tfreopen(_T("CONOUT$"), _T("w+t"), stdout);  
	_tfreopen(_T("CONIN$"), _T("r+t"), stdin); 

    //_tprintf(_T("↓ H2D: "));

	return TRUE;
}

BOOL hgzCloseConsole()
{
	fclose(stdout);
	fclose(stdin);
	FreeConsole();

	return TRUE;
}

void hgzRevertByteOrder( UINT8 *addr, UINT bytes )
{
	unsigned char x;

	if (bytes < 2) return;
	for (int i = 0; i < bytes/2; i++) {
		x = *(addr + i);
		*(addr + i) = *(addr + bytes - 1 - i);
		*(addr + bytes - 1 - i) = x;
	}
}

void hgzRevertByteOrder( UINT8 *out, const UINT8 *in, UINT bytes )
{
    if (bytes < 2) return;
    
    for (int i = 0; i < bytes; i++) 
        out[bytes-1-i] = in[i];
   
}

unsigned __int32 hgzRevertByteOrder32( unsigned __int32 x )
{
	hgzRevertByteOrder((unsigned char *)&x, 4);
	return x;
}

unsigned __int16 hgzRevertByteOrder16( unsigned __int16 x )
{
	hgzRevertByteOrder((unsigned char *)&x, 2);
	return x;
}

UINT64 hgzMaskBits( UINT64 val, int validBits )
{
    // validBits == -1: No mask.
    if (validBits != -1)
    {
        unsigned long y = 0;
        for (int i = 0; i < validBits ; i++)
        {
            y |= 1<<i;
        }
        val &= y;
    }
    return val;
}

/*========================================================================   
  功能: 获取文件版本信息.   
  说明: 要使用此函数必需在程序中加入   
  #pragma comment(lib, "Version.lib")   
  ----------------------------------------------------------------------------   
  参数: lpszFileName = 程序文件名,如果为空则是获取当前运行程序的版本信息   
  来自：http://wenku.baidu.com/view/de635d9cdd88d0d233d46a95.html
  ==========================================================================*/ 
#pragma comment(lib, "Version.lib")
CString GetProductVersion(LPCTSTR lpszFileName)   
{   
    CString strVersion;   
    TCHAR szSrcfn[MAX_PATH]; // 要获取信息的文件   
    if (lpszFileName == NULL)   
        ::GetModuleFileName(NULL, szSrcfn, sizeof(szSrcfn));   
    else   
        lstrcpy(szSrcfn, lpszFileName);   
    
    // 读文件信息   
    DWORD dwVerHnd = 0;   
    DWORD dwVerInfoSize = ::GetFileVersionInfoSize(szSrcfn, &dwVerHnd);   
    if (dwVerInfoSize)   
    {   
        // If we were able to get the information, process it:   
        HANDLE hMem;   
        LPVOID lpvMem;   
        unsigned int uInfoSize = 0;   
        VS_FIXEDFILEINFO * pFileInfo;   
    
        hMem = ::GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);   
        lpvMem = ::GlobalLock(hMem);   
        ::GetFileVersionInfo(szSrcfn, dwVerHnd, dwVerInfoSize, lpvMem);   
        ::VerQueryValue(lpvMem, (LPTSTR)_T("\\"), (void**)&pFileInfo, &uInfoSize);   
    
        WORD nVer[4];   
        nVer[0] = HIWORD(pFileInfo->dwProductVersionMS);   
        nVer[1] = LOWORD(pFileInfo->dwProductVersionMS);   
        nVer[2] = HIWORD(pFileInfo->dwProductVersionLS);   
        nVer[3] = LOWORD(pFileInfo->dwProductVersionLS);   
        strVersion.Format(_T("%d.%d.%d.%d"), nVer[0], nVer[1],nVer[2],nVer[3]);   
    
        ::GlobalUnlock(hMem);   
        ::GlobalFree(hMem);   
    }   
    
    return strVersion;   
}

inline
extern bool hgzIsBigEndian( void )
{
    UINT32 x = 0x01020304;
    return (*(UINT8 *)&x == 0x01);
}

CString hgzGetFolderPath(const CString &filePath)
{
    int n = filePath.ReverseFind(_T('\\'));
    if (n == -1)
        return _T("");
        
    return filePath.Left(n);
}

CString hgzGetFileName(const CString &filePath)
{
    int n = filePath.ReverseFind(_T('\\'));
    if (n == -1)
        return filePath;

    return filePath.Right(filePath.GetLength()-1-n);
}

CString hgzGetFileTitle(const CString &filePath)
{
    CString fn = hgzGetFileName(filePath);
    if (fn.IsEmpty())
        return fn;
    else
    {
        int n = fn.ReverseFind(_T('.'));
        if (n == -1)
            return fn;

        return fn.Left(n);
    }
}
