#ifndef _h_eventoutsipadapter_h__
#define _h_eventoutsipadapter_h__


#include "umseventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumssipadaper
{
#endif
	
	_ev_segment( tpumswithumssipadapter )
		
 
/***********************<<  ums������� >>********************/
_event(  ev_MakeCall_Req )
	_body ( TUmsHandle  , 1  )	
	_body(TMakeCallPara, 1)
_ev_end

/***********************<<  ���з������Э�� >>********************/
_event(  ev_MakeChan_Req )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_body(BOOL32, 1) //�Ƿ���˫��
_ev_end

/***********************<<  umsӦ����� >>*********************/
_event(  ev_AnwserCall_IND )
	_body ( TUmsHandle  , 1  )	
	_body(BOOL32, 1)
	_body(EmCnsCallReason, 1)
	_body(TMakeCallPara, 1)
_ev_end
 
/***********************<<  ums���¼�����ϯͨ�� >>*********************/
_event(  evtp_cascade_OpenChairChan_cmd )
_body ( TUmsHandle  , 1  )	
_body(TCascadeOpenChanCmd, 1)
_ev_end

/***********************<<  ums���¼�����ϯӦ�� >>*********************/
_event(  evtp_cascade_OpenChairChan_ack )
_body ( TUmsHandle  , 1  )	
_body(TCascadeOpenChanAck, 1)
_ev_end


 /***********************<<  ums�ҶϺ��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_HungUp_Req )
_body ( TUmsHandle  , 1  )	
_body ( EmCnsCallReason  , 1  )	
 _ev_end

 /***********************<<  ums����ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_Register_Req )
_body ( TUmsHandle  , 1  )	
_body ( TUmsSipRegCfg  , 1  )	
_body ( u16  , 1  )	
_body ( TTPAlias  , TP_CONFTEMPGROUP_MAXNUM  )		
 _ev_end

  /***********************<<  ums����gkע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_gk_Register_Req )
_body ( TUmsHandle  , 1  )	
_body ( TRegCfg  , 1  )	
_body ( u16  , 1  )		
 _ev_end

   /***********************<<  ע������Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_register_handle_info )
_body ( TUmsHandle  , 1  )	
_body ( EmTpRegType  , 1  )		
 _ev_end

 /***********************<<  ע���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */
 _event(  evtp_ums_reg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TCnsRegRetResult  , 1  )
 _ev_end	


 /***********************<<  ums����ȡ��ע�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event(  ev_UnRegister_Req )
_body ( TUmsHandle  , 1  )	
_body (EmTpRegType, 1 )
 _ev_end

 /***********************<<  ����ɾ��ע���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_unreg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TUCSipRegResult  , 1  )
   _ev_end	

 /***********************<<  323ע��ʧ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]		--> UMS
 *
 */_event(  evtp_ums_323_unreg_ret )
	_body ( TUmsHandle  , 1  )
	_body ( TUCSipRegResult  , 1  )
   _ev_end	

/***********************<<  ���е��� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_UmsConfIncoming )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
_ev_end

/***********************<<  �������� >>********************	 
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_UmsConfCreateMeeting )
_body ( TUmsHandle  , 1  )
_body ( TUmsCallInfo  , 1  )
_body ( TTPConfTemplate  , 1  )
_ev_end

/***********************<<  �᳡���гɹ� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_Conf_UmsCallConnect )
_body ( TUmsHandle  , 1  )		
_body ( TUmsCallInfo, 1)
_ev_end

/***********************<<  ����Ҷ� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_Conf_UmsCallDisConnect )
_body ( TUmsHandle  , 1  )	
_body ( EmCnsCallReason  , 1  )	
_ev_end


/***********************<<  ͨ���� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_Conf_UmsChannelConnect )
_body ( TUmsHandle  , 1  )	
_body ( TUmsNodeCapset  , 1  )	
_ev_end

/***********************<<  ͨ���ر� >>********************	 
 *[��Ϣ��]			 
 *   
 *[��Ϣ����]	call	--> service
 *
 */
_event(  evtp_Conf_UmsChannelDisConnect )
_body ( TUmsHandle  , 1  )	
_ev_end


 /***********************<<  ͨ����Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_ChanBegin )
_ev_end


/***********************<<  �ؼ�֡���� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_AskKeyFrame )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  CNS֪ͨUms�᳡������ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_CnsSpeaker_Notify )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<   >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Chan_FlowCtrol )
_body ( TUmsHandle  , 1  )	
_body( u16 , 1)//����
_ev_end


/***********************<<  ֪ͨͨ��������  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_ChanSeeLocal_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end



/***********************<<  ֪ͨͨ��ȡ��������  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_ChanSeeLocalCancel_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ѡ�����  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_ViewObj_Ind )
_body ( TUmsHandle  , 1  )	
_body( TChanViewRes, 1)	
_ev_end


/***********************<<  ȡ��ѡ�����  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_UndoViewObj_Ind )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)	//����	
_ev_end



 /***********************<<  ˫����Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_DualBegin )
_ev_end


/***********************<<  ��˫��ͨ�� >>********************/
_event(  ev_OpenDualChan_Req )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  ��˫��ͨ�� >>********************/
_event(  ev_OpenDualChan_Incoming )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ˫��ͨ����Ӧ�� >>********************/
_event(  ev_MakeSendDual_Answer )
_body ( TUmsHandle  , 1  )
_body ( BOOL32, 1)	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  ˫��ͨ���� >>********************/
_event(  ev_OpenDualChan_Connect )
_body ( TUmsHandle  , 1  )	
_body(TUmsNodeCapset, 1)
_ev_end

/***********************<<  ˫��ͨ���Ͽ�>********************/
_event(  ev_OpenDualChan_Failed )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ֹͣ˫�� >>********************/
_event(  ev_DualChan_DisConnect )
_body ( TUmsHandle  , 1  )
_body ( EmTPChannelReason, 1 )	
_ev_end

/************************<<  ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_RequestDualStream_cmd  )
_body ( TUmsHandle  , 1  )	
_body( TEpKey, 1)	
_ev_end

/************************<<  ����˫����� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_RequestDualStream_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TDualRequestAckTr, 1)	
_ev_end


/************************<<  ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_cascade_OpenDualChan_Cmd  )
_body ( TUmsHandle  , 1  )	
_body(TDualInfoTr, 1)	
_ev_end


/************************<<  ����˫��Ӧ�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_cascade_OpenDualChan_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TDualInfoAckTr, 1)	
_ev_end

/************************<<  ֹͣ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StopRcvDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end

/************************<<  ����˫���ؼ�֡ >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_DualFastUpdate_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( BOOL32  , 1  )	
_ev_end

/************************<<  ��ʼ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StartRcvDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( TEpKey  , 1  )		//���ͷ�
_ev_end


/************************<<  ֹͣ����˫�� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StopSendDual_Ind  )
_body ( TUmsHandle  , 1  )	
_body ( TEpKey  , 1  )	
_ev_end


/************************<<  ˫��Դ����֪ͨ >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_SrcDualName_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TTPAlias, 1)
_body ( TEpKey  , 1  )	
_ev_end


/***********************<<������˫������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfStartDual_Cmd )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end

/***********************<<������˫������Ӧ��  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfStartDual_Ind )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_body ( EmTPDualReason , 1 )
_ev_end

/***********************<<������ͣ˫������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfStopDual_Cmd )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end

/***********************<<������˫������Ӧ��  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfStopDual_Ind )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_body ( EmTPDualReason , 1 )
_ev_end

/***********************<<������˫���᳡�㲥֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfDualEp_Nty )
_body (TUmsHandle, 1)
_body ( TConfEpID , 1 )
_ev_end




 /***********************<<  ��ѯ��Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_PollBegin )
_ev_end

/************************<<  ��ǰ��ѯĿ������� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_PollDstName_Ind  )
_body ( TUmsHandle  , 1  )	
_body(TPollInfoNtf, 1)
_ev_end

/***********************<<  �ϼ������¼���ʼ��ѯ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_StartPoll_cmd )
_body ( TUmsHandle  , 1  )	
_body( TPollCmdTr, 1)	
_ev_end
		
/***********************<<  �¼�Ӧ���ϼ���ʼ��ѯ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_StartPoll_ack )
_body ( TUmsHandle  , 1  )	
_body( TPollAckTr, 1)	
_ev_end
/***********************<<  �¼�֪ͨ�ϼ���ѯ���任 >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_Poll_NodeChange )
_body ( TUmsHandle  , 1  )	
_body( TEpKey, 1)	
_ev_end
/***********************<<  ֪ͨ��ѯ���� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *	UMS -> UMS
 */
_event( evtp_Conf_Poll_End )	
_body ( TUmsHandle  , 1  )	
_body ( BOOL32	 , 1  )		//�Ƿ���ͣ
_ev_end

/***********************<<  ��ѯ�ؼ�֡���� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_Poll_AskKeyFrame )	
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ������ѯ  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StartPoll_Req	 )
_body ( TUmsHandle  , 1  )	
_ev_end


/***********************<<  ������ѯ���  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StartPoll_Ind	 )
_body ( TUmsHandle  , 1  )	
_body( EmTPPollResult, 1)	//���	
_ev_end

/***********************<<  ֹͣ��ѯ  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StopPoll_Req	 )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  ֹͣ��ѯ���  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_StopPoll_Ind	 )
_body ( TUmsHandle  , 1  )	
_body( u32, 1)	//���	
_ev_end


/***********************<<  ֪ͨCNS��ǰ��ѯ״̬  >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_PollStatus_Notif	 )
_body ( TUmsHandle  , 1  )	
_body( BOOL32, 1)//�Ƿ�����ѯ	
_ev_end


/***********************<<  ѡ��  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_ViewObj_Req )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)	
_ev_end





/***********************<<  ȡ��ѡ��  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_UndoViewObj_Req )
_body ( TUmsHandle  , 1  )	
_ev_end



/***********************<< ������ѯ�б�  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsUpdateConfTurnlist_Nty )
_body (TUmsHandle, 1)
_body ( TConfTurnInfo , 1 )	
_ev_end


 /***********************<<  ������Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_UmsDiscussBegin )
_ev_end

/***********************<< ���������ۿ���  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfAMixUpdate_Cmd )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

  /***********************<<  �ϼ�UMS�����һ·��Ƶͨ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] �ϼ�UMS - �¼�UMS 
 *
 */
 _event(  evtp_OpenVidChan_Cmd )
 	_body (TUmsHandle, 1)
 	_body(TVidChanCmd, 1)
 _ev_end


  /***********************<<  �¼��ظ��ϼ�����Ƶͨ����ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] �¼�UMS - �ϼ�UMS 
 *
 */
 _event(  evtp_OpenVidChan_Ack )
 	_body (TUmsHandle, 1)
 	_body(TVidChanAck, 1)
 _ev_end

   /***********************<<  ֪ͨ�¼�ֹͣ��Ƶͨ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] �¼�UMS - �ϼ�UMS 
 *
 */
 _event(  evtp_CloseVidChan_Cmd )
 	_body (TUmsHandle, 1)
 	_body(u16, 1)
 _ev_end

 /***********************<<  ֪ͨCNS��������״̬�ͱ��� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] UMS->CNS 
 *
 */
_event(  evtp_UmsDiscussScreenStat_Notify )
	_body (TUmsHandle, 1)
	_body ( TDisScreenStat  , 1  )	
_ev_end

 /***********************<<  ��������ؼ�֡ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] UMS->CNS 
 *
 */
_event(  evtp_UmsDiscussFastUpdate_Req )
	_body (TUmsHandle, 1)
	_body (TDisAskKeyFrame  , 1  )	
_ev_end


/***********************<< ���ۻ᳡��������ӡ�ɾ����  >>********************	
*[��Ϣ����]	CNC - UMS
*
*/
_event(  ev_UmsAudMixDisListOpr_Cmd )
_body (TUmsHandle, 1)
_body (TTPDisListOpr , 1 )	
_ev_end

/***********************<< ���ۻ᳡��������ӡ�ɾ����  >>********************	
*[��Ϣ����]	CNC - UMS
*
*/
_event(  ev_UmsAudMixDisListOpr_Ind )
_body (TUmsHandle, 1)
_body (TTPDisListOpr , 1 )	
_ev_end

/***********************<< ���������ۿ�����Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfAMixUpdate_Ind )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

/***********************<< ���������ۿ���֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfAMixUpdate_Nty )
_body (TUmsHandle, 1)
_body ( TConfAuxMixInfo , 1 )	
_ev_end

 /***********************<<  �������������Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_UmsEapuBegin )
_ev_end

/***********************<< �᳡��������״̬֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsAudMixStatus_Nty )
_body (TUmsHandle, 1)
_body ( TAudMixStat , 1 )	
_ev_end

 /***********************<<  ֪ͨ�¼���CNS���»᳡�ķ�����ϯ���� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] UMS->CNS 
 *
 */
_event(  evtp_UmsCnsSpeakerIndxAdjust_Notify )
	_body (TUmsHandle, 1)
	_body (TCnsSpeakerAdjust  , 1  )	
_ev_end

/***********************<<  �ϼ������һ·��Ƶͨ�� >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] UMS - �¼�UMS 
 *
 */
 _event(  evtp_OpenAudChan_Cmd )
	_body (TUmsHandle, 1)
	_body(TAudChanCmd, 1)
 _ev_end

   /***********************<<  �¼��ظ��ϼ�����Ƶͨ����ָʾ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����] �¼�UMS - �ϼ�UMS 
 *
 */
 _event(  evtp_OpenAudChan_Ack )
 	_body (TUmsHandle, 1)
 	_body(TAudChanAck, 1)
 _ev_end

 /***********************<<  ��Ҫ֪ͨCNS�Ļ���״̬��Ϣ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_CnsConfStatBegin )
_ev_end

//////////////////////////////////////////////////////////////////////////
//֪ͨUI��״̬��Ϣ����Ϊ��Sip���͸�CNS


/***********************<< �������л�������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfApplySpeaker_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )	
_ev_end

/***********************<< �������л������˻�Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfApplySpeaker_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( EmTpApplySpeakerRet , 1 )
_ev_end

/***********************<< �������л�������֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfApplySpeaker_Nty )
_body ( TUmsHandle, 1 )
_body ( TConfEpID , 1 )	
_ev_end

/***********************<< ���������Զ������  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfMute_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end

/***********************<< ���������Զ��������Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfMute_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end

/***********************<< ���������Զ������֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfMute_Nty )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ��������FALSEȡ��Զ������_
_ev_end

/***********************<< ���������Զ�˾���  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsConfQuiet_Cmd )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end

/***********************<< ���������Զ�˾�����Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfQuiet_Ind )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end

/***********************<<���������Զ�˾���֪ͨ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsConfQuiet_Nty )
	_body (TUmsHandle, 1)
	_body ( TConfEpID , 1 )
	_body ( BOOL , 1 )//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end

/***********************<<��������ͨ�����������б��в����ڵĻ᳡  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsInviteCnsByAlias_Cmd )
	_body (TUmsHandle, 1)
	_body ( TTPAlias , 1 )
_ev_end

/***********************<<��������ͨ�����������б��в����ڵĻ᳡��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsInviteCnsByAlias_Ind )
	_body (TUmsHandle, 1)
	_body ( TTPAlias , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<��������ͨ�����ֺ����б��д��ڵĲ����߻᳡  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsInviteCnsByEpId_Cmd )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
_ev_end

/***********************<<��������ͨ�����ֺ����б��д��ڵĲ����߻᳡��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsInviteCnsByEpId_Ind )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<���Ҷ�ָ���᳡  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsHangupCns_Cmd )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
_ev_end

/***********************<<���Ҷ�ָ���᳡��Ӧ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsHangupCns_Ind )
	_body (TUmsHandle, 1)
	_body ( u16 , 1 )
	_body ( EmCnsCallReason , 1 )
_ev_end

/***********************<<�Ҷϻ���  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsHangupConf_Cmd )
	_body (TUmsHandle, 1)
_ev_end

/***********************<< ֪ͨ��ϯ������Ϣ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsChairConfInfo_Nty )
	_body (TUmsHandle, 1)
	_body ( TChairConfInfo , 1 )	
_ev_end

/***********************<< ֪ͨ����ԭ����ʾ ͨ��  >>********************	
*[��Ϣ����]	UMS	-->  CNS -> cnc
*
*/
_event(  ev_UmsCommonReasonToUI_Ind )
	_body (TUmsHandle, 1)
	_body ( TTPUmsReasonInd , 1 )	
_ev_end


_event( ev_SipAdapter_GetVid_Begin )
_ev_end

/***********************<<  �ϼ������¼�����Ƶͼ�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_cascade_GetVid_cmd )
_body ( TUmsHandle  , 1  )	
_body( TViewCmdTr, 1)	
_ev_end
		
/***********************<<  �ϼ������¼�����Ƶͼ��Ӧ�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_cascade_GetVid_ack )
_body ( TUmsHandle  , 1  )	
_body( TViewAckTr, 1)	
_ev_end

/***********************<<  �ϼ�ֹͣ�¼���ͼ�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_cascade_StopGetVid_cmd )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)		//���
_ev_end




 /***********************<<  ������Ϣ��ʼ >>********************	
 *[��Ϣ��]			 
 *   NULL
 *[��Ϣ����]	
 *
 */
 _event( ev_SipAdapter_OtherConfBegin )
_ev_end

/***********************<<��ȡȫ����UMS��CNS��ȫ��ע����Ϣ  >>********************	
*[��Ϣ����]	CNS	-->  UMS
*
*/
_event(  ev_UmsGetRegInfo_Req )
	_body ( TUmsHandle, 1)
	_body ( TUmsSipRegCfg, 1)
	_body ( EmGetRegInfoType , 1 )
	_body ( u32,	1)	//SIP ע����
	_body ( u32,	1)	//GK ע����
_ev_end

/***********************<< ��ȡȫ����CNS��ȫ��ע����Ϣ�ظ�  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_Rsp )
	_body ( TUmsHandle, 1)
	_body ( TTPSipRegPackInfo , 1 )
	_body ( EmGetRegInfoType , 1 )
	_body ( TTPSipRegInfo , 1 )
_ev_end

/***********************<< ȫ�ֵ�ַ��UMSע����Ϣ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_UmsRspEx )
_body ( TUmsHandle, 1)
_body ( TRegPackInfoEx, 1)
_body ( TUmsRegPackEx, 1)
_ev_end

/***********************<< ȫ�ֵ�ַ��CNSע����Ϣ  >>********************	
*[��Ϣ����]	UMS	-->  CNS
*
*/
_event(  ev_UmsGetRegInfo_CnsRspEx )
_body ( TUmsHandle, 1)
_body ( TRegPackInfoEx, 1)
_body ( TCnsRegPackEx, 1)
_ev_end

/***********************<< MT ע����Ϣ  >>********************	
*
*/
_event(  ev_UmsGetGkRegInfo_MtRsp )
_body ( TUmsHandle, 1)
_body ( EmGetRegInfoType, 1)
_body ( TTPMtRegInfo, 1)
_ev_end

/***********************<< MCU ע����Ϣ  >>********************	
*
*/
_event(  ev_UmsGetGkRegInfo_McuRsp )
_body ( TUmsHandle, 1)
_body ( EmGetRegInfoType, 1)
_body ( TTPMcuRegInfo, 1)
_ev_end


/***********************<<  �¼����ϼ����»����� >>********************	 
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event(  evtp_Conf_EpCallInfo_Update )
_body ( TUmsHandle  , 1  )	
_body ( TConfNodeCallUpdateTrList, 1 )
_ev_end

/***********************<<  �¼����ϼ����»����� >>********************	 
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event(  evtp_Conf_EpChanInfo_Update )
_body ( TUmsHandle  , 1  )	
_body ( TConfNodeChanUpdateTrList, 1 )
_ev_end

/***********************<<  �¼����ϼ�ɾ�������� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event(  evtp_Conf_EpInfo_Del )
_body ( TUmsHandle  , 1  )	
_body( TConfNodeDelTrList, 1)
_ev_end

/***********************<<  �ϼ����¼�֪ͨ���������� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_YouAreSeeing_Ind )
_body ( TUmsHandle  , 1  )	
_body( TSpeakerCapTr, 1)
_ev_end

/***********************<<  ֪ͨ�ն��ڶ������� H323 >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����] �ն� - > UMS	
 *
 */
_event( evtpH323_Conf_MultipleConference_Ind )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  �����ն��б� H323 >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����] �ն� - > UMS	
 *
 */
