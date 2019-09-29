#ifndef _h_innereventmoon_h__
#define _h_innereventmoon_h__


#include "mooneventcomm.h"


#ifndef _MakeTpEventDescription_
enum EmUmsInnerToCns
{
#endif

_ev_segment( innermoon )

 /***********************<< ι����ʱ��  >>******************
 *[��Ϣ��]
 *  NULL
 *[��Ϣ����]
 *           => MtService
 */_event( ev_TpWatchdogtimer_Nty )
   _ev_end

/***********************<< ι��֪ͨ��Ϣ  >>*********************
 *[��Ϣ��]
 *  NULL
 *[��Ϣ����]
 *  MtSysApi <= MtService
 */_event( ev_TpNotifyWatchdog_Ind )
   _ev_end

/***********************<< ����ι��  >>*************************
 *[��Ϣ��]
 *  +BOOL TRUE=����ι�� FALSE=ֹͣι��
 *[��Ϣ����]
 *  MtSysApi => MtService
 */_event( ev_TpRunWatchdog_Cmd )
   _ev_end

/***********************<<moon��ģ����������>>************************	
 *[����Ϣ��]			 
 *  NULL
 *[��Ϣ����]
 *    moon => moon
 */
_event(  ev_TpModuleStartCmd )
_ev_end

/***********************<<moon����>>************************	
 *[����Ϣ��]			 
 *  TMtTPEpParam �᳡����
 *[��Ϣ����]
 *   moon => moon
 */
_event(  ev_TpMoonOnline_Nty )
_ev_end

 /***********************<<cam��¼>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moonue->moon
 */
_event(  ev_TpCamCPLogin_Ind )
_ev_end

 /***********************<<cam��¼>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon->moon
 */
_event(  ev_TpCamCPLoginInst_Req )
_ev_end

 /***********************<<cam�˳�>>************************	
 *[����Ϣ��]			 
 * u8 Pad ID
 *[��Ϣ����]
 *  moonue->moon
 */
_event(  ev_TpCamCPLogout_Ind )
_body( u8, 1)
_ev_end

 /***********************<<cam��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cns->cns
 */
_event(  ev_TpModuleRebootCmd )
_ev_end

/***********************<<cam���ò���>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam <- moon 
 */
_event(  ev_TpMoonCamInfo_Cmd )
_body( TTPMoonCamInfo, 1)
_body( BOOL, 1 )
_body( BOOL, 1 )//��ʶ��ǰ�Ƿ�Ϊ�ָ�Ĭ��ʱ���ͻ�о��Ϣ
_ev_end

/***********************<<cam����show����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam <- moon 
 */
_event(  ev_TpMoonCamInfoShow_Cmd )
_ev_end

/***********************<<cam��о��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam <- moon 
 */
_event(  ev_TpMoonCamTest_Cmd )
_body( u8, 1)
_body( s8, 20)
_ev_end

/***********************<<cam��о��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam <- moon 
 */
_event(  ev_TpMoonCamQuiryTest_Cmd )
_body( u8, 1)
_body( s8, 20)
_ev_end

/***********************<<cam����˿���ʽ֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam <- moon 
 */
_event(  ev_TpOutPotFormat_Nty )
_body( EmTPMOONOutMode, 1)
_ev_end

/***********************<<cam����˿���ʽ����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam <- moon 
 */
_event(  ev_TpDVIOutPotTest_Cmd )
_body( EmMOONProductTestType, 1 )
_body( u8, 1)
_ev_end

/***********************<<cam����˿���ʽ����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam <- moon 
 */
_event(  ev_TpZoomTest_Timer )
_ev_end

/***********************<<cam���ڲ���>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam -> moon 
 */
_event(  ev_TpRS323Test_Cmd )
_ev_end

/***********************<<cam�����ʽ����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam -> moon 
 */
_event(  ev_TpCamOutFoumat_Cmd )
_ev_end

/***********************<<��մ��������ݶ�ʱ��>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam -> moon 
 */
_event(  ev_TpCamReadDirtyData_Timer )
_ev_end

/***********************<<�������ݸı�>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> moon 
 */
_event(  ev_TpCorrectChange_Cmd )
_body( TTPDistortParam, 1)
_body( EmTPCorrect, 1)
_body( u8, 1)
_ev_end

/***********************<<��ѯ��о�����ʺ������ʽ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> moon 
 */
_event(  ev_TpQuiryTest_Cmd )
_ev_end

_event(  ev_TpTestLvdsBaud_Cmd )
_body( u8, 1)
_ev_end

//add by youjx 2016.11.8
/***********************<<cam��ѯͼ����������ȡ�ɫ�ȡ����Ͷȡ��Աȶ�>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpInquiryImagePara_Cmd )
_body( EmTPImagePara, 1)
_body( u8, 1)
_ev_end 

/***********************<<cam������Ұ��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamSetZoomLimit_Cmd )
_body( u8, 1)
_body( u16, 1)
_ev_end

/***********************<<cam��������ʮ�ּ�>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
 _event( ev_TpCamSetCross_Cmd )
 _body( u8, 1)
 _body( BOOL, 1)
 _ev_end

/***********************<<moon��������У��>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
 _event( ev_TpDistortChange_Cmd)
 _body(TTPDistortCorrectInfo, 1)
 _body(u8, 1)
 _ev_end

/***********************<<moon������ɫУ��>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
 _event( ev_TpChangeColorCoeff_Cmd)
 _body(TTPColorCoeff, 1)
 _body(u8, 1)
 _ev_end

 /************************H650��о��zoomPos�õ�zoom���֪ͨ********
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon <- cam
 */
 _event( ev_TpH650Zoom_Nty)
 _body(u8, 1)
 _body(u32, 1)
 _ev_end
 //add end

#ifndef _MakeTpEventDescription_
   _ev_segment_end(innermoon)
};
#endif



#endif // _h_innereventregsrv_h__
