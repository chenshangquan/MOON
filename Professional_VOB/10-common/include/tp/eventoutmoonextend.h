#ifndef _h_eventoutmoonextend_h__
#define _h_eventoutmoonextend_h__

#include "mooneventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSEXTENDEVENT
{
#endif 

  _ev_segment( outermoonextend  )

 //��¼
 /***********************<< ��¼���� >>********************** 
 *[��Ϣ��]
 *NULL
 *[��Ϣ����]
 *  cam	  -> moon
*/
_event(  ev_TpMoonLogin_Req )
//_body( CLoginRequest, 1 )
_ev_end

 /***********************<< ��¼�����Ӧ >>********************** 
 *[��Ϣ��]
+TLoginRet  ��¼��Ϣ
 *[��Ϣ����]
 *  cam	  <- moon
*/
_event(  ev_TpMoonLogin_Rsp )
_body(TLoginRet,	1)
_ev_end

  /***********************<<  ��������û� >>********************	
  *[��Ϣ����]	cam	-->  moon
  *����û����󣬲���ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_TpMoonAddUser_Req )
  _ev_end



  
  /***********************<< �ظ�����û�  >>********************	
  *[��Ϣ����]	moon	-->  cam
  *��ӷ���
  */
  _event(  ev_TpMoonAddUser_Rsp )
  _body(EmTpRet,	1)	//�������
  _ev_end
  



  /***********************<<  ����ɾ���û� >>********************	
  *[��Ϣ����]	cam	-->  moon
  *ɾ���û����󣬲���ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_TpMoonDelUser_Req )
  _ev_end	
  



  /***********************<<  �ظ�ɾ���û� >>********************	
  *[��Ϣ����]	moon	-->  Cam
  *ɾ������
  */
  _event(  ev_TpMoonDelUser_Rsp )
  _body(EmTpRet,	1)	//�������
  _ev_end
  



  /***********************<<  �����޸����� >>********************	
  *[��Ϣ����]	Cam	-->  moon
  *�޸��û����룬����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_TpMoonChangePWD_Req )
  _ev_end	
  



  /***********************<<   �ظ��޸�����  >>********************	
  *[��Ϣ����]	moon	-->  Cam
  *�޸ķ���
  */
  _event(  ev_TpMoonChangePWD_Rsp )
  _body(EmTpRet,	1)	//�������
  _ev_end	
  



  /***********************<< ��һ���û���¼  >>********************	
  *[��Ϣ����]	moon	-->  Cam
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_TpMoonAddUser_Nty )
  _ev_end	
  



  /***********************<< ��һ���û��˳���¼  >>********************	
  *[��Ϣ����]	moon	-->  Cam
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_TpMoonDelUser_Nty )
  _ev_end	
  



  /***********************<< �޸��û�  >>********************	
  *[��Ϣ����]	moon	-->  Cam
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_TpMoonUpdateUser_Nty )
  _ev_end	
  
  

  /***********************<<�û��������ط���¼  >>********************	
  *[��Ϣ����]	moon	-->  Cam
  *
  */
  _event(  ev_TpMoonLoginByOther_Nty )
  _body(u32_ip, 1)
_ev_end	

/***********************<<cam����֪ͨ����̨>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpMoonVerInfo_Nty )
_body( s8, MOON_MAX_DEVICEVER_LEN)
_body( EmTpVer, 1)
_ev_end 

/***********************<<cam����֪ͨ����̨>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpMoonCamInfo_Nty )
_body( TTPMoonCamInfo, 1)
_ev_end  

 /***********************<<cam�ӿ������������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamOutPortInfo_Cmd )
_body( EmTPDVIOutPortType, 1)
_body( EmTPMOONOutMode, 1)
_ev_end 

 /***********************<<cam�ӿ�������ͻ�Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamOutPortInfo_Ind )
_body( EmTPDVIOutPortType, 1)
_body( EmTPMOONOutMode, 1)
_body( BOOL, 1)
_ev_end 

 /***********************<<cam�ӿ������������֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamOutPortInfo_Nty )
_body( EmTPDVIOutPortType, 1)
_body( EmTPMOONOutMode, 1)
_ev_end

 /***********************<<cam����ͼ��ת����ƽ�⡢��ֱ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamImageAdjust_Cmd )
_body( EmTPImageAdjust, 1)
_ev_end 

 /***********************<<cam����ͼ��ת����ƽ�⡢��ֱ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamImageAdjust_Ind )
_body( EmTPImageAdjust, 1)
_body( BOOL, 1)
_ev_end 

 /***********************<<cam����ͼ��ת����ƽ�⡢��ֱ ֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamImageAdjust_Nty )
_body( EmTPImageAdjust, 1)
_ev_end 

/***********************<<cam���������Ƿ����Ԥ��λ1>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamInitPreset_Cmd )
_body( BOOL, 1)//�����Ƿ����Ԥ��λ
_ev_end

/***********************<<cam���������Ƿ����Ԥ��λ1��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> ue -> camCP
 */
_event(  ev_TpCamInitPreset_Ind )
_body( BOOL, 1)//�����Ƿ����Ԥ��λ
_body( BOOL, 1)//�Ƿ�ɹ�
_ev_end

 /***********************<<cam����Ԥ��λ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamPreSet_Cmd )
_body( TTPCamPre, 1)//Ԥ��λ����
_ev_end

 /***********************<<cam����Ԥ��λ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreSet_Ind )
_body( TTPCamPre, 1)
_body( BOOL, 1)
_ev_end

 /***********************<<cam����Ԥ��λ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreSet_Nty )
_body( TTPPreParam, 1)
_ev_end

/***********************<<cam����Ԥ��λ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamPreRecall_Cmd )
_body( TTPCamPre, 1)
_ev_end

 /***********************<<cam����Ԥ��λ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreRecall_Ind )
_body( TTPCamPre, 1)
_body( BOOL, 1)
_ev_end

/***********************<<camɾ��Ԥ��λ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamPreReset_Cmd )
_body( TTPCamPre, 1)
_ev_end

 /***********************<<camɾ��Ԥ��λ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreReset_Ind )
_body( TTPCamPre, 1)
_body( BOOL, 1)
_ev_end

/***********************<<camɾ��Ԥ��λ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamPreModify_Cmd )
_body( TTPCamPre, 1)
_ev_end

 /***********************<<camɾ��Ԥ��λ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamPreModify_Ind )
_body( TTPCamPre, 1)
_body( BOOL, 1)
_ev_end

/***********************<<cam����Zoom�Ŵ���С>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSetZoonStart_Cmd )
_body( EmTPZOOM, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam����Zoom�Ŵ���С��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamSetZoonStart_Ind )
_body( EmTPZOOM, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam����Zoom�Ŵ���С>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSetZoonStop_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam����Zoom�Ŵ���С>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSetZoonStop_Ind )
_body( u8, 1)
_body( u32, 1)
_body( BOOL, 1)
_body( u32, 1)
_ev_end 

/***********************<<cam����Zoomֵ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSetDrectZoon_Cmd )
_body( u32, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam����Zoomֵ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamSetDrectZoon_Ind )
_body( u32, 1)
_body( u8, 1)
_body( BOOL, 1)
_body(u32, 1)
_ev_end 

/***********************<<cam���þ۽�ģʽ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamFocusMode_Cmd )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam���þ۽�ģʽ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamFocusMode_Ind )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam�����ع�ģʽ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpMode_Cmd )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam�����ع�ģʽ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpMode_Ind )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam�����ع��Ȧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpAperture_Cmd )
_body( EmTPAperture, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam�����ع��Ȧ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpAperture_Ind )
_body( EmTPAperture, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam�����ع����60/30>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpSOrThShutter_Cmd )
_body( EmTPSOrThShutter, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam�����ع����60/30��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpSOrThShutter_Ind )
_body( EmTPSOrThShutter, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam�����ع����50/25>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpFOrTwShutter_Cmd )
_body( EmTPFOrTwShutter, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam�����ع����50/25��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpFOrTwShutter_Ind )
_body( EmTPFOrTwShutter, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam�����ع�����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamExpGain_Cmd )
_body( EmTPExpGain, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam�����ع������Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamExpGain_Ind )
_body( EmTPExpGain, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam���ð�ƽ��ģʽ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamWhiteBalanceMode_Cmd )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam���ð�ƽ��ģʽ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamWhiteBalanceMode_Ind )
_body( EmTPMOOMMode, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam���ð�ƽ���ɫ����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamWhiteBalanceRGain_Cmd )
_body( u32, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam���ð�ƽ���ɫ�����Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamWhiteBalanceRGain_Ind )
_body( u32, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam���ð�ƽ����ɫ����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamWhiteBalanceBGain_Cmd )
_body( u32, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam���ð�ƽ����ɫ�����Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamWhiteBalanceBGain_Ind )
_body( u32, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam���ñ��ⲹ��>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamBackLight_Cmd )
_body( BOOL, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam���ñ��ⲹ����Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamBackLight_Ind )
_body( BOOL, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam����ͼ����������ȡ�ɫ�ȡ����Ͷȡ��Աȶ�>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamImagePara_Cmd )
_body( EmTPImagePara, 1)
_body( u32, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam����ͼ����������ȡ�ɫ�ȡ����Ͷȡ��ԱȶȻ�Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamImagePara_Ind )
_body( EmTPImagePara, 1)
_body( u32, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam����FPGA����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamReduNoise_Cmd )
_body( BOOL, 1)
_body( EmTPFpgaReduNoise, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam���ý����Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamReduNoise_Ind )
_body( BOOL, 1)
_body( EmTPFpgaReduNoise, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSnapshot_Cmd )
_body( TTPSnapshotInfo, 1)//���հ�ťʱ���ýṹ����byIndex����Ϊ3
_ev_end 

 /***********************<<cam���ջ�Ӧ>>***********************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamSnapshot_Ind )
_body( TTPSnapshotInfo, 1)//���հ�ťʱ���ýṹ����byIndex����Ϊ3
_body( BOOL, 1)//�ɹ���񷵻�ֵ
_body(BOOL, 1)//moon90hʱΪTRUE��moon90ΪFALSE
_ev_end 

/***********************<<cam����ƴ�ӽ���>>********************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpImageReduNoise_Cmd )
_body( EmTPFpgaReduNoise, 1)
_body( u8, 1)
_ev_end 

 /***********************<<cam����ƴ�ӻ�Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpImageReduNoise_Ind )
_body( EmTPFpgaReduNoise, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<camֱ����������У��>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpImageDistortCorrect_Cmd )
_body( TTPDistortParam, 1)
_body( EmTPCorrect, 1)
_body( u8, 1)
_ev_end 

 /***********************<<camֱ����������У����Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpImageDistortCorrect_Ind )
_body( TTPDistortParam, 1)
_body( EmTPCorrect, 1)
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam�ϵ�>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamPowerOn_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam�µ�>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamPowerOff_Cmd )
_body( u8, 1)
_ev_end

/***********************<<cam�۽�����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamFocusFar_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam�۽�����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamFocusFar_Ind )
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam�۽�����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamFocusNear_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam�۽�����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamFocusNear_Ind )
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam�۽�����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamFocusStop_Cmd )
_body( u8, 1)
_ev_end 

/***********************<<cam�۽�����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> cam
 */
_event(  ev_TpCamFocusStop_Ind )
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

 /***********************<<camѡ�����������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamSelect_Cmd )
_body( u8, 1)
_ev_end 

 /***********************<<camѡ������������Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamSelect_Ind )
_body( u8, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<camѡ�����������֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamSelect_Nty )
_body( u8, 1)
_ev_end

 /***********************<<cam�ָ�Ĭ������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpCamParamDefault_Cmd )
_body(u8, 1)             //0����һ�����棻1���ڶ�������
_ev_end 

 /***********************<<cam�ָ�Ĭ�������Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamParamDefault_Ind )
_body( TTPMoonCamInfo, 1)
_body( BOOL, 1)
_ev_end 


 /***********************<<����Ԥ��λ��Ϣ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon 
 */
_event(  ev_TpCamParamUpload_Cmd )
_ev_end 

 /***********************<<����Ԥ��λ��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpCamParamUpload_Ind )
_body( BOOL, 1)
_ev_end

 /***********************<<����Ԥ��λ֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon 
 */
_event(  ev_TpCamParamUpload_Nty )
_body( BOOL, 1)
_ev_end 

 /***********************<<camѡ������������Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon  
 */
_event(  ev_TpCamReboot_Ind )
_body( BOOL, 1)//�ϴ�Ԥ��λ�ļ�������������True����������False
_ev_end

/***********************<< �������Թ��ߵ�½������Ϣ >>********************** 
*[��Ϣ��]
*CLoginRequest
*[��Ϣ����]
*    Ӧ���ն� <- cns 
*/
_event( ev_CNPRODUCETESTLOGIN_REQ )
//_body(CLoginRequest ,1)
_ev_end

/***********************<< �������Թ��߲�����������Ϣ >>********************** 
*[��Ϣ��]
*TCnProduceTestMsg
*[��Ϣ����]
*    Ӧ���ն� -> cns 
*/
_event( ev_CNPRODUCETEST_CMD )
_body(TMOONProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��ߵ�½��Ӧ�ɹ���Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]
*    Ӧ���ն� -> cns 
*/
_event( ev_CNPRODUCETESTLOGIN_ACK )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��ߵ�½��Ӧʧ����Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]
*    Ӧ���ն� -> cns 
*/
_event( ev_CNPRODUCETESTLOGIN_NACK )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��߲��Խ����Ϣ >>********************** 
*[��Ϣ��]
*TCnProduceTestMsg
*[��Ϣ����]
*    Ӧ���ն� <- cns 
*/
_event( ev_CNPRODUCETESTRESULT_NTY )
_body(TMOONProduceTestMsg ,1)
_ev_end
	  
