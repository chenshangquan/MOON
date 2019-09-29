#ifndef _h_eventoutcnsextend_h__
#define _h_eventoutcnsextend_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSEXTENDEVENT
{
#endif 

  _ev_segment( outercnsextend  )



  /***********************<<  ��������û� >>********************	
  *[��Ϣ����]	CNC	-->  CNS
  *����û����󣬲���ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSAddUserReq )
  _ev_end



  
  /***********************<< �ظ�����û�  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *��ӷ���
  */
  _event(  ev_CNSAddUserRet )
  _body(EmTpRet,	1)	//�������
  _ev_end
  



  /***********************<<  ����ɾ���û� >>********************	
  *[��Ϣ����]	CNC	-->  CNS
  *ɾ���û����󣬲���ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSDelUserReq )
  _ev_end	
  



  /***********************<<  �ظ�ɾ���û� >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *ɾ������
  */
  _event(  ev_CNSDelUserRet )
  _body(EmTpRet,	1)	//�������
  _ev_end
  



  /***********************<<  �����޸����� >>********************	
  *[��Ϣ����]	CNC	-->  CNS
  *�޸��û����룬����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSChangePWDReq )
  _ev_end	
  



  /***********************<<   �ظ��޸�����  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *�޸ķ���
  */
  _event(  ev_CNSChangePWDRet )
  _body(EmTpRet,	1)	//�������
  _ev_end	
  



  /***********************<< ��һ���û���¼  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSAddUser_Notify )
  _ev_end	
  



  /***********************<< ��һ���û��˳���¼  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSDelUser_Notify )
  _ev_end	
  



  /***********************<< �޸��û�  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *����ΪCUserFullInfo������Ϣֱ����OSP���ͣ�������XML�����
  */
  _event(  ev_CNSUpdateUser_Notify )
  _ev_end	
  
  

  /***********************<<�û��������ط���¼  >>********************	
  *[��Ϣ����]	CNS	-->  CNC
  *
  */
  _event(  ev_CNSLoginByOther_Notify )
  _body(u32_ip, 1)
_ev_end	

  
  /***********************<< CNS����CNAdapter����Gkע�� >>********************** 
*[��Ϣ��]
* TTPGkRegistrarCfg	ע�������������Ϣ
* u32					ע����
*[��Ϣ����]
*  CNS	 ->  CnAdapter
*/
_event(  ev_Cn_GkRegister_Cmd )
_body( TTPGkRegistrarCfg, 1 )
_body( u32, 1 )
_ev_end


  /***********************<< ������֪ͨ >>********************** 
*[��Ϣ��]	
* TCnsCapset				������(��������ȷ�������)		
*[��Ϣ����]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallAddrCapset_Nty )
//_body( TCnsAddrCapset, 1 )
_body( TTPCnUnpackStream, CNS_CALL_MAX_CHANNEL )
_body( u16, 1 )
_body( u32, 1 )
_body( u8, 1 )
_ev_end

  /***********************<< ˫��������֪ͨ >>********************** 
*[��Ϣ��]	
* TCnsCapset				������(��������ȷ�������)		
*[��Ϣ����]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallDualCapset_Nty )
_body( TTPDualCap, 1 )
_ev_end

 /***********************<< ��Ƶ����֪ͨ >>********************** 
*[��Ϣ��]	
* EmTpAudioFormat				��Ƶ����		
*[��Ϣ����]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_AudioFormat_Nty )
_body( EmTpAudioFormat, 1 )
_ev_end
#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsextend )
};
#endif
#endif //TPP_EVENT_H
