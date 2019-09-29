#ifndef MT_EXTEND_EVENT_H
#define MT_EXTEND_EVENT_H
#include "eventcomm.h"

#ifndef _MakeMtEventDescription_
enum EmMtExtend
{
#endif 
   _ev_segment( extend ) //��չ���ⲿ��Ϣ

/***********************<<  ����WiFi����������Ŀ���� >>********************	
 *[��Ϣ��]
 * + TWiFiBSSIDCfg , 1 //WiFi����������Ŀ���ýṹ
 *  
 *[��Ϣ����]
 *   UI => mtservice 
 */_event( ev_WiFiCfgAddItemCmd )
   _body( TWiFiBSSIDCfg, 1 )
   _ev_end


/***********************<<  ɾ��WiFi����������Ŀ���� >>********************	
 *[��Ϣ��]
 * + TWiFiBSSIDCfg , 1 //WiFi����������Ŀ���ýṹ
 *  
 *[��Ϣ����]
 *   UI => mtservice 
 */_event( ev_WiFiCfgDelItemCmd )
   _body( TWiFiBSSIDCfg, 1 )
   _ev_end
   
/***********************<<  �޸�WiFi����������Ŀ���� >>********************	
 *[��Ϣ��]
 * + u32 , 1 //��Ŀ���� 
 * + TWiFiBSSIDCfg , 1 //WiFi����������Ŀ���ýṹ
 *  
 *[��Ϣ����]
 *   UI => mtservice 
 */_event( ev_WiFiCfgModifyItemCmd )
   _body( u32, 1 )
   _body( TWiFiBSSIDCfg, 1 )
   _ev_end

/***********************<< ����WiFi�������� >>********************	
 *[��Ϣ��]
 * + TWiFiBSSIDInfo , 1 //WiFi��������ɨ��ṹ
 *  
 *[��Ϣ����]
 *   UI => mtservice 
 */_event( ev_WiFiConnectCmd )
   _body( TWiFiBSSIDInfo, 1 )
   _ev_end
   
   
/***********************<< �Ͽ�WiFi�������� >>********************	
 *[��Ϣ��]
 *  + ��
 *  
 *[��Ϣ����]
 *   UI  => mtservice 
 */_event( ev_WiFiDisConnectCmd )
   _ev_end
   

/***********************<< WiFi��������״ָ̬ʾ >>********************	
 *[��Ϣ��]
 *  + TWifiLinkCfgItem , 1 //WiFi��������״̬�ṹ
 *  
 *[��Ϣ����]
 *   mtservice  => UI 
 */_event( ev_WiFiLinkStatInd  )
   _body ( TWifiLinkCfgItem, 1 )
   _ev_end


/***********************<< ��ȡWiFi��������״̬���� >>********************	
 *[��Ϣ��]
 *  + ��
 *  
 *[��Ϣ����]
 *   UI  => mtservice 
 */_event( ev_WiFiGetLinkStatCmd )
   _ev_end


/***********************<< WiFi������������ָʾ >>********************	
 *[��Ϣ��]
 *  + TWiFiBSSIDCfg , MT_WIFI_MAX_BSSIDCFG_NUM //WiFi�����������ýṹ
 *  
 *[��Ϣ����]
 *   mtservice  => UI
 */_event( ev_WiFiCfgInd )
   _body ( TWiFiBSSIDCfg, MT_WIFI_MAX_BSSIDCFG_NUM )
   _ev_end


/***********************<< WiFi����ɨ������ >>********************	
 *[��Ϣ��]
 *  + ��
 *  
 *[��Ϣ����]
 *   UI  => mtservice 
 */_event( ev_WiFiScanBSSCmd )
   _ev_end


/***********************<< WiFi����ɨ����ָʾ >>********************	
 *[��Ϣ��]
 *  + TWiFiBSSIDInfo , MT_WIFI_MAX_BSSIDCFG_NUM //WiFi��������ɨ��ṹ
 *  
 *[��Ϣ����]
 *   mtservice  => UI 
 */_event( ev_WiFiScanBSSInd )
   _body ( TWiFiBSSIDInfo, MT_WIFI_MAX_BSSIDCFG_NUM )
   _ev_end

   
/***********************<< ����ǽ������������ָʾ >>**********************	
 *[��Ϣ��]	
 *    + u8        0-�ɹ� 1-��ʱ 2-δ�ҵ� 3-ʧ��
 *[��Ϣ����]
 *    UI <= MtService
 */_event(  ev_FwProxyDomainReqInd  )
   _body( u8        ,1 )
   _ev_end

/***********************<< MTC PC �ֱ���ָʾ >>********************	
 *[��Ϣ��]
 *  
 *[��Ϣ����]
 *   MT  <=> MTC
 */_event(   ev_MTCVideoResInd )
   _body( EmVideoResolution , 1 )
   _ev_end

/***********************<<  �����������Ŷ˿�    >>********************	
 *[��Ϣ��]			 
 *     +EmVideoType first video or second video
 *      u32 : PORT_MASK
 *[��Ϣ����]
 *    MtService = >MtMP
 */_event( ev_SetCodecVideoOutCmd  )
   _body ( EmVideoType   ,1)
   _body ( u32   ,1)
   _ev_end

/***********************<<  ������������˿�    >>********************	
 *[��Ϣ��]			 
 *     +EmVideoType first video or second video
 *      u32 : PORT_MASK
 *[��Ϣ����]
 *    MtService = >MtMP
 */_event( ev_SetCodecVideoInCmd  )
   _body ( EmVideoType   ,1)
   _body ( u32   ,1)
   _ev_end


/***********************<<  ָʾ��ǰ�ľ�������    >>********************	
 *[��Ϣ��]			 
 *     +EmVideoType first video or second video
 *      u32 : PORT_MASK
 *[��Ϣ����]
 *    MtService = >MtMP
 */_event( ev_CurMatrixInd  )
   _body ( TVInnerMatrixScheme   ,1)
   _ev_end


/***********************<<  ������Ƶ�˿�ѡ������    >>********************	
 *[��Ϣ��]			 
 *     +THdAudioPort  ��Ƶ�˿�
 *[��Ϣ����]
 *    UI/MTC => MtService => MTMP_HD
 */_event( ev_CfgHDAudioPortCmd  )
   _body ( THdAudioPort   ,1)
   _ev_end

/***********************<<  ������Ƶ�˿�ѡ��ָʾ    >>********************	
 *[��Ϣ��]			 
 *     +THdAudioPort  ��Ƶ�˿�
 *[��Ϣ����]
 *    UI/MTC <= MtService
 */_event( ev_CfgHDAudioPortInd  )
   _body ( THdAudioPort   ,1)
   _ev_end

/***********************<<  �а���������    >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ��а�����
 *[��Ϣ����]
 *    UI/MTC => MtService => MTMP_HD
 */_event( ev_CfgUseSliceCmd  )
   _body ( BOOL   ,1)
   _ev_end

/***********************<<  �а�����ָʾ    >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ��а�����
 *[��Ϣ����]
 *    UI/MTC <= MtService
 */_event( ev_CfgUseSliceInd  )
   _body ( BOOL   ,1)
   _ev_end

/***********************<<  AAC��Ƶ���ò���    >>********************	
 *[��Ϣ��]			 
 *     +EmCodecComponent	��Ƶ����
 *     +u8		            ͨ��������0--7, ����6��ʾ5.1����, 7��ʾ7.1������
 *     +u32					����������0��ʾ��Ч��
 *	   +u16					���ʣ�Ŀǰδ���壩
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CodecAudAacParamCmd  )
   _body ( EmCodecComponent		,1 )
   _body ( u8                   ,1 )
   _body ( u32                  ,1 )
   _body ( u16                  ,1 )
   _ev_end

/***********************<<  ����ͼ�������������  >>********************	
 *[��Ϣ��]			 
 *     +TImageAdjustParam	���ڸ���Ŀǰ����������
 *[��Ϣ����]
 *    MtService <= MTC/MTMP
 */_event( ev_CfgHDImageParamCmd  )
   _body( TImageAdjustParam     ,MT_HD_IMAGE_PARAM_COUNT )
   _ev_end

/***********************<<  ����ͼ���������ָʾ  >>********************	
 *[��Ϣ��]			 
 *     +TImageAdjustParam	���ڸ���Ŀǰ����������
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CfgHDImageParamInd  )
   _body( TImageAdjustParam     ,MT_HD_IMAGE_PARAM_COUNT )
   _ev_end

/***********************<<  ����ģʽ������������  >>********************	
 *[��Ϣ��]			 
 *     +TImageAdjustParam	���ڸ���Ŀǰ����������
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CfgScreenModeCmd  )
   _body( u8     , 1 )
   _ev_end

/***********************<<  ����ͼ���������ָʾ  >>********************	
 *[��Ϣ��]			 
 *     +TImageAdjustParam	���ڸ���Ŀǰ����������
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CfgScreenModeInd  )
   _body( u8     , 1 )
   _ev_end

/***********************<<  ����DVI������������  >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ�����DVI������ӿ�
 *[��Ϣ����]
 *    MtService <= MTC/MTMP
 */_event( ev_CfgHDDVIParamCmd  )
   _body( BOOL     , 1 )
   _ev_end

/***********************<<  ����DVI��������ָʾ  >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ�����DVI������ӿ�
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CfgHDDVIParamInd  )
   _body( BOOL     , 1 )
   _ev_end
   
/***********************<< ��ȡϵͳ����ʱ��ָʾ >>**********************	
 *[��Ϣ��]	
 *    + u32 ����ʱ��,��λΪ��
 *[��Ϣ����]
 *    UI <= MtService
 */_event(  ev_GetSystemRunTimeInd )
   _body( u32        ,1 )
   _ev_end
   
/***********************<< ��ȡϵͳ����ʱ������ >>**********************	
 *[��Ϣ��]	
 *    + ��
 *[��Ϣ����]
 *    UI <= MtService
 */_event(  ev_GetSystemRunTimeCmd )
   _ev_end
   
/***********************<< ����ģʽ�������� >>************************	
 *[��Ϣ��]			 
 *   + u32 ����ģʽ���� 
 *[��Ϣ����]
 *    UI => MtService
 */_event(  ev_CfgEthModeCmd  )
   _body( u32           ,1 )
   _ev_end
   
/***********************<< ����ģʽ����ָʾ >>************************	
 *[��Ϣ��]			 
 *   + u32 ����ģʽ���� 
 *[��Ϣ����]
 *    UI => MtService
 */_event(  ev_CfgEthModeInd  )
   _body( u32           ,1 )
   _ev_end
     
  
/***********************<< MC��ϯѡ������  >>*************************
 *[��Ϣ��]
 *  BOOL  +1
 *  TMtId +1
 *[��Ϣ����]
 *  UI => MtService => MC
 */_event( ev_mcViewCmd )
   _body( BOOL,      1 )
   _body( TMtId,     1 )
   _ev_end

/***********************<< MC��ϯѡ��ָʾ  >>*************************
 *[��Ϣ��]
 *  BOOL  +1
 *  TMtId +1
 *[��Ϣ����]
 *  UI <= MtService <= MC
 */_event( ev_mcViewInd )
   _body( BOOL,      1 )
   _body( TMtId,     1 )
   _ev_end
   
  
   
/***********************<< pcmt������Ƶ�ɼ���������  >>*************************
 *[��Ϣ��]
 *  u16     1  ��Ƶ����ͼ����
 *  u16     1  ��Ƶ����ͼ��߶�
 *  u8      1  ֡���Ƿ�С��1
 *  u8      1  ��Ƶ����֡��
 *  u8      1  ��Ƶ����֡��ʽ
 *  u32     2  ����λ
 *[��Ϣ����]
 *  MtService <= PCMT
 */_event( ev_PcmtSetCapParamCmd )
   _body( u16,     1 )
   _body( u16,     1 )
   _body( u8,      1 )
   _body( u8,      1 )
   _body( u8,      1 )
   _body( u32,     2 )
   _ev_end
    
  
/*********<< pcmt���ݻ������� >>**************	
 *[��Ϣ��]			 
 *
 *[��Ϣ����]
 *
 *   pcmt => mtservice
 *
 */_event(  ev_PcmtDataConfReq   )    
   _ev_end

/*********<< pcmt���ݻ���Ӧ�� >>**************	
 *[��Ϣ��]			 
 * BOOL //TRUE,����;FALSE,������
 *[��Ϣ����]
 *
 *   mtservice => pcmt
 *
 */_event( ev_PcmtDataConfRsp   )
   _body ( BOOL,    1           )
   _ev_end
   
/***********************<< �ӱ�������ȡ�ĵ�һ��·֡���ϱ� >>************************	
 *[��Ϣ��]		 
 *  +u16  //��һ·��Ƶ����֡��
 *  +u16  //��һ·��Ƶ����֡��
 *  +u16  //�ڶ�·��Ƶ����֡��
 *  +u16  //�ڶ�·��Ƶ����֡��
 *[��Ϣ����]
 *    MtService => UI
 */_event ( ev_VidFramerateInd )
  _body ( u16, 1 )
  _body ( u16, 1 )
  _body ( u16, 1 )
  _body ( u16, 1 )
  _ev_end                           

/***********************<<  ������ֱ������ָʾ  >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ����ð�����ֱ������
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CfgHDResOutputInd  )
   _body( u32     , 1 )
   _body( u32     , 1 )//Reversed 1
   _body( u32     , 1 )//Reversed 2  
   _ev_end  

/***********************<<  ������ֱ����������  >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ����ð�����ֱ������
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CfgHDResOutputCmd  )
   _body( u32     , 1 )
   _body( u32     , 1 )//Reversed 1
   _body( u32     , 1 )//Reversed 2  
   _ev_end  


/***********************<<  ֱ�ӵ���ͼ�����������  >>********************	
 *[��Ϣ��]			 
 *     +EmCodecComponent  �����ƵĶ���Ŀǰֻ������Ƶ��������
 *     +u32               �������� MT_SCALE_BRIGHTNESS��MT_SCALE_CONTRAST��MT_SCALE_HUE��MT_SCALE_SATURATION           
 *     +u32               ����ֵ
 *[��Ϣ����]
 *    UI => MtService => MTMP
 */_event( ev_AdjustImageParamDirectlyCmd  )
   _body( EmCodecComponent     , 1 )
   _body( u32                  , 1 )
   _body( u32                  , 1 )
   _body( u32                  , 2 ) // Reversed
   _ev_end  
   
/***********************<<  ����PicPlus������������  >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ�����PicPlus������ӿ�
 *[��Ϣ����]
 *    MtService <= MTC/MTMP
 */_event( ev_CfgHDPicPlusParamCmd  )
   _body( BOOL     , 1 )
   _ev_end
   
/***********************<<  ����PicPlus��������ָʾ  >>********************	
 *[��Ϣ��]			 
 *     +BOOL  �Ƿ�����PicPlus������ӿ�
 *[��Ϣ����]
 *    MtService => MTC/MTMP
 */_event( ev_CfgHDPicPlusParamInd  )
   _body( BOOL     , 1 )
   _ev_end

/***********************<<  PCMT��Ƶ����ģʽ��������  >>********************	
 *[��Ϣ��]
 *     +u8  PCMT��Ƶ����뷽ʽ  PCMT_VCODEC_SOFTWARE--��������  PCMT_VCODEC_HARDWARE--Ӳ���Կ������
 *     +u8  ����/���� (0:����  1:����)   
 *[��Ϣ����]
 *    MtService <= PCMT
 */_event( ev_CfgVideoWorkModeCmd  )
   _body( u8     , 1 )
   _body( u8     , 1 )
   _body( u32    , 1 )
   _body( u32    , 1 )
   _ev_end

/***********************<<  PCMT��Ƶ����ģʽ����ָʾ  >>********************	
 *[��Ϣ��]
 *     +u8  PCMT��Ƶ����뷽ʽ  PCMT_VCODEC_SOFTWARE--��������  PCMT_VCODEC_HARDWARE--Ӳ���Կ������
 *     +u8  ����/���� (0:����  1:����) 
 *[��Ϣ����]
 *    MtService => PCMT
 */_event( ev_CfgVideoWorkModeInd  )
   _body( u8     , 1 )
   _body( u8     , 1 )
   _body( u32    , 1 )
   _body( u32    , 1 )
   _ev_end

/***********************<<  ���ģʽ֡����������  >>********************	
 *[��Ϣ��]			 
 *     +TVideoOutputFrm  ���֡��

 *[��Ϣ����]
 *    MtService <= MTC/MTMP
 */_event( ev_CfgHDVideoFrmCmd  )
   _body( TVideoDisplayFrm     , 1 )
   _ev_end

/***********************<<  ���ģʽ֡��������ʾ  >>********************	
 *[��Ϣ��]			 
 *     TVideoOutputFrm  ���֡��
 *[��Ϣ����]
 *    MtService <= MTC/MTMP
 */_event( ev_CfgHDVideoFrmInd  )
   _body( TVideoDisplayFrm      , 1 )
   _ev_end
   

/***********************<< �������ʵ�ʵ����ʷֱ���ͳ����Ϣָʾ >>************************	
 *[��Ϣ��]		 
 *  +EmVideoResolution�� �ֱ�Ϊpvenc,svenc, pvdec,svdec
 *[��Ϣ����]
 *    MtMP => MtService 
 */_event ( ev_CodecVideoEncDecResInd )
  _body ( u32, 8 )
  _ev_end
  
/***********************<< �նˣ�������ϯMT��ѡ������ϳ����� >>**********************	
 *[��Ϣ��]			 
 *  ��
 *[��Ϣ����]
 *
 *   MtService => 323/sip/320
 */_event( ev_ConfmtSelectVmpReq  )
   _body ( BOOL           ,1 )
   _ev_end

/***********************<< �նˣ�������ϯMT��ѡ������ϳɷ��� >>**********************	
 *[��Ϣ��]			 
 *  BOOL
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 */_event( ev_ConfmtSelectVmpRsp  )
   _body ( BOOL           ,1 )
   _ev_end

