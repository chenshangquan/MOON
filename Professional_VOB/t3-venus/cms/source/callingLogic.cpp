// callingLogic.cpp: implementation of the CCallingLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "callingLogic.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 
const String CCallingLogic::m_strCallImg = "stcCallImag";
const String CCallingLogic::m_strCallMsg= "stcCallMsg";

CCallingLogic *CCallingLogic::m_pLogic = NULL;


static UINT g_nCallingTmHandle = 0;
static UINT g_nRefreshUITmHandle = 0;//2013.5.30

const String CCallingLogic::m_stcShowTime = "StcShowTime";

const String CCallingLogic::m_shmImg1 = "SchmCalling1";
const String CCallingLogic::m_shmImg2 = "SchmCalling2";
const String CCallingLogic::m_shmImg3 = "SchmCalling3";
const String CCallingLogic::m_shmImg4 = "SchmCalling4";


static u32 g_dwShowTime = 20;  ////呼叫动画显示的时间。若超过改时间，则像mainFrameLogic 发通知
static u32 g_dwShowRefreshUI = 4; /*多点会议 呼叫成功后，由于先发来点对点会议的状态后发多点状态，
								  界面也随之先显示点对点会议界面，然后切到多点会议界面，
								  为掩饰切换流程多显示一会呼叫动画  2013.5.30 yjj*/
static u32 g_dwCounter = 0;
//g_wLocalTimerID = SetTimer( NULL, 0, 60000, CBTimerFun );
VOID   CALLBACK   CTimerFun(  HWND   hwnd,   UINT   uMsg, UINT_PTR  idEvent, DWORD   dwTime  )
{   
    if ( idEvent == g_nCallingTmHandle)
    {  
        if ( g_dwCounter >= g_dwShowTime )
        {  
            s8* pConfName = BusinessManagePtr->GetCurConfName();
            if ( strcmp( pConfName, PTP_CONF ) != 0 )
            {
                ::KillTimer( NULL, g_nCallingTmHandle );
                //UIManagePtr->ShowWindow( g_stcStrCallingBox, false );
                UIFACTORYMGR_PTR->Endmodal( 0, g_stcStrCallingBox );
                UIDATAMGR->setLocalCnsState( emLocalCallingTimeOut );
                
                //显示是 否挂断的对话框  发消息给
                CMsgDispatch::SendMessage( UI_CMS_CALLING_TIME_OUT, 0 , 0 );           
            }
            else
            {
                g_dwCounter = 0;
            }           
        }
        
        g_dwCounter ++; 
        CCallingLogic::GetLogicPtr()->UpdateCallingImg();
    } 
	else if ( idEvent == g_nRefreshUITmHandle )
	{
		if ( g_dwCounter >= g_dwShowRefreshUI )
        {  
             ::KillTimer( NULL,g_nRefreshUITmHandle );
             UIFACTORYMGR_PTR->Endmodal( 0, g_stcStrCallingBox );
           
             g_dwCounter = 0; 
        }
		else
		{
			g_dwCounter ++; 
			CCallingLogic::GetLogicPtr()->UpdateCallingImg();
		} 
       
	}
}



CCallingLogic::CCallingLogic():m_emImgSchm( emImgSchm0 ) 
{  
    g_nCallingTmHandle = 0;
 
}

CCallingLogic::~CCallingLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}


CCallingLogic* CCallingLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CCallingLogic();   
    }
    
    return m_pLogic;
}

void CCallingLogic::RegMsg()
{   

    //显示呼叫dlg的消息
    REG_MSG_HANDLER( UI_UMS_SHOW_CALLING_DLG,CCallingLogic::OnShowNotify, m_pLogic, CCallingLogic  );

    //隐藏呼叫dlg的消息
    REG_MSG_HANDLER( UI_UMS_HIDE_CALLING_DLG,CCallingLogic::OnHideNotify, m_pLogic, CCallingLogic  );
 
   
}

void CCallingLogic::UnRegMsg()
{
    
}

bool CCallingLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CCallingLogic::InitWnd", CCallingLogic::InitWnd, m_pLogic, CCallingLogic);
    REG_GOBAL_MEMBER_FUNC( "CCallingLogic::OnBtnHungupConf", CCallingLogic::OnBtnHungupConf, m_pLogic, CCallingLogic);
    
    return true;
}

