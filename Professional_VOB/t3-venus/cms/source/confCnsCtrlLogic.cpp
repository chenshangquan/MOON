// confCtrlLogic.cpp: implementation of the CConfCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "confCtrlLogic.h"
#include "msgBoxLogic.h"
#include "logicmanage.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
bool CConfCtrlLogic::OnSetSpokeCnsClick( const IArgs & arg )
{  
    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_wConfID;
    tConfEpInfo.m_wEpID = m_wCnsID;
    u16 wRe =  BusinessManagePtr->SetSpokeCns(  tConfEpInfo );
    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR(wRe); 
    } 
     
    return true;
}

/**	 
* 功能:  点击哑音图标
* @return  bool
* @remarks  
*/
bool CConfCtrlLogic::OnSetMuteClick( const IArgs & arg )
{
    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_wConfID;
    tConfEpInfo.m_wEpID = m_wCnsID; 

    TCnsInfo tCnsInfo;
    u16 Re = BusinessManagePtr->GetConfCnsByID( tConfEpInfo, &tCnsInfo ); 
    if (Re == NO_ERROR )
    {
        if ( tCnsInfo.m_bMute )
        {
            //TRACE("\n[CConfCtrlLogic::OnSetMuteClick]confCns[confID = %d, cnsID = %d] is mute yet\n",m_wConfID,m_wCnsID);
            return true;
        }

    } 

    u16 wRe =  BusinessManagePtr->SetMuteCns( tConfEpInfo ,TRUE);
    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR(wRe); 
    } 



   return true;
   
}


/**	 
* 功能:  点击取消哑音图标
* @return  bool
* @remarks  
*/
bool CConfCtrlLogic::OnSetUnMuteClick( const IArgs & arg )
{
    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_wConfID;
    tConfEpInfo.m_wEpID = m_wCnsID;
   
     

    TCnsInfo tCnsInfo;
    u16 Re = BusinessManagePtr->GetConfCnsByID( tConfEpInfo, &tCnsInfo ); 
    if (Re == NO_ERROR )
    {
        if ( !tCnsInfo.m_bMute )
        {
          //  TRACE("\n[CConfCtrlLogic::OnSetMuteClick]confCns[confID = %d, cnsID = %d] is unmute yet\n",m_wConfID,m_wCnsID);
            return true;
        }
       
    }

    u16 wRe =  BusinessManagePtr->SetMuteCns( tConfEpInfo ,FALSE);
    if ( wRe != NO_ERROR )
    {       
        HANDLE_ERROR(wRe); 
    }


    CConfCnsLstLogic *pLogic = NULL ;
    LogicManagePtr->GetLogic( &pLogic );
    if ( pLogic != NULL )
    {
        if ( pLogic->GetCnsShowState() == emShowMute )
        {
            UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg,false);
        } 
    }
 
    return true;
}

/**	 
* 功能:  点击 静音图标
* @return  bool
* @remarks  
*/
bool CConfCtrlLogic::OnSetQuietClick( const IArgs & arg )
{
    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_wConfID;
    tConfEpInfo.m_wEpID = m_wCnsID;
    
     

    TCnsInfo tCnsInfo;
    u16 Re = BusinessManagePtr->GetConfCnsByID( tConfEpInfo, &tCnsInfo ); 
    if (Re == NO_ERROR )
    {
        if (  tCnsInfo.m_bQuiet )
        {
           // TRACE("\n[CConfCtrlLogic::OnSetMuteClick]confCns[confID = %d, cnsID = %d] is quiet yet\n",m_wConfID,m_wCnsID);
            return true;
        }
        
    }

    u16 wRe =  BusinessManagePtr->SetQuietCns( tConfEpInfo ,TRUE);
    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR(wRe); 
    }

 

   return true;
}


