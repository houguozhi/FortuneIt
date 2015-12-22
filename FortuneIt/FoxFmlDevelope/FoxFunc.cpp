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

//�������̼۵ľ���,һ����������,��ʾ��������
//���÷���:
//	"FOXFUNC@MYMACLOSE"(5)

__declspec(dllexport) int WINAPI MYMACLOSE(CALCINFO* pData)
{
	if ( pData->m_pfParam1 &&				//����1��Ч
		 pData->m_nParam1Start<0 &&			//����1Ϊ����
		 pData->m_pfParam2==NULL )			//����һ������
	{
		float fParam = *pData->m_pfParam1;
		int nPeriod = (int)fParam;			//����1
		if(nPeriod>0)
		{
			float fTotal;
			int i, j;
			for ( i = nPeriod-1; i < pData->m_nNumData; i++ )//����nPeriod���ڵľ���,���ݴ�nPeriod-1��ʼ��Ч
			{
				fTotal = 0.0f;
				for ( j = 0; j < nPeriod; j++ )				//�ۼ�
					fTotal += pData->m_pData[i-j].m_fClose;
				pData->m_pResultBuf[i] = fTotal/nPeriod;	//ƽ��
			}
			return nPeriod-1;
		}
	}
	return -1;
}

//�������,2������,����1Ϊ������ߵ�����,����2��ʾ��������
//���÷���:
//	"FOXFUNC@MYMAVAR"(CLOSE-OPEN,5)

__declspec(dllexport) int WINAPI MYMAVAR(CALCINFO* pData)
{
	if(pData->m_pfParam1 && pData->m_pfParam2 && 	//����1,2��Ч
		pData->m_nParam1Start>=0 &&					//����1Ϊ������
		pData->m_pfParam3==NULL)					//��2������
	{
		const float*  pValue = pData->m_pfParam1;	//����1
		int nFirst = pData->m_nParam1Start;			//��Чֵ��ʼλ
		float fParam = *pData->m_pfParam2;			//����2
		int nPeriod = (int)fParam;			

		if( nFirst >= 0 && nPeriod > 0 )
		{
			float fTotal;
			int i, j;
			for ( i = nFirst+nPeriod-1; i < pData->m_nNumData; i++ )
			{
				fTotal = 0.0f;
				for ( j=0; j < nPeriod; j++ )			//�ۼ�
					fTotal += pValue[i-j];
				pData->m_pResultBuf[i] = fTotal/nPeriod;//ƽ��
			}
			return nFirst+nPeriod-1;
		}
	}
	return -1;
}

//���������еľ�ֵ,5������,����1-4Ϊ����������,����5���ھ���˵����ֵ�������÷���ʵ���ڴ���������ò���
/*
���÷���:
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
		 pData->m_pCalcParam[3].m_nParamStart >= 0 )			//4�����ж�����Ч��ֵ
	{
		//���㷵�ص����еĵ�һ����Чֵλ��
		int nFirst = pData->m_pCalcParam[3].m_nParamStart;		//��֪���ص����еĵ�һ����Чֵλ�����4������һ��
//����֪����
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
		int nNum = (int)(pData->m_pCalcParam[4].m_fParam);		//ʵ���ϸ�������֪nNum=4���ڴ�����˵����ֵ�������÷�
		for( int i = nFirst; i < pData->m_nNumData; i++ )
		{
			pData->m_pResultBuf[i] = 
				(pValue1[i] + pValue2[i] + pValue3[i] + pValue4[i])/nNum;
		}
		return nFirst;
	}
	return -1;
}

