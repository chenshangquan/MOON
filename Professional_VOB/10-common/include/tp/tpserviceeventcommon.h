#ifndef _h_serviceeventcommon_h__
#define _h_serviceeventcommon_h__

#include "tpeventcomm.h"

//////////////////////////////////////////////////////////////////////////
//�ⲿ��Ϣ

///updateservice
define_event_count( tpupdateservice, 10 );
define_event_begin( tp_event_value, tpupdateservice );

//////////////////////////////////////////////////////////////////////////
//�ڲ���Ϣ

//updateservice
define_event_count( innerupdateservice, 10 );
define_event_begin( tpsys, innerupdateservice );

#endif // _h_serviceeventcommon_h__
