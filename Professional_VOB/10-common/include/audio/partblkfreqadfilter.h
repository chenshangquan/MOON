/*****************************************************************************
ģ����      : PartBlkFreqAdFilter_fixed32
�ļ���      : PartBlkFreqAdFilter_fixed32.h
����ļ�    : 
�ļ�ʵ�ֹ���: ����AEC��Ƶ��ֿ�����Ӧ�˲���
�汾        : V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
����        : ��  ��
-----------------------------------------------------------------------------
�޸ļ�¼:
��    ��      �汾        �޸���      �޸�����
2005/03/18    1.0         ��  ��      ��    ��(fixed32�汾)
2005/06/03    2.0         ��  ��      �����
******************************************************************************/
#ifndef PARTBLKFREQADFILTER_H
#define PARTBLKFREQADFILTER_H

//Macro define
//�����������ؼ���Ķ���
#define FILTER_LEN		    4096	           //fullband filter length
#define SUB_FILTER_LEN		512		           //the partitional filter length

#define BLK_NUM	(FILTER_LEN/SUB_FILTER_LEN)	   //the partitional BLOCK NUMBER
#define SIGNAL_LEN		    SUB_FILTER_LEN     //the speech signal block length	
#define DFT_LEN     		(2*SIGNAL_LEN)     //the DFT data length

#define AD_FILT_OK       1
#define AD_FILT_ERR     -1

//�˲�������Ķ���
typedef struct TagFqAdFiltHd
{
	//part 1
	//size: DFT_LEN
	l32 *pl32TmZeroSig;    
	l32 *pl32TmFarSig;               //x(n)ʱ��Զ�������ź�buf
	l32 *pl32AvPower;                //ƽ������buf
	s16 *ps16TmErrSig;               //e(...n)
	
	
	
	//size: BLK*DFT_LEN
	l32 *pl32FqFarSigRe;             //X(N).Re 
	l32 *pl32FqFarSigIm;             //X(N).Im
	s16 *ps16FqWgtCoefRe;            //W(N).Re
	s16 *ps16FqWgtCoefIm;            //W(N).Im
	
	
	
	//part 2;
	u32 u32Counter;
	s16 s16Display;
	s16 s16Ncc;
	s16 s16DT;	
	
	
	//part 3
	//����double filter
	s16 (*pas16TmErrSig)[DFT_LEN];                  //ָ��ps16TmErrSig
	s16 (*paas16FqWgtCoefRe)[BLK_NUM][DFT_LEN];     //ָ��ps16FqWgtCoefRe
	s16 (*paas16FqWgtCoefIm)[BLK_NUM][DFT_LEN];     //ָ��ps16FqWgtCoefRe
	l32 (*pal32AvPower)[DFT_LEN];                   //ָ��pl32AvPower
	
	
}TFqAdFiltHd;


//Declare  of function

l32 InitFqAdFilterNew(void **ppAdFiltHd);
void FqAdFilterResetNew(TFqAdFiltHd *pFqAdFiltHd);

void FqAdFilterNew(TFqAdFiltHd *pHd, s16 *ps16FarSinal, \
				   s16 *ps16NearSinal,	s16 *ps16ErrSinal,\
				   s16 *ps16OutSinal);

void FreeFqAdFilterNew(void *pHd);

#endif //end of PARTBLKFREQADFILTER_H
