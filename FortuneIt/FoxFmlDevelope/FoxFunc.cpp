// FoxFunc.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "FoxFunc.h"

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

//计算收盘价的均价,一个常数参数,表示计算周期
//调用方法:
//	"FOXFUNC@MYMACLOSE"(5)

__declspec(dllexport) int WINAPI MYMACLOSE(CALCINFO* pData)
{
	if ( pData->m_pfParam1 &&				//参数1有效
		 pData->m_nParam1Start<0 &&			//参数1为常数
		 pData->m_pfParam2==NULL )			//仅有一个参数
	{
		float fParam = *pData->m_pfParam1;
		int nPeriod = (int)fParam;			//参数1
		if(nPeriod>0)
		{
			float fTotal;
			int i, j;
			for ( i = nPeriod-1; i < pData->m_nNumData; i++ )//计算nPeriod周期的均线,数据从nPeriod-1开始有效
			{
				fTotal = 0.0f;
				for ( j = 0; j < nPeriod; j++ )				//累加
					fTotal += pData->m_pData[i-j].m_fClose;
				pData->m_pResultBuf[i] = fTotal/nPeriod;	//平均
			}
			return nPeriod-1;
		}
	}
	return -1;
}

//计算均价,2个参数,参数1为待求均线的数据,参数2表示计算周期
//调用方法:
//	"FOXFUNC@MYMAVAR"(CLOSE-OPEN,5)

__declspec(dllexport) int WINAPI MYMAVAR(CALCINFO* pData)
{
	if(pData->m_pfParam1 && pData->m_pfParam2 && 	//参数1,2有效
		pData->m_nParam1Start>=0 &&					//参数1为序列数
		pData->m_pfParam3==NULL)					//有2个参数
	{
		const float*  pValue = pData->m_pfParam1;	//参数1
		int nFirst = pData->m_nParam1Start;			//有效值起始位
		float fParam = *pData->m_pfParam2;			//参数2
		int nPeriod = (int)fParam;			

		if( nFirst >= 0 && nPeriod > 0 )
		{
			float fTotal;
			int i, j;
			for ( i = nFirst+nPeriod-1; i < pData->m_nNumData; i++ )
			{
				fTotal = 0.0f;
				for ( j=0; j < nPeriod; j++ )			//累加
					fTotal += pValue[i-j];
				pData->m_pResultBuf[i] = fTotal/nPeriod;//平均
			}
			return nFirst+nPeriod-1;
		}
	}
	return -1;
}

//计算多个序列的均值,5个参数,参数1-4为待求多个序列,参数5用于举例说明数值参数的用法，实际在此例中无需该参数
/*
调用方法:
	MA1:=MA(CLOSE,3);
	MA2:=MA(CLOSE,6);
	MA3:=MA(CLOSE,12);
	MA4:=MA(CLOSE,24);
	MYBBI: "FOXFUNC@MYBBI"(MA1, MA2, MA3, MA4, 4);
*/

__declspec(dllexport) int WINAPI MYBBI(CALCINFO* pData)
{
	if ( pData->m_pCalcParam[0].m_nParamStart >= 0 &&
		 pData->m_pCalcParam[1].m_nParamStart >= 0 &&
		 pData->m_pCalcParam[2].m_nParamStart >= 0 &&
		 pData->m_pCalcParam[3].m_nParamStart >= 0 )			//4个序列都含有效数值
	{
		//计算返回的序列的第一个有效值位置
		int nFirst = pData->m_pCalcParam[3].m_nParamStart;		//已知返回的序列的第一个有效值位置与第4个序列一致
//若不知，则
/*
		int nFirst = pData->m_pCalcParam[0].m_nParamStart;
		if ( nFirst < pData->m_pCalcParam[1].m_nParamStart ) 
			nFirst = pData->m_pCalcParam[1].m_nParamStart;
		if ( nFirst < pData->m_pCalcParam[2].m_nParamStart ) 
			nFirst = pData->m_pCalcParam[2].m_nParamStart;
		if ( nFirst < pData->m_pCalcParam[3].m_nParamStart ) 
			nFirst = pData->m_pCalcParam[3].m_nParamStart;
 */

		const float* pValue1 = pData->m_pCalcParam[0].m_pfParam;
		const float* pValue2 = pData->m_pCalcParam[1].m_pfParam;
		const float* pValue3 = pData->m_pCalcParam[2].m_pfParam;
		const float* pValue4 = pData->m_pCalcParam[3].m_pfParam;
		int nNum = (int)(pData->m_pCalcParam[4].m_fParam);		//实际上该例中已知nNum=4，在此用于说明数值参数的用法
		for( int i = nFirst; i < pData->m_nNumData; i++ )
		{
			pData->m_pResultBuf[i] = 
				(pValue1[i] + pValue2[i] + pValue3[i] + pValue4[i])/nNum;
		}
		return nFirst;
	}
	return -1;
}

