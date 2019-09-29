#ifndef _MakeTpEventDescription_

#ifndef _h_tpeventcomm_h__
#define _h_tpeventcomm_h__

#include "kdvtype.h"
#include "osp.h"
#include "eventid.h"

//[2011/3/8 zhaixiaogang]: tp��Ϣ�����40401��ʼ
#define EV_TP_BGN					  EV_WD8000E_END + 1
#define EV_TP_END				      EV_TP_BGN + 5000

#include "xmldefine.h"

//�ⲿ��Ϣ����
define_event_count( tp_event_value, 0 ); 
define_event_count( tpeventcommon, 2000 ); //������Ϣ��������������


//�ⲿ��Ϣ��Χ
const u16 begin_tp_event_value = EV_TP_BGN;
define_event_begin( tp_event_value, tpeventcommon );



//�ڲ���Ϣ����
define_event_count( tpsys, 70 ); 


//�ڲ���Ϣ��Χ
const u16 begin_tp_inner_event_value = EV_TP_END + 1;
const u16 begin_tpsys = begin_tp_inner_event_value;




#define TP_EVENT_ASSERT( val )\
{\
	if ( ev_segment_range(val) >= event_count(val) )\
{\
	printf( "%s event range overloaded: real<%d>, limit<%d>\n", #val, ev_segment_range(val), event_count(val) );\
	bHaveOverloaded = TRUE;\
}\
}


#endif//_h_tpeventcomm_h__

#endif//_MakeTpEventDescription_


