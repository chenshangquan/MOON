#ifndef _h_eventoutcnds_h__
#define _h_eventoutcnds_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCNDSEVENT
{
#endif 
	
	_ev_segment( outercnds  )


	/***********************<<  创建一个交换 >>********************	
 *[消息体]			 
 *   TTPCnDsData
 *[消息方向]	cndsnodepool	--> cnmediadsinst
 *
 */_event(  ev_cn_media_dscreate )
	_body( TTPCnDsData,		1 )
   _ev_end

/***********************<<  销毁一个交换 >>********************	
 *[消息体]			 
 *   TTPCnDsData
 *[消息方向]		cndsnodepool	--> cnmediadsinst
 *
 */_event(  ev_cn_media_dsdestroy )
	_body( TTPCnDsData,		1)
   _ev_end

     /***********************<< 取得ds handle >>**********************	
 *[消息体]			 
 *无
 *[消息方向]
 *   cnService--> cndsmgr
 */
   _event( ev_Cn_GetDSHandle_Req )
   _body( u8,		1)
   _ev_end

     /***********************<< 取得ds handle >>**********************	
 *[消息体]			 
 *u32_ip 
 *[消息方向]
 *  cndsmgr --> cnService
 */
   _event( ev_Cn_GetDSHandle_Rsp )
   _body( u32, 1 )
   _ev_end



/***********************<< 创建mt到cns交换命令 >>**********************	
 *[消息体]	
 *u32
 *u16 edge tpye
 *u16 RcvFrom Type
 *u16 SendTo Type
 *
 *[消息方向]
 *   cnService--> cndsmgr

 *建立RcvFrom 至 SendTo的rtp交换以及反向的RTCP交换
 */
 _event( ev_Cn_Ds_Create_DsPair_Cmd )
    _body( u32, 1 )
	_body( u16, 1)
   _body ( u16    , 1    )
   _body ( u16    , 1    )
   _ev_end

   /***********************<< 创建Ds >>**********************	
 *[消息体]		
 *u32 Ds Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Create_RTP_Ds_Cmd )
   _body( u32, 1 )
  _body( u16, 1)
  _body( u16, 1)
  _body( u16, 1)
   _ev_end

      /***********************<< 创建Ds >>**********************	
 *[消息体]		
 *u32 Ds Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Create_RTCP_Ds_Cmd )
   _body( u32, 1 )
  _body( u16, 1)
  _body( u16, 1)
  _body( u16, 1)
   _ev_end

    /***********************<< 销毁所有ds和节点 >>**********************	
 *[消息体]			 
 *u32 Ds Handle
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Destroy_All_Cmd )
   _body( u32, 1 )
   _body( BOOL, 1 )
   _ev_end

    /***********************<< 销毁特定类型ds >>**********************	
 *[消息体]			 
 *u32 Ds Handle
 *u16 Ds Type
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Destroy_Ds_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _ev_end

     /***********************<< 销毁特定类型ds和Ds节点 >>**********************	
 *[消息体]			 
 *u32 Ds Handle
 *u16 Ds Type
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Destroy_Ds_And_Node_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _ev_end

        /***********************<< 销毁特定类型ds和Ds节点 >>**********************	
 *[消息体]			 
 *u32 Ds Handle
 *u16 Ds Type
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Destroy_Ds_Port_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _ev_end

      /***********************<< 重建特定类型ds >>**********************	
 *[消息体]			 
 *u32 Ds Handle
 *u16 Ds Type
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Rebuild_Ds_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _ev_end

  /***********************<< 显示特定类型ds >>**********************	
 *[消息体]			 
 *u32 Ds Handle
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Ds_Show_DsNode_Cmd )
   _body( u32, 1 )
   _body( EmTPDsNode, 1 )
   _ev_end

/***********************<< 创建netbuf >>**********************	
 *[消息体]			 
 *u32  Handle
 *u16 Ds Type
 *TTPCnRSParam
 *TTPCnNetBufPara 
 *[消息方向]
 *   cnService --> cndsmgr
 * NB 与dst 端口为自动分配
 */
   _event( ev_Cn_Nb_Create_Cmd )
   _body( u32, 1 )
   _body( u16, 1 )
   _body( u16, 1 )
   _body( TTPCnRSParam, 1 )	 
   _body( TTPCnNetBufPara, 1 )	 
   _ev_end
 
   /***********************<< 创建混音器 >>**********************	
 *[消息体]			 
 *EmCnAudioMixID 混音器类型
 *u16
 *[消息方向]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_Create )
   _body( EmCnAudioMixID, 1 )
   _body( u16, 1 )
   _ev_end

      /***********************<< 销毁混音器 >>**********************	
 *[消息体]			 
 *EmCnAudioMixID 混音器类型
 *u16
 *[消息方向]
 *   cnService --> cnaudiomixinst
 */  
   _event( ev_Cn_AMix_Destroy )
   _body( EmCnAudioMixID, 1 )
   _body( u16, 1 )
   _ev_end

   /***********************<< 加入混音通道 >>**********************	
 *[消息体]			 
 *EmCnAudioMixID 混音器类型
 *u8
 *TTPMixerChannelParam
 *[消息方向]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_CreateChan_Cmd )
   _body( EmCnAudioMixID, 1 )
   _body( u8, 1 )
   _body( TTPMixerChannelParam, 1 )
   _ev_end

      /***********************<< 删除混音通道 >>**********************	
 *[消息体]			 
 *EmCnAudioMixID 混音器类型
 *u8
 *[消息方向]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_DestroyChan_Cmd )
   _body( EmCnAudioMixID, 1 )
   _body( u8, 1 )
   _ev_end


      /***********************<< 设置N模式 >>**********************	
 *[消息体]			 
 *EmCnAudioMixID
 *TTPNetAddress  LocalAddr
 *TTPNetAddress  LocalRtcpAddr
 *TTPNetAddress DstNetAddr
 *[消息方向]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_SetNMode_Cmd )
   _body( EmCnAudioMixID, 1 )
   _body( TTPNetAddress, 1 )
   _body( TTPNetAddress, 1 )
   _body( TTPNetAddress, 1 )
   _ev_end

      /***********************<< 开始混音 >>**********************	
 *[消息体]			 
 *EmCnAudioMixID
 *[消息方向]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_StartMix_Cmd)
   _body( EmCnAudioMixID, 1 )
   _ev_end

        /***********************<< 停止混音 >>**********************	
 *[消息体]			 
 *u32
 *[消息方向]
 *   cnService --> cnaudiomixinst
 */
   _event( ev_Cn_AMix_StopMix_Cmd)
   _body( EmCnAudioMixID, 1 )
   _ev_end

  /***********************<< 激励回调通道 >>**********************	
 *[消息体]			 
 *EmCnAudioMixID
 *u8
 *[消息方向]
 *   cnaudiomixinst --> cnservice
 */
   _event( ev_Cn_AMix_Channel_CBPos_Nty)
   _body( EmCnAudioMixID, 1 )
   _body( u8, 1 )
   _ev_end

   /*********双流通道建立成功通知**************************/
   //参数，是否发送通道
   /*[消息方向]
   *  cnservice --> cnc
   */
   _event( ev_Cn_DualChanConnect_Nty )
   _body( BOOL, 1)
   _ev_end
   
   /*********双流通道释放成功通知**************************/
   /*[消息体]，
    * BOOL 是否发送通道
	* EmTPChannelReason 断开原因
   /*[消息方向]
   *  cnservice --> cnc
   */
   _event( ev_Cn_DualChanDisConnect_Nty )
   _body( BOOL, 1)
   _body( EmTPChannelReason, 1)
   _ev_end
   
  /*********获取Pad关键帧的定时器**************************/
   //[消息体]
   /*无
   *[消息方向]
   *  cnservice --> cnservice
   */
   _event(  ev_CnPadKeyFrame_Timer )
   _ev_end

   /*********添加PC Ds**************************/
   //[消息体]
   /*PC IP：u32_ip
   *[消息方向]
   *  cnservice --> cnservice
   */
   _event(  ev_CnDsAddRcvToPC_Cmd )
   _body( u32_ip, 1)
   _ev_end

   /*********cnds注册cn的定时器**************************/
   //[消息体]
   /*无
   *[消息方向]
   *  cndsmgr --> cndsmgr
   */
   _event(  ev_CnDsRegCn_timer )
  _ev_end

   /*********cnds注册cn的超时定时器**************************/
   //[消息体]
   /*无
   *[消息方向]
   *  cndsmgr --> cndsmgr
   */
  _event(  ev_CnDsRegCn_timer_Out )
  _ev_end

   /*********cnds请求注册cn**************************/
   //[消息体]
   /*无
   *[消息方向]
   *  cndsmgr --> cnservice
   */
  _event(  ev_CnDsregcn_req )
  _body( u32_ip, 1 )
  _ev_end
  
  /*********cnds请求注册cn的回复**************************/
   //[消息体]
   /*cns IP：u32_ip
   *[消息方向]
   *  cnservice -->cndsmgr 
   */
  _event(  ev_CnDsregcn_Rsp )
  _body( u32_ip, 1)
  _ev_end


   /*********cnds请求注册cn的回复**************************/
   //[消息体]
   /*u32:handle
   u16: type
	TTPCnMediaTransPort
   *[消息方向]
   *  cnservice -->cndsmgr 
   */
  _event( ev_Cn_Ds_Add_Port_Cmd )
  _body( u32, 1 )
  _body( u16, 1 )
  _body ( TTPCnMediaTransPort    , 1    )
   _ev_end

  
	  /***********************<< 创建Ds >>**********************	
 *[消息体]	
 *u32 Ds src Handle
 *u32 Ds dest Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Create_Debug_RTP_Ds_Cmd )
   _body( u32, 1 )
    _body( u32, 1 )
  _body( u32, 1 )
  _body( u16, 1)
  _body( u16, 1)
  _body( u16, 1)
   _ev_end
   
   	  /***********************<< 创建Ds >>**********************	
 *[消息体]		
 *u32 Ds src Handle
 *u32 Ds dest Handle
 *u16 Ds Type
 *u16 Rcv From Port Type
 *u16 Snd To Port Type
 *TTPCnMediaTransPort
 *[消息方向]
 *   cnService --> cndsmgr
 */
   _event( ev_Cn_Create_Debug_RTCP_Ds_Cmd )
   _body( u32, 1 )
   _body( u32, 1 )
  _body( u32, 1 )
  _body( u16, 1)
  _body( u16, 1)
  _body( u16, 1)
   _ev_end

#ifndef _MakeTpEventDescription_
		_ev_segment_end( outercnds )
};
#endif
#endif