   /***********************<< MC��ϯѡ����ѯָʾ  >>*************************
   *[��Ϣ��]
   *  TMtViewPollInfo  +1
   *[��Ϣ����]
   *  UI <= MtService <= MC
   */_event( ev_mcViewPollInd )
   _body( TMtViewPollInfo,      1 )
   _body( u32,                  1 ) // Reversed 1
   _body( u32,                  1 ) // Reversed 2
  _ev_end

  /***********************<< MC��ϯѡ����ѯ����  >>*************************
  *[��Ϣ��]
  *  TMtViewPollInfo  +1
  *[��Ϣ����]
  *  UI => MtService => MC
  */
  _event( ev_mcViewPollCmd )
  _body( TMtViewPollInfo,      1 )
  _body( u32,                  1 ) // Reversed 1
  _body( u32,                  1 ) // Reversed 2
	_ev_end

    /////////////////////////////////////////////////////////////////////////////////
   //wangxiaoyi 20091014
   /************************************************************************/
   /*                            ����ϵͳ����                              */
   /************************************************************************/
   /*[��Ϣ��]
   * + ϵͳ����
   *[��Ϣ����
   *     mtui => mtservice
   */_event ( ev_CfgSecurePwdCmd )
   _body ( TSecurePwd, 1 )
   _ev_end
   /////////////////////////////////////////////////////////////////////////////////
   //wangxiaoyi 20091014
   /************************************************************************/
   /*                            ����ϵͳ����                              */
   /************************************************************************/
   /*[��Ϣ��]
   * + ϵͳ����
   *[��Ϣ����
   *     mtui <= mtservice
   */_event ( ev_CfgSecurePwdInd )
   _body ( TSecurePwd, 1 )
   _ev_end

