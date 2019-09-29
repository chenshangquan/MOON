#ifndef _h_eventoutmoonsys_h__
#define _h_eventoutmoonsys_h__

#include "mooneventcomm.h"

#ifndef _MakeTpEventDescription_
enum EmCNSSYSEVENT
{
#endif 

  _ev_segment( outermoonsys  )

/***********************<< ����moonʱ�� >>********************** 
*[��Ϣ��]
+TTPTime		
*[��Ϣ����]
*  moon	  <- camCP
*/
_event( ev_TpMoonSetSysTime_Cmd )
_body( TTPTime, 1 )
_ev_end

/***********************<< ��ѯmoonʱ�� >>********************** 
*[��Ϣ��]
*NULL
*[��Ϣ����]
*  moon	  <- camCP
*/
_event( ev_TpMoonGetSysTime_Req)
_ev_end


/***********************<< ��ѯmoonʱ����Ӧ >>********************** 
*[��Ϣ��]
+TTPTime
*[��Ϣ����]
*  moon  -> camCP
*/
_event( ev_TpMoonGetSysTime_Rsp)
_body( TTPTime, 1 )
_ev_end

/***********************<< ����������Ϣ >>********************** 
*[��Ϣ��]
+TTPEthnetInfo		moon����������Ϣ
*[��Ϣ����]
*  camCP  -> moon
*/
_event( ev_TpMoonCfgEthnet_Cmd )
_body(TTPEthnetInfo, 1 )
_ev_end

/***********************<< ֪ͨ�����Ӧ >>********************** 
*[��Ϣ��]
+TTPEthnetInfo		moon����������Ϣ
*[��Ϣ����]
*  moon	  -> camCP
*/
_event(  ev_TpMoonCfgEthnet_Ind )
_body(TTPEthnetInfo, 1 )
_ev_end

  /***********************<<  moon ���� >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  camCP -> moon
  */_event(   ev_TpMoonUpgrade_Cmd )
  _body(s8,  TP_MAX_FILENAME_LEN + 1)
  _ev_end

  /***********************<<  Moon ������Ӧ >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  moon -> camCP
  */_event(   ev_TpMoonUpgrade_Ind )
  _body(BOOL,  1)
  _ev_end

  /***********************<< ����Moon����  >>********************	
  *[��Ϣ��]
  *NULL
  *[��Ϣ����]	  camCP	-->  Moon
  *
  */
  _event(  ev_tpMoonReboot_Cmd )
_ev_end

/***********************<<  Moon ������Ӧ >>********************	
  *[��Ϣ��]
  *[��Ϣ����]
  *  moon -> camCP
  */_event(   ev_TpMoonUpgradeCleanEnv_Ind )
  _ev_end

#ifndef _MakeTpEventDescription_
   _ev_segment_end( outermoonsys )
};
#endif
#endif //TPP_EVENT_H
