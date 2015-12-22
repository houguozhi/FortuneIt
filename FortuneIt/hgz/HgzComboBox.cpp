// HgzComboBox.cpp : 实现文件
//
#include "StdAfx.h"
#include "hgz.h"
#include "HgzComboBox.h"
#include <string>



// CHgzComboBox

IMPLEMENT_DYNAMIC(CHgzComboBox, CComboBox)

CHgzComboBox::CHgzComboBox()
{

}

CHgzComboBox::~CHgzComboBox()
{
}


BEGIN_MESSAGE_MAP(CHgzComboBox, CComboBox)
END_MESSAGE_MAP()



// 增开型 AddString()，使添加新行时不重复，且不添加空行。

int CHgzComboBox::AddStringWithoutDuplication(LPCTSTR lpszString) // 1、大小写不敏感；2、首尾空格有效。
{
	CString cstr = lpszString;

	if (!cstr.IsEmpty() && (FindStringExact(-1, cstr)) == CB_ERR)
	{
		CComboBox::AddString(cstr);
		return TRUE;
	}

	return FALSE;
}

//int CHgzComboBox::GetWindowHex(unsigned char &Hex)
//{
//    CString str;
//    GetWindowText(str);
//    if (!str.IsEmpty())
//    {
//        UINT x;
//        _stscanf_s(str, _T("%x"), &x);
//        Hex = (UINT8)x;
//        return 1;
//    }
//    else
//        return 0;
//}

int CHgzComboBox::GetWindowHex(unsigned char * pHex)
{
	CString str;
	GetWindowText(str);

	CStringArray arr;
    hgzExtractSubStrings(arr, str, _T(" +"));
	unsigned int *pi = new unsigned int[arr.GetSize()];
	int i;
	for (i = 0; i < arr.GetSize(); i++)
	{
	    _stscanf_s(arr[i], _T("%x"), pi + i);
		pHex[i] = (unsigned char)pi[i]; // 将输入序列的高字节存储在 Bytes 中的低地址中。(Big-Endian)
	}

	delete [] pi;
	return i;
}

int CHgzComboBox::GetWindowHexArray(unsigned char * pHex)
{
	CString str;
	GetWindowText(str);

	CStringArray arr;
	hgzExtractSubStrings(arr, str, _T(" +"));
	//unsigned int *pi = new unsigned int[arr.GetSize()];
	int i;
	int n = 0;
	for (i = 0; i < arr.GetSize(); i++)
	{
		long long x;
		int j = 0;
		x = stoull((tstring)arr[i].GetString(), 0, 16);
		if      (x <= 0xFF)  j = 1;
		else if (x <= 0xFFFF)  j = 2;
		else if (x <= 0xFFFFFF)  j = 3;
		else if (x <= 0xFFFFFFFF)  j = 4;
		else if (x <= 0xFFFFFFFFFF)  j = 5;
		else if (x <= 0xFFFFFFFFFFFF)  j = 6;
		else if (x <= 0xFFFFFFFFFFFFFF)  j = 7;
		else if (x <= 0xFFffFFffFFffFFff)  j = 8;
		hgzRevertByteOrder((unsigned char *)&x, j);
		for (int m = 0; m < j; m++) {
			pHex[n+m] = ((unsigned char *)&x)[m];
		}
		n += j;
	}

	//delete [] pi;
	return n;
}

int CHgzComboBox::SetWindowHex(const unsigned char * pHex, int num)
{
	CString str;

	if (num) 
	{
		str.Format(_T("%02x"), pHex[0]);
		for (int i = 1; i < num; i++)
		{
			str.AppendFormat(_T(" %02x"), pHex[i]);  // 按 BIG-Endian 字节序显示。
		}
		
		SetWindowText(str);
		return num;
	}
	
	return 0;
}

int CHgzComboBox::GetWindowDec(int *pDec)
{
	CString str;
	GetWindowText(str);

	CStringArray arr;
    hgzExtractSubStrings(arr, str, _T(" +"));
	int *pi = new int[arr.GetSize()];
	int i;
	for (i = 0; i < arr.GetSize(); i++)
	{
	    _stscanf_s(arr[i], _T("%d"), pi + i);
		pDec[i] = pi[i]; // 将输入序列的高字节存储在 Bytes 中的低地址中。(Big-Endian)
	}

	delete [] pi;
	return i;
}

int CHgzComboBox::GetWindowDec( unsigned char *pDec )
{
	CString str;
	GetWindowText(str);

	CStringArray arr;
	hgzExtractSubStrings(arr, str, _T(" +"));
	unsigned int *pi = new unsigned int[arr.GetSize()];
	int i;
	for (i = 0; i < arr.GetSize(); i++)
	{
		_stscanf_s(arr[i], _T("%d"), pi + i);
		pDec[i] = (unsigned char)pi[i]; // 将输入序列的高字节存储在 Bytes 中的低地址中。(Big-Endian)
	}

	delete [] pi;
	return i;
}

unsigned char CHgzComboBox::GetWindowDec( void )
{
	CString str;
	GetWindowText(str);

	CStringArray arr;
	hgzExtractSubStrings(arr, str, _T(" +"));
	unsigned int *pi = new unsigned int[arr.GetSize()];
	int i;
	for (i = 0; i < arr.GetSize(); i++)
	{
		_stscanf_s(arr[i], _T("%d"), pi + i);
	}
	unsigned char x = (unsigned char)pi[0];
	delete [] pi;
	return x;
}


int CHgzComboBox::GetWindowHexByteCount(void)
{
	CString str;
	GetWindowText(str);
	
	CStringArray arr;
    hgzExtractSubStrings(arr, str, _T(" +"));
	
	return arr.GetSize();
}

int CHgzComboBox::SetWindowsTextFormat( const TCHAR * szFormat, ... )
{
    va_list arglist;
    va_start(arglist, szFormat);
    int len = _vsctprintf(szFormat, arglist)+1;
    TCHAR *buf = new TCHAR[len];
    //TCHAR *buf = (TCHAR *)_alloca((_vsctprintf(szFormat, arglist)+1)*sizeof(TCHAR)); // 动态分配栈内存，无需手动释放。
    _vstprintf(buf, szFormat, arglist);

    SetWindowText(buf);
    delete [] buf;

    return len-1;
}