   //add by fanjunshuang for innner mc
   /***********************<< ˫�������������� >>************************	
   *[��Ϣ��]			 
   *   + EmVideoFormat     ˫����ʽ 
   *   + EmVideoResolution ˫���ֱ���
   *   + u32               ˫��֡��
   *   + u32               ����
   *   + u32               ����
   *[��Ϣ����]
   *    UI => MtService
   */_event(  ev_CfgDualParamCmd  )
   _body( EmVideoFormat           ,1 )
   _body( EmVideoResolution       ,1 )
   _body( u32                     ,1 )
   _body( u32                     ,1 )
   _body( u32                     ,1 )
   _ev_end
   
   /***********************<< ˫����������ָʾ >>************************	
   *[��Ϣ��]			 
   *   + EmVideoFormat     ˫����ʽ 
   *   + EmVideoResolution ˫���ֱ���
   *   + u32               ˫��֡��
   *   + u32               ����
   *   + u32               ����
   *[��Ϣ����]
   *     MtServiceUI => UI
   */_event(  ev_CfgDualParamInd  )
   _body( EmVideoFormat           ,1 )
   _body( EmVideoResolution       ,1 )
   _body( u32                     ,1 )
   _body( u32                     ,1 )
   _body( u32                     ,1 )
   _ev_end
	//end add by fanjunshuang for innner mc
	   /***********************<< �ն��������� >>**********************	
 *[��Ϣ��]			 
 *  u32  : type
 *  u32  : size
 *  u32  : ��������
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 */_event( ev_ExtMtCfgCmd  )
   _body ( u32           ,1 )
   _body ( u32           ,1 )
   _body ( u32           ,15 )
   _ev_end

