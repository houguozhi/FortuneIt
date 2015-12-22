#pragma once

template <class IntType>
class CHgzFormatTransformer
{
public:
	CHgzFormatTransformer(void){};
	~CHgzFormatTransformer(void){};

	// һ����ԣ�����һ�������ĵ�ַ�������ͨ��ϰ�ߴӵ͵�ַ�˿�ʼ���ʡ�
	// Endian ָ����һ��������ַ�ĵ͵�ַ�ˣ���ˣ�
	// Lendian -- Little-Endian, ��λ�ֽ��ŷ����ڴ�ĵ͵�ַ�ˣ���λ�ֽ��ŷ����ڴ�ĸߵ�ַ�ˡ�
	// Bendian -- Big-Endian,    ��λ�ֽ��ŷ����ڴ�ĵ͵�ַ�ˣ���λ�ֽ��ŷ����ڴ�ĸߵ�ַ�ˡ�


///////////////////////////////////////////////////////////////
	// UINT2ByteArray
	/** 
	* ��intתΪ��byte���� int32 -> Lendian ���� ByteLE
	* @param n int 
	* @return byte[] 
	*/  
	
	//template <class IntType>
	BOOL UInt_to_ByteArrayLE(IntType n, CByteArray& b) 
	{  
		int size = sizeof(IntType);
		b.SetSize(size);

		for (int i = 0; i < size; i++)
			b[i] = (byte) ((n>>(8*i)) & 0xff);

		return 1;  
	}

	BOOL UInt8_to_ByteArrayLE(__int8 n, CByteArray& b) 
	{  
		b.SetSize(1);

		b[0] = (byte) n;  

		return 1;  
	}
	
	BOOL UInt16_to_ByteArrayLE(__int16 n, CByteArray& b) 
	{  
		b.SetSize(2);

		b[0] = (byte) ((n)		& 0xff);  
		b[1] = (byte) ((n>>8)	& 0xff);  

		return 1;  
	}

	BOOL UInt32_to_ByteArrayLE(__int32 n, CByteArray& b) 
	{  
		b.SetSize(4);

		b[0] = (byte) ((n)		& 0xff);  
		b[1] = (byte) ((n>>8)	& 0xff);  
		b[2] = (byte) ((n>>16)	& 0xff);  
		b[3] = (byte) ((n>>24)	& 0xff);  

		return 1;  
	}

	BOOL UInt64_to_ByteArrayLE(__int64 n, CByteArray& b) 
	{  
		b.SetSize(8);

		b[0] = (byte) ((n)		& 0xff);
		b[1] = (byte) ((n>>8)	& 0xff); 
		b[2] = (byte) ((n>>16)	& 0xff);  
		b[3] = (byte) ((n>>24)	& 0xff);  
		b[4] = (byte) ((n>>32)	& 0xff);
		b[5] = (byte) ((n>>40)	& 0xff); 
		b[6] = (byte) ((n>>48)	& 0xff);  
		b[7] = (byte) ((n>>56)	& 0xff);  

		return 1;  
	}



	////////////////////////////////////////////////////
	//template <class IntType>
	BOOL UInt_to_ByteArrayBE(IntType n, CByteArray& b) 
	{  
		int size = sizeof(IntType);
		b.SetSize(size);

		for (int i = 0; i < size; i++)
			b[i] = (byte) ((n>>(8*(size-1-i))) & 0xff);

		return 1;  
	}

	BOOL UInt8_to_ByteArrayBE(__int8 n, CByteArray& b) 
	{  
		b.SetSize(1);

		b[0] = (byte) n;  

		return 1;  
	}

	BOOL UInt16_to_ByteArrayBE(__int16 n, CByteArray& b) 
	{  
		b.SetSize(2);

		b[1] = (byte) ((n)		& 0xff);
		b[0] = (byte) ((n>>8)	& 0xff); 

		return 1;  
	}

	BOOL UInt32_to_ByteArrayBE(__int32 n, CByteArray& b) 
	{  
		b.SetSize(4);

		b[3] = (byte) ((n)		& 0xff);
		b[2] = (byte) ((n>>8)	& 0xff); 
		b[1] = (byte) ((n>>16)	& 0xff);  
		b[0] = (byte) ((n>>24)	& 0xff);
		
		return 1;  
	}

