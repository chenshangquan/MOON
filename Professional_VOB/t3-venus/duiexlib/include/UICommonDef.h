/*****************************************************************************
ģ����      : UICommonDef
�ļ���      : UICommonDef.h
����ļ�    : 
�ļ�ʵ�ֹ���: ������й���Ԥ�����ļ�
����        : ����ӡ
�汾        : V1.0  Copyright(C) 2012-2013 KDV, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2013/5/26      1.0         ����ӡ      ����
******************************************************************************/
#ifndef _UICOMMONDEF_H_
#define _UICOMMONDEF_H_

namespace DuiLib {
	/////////////////////////////////////////////////////////////////////////////////////
	//
enum EM_TIMER_ID
{
	TIMER_ID_DRAGWNDLIST = 200,       //���CommonListUI������ק���ڶ�ʱ��    �յ�UP��KillTimer
	TIMER_ID_REDRAWPREVIEW,

};

#define IMAGE_FILE_EXT _T(".bmp.jpg.jpeg.png.gif.svg.tiff.emf.dib")   // ͼƬ���͵�ת��֧�֣�bmp��dib��png��gif��jpeg/jpg��tiff��emf��

#define SAFE_RELEASE( X ) { if( X ) { delete X; X = NULL; } }
#define SAFE_RELEASE_ARRAY( X ) { if( X ) { delete[] X; X = NULL; } }

};

#endif