/***********************<< �������Թ������Ӷ�ʱ����Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTCONNECT_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��ߵ�½ע�ᶨʱ����Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLOGIN_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ���ָʾ�ƶ�ʱ����Ϣ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLIGHT_TIMER )
//_body(TCnProduceTestMsg ,1)
_ev_end

/***********************<< �������Թ��߻ָ�Ĭ��ֵ >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]Ӧ�� -> cns
*    
*/
_event( ev_CNPRODUCETESTDEFAULT_CMD )
//_body(TCnProduceTestMsg ,1)
_ev_end
 
/***********************<< �������Թ��߻ָ�Ĭ��ֵӦ�� >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTDEFAULT_NTY )
_body(BOOL ,1)
_ev_end

/***********************<< �������Թ��ߺ������IR OUT ����LED�ƶ�ʱ�� >>********************** 
*[��Ϣ��]
*
*[��Ϣ����]cns -> cns
*    
*/
_event( ev_CNPRODUCETESTLED_TIMER )
//_body(BOOL ,1)
_ev_end

/***********************<<����LVDS����������>>************************	
*[����Ϣ��]			 
* NULL
*[��Ϣ����]
*  camCP -> moon 
*/
_event(  ev_TpSetLVDSBaud_Cmd )
_body( EmTPLVDSBaud, 1)//������ѡ��
_ev_end 

