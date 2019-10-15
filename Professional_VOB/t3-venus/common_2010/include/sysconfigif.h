/*****************************************************************************
ģ����      : moon90 moonlib�ӿ�
�ļ���      : sysconfigif.h
����ļ�    : 
�ļ�ʵ�ֹ���: ϵͳ����
����        : ���`�`
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��      �汾        �޸���      �޸�����
2014/11/26  1.0         ���`�`        ����
******************************************************************************/
#ifndef __SYSCONFIGIF_H__
#define __SYSCONFIGIF_H__

#include "kdvdispevent.h"
#include "moonstruct.h"
#include <vector>

class CSysConfigIF : public CKdvDispEvent
{
public:

	/** ����   �����������
	 *  @return tagTTPEthnetInfo ����������Ϣ
	 */
	virtual const TTPEthnetInfo& GetEthnetCfg() const = 0;

	/** ����   ��Ƶ�����ʽ����
	 *  @return tagTTPEthnetInfo ����������Ϣ
	 */
	virtual u16 SetOutPortTypeCmd( EmTPDVIOutPortType emDVIOutPortType, EmTPMOONOutMode emMOONOutMode ) = 0;

	/** ����   ͼƬ��ת��ʽ����
	 *  @return tagTTPEthnetInfo ����������Ϣ
	 */
	virtual u16 SetImageAdjustCmd( EmTPImageAdjust emImageAdjust ) = 0;

	/** ����   ������������
	 *  @param[in] cfg ��������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 UpdateEthnetCfg( const TTPEthnetInfo& cfg ) = 0;
	/** ����   ����LVDS������
	 *  @param[in] emBaudRate ������
	 *  @return �ɹ�����0,ʧ�ܷ��ط�0������
	 *  @remarks 
	 */
	virtual u16 SetBaudRateCmd( EmTPLVDSBaud emBaudRate ) = 0;
};

#endif