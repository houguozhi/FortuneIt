#pragma once

template <class IntType>
class CHgzFormatTransformer
{
public:
	CHgzFormatTransformer(void){};
	~CHgzFormatTransformer(void){};

	// 一般而言，对于一段连续的地址，计算机通常习惯从低地址端开始访问。
	// Endian 指的是一段连续地址的低地址端，因此：
	// Lendian -- Little-Endian, 低位字节排放在内存的低地址端，高位字节排放在内存的高地址端。
	// Bendian -- Big-Endian,    高位字节排放在内存的低地址端，低位字节排放在内存的高地址端。


///////////////////////////////////////////////////////////////
	// UINT2ByteArray
	/** 
	* 将int转为的byte数组 int32 -> Lendian 数组 ByteLE
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
			n += ((IntType)b[i]<<(8*(size-1-i))); // 注意：必须对 b[i] 进行强制类型转换。否则，b[i] 的值会被作为 32 位整型值进行移位操作，若移位位数大于 32 位，就会循环至开头位置，出现出人意料的结果。这是一个很容易犯的隐蔽 bug。

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
			n += ((IntType)b[i]<<(8*(size-1-i))); // 注意：必须对 b[i] 进行强制类型转换。否则，b[i] 的值会被作为 32 位整型值进行移位操作，若移位位数大于 32 位，就会循环至开头位置，出现出人意料的结果。这是一个很容易犯的隐蔽 bug。

		return n;
	}

/////////////////////////////////////////////////////////
	// Bytes2CString
	void Bytes_to_CString(BYTE *b, CString& s, int size)
	{
		// 显示字节数组的前 size 个字节：以 b[0] 至 b[size-1] 顺序显示
		if (size) s.Format(_T("%02x"), b[0]);
		else s.Format(_T(""));
		for (int i = 1; i < size; i++)
			s.AppendFormat(_T(" %02x"), b[i]);
	}
	
	// ByteArray2CString
	void ByteArray_to_CString(CByteArray& b, CString& s, int size)
	{
		ASSERT(size <= b.GetSize());

		// 显示字节数组的前 size 个字节：以 b[0] 至 b[size-1] 顺序显示
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
		UInt_to_ByteArrayLE(n, b); // 小端字节序用于存储均较方便，但对于人来说不直观，故以大端显示字符串。
		if (size) s.Format(_T("%02x"), b[size-1]);
		else s.Format(_T(""));
		for (int i = size-2; i >= 0; i--)
			s.AppendFormat(_T(" %02x"), b[i]);
	}







};