   /***********************<< �ն�����ָʾ >>**********************	
 *[��Ϣ��]			 
 *  u32  : type
 *  u32  : size
 *  u32  : ��������
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 */_event( ev_ExtMtCfgInd  )
   _body ( u32           ,1 )
   _body ( u32           ,1 )
   _body ( u32           ,15 )
   _ev_end

   /***********************<< ��ϯ�ն˱���������ѯ�������� >>************************	
   *[��Ϣ��]		 
   *  + u32:������Ŀ  
   *  + s8:���з������� 
   *  + TMtPollInfo:����
   *[��Ϣ����
   *   ui => mtservice 
   */_event ( ev_CfgAllPollSchemeCmd )
   _body ( u32 , 1 )
   //_body ( s8 , (MAX_CHAIR_POLLSCHEME_NUM * (MT_MAX_NAME_LEN + 1)) )
   _body ( TMtPollSchemeNameSet , 1 )
   _body ( TMtPollInfo , MAX_CHAIR_POLLSCHEME_NUM )
   _ev_end
   
   /***********************<< ��ϯ�ն˱���������ѯ����ָʾ >>************************	
   *[��Ϣ��]		 
   *  + u32:������Ŀ  
   *  + s8:���з�������
   *  + TMtPollInfo:����
   *[��Ϣ����
   *   ui => mtservice 
   */_event ( ev_CfgAllPollSchemeInd )
   _body ( u32 , 1 )
   //_body ( s8 , (MAX_CHAIR_POLLSCHEME_NUM * (MT_MAX_NAME_LEN + 1)) )
   _body ( TMtPollSchemeNameSet , 1 )
   _body ( TMtPollInfo , MAX_CHAIR_POLLSCHEME_NUM )
   _ev_end