/***********************<<����LVDS�����ʻ�Ӧ>>************************	
*[����Ϣ��]			 
* NULL
*[��Ϣ����]
*  camCP <- moon 
*/
_event(  ev_TpSetLVDSBaud_Ind )
_body( EmTPLVDSBaud, 1)//������ѡ��
_body( BOOL, 1)//�ɹ���񷵻�ֵ
_ev_end 

/***********************<<���õ�½ʱ��LVDS������֪ͨ����>>*************	
*[����Ϣ��]			 
* NULL
*[��Ϣ����]
*  camCP <- moon 
*/
_event(  ev_TpSetLVDSBaud_Nty )
_body( EmTPLVDSBaud, 1)//������ѡ��
_ev_end 

/***********************<<�����ο�������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpSetRefer_Cmd )
_body( BOOL, 1)//����
_body(u8, 1)//���۴򿪻��ǹر�ʱ����ֵ������Ϊ3
_ev_end 

 /***********************<<�����ο��߻�Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpSetRefer_Ind )
_body( BOOL, 1)//����
_body( BOOL, 1)//�ɹ���񷵻�ֵ
_ev_end 

 /***********************<<�����ο���֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpSetRefer_Nty )
_body( BOOL, 1)//���أ�֪ͨ����
_ev_end 

 /***********************<<����ˮƽ��ת����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpFlatTurn_Cmd )
_body( BOOL, 1)//����
_ev_end 

 /***********************<<����ˮƽ��ת��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpFlatTurn_Ind )
_body( BOOL, 1)//����
_body( BOOL, 1)//�ɹ���񷵻�ֵ
_ev_end 

 /***********************<<����ˮƽ��ת֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpFlatTurn_Nty )
_body( BOOL, 1)//����֪ͨ����
_ev_end 

 /***********************<<����У���ı�����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpSetDisort_Cmd )
_body( EmTPCorrect, 1)//��Ŀ��ʶ����ʶ���������һ��
_body( EmTPCorrectChange, 1)//���ӻ��Ǽ�С��ʶ
_ev_end 

 /***********************<<����У���ı���Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpSetDisort_Ind )
_body( u32, 1)//ÿ�����ú�ķ���ֵ������������
_body( EmTPCorrect, 1)//��Ŀ��ʶ����ʶ���������һ��
_ev_end 
 /***********************<<����У���ذ�ť����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
_event(  ev_TpDisortSwitch_Cmd )
_body( BOOL, 1)//����
_ev_end 
 /***********************<<����У���ذ�ť��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon
 */