bool CCallingLogic::UnRegFunc()
{
    //	UN_REG_GOBAL_FUNC( "CConftempEdtLogic::InitWnd" );
    return true;
}

void CCallingLogic::Clear()
{
    m_emImgSchm  = emImgSchm0 ; 
    
    if ( m_pWndTree != NULL )
    {
        OnHideNotify( 0, 0 );
    }
    
}


bool CCallingLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg ); 
   
     
    String strTime;
    UIManagePtr->GetCaption(m_stcShowTime,  strTime, m_pWndTree );
    g_dwShowTime = atoi( strTime.c_str() ) * 2 ;
    return true;
}

bool CCallingLogic::OnBtnHungupConf( const IArgs & arg )
{  
   OnHideNotify( 0, 0);
   s8*pConfName = UIDATAMGR->GetCurConfName();

   if ( strcmp( pConfName, PTP_CONF ) ==0 )
   {
       BusinessManagePtr->HungupPtpConf();
       if ( UIDATAMGR->GetLocalCnsState() == emLocalCnsCalling )
       {     
            OnHideNotify( 0, 0 );
       }
   }
   else
   {
       
       if ( BusinessManagePtr->IsInConf() )
       {
           BusinessManagePtr->HangupConf();
       }
   }
  

   return true;
}

//更换呼叫图片
void CCallingLogic::UpdateCallingImg()
{  
    switch ( m_emImgSchm )
    {
    case emImgSchm0:
        m_emImgSchm = emImgSchm1;
        UIManagePtr->LoadScheme( m_shmImg1, m_pWndTree, m_strCallImg );
        break;
    case emImgSchm1:
        m_emImgSchm = emImgSchm2;
        UIManagePtr->LoadScheme( m_shmImg2, m_pWndTree, m_strCallImg );
        break;
    case emImgSchm2:
        m_emImgSchm = emImgSchm3;
        UIManagePtr->LoadScheme( m_shmImg3, m_pWndTree, m_strCallImg );
        break;
    case emImgSchm3:
        m_emImgSchm = emImgSchm0;
        UIManagePtr->LoadScheme( m_shmImg4, m_pWndTree, m_strCallImg );
        break;

    default:
        m_emImgSchm = emImgSchm0;
        UIManagePtr->LoadScheme( m_shmImg1, m_pWndTree, m_strCallImg );
         break;    
    } 
 
}

 

HRESULT CCallingLogic::OnShowNotify( WPARAM wparam, LPARAM lparam)
{   
	m_emTimer = (EMTimer)wparam;
	g_dwCounter = 0;
	if ( m_emTimer == emTimerCalling )
	{   
		if ( UIDATAMGR->GetLocalCnsState() != emLocalCnsCalling )
		{ 
			UIDATAMGR->setLocalCnsState( emLocalCnsCalling ); 
		}
		
	
		g_nCallingTmHandle = SetTimer( NULL, 0, 500, CTimerFun); 
        UIFACTORYMGR_PTR->Domodal( g_stcStrCallingBox );
	}
	else
	{
		KillTimer(NULL, g_nCallingTmHandle );
		if ( !UIFACTORYMGR_PTR->IsVisible(g_stcStrCallingBox) )
		{
			UIFACTORYMGR_PTR->Domodal( g_stcStrCallingBox );
		}
		
		g_dwCounter = 0;
		g_nRefreshUITmHandle = SetTimer( NULL, 0, 500, CTimerFun);
	}
    
    

   return NO_ERROR;
}


HRESULT CCallingLogic::OnHideNotify( WPARAM wparam, LPARAM lparam)
{ 
//setLocalCnsState 统一在OnConfStateNotify中修改	2013.1.16 BY YJJ
//    if ( UIDATAMGR->GetLocalCnsState() == emLocalCnsCalling )
//    {
//        if ( BusinessManagePtr->IsInConf() )
//        {
//            UIDATAMGR->setLocalCnsState( emLocalCnsInConf );
//        }
//        else
//        {
//            UIDATAMGR->setLocalCnsState( emLocalCnsIdle );
//        }
//        
//    }
   
   KillTimer( NULL, g_nCallingTmHandle );  
   UIFACTORYMGR_PTR->Endmodal( 0, g_stcStrCallingBox );
   return NO_ERROR;
} 