   /***********************<< ��ϯ�ն˱���һ����ѯ�������� >>************************	
   *[��Ϣ��]		 
   *  + u32:�������� 
   *  + s8:��������
   *  + TMtPollInfo:����
   *[��Ϣ����
   *   ui => mtservice 
   */_event ( ev_CfgOnePollSchemeCmd )
   _body ( u32 , 1 )
   _body ( s8 , (MT_MAX_NAME_LEN + 1) )
   _body ( TMtPollInfo , 1 )
   _ev_end
   
   /***********************<< ��ϯ�ն˱���һ����ѯ����ָʾ >>************************	
   *[��Ϣ��]		 
   *  + u32:��������
   *  + s8:��������
   *  + TMtPollInfo:����
   *[��Ϣ����
   *   ui => mtservice 
   */_event ( ev_CfgOnePollSchemeInd )
   _body ( u32 , 1 )
   _body ( s8 , (MT_MAX_NAME_LEN + 1) )
   _body ( TMtPollInfo , 1 )
   _ev_end

   /***********************<< ˫�������������� >>************************	
   *[��Ϣ��]			 
   *   + BOOL     �Ƿ�ָ��IP 
   *[��Ϣ����]
   *    UI => MtService
   */_event(  ev_Cfg323UseSpecialIpCmd  )
   _body( BOOL           ,1 )
   _ev_end
   