_event(  ev_TpDisortSwitch_Ind )
_body( BOOL, 1)//����
_body( BOOL, 1)//�ɹ�����Ӧ
_ev_end 

/*add by youjx 2016.11.8
/***********************<<cam����Gamma>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP -> moon -> cam
 */
 _event( ev_TpCamSetGamma_Cmd )
 _body( EmH650Gamma, 1)
 _body( u8, 1)
 _ev_end

 /***********************<<ѡ���о����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  CamCP-> moon
 */
 _event( ev_TpMechanismSelect_Cmd )
 _body( EmTPMechanism, 1)
 _ev_end

 /***********************<<��оѡ�������Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon 
 */
_event(  ev_TpMechanismSelect_Ind )
_body( EmTPMechanism, 1)
_body( BOOL, 1)
_ev_end 

/***********************<<cam����Gamma��Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  moon -> camCP
 */
 _event( ev_TpCamSetGamma_Ind )
 _body( EmH650Gamma, 1)
  _body( u8, 1)
 _body( BOOL, 1)
 _ev_end

 /***********************<<camѡ���о����֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon <- Cam
 */
_event(  ev_TpMechanismSelect_Nty )
_body( EmTPMechanism, 1)
_ev_end

 /***********************<<cam�汾֪ͨ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon <- cam
 */
