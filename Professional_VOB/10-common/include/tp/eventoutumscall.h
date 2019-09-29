#ifndef _h_eventoutumscall_h__
#define _h_eventoutumscall_h__


#include "tpeventcomm.h"


#ifndef _MakeTpEventDescription_
enum Emtpouterumscall
{
#endif
	
	_ev_segment( outerumscall )

// Notify����Ϣ
/***********************<<  UMS֪ͨUMC���ӻ����б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
 _event(  evtp_AddConfList_Notify )
_body ( TAddConfList  , 1  )
 _ev_end

/***********************<<  UMS֪ͨUMCɾ���Ļ����б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */_event(  evtp_DelConflist_Notify )
	_body ( TDelConfList  , 1  )
   _ev_end

/***********************<<  UMS֪ͨUMC����᳡�б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */_event(  evtp_UpdateConfCnsList_Notify )
	_body ( TConfCnsInfo  , 1  )
   _ev_end

/***********************<<  UMS֪ͨUMC�����˸ı� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_SpeakerChange_Notify )  //brd
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMS֪ͨCMS��ϯ�ı� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */
_event(  evtp_ChairManChange_Notify )
_body ( TConfEpID  , 1  )
_ev_end

/***********************<<  UMS֪ͨUMC��ϯ��Ļ״̬ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_ChairStreenStatus_Notify )  //brd
_body ( TChairStreenInfo, 1)
_ev_end

// begin edit by gaoyong
/***********************<<  UMS֪ͨUMC���������б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_AuxMixInfo_Notify ) //brd
_body ( TConfAuxMixInfo  , 1  )
_ev_end

/***********************<<  UMS֪ͨUMC������ѯ�б� >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_UpdateConfTurnlist_Notify )  //brd
_body ( TConfTurnInfo  , 1  )
_ev_end


// cmd��Ϣ
/***********************<<  UMC����UMS���������б� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_UpdateAudMixInfo_cmd )
_body (TTPDisListOpr , 1 )
_ev_end


/***********************<<  UMC����UMS���������б��Ӧ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_UpdateAudMixInfo_Ind )
_body (TTPDisListOpr , 1 )
_ev_end

/***********************<<  UMC����UMS�������� >>********************	
 *[��Ϣ����]	UMC	-->  UMS
 *
 */
_event(  evtp_StartAuxMix_cmd )
_body (TConfAuxMixInfo , 1 )
_ev_end


/***********************<<  UMC����UMS�������ۻ�Ӧ >>********************	
 *[��Ϣ����]	UMS	-->  UMC
 *
 */
_event(  evtp_StartAuxMix_ind )
_body (TConfAuxMixInfo , 1 )
_ev_end

/***********************<<  UMC����UMS������ѯ�б� >>********************	
*[��Ϣ����]	  UMC	-->  UMS
*
*/
_event(  evtp_UpdateTurn_cmd )
_body ( TConfTurnInfo  , 1  )
_ev_end


/***********************<<  UMC����UMS������ѯ�б��Ӧ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_UpdateTurn_ind )
_body ( TConfTurnInfo  , 1  )
_body ( u32, 1) // TP_RET_ERROR  and  TP_RET_OK
_ev_end

/***********************<<  UMC����UMS������ѯ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_StartTurn_cmd )
_body ( u16  , 1  )
_ev_end

/***********************<<  UMC����UMS������ѯ��Ӧ>>********************	
*[��Ϣ����]	UMS -->  UMC
*	����Ϊ����ID
*/
_event(  evtp_StartTurn_ind )
_body ( u16  , 1  )
_body ( EmTPPollResult, 1)
_ev_end


/***********************<<  UMC����UMS�ر���ѯ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_StopTurn_cmd )
_body ( u16  , 1  )
_ev_end


/***********************<<  UMC����UMS�ر���ѯ��Ӧ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*	����Ϊ����ID
*/
_event(  evtp_StopTurn_ind )
_body ( u16  , 1  )
_body ( u32, 1) // TP_RET_ERROR  and  TP_RET_OK
_ev_end

/***********************<<  UMC����UMSѡ���᳡ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_ViewObj_cmd )
_body ( TConfEpID  , 1  ) // �����id����Ҫѡ���᳡��id
_body ( u16  , 1  ) // // ѡ������� 0 1 2
_ev_end

/***********************<<  UMC����UMSѡ���᳡��Ӧ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*	����Ϊ����ID
*/
_event(  evtp_ViewObj_ind )
_body ( TConfEpID  , 1  ) // �����id����Ҫѡ���᳡��id
_body ( u16  , 1  ) // // ѡ������� 0 1 2
_body ( TChanViewRes, 1) 
_ev_end

/***********************<<  UMC����UMSȡ��ѡ���᳡ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*	����Ϊ����ID
*/
_event(  evtp_UndoViewObj_cmd )
_body ( u16  , 1) // confid
_body ( u16, 1)  // ѡ��������� 0 1 2
_ev_end


/***********************<<  UMC����UMSȡ��ѡ���᳡��Ӧ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*	����Ϊ����ID
*/
_event(  evtp_UndoViewObj_ind )
_body ( u16  , 1  ) // confid
_body ( u16, 1)  // ѡ��������� 0 1 2
_body ( EmTPViewResult, 1) 
_ev_end

// end edit by gaoyong 

/***********************<<  CMS�����ٿ����� >>********************	
*[��Ϣ����]	UMS	-->  CMS
*
*/
_event(  evtp_StartConfTemplate_Req )
_body ( u16  , 1  )
_ev_end


/***********************<<  CMS����UMS�ٿ������� >>********************	
*[��Ϣ����]	CMS	-->  UMS
*
*/
_event(  evtp_StartConfTemplate_Ret )
_body ( TStartConfResult  , 1  )
_ev_end


/***********************<<  CMS����UMS�Ҷϻ��� >>********************	
*[��Ϣ����]	CMS	-->  UMS
*	����Ϊ����ID
*/	
_event(  evtp_HungUpConf_cmd )
_body ( u16  , 1  )
_ev_end

/***********************<<  CMS����UMS�Ҷϻ����� >>********************	
*[��Ϣ����]	UMS	-->  CMS
*	����Ϊ����ID
*/	
_event(  evtp_HungUpConf_result )
_body ( u16  , 1  )			//����ID
_body ( EmTpDropConfRet, 1) //���
_ev_end


// begin edit by gaoyong
/***********************<<  UMC��ʱ����EP >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/ 
_event(  evtp_CallEP_cmd )
_body ( TConfCallEpAddr  , 1  )
_ev_end


/***********************<<  UMC����UMS�����Ѿ����ڵ�EP : δ���� >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_CallExistEP_cmd )
_body ( TConfEpID  , 1  )
_ev_end

/***********************<<  UMC��ʱ����EP��� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_CallEP_result )
_body ( TConfCallEpAddr  , 1  )
_body ( EmCnsCallReason  , 1  )
_ev_end

/***********************<<  UMC����UMS�����Ѿ����ڵ�EP���>>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_CallExistEP_result )
_body ( TConfEpID  , 1  )
_body ( EmCnsCallReason  , 1  )
_ev_end

/***********************<<  UMC����UMS�Ҷ�EP >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_DropEp_cmd )
_body ( TConfEpID  , 1  )	
_ev_end


/***********************<<  UMC����UMS�Ҷ�EP��� >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_DropEp_Ind )
_body ( TConfEpID  , 1  )
_body ( EmCnsCallReason, 1)	//EmCnsCallReason_hungup ���عҶϳɹ�  EmCnsCallReason_dstnotfind Ŀ�겻����
_ev_end

/***********************<<  CMS����UMSɾ��EP >>********************	
*[��Ϣ����]	CMS	-->  UMS   // umsδ����
*
*/
_event(  evtp_DeleteEp_cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMC����UMSָ�������� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_ApplySpeaker_cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  UMS֪ͨUMCָ�������˽�� >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_ApplySpeaker_result )
_body ( TConfEpID  , 1  )	
_body ( EmTpApplySpeakerRet  , 1  )	
_ev_end


/***********************<<  UMCָ��Զ������ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_MuteEp_cmd )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUEָʾԶ��������FALSEȡ��Զ������
_ev_end

/***********************<<  UMCָ��Զ��������Ӧ >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_MuteEp_Ind )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUEָʾԶ��������FALSEȡ��Զ������
_ev_end


/***********************<<  UMCָ��Զ�˾��� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_QuietEp_cmd )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end

/***********************<<  UMCָ��Զ�˾�����Ӧ >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_QuietEp_Ind )
_body ( TConfEpID  , 1  )	
_body ( BOOL32,		1)	//TRUEָʾԶ�˾�����FALSEȡ��Զ�˾���
_ev_end


/***********************<<  ������˫�� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_StartDual_Cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  ������˫�����  >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_StartDual_Ind )
_body ( TConfEpID  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end

/***********************<<  ����ر�˫�� >>********************	
*[��Ϣ����]	UMC	-->  UMS
*
*/
_event(  evtp_StopDual_Cmd )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<<  ����ر�˫�����  >>********************	
*[��Ϣ����]	UMS	-->  UMC
*
*/
_event(  evtp_StopDual_Ind )
_body ( TConfEpID  , 1  )	
_body ( EmTPDualReason  , 1  )	
_ev_end
// end eidt by gaoyong 

/***********************<<  UMS֪ͨCMS˫��Դ�ı� >>********************	
 *[��Ϣ����]	UMS	-->  CMS
 *
 */
_event(  evtp_DualEp_Notify )
_body ( TConfEpID  , 1  )	
_ev_end

/***********************<< ֪ͨ��ϯ������Ϣ  >>********************	
*[��Ϣ����]	UMS	-->  CMS
*
*/
_event(  evtp_ChairConfInfo_Notify )
_body ( TChairConfInfo  , 1  )	
_ev_end

/***********************<< ����Ҷϵ�ԭ��  >>********************	
*[��Ϣ����]	UMS	-->  CMS
*
*/
_event(  evtp_HungUp_Conf_Reason)
_body ( u16,   1  )    //ConfID
_body ( u32  , 1  )	   //�Ҷ�ԭ��
_ev_end

/***********************<< ֪ͨUMC��ʾ��Ϣ >>********************
*[��Ϣ����] UMS -- > CMS
*
*/
_event( evtp_UmsCommonReasonToUI_Ind )
_body ( TTPUmsReasonInd, 1 )
_ev_end

#ifndef _MakeTpEventDescription_
		_ev_segment_end(outerumscall)
};
#endif


#endif // _h_eventoutumscall_h__