   /***********************<< ˫����������ָʾ >>************************	
   *[��Ϣ��]			 
   *   + BOOL     �Ƿ�ָ��IP  
   *[��Ϣ����]
   *     MtServiceUI => UI
   */_event(  ev_Cfg323UseSpecialIpInd  )
   _body( BOOL           ,1 )
   _ev_end


   //////////////////////////////////////////////////////////////////////////
   /***********************<< ��ϯ���Ƿ񵯳� ���뷢���˵Ŀ��Ʋ��� >>************************	
   *[��Ϣ��]		 
   *  + u8    
   *[��Ϣ����
   *   ui => mtservice 
   */_event ( ev_CfgChairContorlCmd )
   _body ( u32 , 1 )
   _ev_end
   
   //////////////////////////////////////////////////////////////////////////
   /***********************<< ��ϯ���Ƿ񵯳� ���뷢���˵Ŀ��Ʋ��� >>************************
   *[��Ϣ��]		 
   *  + u8    
   *[��Ϣ����
   *   ui <= mtservice 
   */_event ( ev_CfgChairContorlInd )
   _body ( u32 , 1 )
   _ev_end
   
   /************************************************************************/
   /*                            G7221�Ƿ�ת�ϱ�MTC                      */
   /************************************************************************/
   /*[��Ϣ��]
   * + ϵͳ����
   *[��Ϣ����
   *     mtservice=>mtc
   */_event ( ev_G7221cReverseToMtcCmd )
   _body ( EmSite, 1 )
   _body ( BOOL, 1 )
   _ev_end
   
   /************************************************************************/
   /*                           ȡ��ע��GK���֪ͨ                      */
   /************************************************************************/
   /*[��Ϣ��]
   * + ϵͳ����
   *[��Ϣ����
   *     mtservice=>mtc,    TRUE ��ʾ�ɹ�.  FALSE��ʾʧ��
   */_event ( ev_GKUnRegistResultInd )
   _body ( BOOL, 1 )
     _ev_end

