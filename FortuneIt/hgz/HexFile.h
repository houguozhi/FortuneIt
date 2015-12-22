#ifndef HexFile_h__
#define HexFile_h__

#include "hgz.h"




typedef enum {
	HEX_REC_DAT = 0, // Data Record
	HEX_REC_EOF = 1, // End of File Record
	HEX_REC_ESA = 2, // Extended Segment Address Record
	HEX_REC_SSA = 3, // Start Segment Address Record
	HEX_REC_ELA = 4, // Extended Linear Address Record
	HEX_REC_SLA = 5  // Start Linear Address Record
} HEXRECTYPE_t;

typedef struct {
	unsigned char recmark;
	unsigned char reclen;
	unsigned char addrh;
	unsigned char addrl;
	unsigned char rectype;
	unsigned char data[256];

	unsigned char checksum() {
		data[reclen] = reclen + addrh + addrl + rectype;
		for (unsigned int i = 0; i < reclen; i++){
			data[reclen] += data[i];
		}
		data[reclen] = ~data[reclen] + 1;
		return data[reclen];
	};
} HEXRECORD_t; 

/*typedef struct {
	CString recmark;
	CString reclen;
	CString address;
	CString rectype;
	CString data;
} HEXRECORDSTRING_t;*/


void HexRec(HEXRECORD_t & hr, HEXRECTYPE_t rectype, unsigned char reclen, unsigned int addr, unsigned char *buf);
void HexRecPrint( HEXRECORD_t &hr );
bool HexRecReadFromFile( unsigned char *buf, unsigned char *buf_flag, CStdioFile &mFile, HEXRECORD_t &hr, unsigned int &cur_addr );
void HexRecSaveToFile( HEXRECORD_t &hr, CStdioFile &mFile );


#endif // HexFile_h__
