// \HeaderCtrl.h 


#if !defined(HEADERCTRL_H)
#define HEADERCTRL_H

#pragma warning( disable : 4786 )	// 标识符名称超过255字节
#pragma warning( disable : 4503 )
#pragma warning( disable : 4800 )

#include "UifactoryHeader.h"

#pragma comment (lib, "UIFactory.lib ") 
#include "uifactorylib.h"

#include "kdvtype.h"
#include "kdvsys.h"

#include "cmsconst.h"
#include "evCmsLib.h"  
#include "msgdispatch.h"
#include "commoninterface.h"
#include "alarminfologic.h"
#include "tpadplatconst.h"
#include "tpadplatstuct.h"
#include "confSign.h"
#include "tperrno.h"

//#pragma comment(lib, "umclib.lib")
#pragma comment(lib, "cnclib.lib")
#pragma comment(lib, "osplib.lib")
#pragma comment(lib, "kdvsys.lib") 
#pragma comment(lib, "kdvaddrbook.lib")


#pragma comment( lib, "iphlpapi.lib" )
#pragma comment(lib, "SensAPI.Lib")

//打印控制  
#pragma comment (lib,"nmscommon.lib")
//ftp
#pragma comment(lib, "wininet.lib")


//cns库 
#pragma comment(lib, "kdvlog.lib")
#pragma comment(lib, "tpmsgmgr.lib")
#pragma comment(lib, "cnmsg.lib")
#pragma comment(lib, "xmlengine.lib")



#endif