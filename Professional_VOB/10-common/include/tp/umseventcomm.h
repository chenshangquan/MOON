#ifndef _h_umseventcomm_h__
#define _h_umseventcomm_h__

#include "tpeventcomm.h"


//��Ϣ��������
define_event_count( tpumswithcms, 400 );
define_event_count( tpumswithumssipadapter, 150 );
define_event_count( tpumswithumsaudiomix, 20 ); 
define_event_count( tpumswithmediatrans, 20 ); 
define_event_count( tpumswithumshdu2, 40 ); 



//��Ϣ��ʼ����
define_event_begin( tpeventcommon, tpumswithcms );
define_event_begin( tpumswithcms, tpumswithumssipadapter );
define_event_begin( tpumswithumssipadapter, tpumswithumsaudiomix );
define_event_begin( tpumswithumsaudiomix, tpumswithmediatrans );
define_event_begin( tpumswithmediatrans, tpumswithumshdu2 );

const u16 last_outer_event_value = begin_tpumswithumshdu2 + event_count(tpumswithumshdu2);


//////////��������ⲿ��Ϣ //////////////////
//ums��Ϣ����
define_event_count( outerumslogin, 20 );
define_event_count( outerumsreg, 20 );
define_event_count( outerumsconftemplate, 20 );
define_event_count( outerumscall, 100 );
define_event_count( outerumscfg, 25 );
define_event_count( outerumshdu, 20 );
define_event_count( outerumseqp, 80 );
define_event_count( outerumstool, 20);
define_event_count( outerumsboard, 25);
define_event_count( outerumscommonbrd, 30);
define_event_count( outerumsrec, 35);

//define_event_range( tpumswithcms, outerumsreg );
const u16 begin_outerumslogin = begin_tpumswithcms;
define_event_begin( outerumslogin, outerumsreg );
define_event_begin( outerumsreg, outerumsconftemplate );
define_event_begin( outerumsconftemplate, outerumscall );
define_event_begin( outerumscall, outerumscfg );
define_event_begin( outerumscfg, outerumshdu );
define_event_begin( outerumshdu, outerumseqp );
define_event_begin( outerumseqp, outerumstool);
define_event_begin( outerumstool, outerumsboard);
define_event_begin( outerumsboard, outerumscommonbrd);
define_event_begin( outerumscommonbrd, outerumsrec);

define_event_begin( outerumsrec, umsouteventcheck);//�������ֵ





define_event_count( tpumsinner, 1000 );
const u16 last_inner_event_value = begin_tp_inner_event_value + event_count(tpsys) + event_count(tpumsinner);




//////////��������ڲ���Ϣ //////////////////
//UMS�ڲ���Ϣ�λ���
define_event_count( innerregsrv, 30 );
define_event_count( umsinnerserver, 10 );
define_event_count( umsinnercall, 40);
define_event_count( umsinnerconf, 60);
define_event_count( umsinnermediads, 10);
define_event_count( umsinnertvwall, 10);
define_event_count( umsinnerhdu, 30);
define_event_count( umsinneragent, 30);
define_event_count( umsinnerboard, 20);
define_event_count( umsinnermpu2, 40);
define_event_count( umsinnerrec, 70);


define_event_count( innerumssipadapter, 50 );
define_event_count( innerumsaudiomix, 50 );
define_event_count( innerumsmediatrans, 50 );
define_event_count( innerumsnetbuf, 50 );
define_event_count( innerumsmpc, 50 );


define_event_begin( tpsys, innerregsrv );
define_event_begin( innerregsrv, umsinnerserver );
define_event_begin( umsinnerserver, umsinnercall );
define_event_begin( umsinnercall, umsinnerconf );
define_event_begin( umsinnerconf, umsinnermediads );
define_event_begin( umsinnermediads, umsinnertvwall );
define_event_begin( umsinnertvwall, umsinnerhdu);
define_event_begin( umsinnerhdu, umsinneragent);
define_event_begin( umsinneragent, umsinnerboard);
define_event_begin( umsinnerboard, umsinnermpu2);
define_event_begin( umsinnermpu2, umsinnerrec);


define_event_begin( umsinnerrec, innerumssipadapter );
define_event_begin( innerumssipadapter, innerumsaudiomix );
define_event_begin( innerumsaudiomix, innerumsmediatrans );
define_event_begin( innerumsmediatrans, innerumsnetbuf );
define_event_begin( innerumsnetbuf, innerumsmpc );


define_event_begin( innerumsmpc, umsinnereventcheck);//�������ֵ

#endif // _h_umseventcomm_h__
