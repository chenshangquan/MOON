#ifndef CHAN_EVENT_H
#define CHAN_EVENT_H
#include "innereventcomm.h"

#ifndef _MakeMtEventDescription_
enum EmMtChan
{
#endif 
   _ev_segment( chan )//MtService ͨ����Ϣ

	
/***********************<< �����ͨ��֪ͨ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *
 *[��Ϣ����]
 *
 *   StackIn => MtH323Service
 */_event(  ev_ChanCanOpenInd   )
   _body(   EmChanType  ,1      )
   _ev_end


/***********************<< ��ͨ������ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *  + TIPTransAddr    ��ͨ����RTCP���յ�ַ
 *  + EmMtVideoPort   ���ڶ�·��Ƶ��Ч
 *[��Ϣ����]
 *
 *   StackIn <=> MtH323Service
 */_event(  ev_ChanOpenCmd   )
   _body(   EmChanType     ,1      )
   _body(   TIPTransAddr   ,1      )
   _body(   EmMtVideoPort  ,1      )
   _ev_end


/***********************<< ��ͨ����Ӧ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *    + TIPTransAddr    RTP  ��ַ
 *    + TIPTransAddr    ��Ӧͨ����RTCP���յ�ַ
 *    + u32             �ص�����ָ�� ��320ϵͳ��Ч
 *[��Ϣ����]
 *
 *   StackIn <=> MtH323Service
 */_event(  ev_ChanOpenRsp   )
   _body(   EmChanType     ,1      )
   _body(   TIPTransAddr   ,1      )
   _body(   TIPTransAddr   ,1      )
   _body(   u32            ,1      )
   _ev_end


 /***********************<< ͨ�������ɹ�ָʾ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *    ......��Ƶ.........��Ƶ..........����
 *  + TVideoChanParam TAudioChanParam  null
 *[��Ϣ����]
 *
 *   StackIn <=> MtH323Service
 */_event(  ev_ChanConnectedInd   )
   _body(   u8     ,1        )
   _ev_end