_event( evtpH323_Conf_TerminalListRequest )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums֪ͨCNS��ϯ��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_IsChair_Notify )
_body ( TUmsHandle  , 1  )	
_body( BOOL32, 1)
_ev_end

/***********************<<  Ums֪ͨ��ϯ�л᳡��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_LeftConf_Notify )
_body ( TUmsHandle  , 1  )	
_body( TConfEpIDInfo, 1)
_ev_end

/***********************<<  Ums֪ͨ��ϯ�л᳡��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_JoinConf_Notify )
_body ( TUmsHandle  , 1  )	
_body( TConfEpIDInfo, 1)
_ev_end

/***********************<<  Ums֪ͨCNS���������  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_MultConf_Notify )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums֪ͨCNS�뿪������  >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_CancelMultConf_Notify )
_body ( TUmsHandle  , 1  )	
_ev_end

/***********************<<  Ums֪ͨCNS����״̬ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_StatusInfo_Notify )
_body ( TUmsHandle  , 1  )	
_body( TTPConfInfoNtfy, 1)
_ev_end


/***********************<<  Ums֪ͨUms�᳡������ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_CnsSpeakerCascad_Notify )
_body ( TUmsHandle  , 1  )	
_body(TCnsSpeakerAdjust, 1)
_ev_end

/***********************<<  ֪ͨԶ������ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_MuteRemoteEp_Cmd )
_body ( TUmsHandle  , 1  )	
_body(TMuteRmtEpCmd, 1)
_ev_end


/***********************<<  Զ������ָʾ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_MuteRemoteEp_Ind )
_body ( TUmsHandle  , 1  )	
_body(TMuteRmtEpInd, 1)
_ev_end


/***********************<<  ֪ͨԶ�˾��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_QuietRemoteEp_Cmd )
_body ( TUmsHandle  , 1  )	
_body(TQuietRmtEpCmd, 1)
_ev_end


/***********************<<  Զ�˾���ָʾ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_QuietRemoteEp_Ind )
_body ( TUmsHandle  , 1  )	
_body(TQuietRmtEpInd, 1)
_ev_end

/***********************<<  ����δ���߻᳡ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_CallExistEPTr_cmd )
_body ( TUmsHandle  , 1  )	
_body(u16, 1)	//epID
_body(TTPAlias, 1)
_ev_end

/***********************<<  �Ҷϻ᳡ >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_DropEPTr_cmd )
_body ( TUmsHandle  , 1  )	
_body(TDropEpCmd, 1)	
_ev_end

/************************<<  ����ǽ��� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_TvMonitor_Cmd  )
_body ( TUmsHandle  , 1  )	
_body( TTvMonitorCmdTr, 1)
_ev_end

/************************<<  ����ǽ��� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_TvMonitor_Ind  )
_body ( TUmsHandle  , 1  )	
_body( TTvMonitorIndTr, 1)
_ev_end

/************************<<  ����ǽ��� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_TvMonitor_stop  )
_body ( TUmsHandle  , 1  )	
_body( u16, 1)
_ev_end

/************************<<  �ؼ�֡���� >>********************
*[��Ϣ��]			 
*   NULL	
*[��Ϣ����]	
*
*/
_event( evtp_Conf_AskKeyByScreen  )
_body ( TUmsHandle  , 1  )	
_body( TAskKeyByScreenTr, 1)
_ev_end


