/*****************************************************************************
ģ����      : g728�������
�ļ���      : g728.h
����ļ�    : 
�ļ�ʵ�ֹ���: g728����빦�ܾ��ʽ�ӿ�����
�汾        : V1.0  Copyright(C) 2005-2007 KDC, All rights reserved.
����        : �쳬
-----------------------------------------------------------------------------
�޸ļ�¼:
��    ��      �汾        �޸���      �޸�����
2006/04/30    1.0         ��  ��      �淶����
******************************************************************************/
#ifndef G728_H
#define G728_H

#ifdef __CPLUSPLUS
extern "C" {
#endif

// external interface declaration

// macro definitions
#define G728_OK   0
#define G728_ERR -1
#define HG728    void *

int  g728_encinit(HG728* encptr);
int  g728_decinit(HG728* decptr);

int  g728_encode(HG728 pG728,
				 short* EncIn,
				 int inputlengthinbyte,	//����40��������
				 unsigned char* encbitstream);
int  g728_decode(HG728 pG728,
				 unsigned char* decbitstream,
				 int inputlengthinbyte,	//����5��������
				 short* DecOut);

void g728_encfree(HG728 encptr);
void g728_decfree(HG728 decptr);
void  GetG728Version(char *Version, int StrLen, int * StrLenUsed);

#ifdef __CPLUSPLUS
}
#endif

#endif /*G728_H*/

