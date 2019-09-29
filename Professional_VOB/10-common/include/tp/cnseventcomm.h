#ifndef _h_cnseventcomm_h__
#define _h_cnseventcomm_h__

#include "tpeventcomm.h"

define_event_count( tpcnswithmt, 1100 );
define_event_count( tpcnswithcms, 110 ); 

define_event_begin( tpeventcommon, tpcnswithmt );
define_event_begin( tpcnswithmt, tpcnswithcms );

const u16 last_outer_event_value = begin_tpcnswithcms + event_count(tpcnswithcms);


//cns内部消息段划分
define_event_count( innercns, 100 );
define_event_begin( tpsys, innercns );
const u16 last_inner_event_value = begin_innercns +  event_count(innercns);


//cns消息定义
define_event_count( outercnsmp, 50 );
define_event_count( outercnssys, 50 );
define_event_count( outercnssipreg, 20 );
define_event_count( outercnssipcall, 50 );
define_event_count( outercnssipconf, 65 );
define_event_count( outercnssipdual, 45 );
define_event_count( outercnsh323reg, 10 );
define_event_count( outercnsh323call, 50 );
define_event_count( outercnsh323conf, 50 );
define_event_count( outercnsh323dual, 20 );
define_event_count( outercnsdevice, 70 );
define_event_count( outercnsmediatrans, 50 );
define_event_count( outercnsextend, 100 );
define_event_count( outercnscamera, 60);
//Add by tanxiaodnog 2012 -11-20.
define_event_count( outercnstool, 80 );
//End to add.
define_event_count( outercncode, 120 );
define_event_count( outercnds, 60 );
define_event_count( outercnscentre, 90);

const u16 begin_outercnsmp = begin_tpcnswithmt;
define_event_begin( outercnsmp, outercnssys );
define_event_begin( outercnssys, outercnssipreg );
define_event_begin( outercnssipreg,outercnssipcall );
define_event_begin( outercnssipcall,outercnssipconf );
define_event_begin( outercnssipconf,outercnssipdual );
define_event_begin( outercnssipdual,outercnsh323reg );
define_event_begin( outercnsh323reg,outercnsh323call );
define_event_begin( outercnsh323call,outercnsh323conf );
define_event_begin( outercnsh323conf,outercnsh323dual );
define_event_begin( outercnsh323dual,outercnsdevice );
define_event_begin( outercnsdevice,outercnsmediatrans );
define_event_begin( outercnsmediatrans,outercnsextend );
define_event_begin( outercnsextend,outercnscamera );
//Add by tanxiaodong 2012-11-20.
define_event_begin( outercnscamera,outercnstool );
//End to add.
define_event_begin(outercnstool, outercncode);
define_event_begin(outercncode, outercnds);
define_event_begin(outercnds, outercnscentre);










#endif // _h_cnseventcomm_h__
