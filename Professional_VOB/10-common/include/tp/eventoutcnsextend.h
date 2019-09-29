#ifndef _h_eventoutcnsextend_h__
#define _h_eventoutcnsextend_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSEXTENDEVENT
{
#endif 

  _ev_segment( outercnsextend  )



  /***********************<<  请求添加用户 >>********************	
  *[消息方向]	CNC	-->  CNS
  *添加用户请求，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSAddUserReq )
  _ev_end



  
  /***********************<< 回复添加用户  >>********************	
  *[消息方向]	CNS	-->  CNC
  *添加反馈
  */
  _event(  ev_CNSAddUserRet )
  _body(EmTpRet,	1)	//操作结果
  _ev_end
  



  /***********************<<  请求删除用户 >>********************	
  *[消息方向]	CNC	-->  CNS
  *删除用户请求，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSDelUserReq )
  _ev_end	
  



  /***********************<<  回复删除用户 >>********************	
  *[消息方向]	CNS	-->  CNC
  *删除反馈
  */
  _event(  ev_CNSDelUserRet )
  _body(EmTpRet,	1)	//操作结果
  _ev_end
  



  /***********************<<  请求修改密码 >>********************	
  *[消息方向]	CNC	-->  CNS
  *修改用户密码，参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSChangePWDReq )
  _ev_end	
  



  /***********************<<   回复修改密码  >>********************	
  *[消息方向]	CNS	-->  CNC
  *修改反馈
  */
  _event(  ev_CNSChangePWDRet )
  _body(EmTpRet,	1)	//操作结果
  _ev_end	
  



  /***********************<< 有一个用户登录  >>********************	
  *[消息方向]	CNS	-->  CNC
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSAddUser_Notify )
  _ev_end	
  



  /***********************<< 有一个用户退出登录  >>********************	
  *[消息方向]	CNS	-->  CNC
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSDelUser_Notify )
  _ev_end	
  



  /***********************<< 修改用户  >>********************	
  *[消息方向]	CNS	-->  CNC
  *参数为CUserFullInfo，此消息直接用OSP发送，不经过XML编解码
  */
  _event(  ev_CNSUpdateUser_Notify )
  _ev_end	
  
  

  /***********************<<用户在其它地方登录  >>********************	
  *[消息方向]	CNS	-->  CNC
  *
  */
  _event(  ev_CNSLoginByOther_Notify )
  _body(u32_ip, 1)
_ev_end	

  
  /***********************<< CNS发送CNAdapter请求Gk注册 >>********************** 
*[消息体]
* TTPGkRegistrarCfg	注册服务器配置信息
* u32					注册句柄
*[消息方向]
*  CNS	 ->  CnAdapter
*/
_event(  ev_Cn_GkRegister_Cmd )
_body( TTPGkRegistrarCfg, 1 )
_body( u32, 1 )
_ev_end


  /***********************<< 能力集通知 >>********************** 
*[消息体]	
* TCnsCapset				能力集(拆包发，先发能力集)		
*[消息方向]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallAddrCapset_Nty )
//_body( TCnsAddrCapset, 1 )
_body( TTPCnUnpackStream, CNS_CALL_MAX_CHANNEL )
_body( u16, 1 )
_body( u32, 1 )
_body( u8, 1 )
_ev_end

  /***********************<< 双流能力集通知 >>********************** 
*[消息体]	
* TCnsCapset				能力集(拆包发，先发能力集)		
*[消息方向]
*  cns	  ->  CNAdapter
*/
_event(  ev_Cn_CallDualCapset_Nty )
_body( TTPDualCap, 1 )
_ev_end

 /***********************<< 音频类型通知 >>********************** 
*[消息体]	
* EmTpAudioFormat				音频类型		
*[消息方向]
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
