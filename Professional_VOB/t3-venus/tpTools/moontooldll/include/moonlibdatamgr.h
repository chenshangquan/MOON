/*****************************************************************************
ģ����      : ������ص�cnclib����ģ��
�ļ���      : cnclibdatamgr.h
����ļ�    : cnclib.h
�ļ�ʵ�ֹ���: ת������cnclib����Ϣ���ṩ����cnclib�Ľӿ�
����        : ������
�汾        : V1.0  Copyright(C) 2011-2012 KDC, All rights reserved.
-----------------------------------------------------------------------------
�޸ļ�¼:
��  ��         �汾        �޸���      �޸�����
2012/11/23     1.0						����
******************************************************************************/
#include "moonToolDll.h"
#include "rkclib.h"
#include "msgdispatch.h"
#include "sessionmgr.h"

#ifndef CMOONLIBDATAMGR_H
#define CMOONLIBDATAMGR_H

class CMoonlibDataMgr : public CWnd
{
public:

	~CMoonlibDataMgr();
	/** ����   ��ʼ��CCnclibDataMgr��
	*  @param[out]
	*  @return 
	*/
	void InitDataMgr();
	       
    	
	/** ����   ���CCnclibDataMgr�����ָ��
	*  @param[in] 
	*  @return �ɹ�����CCnclibDataMgr���͵�ָ��
	*/
	static CMoonlibDataMgr* GetDataMgrIF();

	/**
	* ����:	��ȡ��¼cns��IP
	*  @param[in] u32  IP
	*  @return  
    */
	u16 GetLoginIp( u32 &dwIP )const;

	/** 
	* ����  ��ȡ���������
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamCfg( TTPMoonCamInfo &tMoonCameraCfg )const;

	u16 GetCamZoom( u32& dwZoom )const;

	u16 GetExtCamZoom( u32& dwZoomPos )const;

	/** 
	* ����  ��ȡ��ѡ�е������
	* @param [in] 	 
	* @return  �ɹ�����0,ʧ�ܷ��ط�0������
	*/		
	u16 GetCamSel( u8& byCameraIndx )const;

	/** 
	* ����  	��ȡ�ع�ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamMoonMode( EmTPMOOMMode& emExpMode )const;

	/** 
	* ����  	��ȡ��Ȧֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamAperture(EmTPAperture &emAper) const;

	/** 
	* ����  	��ȡ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 GetCamGain(EmTPExpGain &emGain) const;

	/** 
	* ����  	��ȡ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 GetCamShutSpd(EmTPSOrThShutter &emSOrThShutSpd) const;

	u16 GetTwCamShutSpd(EmTPFOrTwShutter &emFOrTwShutSpd) const;

	/** 
	* ���� ��ȡ��ɫ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 GetCamRGain(u32& dwRGain) const;

	/** 
	* ���� ��ȡ��ɫ����ֵ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/
	u16 GetCamBGain(u32& dwBGain) const;

	u16 GetCamAdjustRange(u32 &dwAdjustRange) const;

	u16 GetCamHoriStretch(u32 &dwHoriStretch) const;

	/** 
	* ���� ��ȡ��ƽ��ģʽ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetCamWBMode( EmTPMOOMMode& emWBMode )const;

	/** 
	* ���� ��ȡIP��Ϣ
	* @param [in] 	 
	* @return  
	* @remarks 
	*/	
	u16 GetEthnetCfg( TTPEthnetInfo &tEthnetInfo );

	TTPCamPre* GetCamPreInfo();


protected:
    virtual BOOL PreCreateWindow( CREATESTRUCT& cs );
    virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam); 
private:
	CMoonlibDataMgr();

private:
	static CMoonlibDataMgr* m_pThis;
};

#define MOONLIBDATAMGRPTR   CMoonlibDataMgr::GetDataMgrIF()

#endif