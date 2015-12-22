#pragma once


// CHgzComboBox

class CHgzComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CHgzComboBox)

public:
	CHgzComboBox();
	virtual ~CHgzComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	int AddStringWithoutDuplication(LPCTSTR lpszString);
	int GetWindowHex(unsigned char *pHex); // 取 16 进制数
 //   int GetWindowHex(unsigned char &Hex);
    int SetWindowHex(const unsigned char *pHex, int num); 
	int GetWindowDec(int *pDec); // 取 10 进制数
	int GetWindowDec(unsigned char *pDec); // 取 10 进制数
	unsigned char GetWindowDec(void); // 取 10 进制数
	int GetWindowHexByteCount(void);
	int GetWindowHexArray(unsigned char * pHex);

    int SetWindowsTextFormat(const TCHAR * szFormat, ...);
};