	 /***********************<< mtcbox config  >>************************	
	 *[��Ϣ��]
	 *  TMtcBoxCallCfg
	 *[��Ϣ����]
	 *    mtservice => mtc | ui
	 */_event(  ev_MtcBoxCfgInd  )
	 _body ( TMtcBoxCallCfg    , 4 )
	 _ev_end
	 
	 /***********************<< mtcbox config  >>************************	
	 *[��Ϣ��]
	 *  u8 �������
	 *  TMtcBoxCallCfg
	 *[��Ϣ����]
	 *    mtservice <= mtc | ui
	 */_event(  ev_MtcBoxCfgCmd  )
	 _body ( u8 , 1 )
	 _body ( TMtcBoxCallCfg  , 1 )
	 _ev_end
	 /***********************<< ֪ͨservice E164 >********************** 
	 *[��Ϣ��]    
	 *  
	 *[��Ϣ����]
	 *
	 *   H323Service => mtservice
	 *   
	 */
	 _event(  ev_CallE164Ind   )
	 _body( s8          ,MT_MAX_E164NUM_LEN+1  )
	 _ev_end

	 /***********************<< ����mc�ش���������ָʾ >>************************	
   *[��Ϣ��]			 
   *   + TMTRSParam     �ش����� 
   *[��Ϣ����]
   *     MtServiceUI <= UI
   */_event(  ev_CfgMCRSParamCmd  )
   _body( TMTRSParam           ,1 )
   _ev_end

	 /***********************<< ����mc�ش���������ָʾ >>************************	
   *[��Ϣ��]			 
   *   + TMTRSParam     �ش����� 
   *[��Ϣ����]
   *     MtServiceUI => UI
   */_event(  ev_CfgMCRSParamInd  )
   _body( TMTRSParam           ,1 )
   _ev_end

   /**********************************************************
	 ����ΪREC�����Ϣ   mt<=>mtc 
	**********************************************************/
   /***********************<< >>********************** 
	*[��Ϣ��]    
	*TMtRecRegParam
	*[��Ϣ����]
	*mtc->mtservice->mtdevice
	*   
	*   
	*/
   _event(  ev_RecServer_Reg_Req  )
   _body( u32_ip , 1 )
   _body( u32_ip , 1 )
   _body( s8       , MT_MAX_H323ALIAS_LEN+1 )
   _ev_end

   /***********************<< >>********************** 
	*[��Ϣ��]    
	*  BOOL TRUE�ɹ�
	*		FALSEʧ��
	*  u16 error code ʧ������Ч
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_RecServer_Reg_Rsp  )
    _body( BOOL          ,1  )
	_body( u16          ,1  )
   _ev_end

   /***********************<< >>********************** 
	*[��Ϣ��]    
	*
	*  TMtRecStartParam
	*
	*[��Ϣ����]
	*
	*   mtc->mtservice->mtdevice
	*   
	*/
   _event(  ev_StartRec_Req  )
   _body(   TMtRecStartParam , 1 )
   _ev_end

   /***********************<< >>********************** 
	*[��Ϣ��]    
	*   BOOL TRUE�ɹ�
	*		FALSEʧ�� 
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_StartRec_Rsp  )
   _body( BOOL          ,1  )
   _body( u16          ,1  )
   _ev_end

   /***********************<< >>********************** 
	*[��Ϣ��]    
	*  
	*[��Ϣ����]
	*
	*   mtc->mtservice->mtdevice
	*   
	*/
   _event(  ev_PauseRec_Req  )
   _ev_end

     /***********************<< >>********************** 
	*[��Ϣ��]    
	*   BOOL TRUE�ɹ�
	*		FALSEʧ��  
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_PauseRec_Rsp  )
   _body( BOOL          ,1  )
   _body( u16          ,1  )
   _ev_end

    /***********************<< >>********************** 
	*[��Ϣ��]    
	*  
	*[��Ϣ����]
	*
	*   mtc->mtservice->mtdevice
	*   
	*/
   _event(  ev_ResumeRec_Req  )
   _ev_end

     /***********************<< >>********************** 
	*[��Ϣ��]    
	*   BOOL TRUE�ɹ�
	*		FALSEʧ��  
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_ResumeRec_Rsp  )
   _body( BOOL          ,1  )
   _body( u16          ,1  )
   _ev_end


   /***********************<< >>********************** 
	*[��Ϣ��]    
	*  
	*[��Ϣ����]
	*
	*   mtc->mtservice->mtdevice
	*   
	*/
   _event(  ev_StopRec_Req  )
   _ev_end