/**	 
* 功能:  点击 取消静音图标
* @return  bool
* @remarks  
*/
bool CConfCtrlLogic::OnSetUnQuietClick( const IArgs & arg )
{
    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_wConfID;
    tConfEpInfo.m_wEpID = m_wCnsID; 

     

    TCnsInfo tCnsInfo;
    u16 Re = BusinessManagePtr->GetConfCnsByID( tConfEpInfo, &tCnsInfo ); 
    if (Re == NO_ERROR )
    {
        if ( !tCnsInfo.m_bQuiet )
        {
           // TRACE("\n[CConfCtrlLogic::OnSetMuteClick]confCns[confID = %d, cnsID = %d] is unquiet yet\n",m_wConfID,m_wCnsID);
            return true;
        }
        
    }


    u16 wRe =  BusinessManagePtr->SetQuietCns( tConfEpInfo ,FALSE);
    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR(wRe); 
    }

    CConfCnsLstLogic *pLogic = NULL ;
    LogicManagePtr->GetLogic( &pLogic );
    if ( pLogic != NULL )
    {
        if ( pLogic->GetCnsShowState() == emShowQuiet )
        {
            UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg,false);
        } 
    }

   return true;
}


/**	 
* 功能:  点击开启双流开关
* @return  bool
* @remarks  
*/
bool CConfCtrlLogic::OnStartDualClick ( const IArgs & arg )
{
    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_wConfID;
    tConfEpInfo.m_wEpID = m_wCnsID;

     

    u16 wRe =  BusinessManagePtr->SetDualCns( tConfEpInfo ,TRUE);
    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR(wRe); 
    }

    

   return true;
}

/**	 
* 功能:  点击关闭双流开关
* @return  bool
* @remarks  
*/
bool CConfCtrlLogic::OnStopDualClick ( const IArgs & arg )
{
    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_wConfID;
    tConfEpInfo.m_wEpID = m_wCnsID;

     

    u16 wRe =  BusinessManagePtr->SetDualCns( tConfEpInfo ,FALSE);
    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR(wRe); 
    }

    CConfCnsLstLogic *pLogic = NULL ;
    LogicManagePtr->GetLogic( &pLogic );
    if ( pLogic != NULL )
    {
        if ( pLogic->GetCnsShowState() == emShowDual )
        {
            UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg,false);
        } 
    }

   return true;
}

 

bool CConfCtrlLogic::OnHungupConfClick( const IArgs &arg)
{
    //弹出提示框，请用户确认是否要结束会议
    //弹出的模态提示框中传入函数“HungupConf”，在用户点击 “确认”按钮的时候调用 

    TCMSConf tConfInfo ;
    BOOL32 bIn =  BusinessManagePtr->IsInConf( &tConfInfo );
    if ( !bIn )
    {  
        PrtMsg( 0, emEventTypeCmsWindow, "[CConfCtrlLogic::OnHungupConfClick] 挂断 cns(id=%d) 失败：当前没有会议存在");
        return false;
    }
     
     
    HungupConf( arg );
//     CString msg;
//     msg.Format("是否要挂断会议？");
// 
//     Args_MsgBox argMsg;
//     argMsg.pOwnerWnd = UIManagePtr->GetWindowPtr( g_stcStrConfCnsCtrlDlg );
//     MSG_BOX((LPCSTR)msg ,CConfCtrlLogic::HungupConf,NULL,m_pLogic,CConfCtrlLogic,&argMsg,TRUE); 
    
   return true;
}

bool CConfCtrlLogic::HungupConf( const IArgs & arg )
{ 
    u16 wRe = NO_ERROR;

    TCMSConf tConfInfo ;
    BOOL32 bIn =  BusinessManagePtr->IsInConf( &tConfInfo );


    if ( bIn &&  tConfInfo.m_emConfType == emCallType_Conf )
    {
        wRe = BusinessManagePtr->HangupConf( );
    }
    else
    { 
       // if ( tConfInfo.m_emConfType == emCallType_P2P )
        {
            wRe = BusinessManagePtr->HungupPtpConf();
        }
        
    }
    
    
   
   if ( wRe != NO_ERROR )
   {
       HANDLE_ERROR(wRe); 
       return false;
   }
    
   return true;
}