	BOOL UInt64_to_ByteArrayBE(__int64 n, CByteArray& b) 
	{  
		b.SetSize(8);

		b[7] = (byte) ((n)		& 0xff);
		b[6] = (byte) ((n>>8)	& 0xff);
		b[5] = (byte) ((n>>16)	& 0xff);
		b[4] = (byte) ((n>>24)	& 0xff);
		b[3] = (byte) ((n>>32)	& 0xff);
		b[2] = (byte) ((n>>40)	& 0xff);
		b[1] = (byte) ((n>>48)	& 0xff);
		b[0] = (byte) ((n>>56)	& 0xff);

		return 1;  
	}



/////////////////////////////////////////////////////////
	// ByteArray2UINT

	//template <class IntType>
	IntType ByteArrayLE_to_UInt(CByteArray& b) 
	{  
		IntType n = 0;
		int size = min(sizeof(IntType), b.GetSize());

		for (int i = 0; i < size; i++)
			n += ((IntType)b[i]<<(8*i));

		return n;  
	}

	//template <class IntType>
	IntType ByteArrayBE_to_UInt(CByteArray& b) 
	{  
		IntType n = 0;
		int size = min(sizeof(IntType), b.GetSize());

		for (int i = 0; i < size; i++)
			n += ((IntType)b[i]<<(8*(size-1-i))); // ע�⣺����� b[i] ����ǿ������ת��������b[i] ��ֵ�ᱻ��Ϊ 32 λ����ֵ������λ����������λλ������ 32 λ���ͻ�ѭ������ͷλ�ã����ֳ������ϵĽ��������һ�������׷������� bug��

		return n;  
	}

/////////////////////////////////////////////////////////
	// Bytes2UINT

	//template <class IntType>
	IntType BytesLE_to_UInt(BYTE *b, int bsize) 
	{
		IntType n = 0;
		int size = min(sizeof(IntType), bsize);

		for (int i = 0; i < size; i++)
			n += ((IntType)b[i]<<(8*i));

		return n;
	}

	//template <class IntType>
	IntType BytesBE_to_UInt(BYTE *b, int bsize) 
	{
		IntType n = 0;
		int size = min(sizeof(IntType), bsize);

		for (int i = 0; i < size; i++)
			n += ((IntType)b[i]<<(8*(size-1-i))); // ע�⣺����� b[i] ����ǿ������ת��������b[i] ��ֵ�ᱻ��Ϊ 32 λ����ֵ������λ����������λλ������ 32 λ���ͻ�ѭ������ͷλ�ã����ֳ������ϵĽ��������һ�������׷������� bug��

		return n;
	}

/////////////////////////////////////////////////////////
	// Bytes2CString
	void Bytes_to_CString(BYTE *b, CString& s, int size)
	{
		// ��ʾ�ֽ������ǰ size ���ֽڣ��� b[0] �� b[size-1] ˳����ʾ
		if (size) s.Format(_T("%02x"), b[0]);
		else s.Format(_T(""));
		for (int i = 1; i < size; i++)
			s.AppendFormat(_T(" %02x"), b[i]);
	}
	
	// ByteArray2CString
	void ByteArray_to_CString(CByteArray& b, CString& s, int size)
	{
		ASSERT(size <= b.GetSize());

		// ��ʾ�ֽ������ǰ size ���ֽڣ��� b[0] �� b[size-1] ˳����ʾ
		if (size) s.Format(_T("%02x"), b[0]);
		else s.Format(_T(""));
		for (int i = 1; i < size; i++)
			s.AppendFormat(_T(" %02x"), b[i]);
	}
	
	// UINT2CString
	void UInt_to_CString(IntType n, CString& s, int size)
	{
		ASSERT(size <= sizeof(IntType));

		CByteArray b;
		UInt_to_ByteArrayLE(n, b); // С���ֽ������ڴ洢���Ϸ��㣬����������˵��ֱ�ۣ����Դ����ʾ�ַ�����
		if (size) s.Format(_T("%02x"), b[size-1]);
		else s.Format(_T(""));
		for (int i = size-2; i >= 0; i--)
			s.AppendFormat(_T(" %02x"), b[i]);
	}







};

