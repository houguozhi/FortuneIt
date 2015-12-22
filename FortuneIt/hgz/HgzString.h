#pragma once

#include "hgz.h"
#include <string>
#include <cstringt.h>
#include <cstring>


using namespace std;

class CHgzString :
	public CString
{
public:
	CHgzString(void);
	~CHgzString(void);

	CHgzString( const CString &stringSrc ){
		SetString(stringSrc);
	}

	CHgzString( const CHgzString &stringSrc ) {
		SetString(stringSrc);
	}

	CHgzString (const TCHAR *stringSrc ) {
		SetString(stringSrc);
	}

	/*const CHgzString& CHgzString::operator=(LPCTSTR lpsz)
	{
		ASSERT(lpsz == NULL || AfxIsValidString(lpsz));
		SetString(lpsz);
		return *this;
	}

	const CHgzString& CHgzString::operator=(CString s)
	{
		SetString(s);
		return *this;
	}*/


public:
	long stol( size_t *_Idx = 0, int _Base = 10, bool _ExceptionNotice = 1 )
	{
		try 
		{
			return std::stol(GetString(), _Idx, _Base);
		}
		catch (const std::invalid_argument& ia)
		{
			if (_ExceptionNotice) AfxMessageBox(_T("Invalid digitals!"));
		}
		catch (const std::out_of_range& oor)
		{
			if (_ExceptionNotice) AfxMessageBox(_T("Out of range!"));
		}
        
        return 0;
	}
	
	unsigned long stoul( size_t *_Idx = 0, int _Base = 10, bool _ExceptionNotice = 1 )
	{
		try 
		{
			return std::stoul(GetString(), _Idx, _Base);
		}
		catch (const std::invalid_argument& ia)
		{
			if (_ExceptionNotice) AfxMessageBox(_T("Invalid digitals!"));
		}
		catch (const std::out_of_range& oor)
		{
			if (_ExceptionNotice) AfxMessageBox(_T("Out of range!"));
		}

        return 0;
	}
	
	long long stoll( size_t *_Idx = 0, int _Base = 10, bool _ExceptionNotice = 1 )
	{
		try 
		{
			return std::stoll(GetString(), _Idx, _Base);
		}
		catch (const std::invalid_argument& ia)
		{
			if (_ExceptionNotice) AfxMessageBox(_T("Invalid digitals!"));
		}
		catch (const std::out_of_range& oor)
		{
			if (_ExceptionNotice) AfxMessageBox(_T("Out of range!"));
		}

        return 0;
	}
	
	unsigned long long stoull( size_t *_Idx = 0, int _Base = 10, bool _ExceptionNotice = 1/*, CString sep = _T(" +"), BOOL bByteSep = FALSE*/ )
	{
        // bByteSep ＝ TRUE: 表示 sep 将作为字节分隔符，否则 sep 将不作为分隔符。
        // 无论 sep 是否作为字节分隔符，都会首先被去掉。
        // 暂不实现字节分隔情况。

		try
		{
			return std::stoull(GetString(), _Idx, _Base);
		}
		catch (const std::invalid_argument& ia)
		{
			if (_ExceptionNotice) AfxMessageBox(_T("Invalid digitals!"));
		}
		catch (const std::out_of_range& oor)
		{
			if (_ExceptionNotice) AfxMessageBox(_T("Out of range!"));
		}

        return 0;
	}

	int ultoa( unsigned long value, int radix = 10 ) 
	{
		TCHAR str[65];
		_ultot(value, str, radix);
		SetString(str);
		return GetLength();
	}
	
    int ulltoa( unsigned long long value, int radix = 10, int digitlength = -1, int segment_digits = 0, CString sep = _T(" ") ) 
    {
        // digitlength = -1: 表示从第一个非0数字起的数字数。

        TCHAR tc[100];
        _ui64tot(value, tc, radix);

        CString s1 = tc;
        CString s(_T(""));

        if (!s1.IsEmpty() && segment_digits > 0 && !sep.IsEmpty())
        {
            if (digitlength == -1)
                digitlength = s1.GetLength();
            else
            {
                int x = s1.GetLength();
                if (digitlength < x)
                    // 要显示的长度 小于 实际长度，则字符串前移。
                    s1 = s1.Right(digitlength);
                else
                {// 要显示的长度大于实际长度，则前面补 0
                    for (int i = 0; i < digitlength-x ; i++)
                    {
                        s1.Insert(0, _T("0"));
                    }
                }
            }

            for (int i = digitlength-1; i >= 0; i -= segment_digits)
            {
                for (int j = i; j > i-segment_digits && j >= 0; j--)
                {
                    s.Insert(0, s1[j]);
                }
                if (i/segment_digits) s.Insert(0, sep);
            }
        }
        else
        {
            s = tc;
        }

        SetString(s);

        return GetLength();
    }

    int ToHexArr(unsigned char * pHex, CString strSep = _T(" +"), BOOL bByteSep = FALSE)
    {
        if (bByteSep)
        {
            CStringArray arr;
            hgzExtractSubStrings(arr, GetString(), strSep);
            int i;
            for (i = 0; i < arr.GetSize(); i++)
            {
                UINT tmp;
                _stscanf_s(arr[i], _T("%x"), &tmp);
                pHex[i] = (UINT8)tmp; // 将输入序列的高字节存储在 Bytes 中的低地址中。(Big-Endian)
            }

            return i;
        }
        else
        {
            CHgzString s = GetString();
            DeleteSpaceFromString(s);
            if (s.GetLength()%2 == 1)
            {
                s.Insert(0, _T("0"));
            }

            int i;
            for (i = 0; i < s.GetLength()/2 ; i++)
            {
                UINT tmp;
            	_stscanf_s(s.Mid(i*2, 2), _T("%X"), &tmp);
                pHex[i] = (UINT8)tmp;
            }
            return i;
        }
    }

    int GetByteNum(int radix = 16, CString strSep = _T(" +"), BOOL bByteSep = FALSE)
    {
        // Now, only hex and bin are supported.

        switch (radix)
        {
        case 16:
            {
                if (bByteSep)
                {
                    CStringArray arr;
                    hgzExtractSubStrings(arr, GetString(), strSep);
                    return arr.GetSize();
                }
                else
                {
                    CHgzString s = GetString();
                    DeleteSpaceFromString(s);
                    return (s.GetLength()+1)/2;
                }
            }
            break;

        case 2:
            {
                if (bByteSep)
                {
                    CStringArray arr;
                    hgzExtractSubStrings(arr, GetString(), strSep);
                    return arr.GetSize();
                }
                else
                {
                    CHgzString s = GetString();
                    DeleteSpaceFromString(s);
                    return (s.GetLength()+7)/8;
                }
            }
            break;

        default:
            return 0;
        }
    }
};