     /***********************<< >>********************** 
	*[��Ϣ��]    
	*   BOOL TRUE�ɹ�
	*		FALSEʧ��  
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_StopRec_Rsp  )
   _body( BOOL          ,1  )
   _body( u16          ,1  )
   _ev_end

    /***********************<< >>********************** 
	*[��Ϣ��]    
	*  
	*[��Ϣ����]
	*
	*   mtc->mtservice->mtdevice
	*   
	*/
   _event(  ev_GetRecStatus_Req  )
   _ev_end

     /***********************<< >>********************** 
	*[��Ϣ��]    
	*   BOOL TRUE�ɹ�
	*		FALSEʧ��  
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_GetRecStatus_Rsp  )
   _body( BOOL          ,1  )
   _body( u16          ,1  )
   _ev_end

     /***********************<< >>********************** 
	*[��Ϣ��]    
	*   
	*		
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_GetRecStatus_Nty  )
   _body( BOOL          ,1  )
   _body( u16          ,1  )
   _ev_end

   /***********************<< >>********************** 
	*[��Ϣ��]    
	*  EmCodecComponent 
	*    TIPTransAddr
	*[��Ϣ����]
	*
	*   mtdevice->mtservice->mtmp
	*   
	*/
   _event(  ev_StartRecord_Cmd  )
   _body( EmCodecComponent, 1 )
   _body( TIPTransAddr          ,1  )
   _ev_end
   /***********************<< >>********************** 
	*[��Ϣ��]    
	*  
	*[��Ϣ����]
	*
	*   mtdevice->mtservice->mtmp
	*   
	*/
   _event(  ev_StopRecord_Cmd  )
   _ev_end

   /***********************<< >>********************** 
	*[��Ϣ��]    
	*  
	*[��Ϣ����]
	*
	*   mtdevice
	*   
	*/
   _event(  ev_ConnetRecSrv_Timer  )
   _ev_end

   /***********************<< >>********************** 
	*[��Ϣ��]    
	*  
	*[��Ϣ����]
	*
	*   mtdevice
	*   
	*/
   _event(  ev_DisConnectRec_Cmd  )
   _ev_end

   /***********************<< >>********************** 
	*[��Ϣ��]    
	*   
	*		
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_GetCurRecParam_Req  )
   _ev_end

	/***********************<< >>********************** 
	*[��Ϣ��]    
	*   
	*		
	*[��Ϣ����]
	*
	* mtc<-mtservice<-mtdevice  
	*   
	*/
   _event(  ev_GetCurRecParam_Rsp  )
   _body( TMtRecParam          ,1  )
   _ev_end

   	/***********************<< >>********************** 
	* ��һ·Դ�Զ�
	*[��Ϣ��]
	* BOOL
	*[��Ϣ����]
	* mtc->mtservice   
	*/
   _event(  ev_SetAutoSecSrcCmd  )
   _body( BOOL          ,1  )
   _ev_end

    /***********************<< >>********************** 
	* ��һ·Դ�Զ�
	*[��Ϣ��]
	* BOOL
	*[��Ϣ����]
	* mtc->mtservice   
	*/
   _event(  ev_SetAutoSecSrcInd  )
   _body( BOOL          ,1  )
   _ev_end


    /***********************<< >>********************** 
	* ��ȡ��ƵԴ״̬
	*[��Ϣ��]
	* 
	*[��Ϣ����]
	* mtue->mtmp   
	*/
   _event( ev_GetVidSrcStatusCmd )
	_body( EmCodecComponent          ,1  )
	_body( BOOL          ,1  )
   _ev_end

   /***********************<< >>********************** 
	* ��ȡ��ƵԴ״̬���
	*[��Ϣ��]
	* BOOL
	*[��Ϣ����]
	* mtmp->mtue  
	*/
   _event( ev_GetVidSrcStatusInd )
   _body( EmCodecComponent          ,1  )
   _body( BOOL          ,1  )
   _body( BOOL          ,1  )
   _ev_end

   /***********************<<  AEC΢��ָʾ >>********************	
   *[��Ϣ��]
   +
   *[��Ϣ����]
   *   mtservice  => ui 
   */_event( ev_CfgAECAdjustInd )
   _body( u32, 1 )
   _ev_end
   
   /***********************<<  AEC΢������ >>********************	
   *[��Ϣ��]
   +
   *[��Ϣ����]
   *   ui  => mtservice
   */_event( ev_CfgAECAdjustCmd )
   _body( u32, 1 )
   _ev_end
#ifndef _MakeMtEventDescription_
   _ev_segment_end( extend )
};
#endif

#endif
