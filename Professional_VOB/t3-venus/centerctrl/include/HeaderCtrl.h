//HeaderCtrl.h 
#if !defined HEADERCTRL_H
#define HEADERCTRL_H

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )


#include "kdvtype.h"
#include "kdvsys.h"

#include "UifactoryHeader.h"
#include "uifactorylib.h"
#pragma comment (lib, "UIFactory.lib ") 

#include "evCmsLib.h" 
#include "tpadplatconst.h"
//#include "tpadplatstuct.h"

#include "msgdispatch.h"
#include "commoninterface.h"

#pragma comment (lib, "cnclib.lib")
#pragma comment (lib, "osplib.lib")
#pragma comment (lib, "kdvsys.lib") 
#pragma comment (lib, "kdvaddrbook.lib")
#pragma comment (lib, "nmscommon.lib" )

//cns库
#pragma comment (lib, "kdvlog.lib")
#pragma comment (lib, "tpmsgmgr.lib")
#pragma comment (lib, "cnmsg.lib")
#pragma comment (lib, "xmlengine.lib")

#endif