
#include "stdafx.h"
#include "HexFile.h"


void HexRec(HEXRECORD_t & hr, HEXRECTYPE_t rectype, unsigned char reclen, unsigned int addr, unsigned char *buf)
{
	switch (rectype) {
	case HEX_REC_DAT:
		hr.reclen = reclen;
		hr.addrh = (unsigned char)(addr>>8);
		hr.addrl = (unsigned char)addr;
		hr.rectype = (unsigned char)HEX_REC_DAT;
		for (unsigned int i = 0; i < hr.reclen; i++)
			hr.data[i] = buf[addr++];
		hr.checksum();
		break;
	case HEX_REC_EOF: // :00000001FF
		hr.reclen = 0x00;
		hr.addrh = 0x00;
		hr.addrl = 0x00;
		hr.rectype = 0x01;
		hr.data[0] = 0xFF;
		break;
	case HEX_REC_ESA:
		hr.reclen = 0x02;
		hr.addrh = 0x00;
		hr.addrl = 0x00;
		hr.rectype = (unsigned char)HEX_REC_ESA;
		hr.data[0] = (unsigned char)(addr>>12);
		hr.data[1] = (unsigned char)(addr>>4);
		hr.checksum();
		break;
	case HEX_REC_SSA:
		break;
	case HEX_REC_ELA:
		hr.reclen = 0x02;
		hr.addrh = 0x00;
		hr.addrl = 0x00;
		hr.rectype = (unsigned char)HEX_REC_ELA;
		hr.data[0] = (unsigned char)(addr>>24);
		hr.data[1] = (unsigned char)(addr>>16);
		hr.checksum();
		break;
	case HEX_REC_SLA:
		break;
	default:
		break;
	}
}

void HexRecPrint( HEXRECORD_t &hr )
{
	_tprintf(_T("\nhex record:  %02X | %02X%02X | %02X | "), hr.reclen, hr.addrh, hr.addrl, hr.rectype);
	for (int i = 0; i < hr.reclen; i++)	_tprintf(_T("%02X"), hr.data[i]);
	_tprintf(_T(" | %02X"), hr.data[hr.reclen]);
}


bool HexRecReadFromFile( unsigned char *buf, unsigned char *buf_flag, CStdioFile &mFile, HEXRECORD_t &hr, unsigned int &cur_addr )
{
    CString s;
    mFile.ReadString(s);
    for (int i = 1; i < s.GetLength(); i+=2) {
        ((unsigned char *)&hr)[1+i/2] = (unsigned char)stoul((tstring)(s.Mid(i, 2).GetString()), 0, 16);
    }
    //HexRecPrint(hr);
    // check checksum
    UINT8 checksum = hr.data[hr.reclen];
    if (checksum != hr.checksum())
    {
        hr.data[hr.reclen] = checksum;
        CString str;
        str.Format(_T("CheckSum error: %s"), s);
        //printf(str);
        HexRecPrint(hr);
        AfxMessageBox(str);
        return false;
    }

    unsigned int addr;
    unsigned int base_addr = cur_addr & 0xffff0000;

    switch ((HEXRECTYPE_t)hr.rectype) 
    {
    case HEX_REC_DAT: // Data Record
        addr = base_addr + (hr.addrh<<8) + hr.addrl;
        //_tprintf(_T(" | %08X"), addr);
        //memset(buf+cur_addr, 0, addr-cur_addr);
        //memset(buf_flag+cur_addr, 0, addr-cur_addr);
        memcpy(buf+addr, hr.data, hr.reclen);
        memset(buf_flag+addr, 1, hr.reclen);
        cur_addr = addr + hr.reclen;
        break;
    case HEX_REC_EOF: // End of File Record
        //wbuf_data_length = cur_addr;
        break;
    case HEX_REC_ESA: // Extended Segment Address Record
        base_addr = (hr.data[0]<<12) + (hr.data[1]<<4);
        //memset(buf+cur_addr, 0, base_addr-cur_addr);
        //memset(buf_flag+cur_addr, 0, base_addr-cur_addr);
        cur_addr = base_addr;
        break;
    case HEX_REC_SSA: // Start Segment Address Record
        AfxMessageBox(_T("Hex item type: 0x03 (Start Segment Address Record), unprocessed."));
        return false;
        break;
    case HEX_REC_ELA: // Extended Linear Address Record
        base_addr = (hr.data[0]<<24) + (hr.data[1]<<16);
        //memset(buf+cur_addr, 0, base_addr-cur_addr);
        //memset(buf_flag+cur_addr, 0, base_addr-cur_addr);
        cur_addr = base_addr;
        break;
    case HEX_REC_SLA: // Start Linear Address Record
        AfxMessageBox(_T("Hex item type: 0x05 (Start Linear Address Record), unprocessed."));
        return false;
        break;
    default:
        break;
    }

    return true;
}

void HexRecSaveToFile(HEXRECORD_t &hr, CStdioFile &mFile )
{
	CString s;
	s.Format(_T(":%02X%02X%02X%02X"), hr.reclen, hr.addrh, hr.addrl, hr.rectype);
	for (unsigned int i = 0; i < hr.reclen; i++)
		s.AppendFormat(_T("%02X"), hr.data[i]);
	s.AppendFormat(_T("%02X\n"), hr.data[hr.reclen]);
	mFile.WriteString(s);

#if 0
	_tprintf(_T("%s"), s);
#endif
}