_event( ev_TpMechVer_Nty )
_body( u8, 1)
_body( s8, MOON_MAX_DEVICEVER_LEN)
_body( s8, MOON_MAX_DEVICEVER_LEN)
_ev_end
 /***********************<<Moon���߻��cam�汾>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * moon -> cam
 */
 _event( ev_TpGetMechVer_Cmd )
 _ev_end
 /***********************<<��о2D��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon -> cam
 */
 _event( ev_TpSetCam2DNoiseLevle_Cmd )
 _body( BOOL, 1)
 _body( EmTPCamNoiseLevel, 1)
 _body( u8, 1)
 _ev_end
 /***********************<<��о3D��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon -> cam
 */
 _event( ev_TpSetCam3DNoiseLevle_Cmd )
 _body( BOOL, 1)
 _body( EmTPCamNoiseLevel, 1)
 _body( u8, 1)
 _ev_end
 /***********************<<��о2D�������û�Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon
 */
 _event( ev_TpSetCam2DNoiseLevle_Ind )
 _body( BOOL, 1)
 _body( EmTPCamNoiseLevel, 1)
 _body( u8, 1)
 _body( BOOL, 1)
 _ev_end
  /***********************<<��о3D�������û�Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event( ev_TpSetCam3DNoiseLevle_Ind )
 _body( BOOL, 1)
 _body( EmTPCamNoiseLevel, 1)
 _body( u8, 1)
 _body( BOOL, 1)
 _ev_end

/***********************<<��о��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon ->cam
 */
 _event( ev_CamUpgrade_Cmd )
 _body(s8,  TP_MAX_FILENAME_LEN + 1)
 _ev_end