 /***********************<< �ر�ͨ������ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *[��Ϣ����]
 *
 *   StackIn <=> MtH323Service
 */_event(  ev_ChanCloseCmd   )
   _body(   EmChanType     ,1      )
   _ev_end


/***********************<< �ر�ͨ��ָʾ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *[��Ϣ����]
 *
 *   StackIn <=> MtH323Service
 */_event(  ev_ChanDisconnectedInd   )
   _body(   EmChanType     ,1      )
   _ev_end


/***********************<< ��̬�غ�֪ͨ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *  + u8    dynamic payload
 *[��Ϣ����]
 *
 *   StackIn <=> MtH323Service
 */_event(  ev_ChanDynamicPayloadInd   )
   _body(   EmChanType     ,1      )
   _body(   u8             ,1      )
   _ev_end


/***********************<< ��Կ֪ͨ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *  + TEncryptKey
 *[��Ϣ����]
 *
 *   StackIn <=> MtH323Service
 */_event(  ev_ChanEncryptKeyInd   )
   _body(   EmChanType     ,1      ) 
   _body(   TEncryptKey    ,1      ) 
   _ev_end



/***********************<< ������Ƶͨ������ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *  + u16    ��λ Kbps
 *[��Ϣ����]
 *
 *   MtService => 323/sip/320
 */_event(  ev_ChanSetBitrateCmd   )
   _body(   EmChanType     ,1      ) 
   _body(   u16            ,1      ) 
   _ev_end


/***********************<< ͨ������ָʾ >>************************	
 *[��Ϣ��]			 
 *  + EmChanType
 *  + u16    ��λ Kbps
 *[��Ϣ����]
 *
 *   MtService <= 323/sip/320
 */_event(  ev_ChanBitrateInd   )
   _body(   EmChanType     ,1      ) 
   _body(   u16            ,1      ) 
   _ev_end


/***********************<< ����ؼ�(I)֡ >>***********************	
 *[��Ϣ��]			 
 *  + EmChanType
 *[��Ϣ����]
 *
 *   MtService <=> 323/sip/320
 */_event(  ev_ChanIFrameCmd   )
   _body(   EmChanType     ,1      ) 
   _ev_end


/***********************<< ͨ��״ָ̬ʾ >>***********************	
 *[��Ϣ��]			 
 *  + EmChanType
 *  + BOOL           TRUE ���� FALSE�ر�
 *[��Ϣ����]
 *
 *   MtService <=> 323/sip/320
 */_event(  ev_ChanStateInd   )
   _body(   EmChanType     ,1      ) 
   _body(   BOOL           ,1      ) 
   _ev_end


/***********************<< ֪ͨͨ���������仯ָʾ >>***********************	
 *[��Ϣ��]			 
 *  + EmChanType    ������
 *  + u16           ��ǰ�������
 *[��Ϣ����]
 *
 *   MtService <=> 323/sip/320
 */_event(  ev_ChanBandwidthChangeInd   )
   _body(   EmChanType     ,1      ) 
   _body(   u16            ,1      ) 
   _ev_end

//[xujinxing-2006-06-07]
/***********************<<  ����ͨ���ֱ��� >>********************** 
 *[��Ϣ��]
//*    +EmChanType
//*    +EmVideoResolution
 *[��Ϣ����]
 *  h323service -> mtservice(channelservie)
 */_event( ev_ChanAdjustVideoResCmd )
   _body( EmChanType, 1 )
   _body( EmVideoResolution, 1 )   
   _ev_end
 

//[xujinxing-2006-08-08]
/***********************<<  �����鲥���յ�ַ >>********************** 
 *[��Ϣ��]
//*    +EmChanType
//*    +u32  ip
//*    +u16  port
 *[��Ϣ����]
 *  h323service -> mtservice(channelservie)
 */_event( ev_ChanMultiCastAddrCmd)
   _body( EmChanType, 1 )
   _body( u32_ip,  1 )  
   _body( u16, 1 ) 
   _ev_end
   
//[Fangtao,2006-12-26]
/***********************<<  ������Ƶ��������������� >>********************** 
 *[��Ϣ��]
//*    +u8  Input volume
//*    +u8  Output volume
 *[��Ϣ����]
 *  h323service -> mtservice(channelservie)
 */_event( ev_ChanSetAudioVolumeCmd)
   _body( u8,  1 )  
   _body( u8,  1 ) 
   _ev_end


/***********************<< ������Ƶ�������Ķ�̬�غ� >>********************** 
 *[��Ϣ��]
//*    +u8  Input volume
//*    +u8  Output volume
 *[��Ϣ����]
 *  h323service -> mtservice(channelservie)
 */_event( ev_ChanDynamicPayloadParamInd )
   _body( EmChanType, 1 )
   _body( EmVideoFormat,  1 )  
   _body( u8,  1 ) 
   _ev_end
   
/***********************<< ������Ƶ�������Ķ�̬�غ� >>********************** 
 *[��Ϣ��]
//*    EmChanType
//*    bool
 *[��Ϣ����]
 *  h323service -> mtservice(channelservie)
 */_event( ev_ChanSetReverseG7221cCmd )
   _body( EmChanType, 1 )
   _body( BOOL,  1 )  
   _ev_end

/***************<< Զ���Ի����� >>***********************	
 *[��Ϣ��]			 
 *  + EmChanType= emChanTypeEnd �޺���)
   _ev_end��Ϊ��Ϣһ�¶�����
 *[��Ϣ����]
 *
 *    H239 class  (323 �ڲ�ʹ��)
 */_event( ev_chanRemoteLoopCmd )
   _body( EmChanType, 1 )
   _body( BOOL,  1 )  
   _ev_end
   
/***********************<<  ����ͨ��֡�� >>********************** 
 *[��Ϣ��]
//*    +EmChanType
//*    +EmVideoResolution
 *[��Ϣ����]
 *  h323service -> mtservice(channelservie)
 */_event( ev_ChanAdjustVideoFpsCmd )
   _body( EmChanType, 1 )
   _body( u8, 1 )
   _ev_end

#ifndef _MakeMtEventDescription_
   _ev_segment_end(chan)
};
inline BOOL IsMtChanEvent(u16 wEvent)
{
	return (wEvent > get_first_event_val(chan)) && ( wEvent < get_last_event_val(chan));
}
#endif


#endif