/***********************<<  Ums֪ͨUMS��ϯ���� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_ChairCap_Notify )
_body ( TUmsHandle  , 1  )	
_body( TChairInfoTr, 1)
_ev_end


/***********************<<  UMS֪ͨCMS����CNS�б� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */_event(  evtp_Conf_CnsList_Notify )
 _body ( TUmsHandle  , 1  )	
	_body ( TConfCnsInfo  , 1  )
   _ev_end

   /************************<<  viewlocal >>********************
   *[��Ϣ��]			 
   *   NULL	
   *[��Ϣ����]	
   *
   */
   _event( evtp_Conf_ViewLocal_Cmd  )
   _body ( TUmsHandle  , 1  )	
   _ev_end
   
   /************************<<  cannelviewlocal >>********************
   *[��Ϣ��]			 
   *   NULL	
   *[��Ϣ����]	
   *
   */
   _event( evtp_Conf_CancelViewLocal_Cmd  )
   _body ( TUmsHandle  , 1  )	
   _ev_end
   
/***********************<<   >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_FlowCtrol )
_body ( TUmsHandle  , 1  )	
_body ( TEpKey  , 1  )	
_body( u16 , 1)//����
_ev_end

/***********************<<  ����֡�� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_AdjustFrameRate )
_body ( TUmsHandle  , 1  )	
_body ( TAdjustFrameRate  , 1  )	
_ev_end

/***********************<<  �����ֱ��� >>********************
 *[��Ϣ��]			 
 *   NULL	
 *[��Ϣ����]	
 *
 */
