/*****************************************************************************
   ģ����      : ���ǳ�������
   �ļ���      : satconst.h
   ����ļ�    : satmtstrc.cpp
   �ļ�����    : 
   ����        : ������
   �汾        : V1.0  Copyright(C) 2001-2002 KDC, All rights reserved.
-----------------------------------------------------------------------------
   �޸ļ�¼:
   ��  ��      �汾        �޸���      �޸�����
   2004/11/02  1.0         ������      ����
******************************************************************************/

#ifndef _SAT_CONST_H_
#define _SAT_CONST_H_

#include "kdvsys.h"

#define MAXLEN_SATMTALIAS     16
#define MAXNUM_SATMT         1024//����ն���
#define MAXNUM_CONFLIST       16

//��Ƶ�ŵ�����
#define SAT_AUDIO_G711A			 1	//g711alaw
#define SAT_AUDIO_G711U			 2	//g911ulaw
#define SAT_AUDIO_G722			3
#define SAT_AUDIO_G7231			 4	//g7231
#define SAT_AUDIO_G728			 5	//g728
#define SAT_AUDIO_G729			 6	//g728
#define SAT_AUDIO_MP3			 7	//mp3
#define SAT_AUDIO_G7221C         8
//��Ƶ�ŵ�����
#define SAT_VIDEO_H261			 1	//h261
#define SAT_VIDEO_H263			 2	//h263
#define SAT_VIDEO_H264			 3	//h263
#define SAT_VIDEO_MPEG2			 4	//mpeg4
#define SAT_VIDEO_MPEG4			 5	//mpeg4
//�����ŵ�����
#define DATA_T120			 201	//t120
//�ֱ���
/*#define TYPE_CIF			 1
#define TYPE_2CIF			 2
#define TYPE_4CIF			 3
*/

#define     TYPE_RES_INVALID				0
#define		TYPE_QCIF				1
#define		TYPE_CIF				2
#define		TYPE_2CIF				3
#define		TYPE_4CIF				4
#define		TYPE_16CIF				5
#define		TYPE_SQCIF				6
#define     TYPE_720P				7
#define     TYPE_1080P				8



//����ϳɷ�ʽ����--�ն˱������
#define   CONF_VMPMODE_NONE                0  //�����л���ϳ�
#define   CONF_VMPMODE_CTRL                1  //��ػ���ϯѡ���Ա�ϳ�
//����ϳɷ����
#define VMP_TYPE_ONE        1 //������
#define VMP_TYPE_VTWO       2 //�����棺���ҷ�
#define VMP_TYPE_THREE      3//������
#define VMP_TYPE_FOUR       4//�Ļ��棺�ȴ�
#define VMP_TYPE_ITWO       5//�����棺 һ��һС
#define VMP_TYPE_SFOUR      6//�Ļ��棺һ����С
#define VMP_TYPE_SIX        7//������

//ʹ�ܽ�ֹ 
#define KDV_AUTO                   0 //���ݵ�ǰʹ�ܴ��� 
#define KDV_ENABLE		   1 //ʹ��
#define KDV_DISABLE		   2 //��ֹ
//������ʽ����
#define FOCUS_AUTO			1		//�Զ�����
#define FOCUS_MANUAL			2		//�ֶ�����
#define FOCUS_STOP			4		//ֹͣ����

//����������
#define	DIRECT_FAR			2		//��Զ
#define	DIRECT_NEAR			3		//����

//�˶�������
#define	DIRECT_UP			1		//��	
#define	DIRECT_DOWN			2		//��
#define	DIRECT_LEFT			3		//��
#define DIRECT_RIGHT			4		//��
#define	DIRECT_UPLEFT			5		//����
#define	DIRECT_UPRIGHT			6		//����
#define	DIRECT_DOWNLEFT			7		//����
#define	DIRECT_DOWNRIGHT		8		//����
#define DIRECT_HOME			9		//�ص�����ƽ��λ��
#define	DIRECT_STOP			10		//ֹͣת��

//��Ұ���ڷ�ʽ����
#define	DIRECT_TELE			1		//��С����ͷ����
#define	DIRECT_WIDE			2		//���󣬾�ͷ��Զ

//������ɾ
#define BACKLIGHT_ON			1		//���ϱ���
#define BACKLIGHT_OFF			2		//ȥ������

//�������ȵ���
#define BRIGHT_UP			1		//����
#define	BRIGHT_DOWN			2		//����
#define BRIGHT_RESET			3		//����
#define  CAM_PANTILT_CMD		1		//����ͷ�ƶ�
#define  CAM_FOCUS_CMD			2		//����ͷ�۽�
#define  CAM_ZOOM_CMD			3		//����ͷ��Ұ
#define  CAM_BRIGHT_CMD			4		//����ͷ����
#define  CAM_PRESET_SAVE_CMD	5		//Ԥ��λ����
#define  CAM_PRESET_MOVE_CMD	6		//Ԥ��λ�ƶ�



#endif //!_SAT_CONST_H_