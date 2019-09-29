#ifndef _h_eventoutcnsh323conf_h__
#define _h_eventoutcnsh323conf_h__

#include "cnseventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSH323CONFEVENT
{
#endif 

  _ev_segment( outercnsh323conf  )


/***********************<< 开始多点会议指示 >>********************** 
*[消息体]

*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleMultipleConference )
_ev_end
	  
/***********************<< 取消多点会议指示 >>********************** 
*[消息体]

*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleCancelMultipleConference )
_ev_end

/***********************<< 分配终端编号 >>********************** 
*[消息体]
TTPMDLTERLABEL
*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleTerminalNumberAssign )
_body(TTPTerLabel, 1)
_ev_end

/***********************<< 被别人看，发言人 >>********************** 
*[消息体]

*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleSeenByAll )
_ev_end

/***********************<< 取消被别人看 >>********************** 
*[消息体]

*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleCancelSeenByAll )
_ev_end

/***********************<< 请求列表 >>********************** 
*[消息体]

*[消息方向]
*  cncall	  <- cns
*/
_event(  ev_CnModuleTerminalListRequest )

_ev_end

/***********************<< 请求列表 >>********************** 
*[消息体]

*[消息方向]
*  cncall	  <- cns
*/
_event(  ev_CnModuleTerminalIDListRequest )

_ev_end



/***********************<< 加入会议 >>********************** 
*[消息体]
TTPMDLTERLABEL
*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleTerminalJoinConf )
_body( TCnsInfo, 1 )
_ev_end

/***********************<< 离开会议 >>********************** 
*[消息体]
TTPMDLTERLABEL
*[消息方向]
*  cns	  <- cncall
*/
_event(  ev_CnModuleterminalLeftConf )
_body( TCnsInfo, 1 )
_ev_end

  
#ifndef _MakeTpEventDescription_
   _ev_segment_end( outercnsh323conf )
};
#endif
#endif //TPP_EVENT_H
