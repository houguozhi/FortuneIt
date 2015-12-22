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
	int GetWindowHex(unsigned char *pHex); // ȡ 16 ������
 //   int GetWindowHex(unsigned char &Hex);
    int SetWindowHex(const unsigned char *pHex, int num); 
	int GetWindowDec(int *pDec); // ȡ 10 ������
	int GetWindowDec(unsigned char *pDec); // ȡ 10 ������
	unsigned char GetWindowDec(void); // ȡ 10 ������
	int GetWindowHexByteCount(void);
	int GetWindowHexArray(unsigned char * pHex);

    int SetWindowsTextFormat(const TCHAR * szFormat, ...);
};


