#ifndef _h_eventoutmooncamera_h__
#define _h_eventoutmooncamera_h__

#include "mooneventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSCAMERAEVENT
{
#endif 
	
	_ev_segment( outermooncamera  )


  /**********************<< ������ϵ�֪ͨ >>**********************
  *[��Ϣ��]
  *
  *    + BOOL    =TRUE tptools����ʱ���������ϵ��֪ͨ FALSE �������
  *
  *[��Ϣ����]
  *
  *   cnDevice => cnDevice
  */_event( ev_Cn_CameraPowerOnNty )
	_body(  BOOL,      1           )
    _ev_end

/***********************<<�м�����ʱ����>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  camCP <- moon
 */
_event(  ev_TpSetMidDelay_Cmd )
_body( u32, 1)//����
_ev_end 
/***********************<<sony��о��������>>************************	
 *[����Ϣ��]			 
 * NULL
 *[��Ϣ����]
 *  cam <- moon
 */
_event(  ev_TpCamNoiseLevel_Cmd )
_body( EmTPCamNoiseLevel, 1)
_body( u8, 1)
_ev_end 

#ifndef _MakeTpEventDescription_
		_ev_segment_end( outermooncamera )
};
#endif
#endif 