/***********************<<��о������Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon <- cam
 */
 _event( ev_CamUpgrade_Ind )
 _body(BOOL,  1)
 _ev_end

 /***********************<<��о����ͬ������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon 
 */
 _event( ev_CamParaSynchronize_Cmd )
 _body(u8,  1)
 _ev_end

 /***********************<<��о����ͬ����Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event( ev_CamParaSynchronize_Ind )
 _body(u8,  1)
 _body(BOOL, 1)
 _ev_end

 /***********************<<�ı���ɫRGBϵ������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon -> cam
 */
 _event( ev_TPSetColorRGB_Cmd )
 _body(u8,  1)
 _body(EmTPColorConsistency, 1)
 _body(EmTPCorrectChange, 1)
 _ev_end

 /***********************<<�ı���ɫRGBϵ����Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event( ev_TPSetColorRGB_Ind )
 _body(u8,  1)
 _body(EmTPColorConsistency, 1)
 _body(u32, 1)
 _body(BOOL, 1)
 _ev_end

 /***********************<<�Զ�������ɫһ��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon ->cam
 */
 _event( ev_TPAutoSetColorConstancy_Cmd )
 _ev_end

 /***********************<<�Զ�������ɫһ���Ի�Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon <- cam
 */
 _event( ev_TPAutoSetColorConstancy_Ind )
 _body(u32, MOON_COLOR_COEFF_NUM)    //֪ͨ���������������Ϊ��ͼR����ͼG����ͼB����ͼR
                                     //��ͼG����ͼB����ͼR����ͼG����ͼB
 _body(BOOL, 1)
 _ev_end

 /***********************<<������ɫRGBϵ������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon -> cam
 */
 _event( ev_TPDirectSetColorRGB_Cmd )
 _body(u8,  1)
 _body(EmTPColorConsistency, 1)
 _body(u32, 1)
 _ev_end

  /***********************<<������ɫRGBϵ����Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event( ev_TPDirectSetColorRGB_Ind )
 _body(u8,  1)
 _body(EmTPColorConsistency, 1)
 _body(u32, 1)
 _body(BOOL, 1)
 _ev_end

  /***********************<<ѡȡ������������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon -> cam
 */
 _event( ev_TPChooseRectangle_Cmd )
 _body(TTPMoonRectRegion, 1)        //��������λ����Ϣ���������Ͻ����꣬������
 _ev_end

   /***********************<<ѡȡ���������Ӧ>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event( ev_TPChooseRectangle_Ind )
 _body(TTPMoonRectRegion, 1)
 _body(BOOL, 1)
 _ev_end

 /************<<�м�·RGBϵ���ı�ʱ֪ͨ����·RGB�ı�ϵ��>>**********
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event( ev_TPChangeSideRGB_Nty)
 _body(EmTPColorConsistency, 1)
 _body(u32, 1)                   //��һ·RGBϵ��
 _body(u32, 1)                   //����·RGBϵ��
 _ev_end

 /*****************<<�ı�����У������>>******************************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon ->cam
 */
 _event(ev_TPChangeDistor_Cmd)
 _body(u8, 1)                         //��ʾ��һ·ͼ��
 _body(EmTPDistortPosition, 1)        //��ʾ����У������
 _body(EmTPCorrectChange, 1)          //��ʾ����У���ı����ͣ����ӻ����
 _ev_end

 /*****************<<�ı�����У����Ӧ>>******************************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TPChangeDistor_Ind)
 _body(TTPDistortInfo, 1)          //����У������
 _body(BOOL, 1)
 _ev_end

 /*****************<<ֱ����������У������>>**************************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon ->cam
 */
 _event(ev_TPDirectSetDistor_Cmd)
 _body(TTPDistortInfo, 1)
 _ev_end

 /*****************<<ֱ����������У����Ӧ>>******************************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TPDirectSetDistor_Ind)
 _body(TTPDistortInfo, 1)
 _body(BOOL, 1)
 _ev_end

 /*****************<<ʹ����ʾ�������>>******************************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP -> moon 
 */
 _event(ev_TPMoonShowRectRegion_Cmd)
 _body(BOOL, 1)
 _ev_end

 /*****************<<ʹ����ʾ��������Ӧ>>******************************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TPMoonShowRectRegion_Ind)
 _body(BOOL, 1)
 _body(BOOL, 1)
 _ev_end

  /*****************<<�ָ�Ĭ��ֵ֪ͨ����ڶ�ҳ>>******************************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TpSecDefault_Nty)
 _body(TTPSecBoundaryInfo, 1)
 _body(BOOL, 1)
 _ev_end

  /*****************<<tptool��½ʱ֪ͨ����ڶ�ҳ����Ϣ>>****************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TpSecBoundary_Nty)
 _body(TTPSecBoundaryInfo, 1)
 _ev_end

 /*****************<<��ɫһ����У������>>****************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TpColorSwich_Cmd)
 _body(BOOL, 1)
 _ev_end

 /*****************<<��ɫһ����У�����ػ�Ӧ>>****************
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TpColorSwich_Ind)
 _body(BOOL, 1)
 _body(BOOL, 1)
 _ev_end

 /*****************<<����fpga��ʱ֡��>>****************
 *[����Ϣ��]			 
 * u8 �ڼ�·��о
 * u32 0-5֡
 *[��Ϣ����]
 * camCP -> moon 
 */
 _event(ev_TpFpgaDelayCorrect_Cmd)
 _body(u8, 1)
 _body(u32, 1)
 _ev_end

 /*****************<<����fpga��ʱ֡����Ӧ>>****************
 *[����Ϣ��]			 
 * u8 �ڼ�·��о
 * u32 0-5֡
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TpFpgaDelayCorrect_Ind)
 _body(u8, 1)
 _body(u32, 1)
 _body(BOOL, 1)
 _ev_end

  /*****************<<fpga��ʱ֡��֪ͨ>>****************
 *[����Ϣ��]			 
 * u8 �ڼ�·��о
 * u32 0-5֡
 *[��Ϣ����]
 * camCP <- moon 
 */
 _event(ev_TpFpgaDelayCorrect_Nty)
 _body(u8, 1)
 _body(u32, 1)
 _ev_end
//add end


#ifndef _MakeTpEventDescription_
   _ev_segment_end( outermoonextend )
};
#endif
#endif //TPP_EVENT_H