bool CConfCtrlLogic::OnHungupCnsClick( const IArgs & arg)
{
    //弹出提示框，请用户确认是否要结束会议
    //弹出的模态提示框中传入函数“HungupCns”，在用户点击 “确认”按钮的时候调用
       

      TCMSConf tConfInfo;
      BOOL32 re = BusinessManagePtr->IsInConf(&tConfInfo);
      if ( !re )
      {   
          PrtMsg( 0, emEventTypeCmsWindow, "[CConfCtrlLogic::OnHungupCnsClick] 挂断 cns(id=%d) 失败：当前cns不在会议中");
          return false;
      }
 

       
//如果是主会场，则需要用户确认     
    TCnsInfo *p = tConfInfo.GetCnsInfoFrmCnsLst(m_wCnsID);
    if ( p != NULL  && m_wCnsID == tConfInfo.GetChairCnsID()  )
    {
        Args_MsgBox arg;
        arg.pOwnerWnd = UIManagePtr->GetWindowPtr( /*g_stcStrConfCnsCtrlDlg*/g_stcStrCnsLstDlg ); 
        UIDATAMGR->setLocalCnsState( emLocalCnsWillHungup ); //2012.11.14 by yjj Bug00113809
        int nReslut = MSG_BOX(  "挂断主席会场将结束会议，是否结束会议？", TRUE, &arg);
		if ( IDOK == nReslut )
		{
			IArgs arg("");
			HungupConf( arg );
		}
   }
    else
    {
        HungupCns(arg);
    }
    
    return true;
}

bool CConfCtrlLogic::HungupCns( const IArgs & arg)
{  
    TConfEpID  tConfEpInfo ;
    tConfEpInfo.m_wConfID = m_wConfID;
    tConfEpInfo.m_wEpID = m_wCnsID;
    
    u16 wRe = BusinessManagePtr->HangupCNS( tConfEpInfo );
    if ( wRe != NO_ERROR )
    {
        HANDLE_ERROR(wRe); 
        return false;
    }
 
    if ( BusinessManagePtr->IsCnsChairMan( m_wCnsID) )
    {
       // if ( BusinessManagePtr->GetLocalCnsState() == emLocalCnsLocking )
        {
            UIDATAMGR->setLocalCnsState( emLocalCnsHungup  );
        }

    }
    
    UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg, false );
    UIManagePtr->ShowWindow( "ConfCnsCtrlSpeakerDlg", false );
     
    return true;   
} 


 

 /**	 
  * 功能:   挂断cns
  * param [in] strMsg 要提示的消息
  * param [in] tCns 要挂断的cns信息
  * param [in] bShowCancle 是否显示取消
  * @return  bool
  * @remarks 供外部调用 
  */ 
bool CConfCtrlLogic::HungupLocalConf( const confID, const CString strMsg, bool bShowCancle /*= true*/ ,Window *pParendWnd/* = NULL*/ ) 
{  
   m_wConfID = confID;
   
   IArgs*p=NULL;
   HungupConf(*p);

//    Args_MsgBox arg;
//    arg.pOwnerWnd = pParendWnd;
//    MSG_BOX( strMsg, CConfCtrlLogic::HungupConf,NULL,m_pLogic,CConfCtrlLogic,&arg,bShowCancle);
   return true;
}

//挂断本地cns
bool CConfCtrlLogic::HungupLocalCns( const TConfEpID& tCns, const CString strMsg, bool bShowCancle/* = true */,Window *pParendWnd/* = NULL*/)
{
    m_wConfID = tCns.m_wConfID;  
    m_wCnsID = tCns.m_wEpID;
    
    Args_MsgBox arg;
    arg.pOwnerWnd = pParendWnd;
    int nReslut = MSG_BOX( strMsg, bShowCancle, &arg ); 
	if ( IDOK == nReslut )
	{
		IArgs arg("");
		HungupCns( arg );
	}
    return true;
}
 

bool CConfCtrlLogic::CloseConfCnsMenuDlg( const IArgs & arg  )
{
   return UIManagePtr->ShowWindow(g_stcStrConfCnsCtrlDlg,false);
}

bool CConfCtrlLogic::BtnSaveConfCnsMenu2FileClick( const IArgs & arg )
{
  return  UIManagePtr->SaveToFile( g_stcStrConfCnsCtrlDlg  );  
}

 
bool CConfCtrlLogic::UserDefinedFun( const IArgs & arg )
{
//     UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg,FALSE);
//     RefreshConfCnsCtrlDlg();

    // 会议cns管理菜单不隐藏 2013年8月14日  dyy
    Value_WindowOwer owerVal;
    owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrCnsLstDlg );
    UIManagePtr->SetPropertyValue(owerVal, g_stcStrConfCnsCtrlDlg);

    AdjustMenuPos();
    UIManagePtr->ShowWindow( g_stcStrConfCnsCtrlDlg);
    
    return true;
}