_event( evtp_Conf_AdjustVidRes )
_body ( TUmsHandle  , 1  )	
_body ( TAdjustVidRes  , 1  )	
_ev_end


/***********************<<���������Ϣ   >>********************
 */
_event( evtp_Conf_Clear )
_body ( TUmsHandle  , 1  )	
_ev_end


/***********************<<����״̬����  >>********************
 */
_event( evtp_Conf_RecPlayState_Nty )
_body ( TUmsHandle  , 1  )
_body ( TUpRecPlayState, 1)
_ev_end

/***********************<< �ϼ�֪ͨ�¼�ֹͣ����  >>********************
 */

 _event( evtp_Conf_StopRecPlay_Req )
 _body ( TUmsHandle  , 1  )
 _body ( u32,	1)
_ev_end


/***********************<< ����ؼ�֡����  >>********************
 */

 _event( evtp_Conf_ResetFastUpdate )
 _body ( TUmsHandle  , 1  )
 _body ( u32,	1)
_ev_end

/***********************<< �ر�ͨ������  >>********************
 */

 _event( evtp_Close_Chan_Req )
 _body ( TUmsHandle  , 1  )
 _body ( EmChanType,	1) //�ر�ͨ������
 _body ( TUmsNodeCapset, 1)
_ev_end

#ifndef _MakeTpEventDescription_
_ev_segment_end(tpumswithumssipadapter)
};
#endif


#endif // _h_eventoutsipadapter_h__
