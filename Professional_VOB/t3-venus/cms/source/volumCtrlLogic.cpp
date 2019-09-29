// volumCtrlLogic.cpp: implementation of the CVolumCtrlLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "cms.h"
#include "volumCtrlLogic.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CVolumCtrlLogic *CVolumCtrlLogic::m_pLogic = NULL;

const String CVolumCtrlLogic::m_strBtnMute = "btnMute";       //哑音按钮    
const String CVolumCtrlLogic::m_strSliderVolum = "SliderVolum";   //音量控制
           
EM_VolumType CVolumCtrlLogic::m_emVolumType = emVolumSpeaker;             //音量类型
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
 

CVolumCtrlLogic::CVolumCtrlLogic()
{
    
}

CVolumCtrlLogic::~CVolumCtrlLogic()
{
    
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL; 
    }
}




CVolumCtrlLogic* CVolumCtrlLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {  
        m_pLogic = new CVolumCtrlLogic();   
    }
    
    return m_pLogic;
}

void CVolumCtrlLogic::RegMsg()
{    
    
//    REG_MSG_HANDLER(UI_CNS_QUITE_MUTE,  CVolumCtrlLogic::OnMuteInd, m_pLogic, CVolumCtrlLogic); 2012.1.6 音量设置一直可用
    REG_MSG_HANDLER(UI_CNS_INVOL_UPDATE,  CVolumCtrlLogic::OnInputInd, m_pLogic, CVolumCtrlLogic);
    REG_MSG_HANDLER(UI_CNS_OUTVOL_UPDATE,  CVolumCtrlLogic::OnOutputInd, m_pLogic, CVolumCtrlLogic); 
    
    //停止拖动滑块
   // REG_MSG_HANDLER(SLIDER_RELEASED_CAPTURE,  CVolumCtrlLogic::OnReleasedcaptureVolumn, m_pLogic, CVolumCtrlLogic); 
    //鼠标移动 SLIDER_CHANGED
    REG_MSG_HANDLER(WM_MOUSEMOVE,  CVolumCtrlLogic::OnMouseMoveVolumn, m_pLogic, CVolumCtrlLogic); 
    
}

void CVolumCtrlLogic::UnRegMsg()
{
    
}

bool CVolumCtrlLogic::RegCBFun()
{   	 
    REG_GOBAL_MEMBER_FUNC( "CVolumCtrlLogic::InitWnd", CVolumCtrlLogic::InitWnd, m_pLogic, CVolumCtrlLogic);
    REG_GOBAL_MEMBER_FUNC( "CVolumCtrlLogic::BtnSaveToFileClick", CVolumCtrlLogic::BtnSaveToFileClick, m_pLogic, CVolumCtrlLogic ) ; 
    REG_GOBAL_MEMBER_FUNC( "CVolumCtrlLogic::BtnCloseClick", CVolumCtrlLogic::BtnCloseClick, m_pLogic, CVolumCtrlLogic ) ; 

    //点击哑音
    REG_GOBAL_MEMBER_FUNC( "CVolumCtrlLogic::OnBntMuteClick", CVolumCtrlLogic::OnBntMuteClick, m_pLogic, CVolumCtrlLogic);

    REG_GOBAL_MEMBER_FUNC( "CVolumCtrlLogic::OnBntQuietClick", CVolumCtrlLogic::OnBntQuietClick, m_pLogic, CVolumCtrlLogic);

    //slider变化
    REG_GOBAL_MEMBER_FUNC( "CVolumCtrlLogic::OnReleasedcaptureVolumn", CVolumCtrlLogic::OnReleasedcaptureVolumn, m_pLogic, CVolumCtrlLogic);


    REG_GOBAL_MEMBER_FUNC( "CVolumCtrlLogic::BtnMinusVolClick", CVolumCtrlLogic::BtnMinusVolClick, m_pLogic, CVolumCtrlLogic);
    REG_GOBAL_MEMBER_FUNC( "CVolumCtrlLogic::BtnAddVolClick", CVolumCtrlLogic::BtnAddVolClick, m_pLogic, CVolumCtrlLogic);
 

    
    return true;
}

bool CVolumCtrlLogic::UnRegFunc()
{
    //	UN_REG_GOBAL_FUNC( "CConftempLstLogic::InitWnd" );
    return true;
}


bool CVolumCtrlLogic::InitWnd(  const IArgs & arg )
{   
    CWndLogicBase::InitWnd( arg );
   
    Value_WindowOwer valOwner;
    valOwner.pWnd = UIManagePtr->GetWindowPtr( g_stcStrConfCnsCtrlDlg );
    UIManagePtr->SetPropertyValue(valOwner, "", m_pWndTree );


    //初始化音量控件
//     Value_CSliderCtrlRange val;
//     val.nMax = 31;
//     val.nMin = 0;
//     UIManagePtr->SetPropertyValue(val,m_strSliderVolum,m_pWndTree);
     
    Value_WindowOwer owerVal;
    owerVal.pWnd = UIManagePtr->GetWindowPtr( g_stcStrConfCnsCtrlDlg );
    UIManagePtr->SetPropertyValue(owerVal, g_stcStrVolumCtrlDlg );
    return true;
}

void CVolumCtrlLogic::Clear()
{
	if ( m_pWndTree != NULL )
	{
		UIManagePtr->ShowWindow( g_stcStrVolumCtrlDlg, false );
	}
}
void CVolumCtrlLogic::UpdateVolum( s32 nPos )
{
    if ( m_pWndTree == NULL )
   {
        return ;
    }  
   Value_CSliderCtrlPos val;
   val.nPos = nPos; 
   UIManagePtr->SetPropertyValue(val,m_strSliderVolum,m_pWndTree); 

//    CString msg;
//    msg.Format("\n[CVolumCtrlLogic::UpdateVolum]vol=%d \n",nPos);
//    AfxOutputDebugString( msg );
}

void CVolumCtrlLogic::InitDlg()
{
    
  UIManagePtr->ShowWindow( g_stcStrVolumCtrlDlg ); 
  if ( m_pWndTree == NULL )
  {  
      return ;
  }
  
  if ( m_emVolumType == emVolumSpeaker )
  {  
//       BOOL32 bQuit = BusinessManagePtr->IsLocalCnsQuite();
//       if ( bQuit )
//       {
//           //显示静音图标
//           UIManagePtr->LoadScheme("SchmQuiet",m_pWndTree);
//       }
//       else
//       {
//           //显示非静音图标
//           UIManagePtr->LoadScheme("SchmUnQuiet",m_pWndTree);
//       }

      u8 vol = BusinessManagePtr->GetOutputVol();
      UpdateVolum( vol );

      UIManagePtr->LoadScheme("SchmSpeakerShow",m_pWndTree);
  }
  else
  {
//       BOOL32 bMute = BusinessManagePtr->IsLocalCnsMute();
//       if ( bMute )
//       {
//           //显示哑音图标
//           UIManagePtr->LoadScheme("SchmMute",m_pWndTree);
//       }
//       else
//       {
//           //显示非哑音图标
//           UIManagePtr->LoadScheme("SchmUnMute",m_pWndTree);
//       }
      
      u8 vol = BusinessManagePtr->GetInputVol();
      UpdateVolum( vol );

      UIManagePtr->LoadScheme("SchmMicphoneShow",m_pWndTree);

  }

}

void CVolumCtrlLogic::ShowVolum( EM_VolumType emVolum /*= emVolumSpeaker*/ , Window *pOwner /*= NULL*/ )
{   
    m_emVolumType = emVolum;

    if ( m_pWndTree == NULL )
    {
        UIManagePtr->GetWindow( g_stcStrVolumCtrlDlg );
    }
   
    
    Value_WindowOwer val;
    val.pWnd = pOwner;
    UIManagePtr->SetPropertyValue( val, g_stcStrVolumCtrlDlg );

    InitDlg();  
}


bool CVolumCtrlLogic::BtnSaveToFileClick( const IArgs & arg )
{
    bool bRe = UIManagePtr->SaveToFile( g_stcStrVolumCtrlDlg  );  
    
    return bRe;
}


bool CVolumCtrlLogic::BtnCloseClick( const IArgs & arg )
{
    bool bRe = UIManagePtr->ShowWindow( g_stcStrVolumCtrlDlg, false  );  
    
    return bRe;
}


/**	 
* 功能:  点击显示静音
* @return  bool
* @remarks  
*/
bool CVolumCtrlLogic::OnBntQuietClick( const IArgs & arg )
{ 
   

    BOOL32 re = BusinessManagePtr->IsLocalCnsQuite();
    if ( !re )
    {
        BusinessManagePtr->SetLocalCnsQuite(TRUE);
    }
    else
    {
       BusinessManagePtr->SetLocalCnsQuite(FALSE);
    }
  
  return true;
}


/**	 
* 功能:  点击显示哑音
* @return  bool
* @remarks  
*/
bool CVolumCtrlLogic::OnBntMuteClick( const IArgs & arg )
{
    BOOL32 re = BusinessManagePtr->IsLocalCnsMute();
    if ( !re )
    {
        BusinessManagePtr->SetLocalCnsMute(TRUE);
    }
    else
    {
        BusinessManagePtr->SetLocalCnsMute(FALSE);
    }
   return true;
}


//设置 音量
bool CVolumCtrlLogic::OnReleasedcaptureVolumn( const IArgs & arg ) 
{
   Value_CSliderCtrlPos pos;
   UIManagePtr->GetPropertyValue(pos,m_strSliderVolum,m_pWndTree);
   u16 wRe = NO_ERROR;
   if ( m_emVolumType == emVolumMic )
   {
       BeforeUpdateVol(emVolumMic);
       wRe =  BusinessManagePtr->AdjustInputVol( pos.nPos );
   }
   else
   {
       BeforeUpdateVol(emVolumSpeaker);
       wRe =  BusinessManagePtr->AdjustOutputVol( pos.nPos );
   }
  
   if ( wRe!= NO_ERROR )
   {
       HANDLE_ERROR( wRe );
   }
   return true;
}

 
//设置 音量
bool CVolumCtrlLogic::BtnMinusVolClick( const IArgs & arg )
{
    u8 abVol = 0;
    u16 wRe = NO_ERROR;

    switch ( m_emVolumType )
    {
    case emVolumMic:
        BeforeUpdateVol(emVolumMic);
        abVol = BusinessManagePtr->GetInputVol();
        if ( abVol > 0  )
        {
            wRe = BusinessManagePtr->AdjustInputVol( abVol - 1 );
        }
        
        break;
    default:
        BeforeUpdateVol(emVolumSpeaker);
        abVol = BusinessManagePtr->GetOutputVol();
        if (   abVol> 0 )
        {
            wRe =  BusinessManagePtr->AdjustOutputVol( abVol - 1  );
        } 
    }
     
    if ( wRe!= NO_ERROR )
    {
        HANDLE_ERROR( wRe );
    }
   return true;
}

//设置 音量
bool CVolumCtrlLogic::BtnAddVolClick( const IArgs & arg )
{
    u8 abVol = 0;
    u16 wRe = NO_ERROR;
    
    switch ( m_emVolumType )
    {
    case emVolumMic:
        BeforeUpdateVol(emVolumMic);
        abVol = BusinessManagePtr->GetInputVol();
        if ( abVol <  MAX_VOLUME)
        {
            wRe = BusinessManagePtr->AdjustInputVol( abVol + 1 ); 
        }
        
        break;
    default:
        BeforeUpdateVol(emVolumSpeaker);
        abVol = BusinessManagePtr->GetOutputVol();
        if ( abVol <  MAX_VOLUME)
        {
            wRe = BusinessManagePtr->AdjustOutputVol( abVol + 1 ); 
        }
        
    }
    
    if ( wRe!= NO_ERROR )
    {
        HANDLE_ERROR( wRe );
    }
   return true;
    
}


HRESULT CVolumCtrlLogic::OnMouseMoveVolumn( WPARAM wparam, LPARAM lparam )
{
    bool bVisible = UIManagePtr->IsVisible( g_stcStrVolumCtrlDlg );
    if ( !bVisible )
    {
        return NO_ERROR;
    }

    Value_CSliderCtrlPos pos;
    UIManagePtr->GetPropertyValue(pos,m_strSliderVolum,m_pWndTree);
    u16 wRe = NO_ERROR;
    if ( m_emVolumType == emVolumMic )
    {
        BeforeUpdateVol(emVolumMic);
        wRe =  BusinessManagePtr->AdjustInputVol( pos.nPos );
    }
    else
    {
        BeforeUpdateVol(emVolumSpeaker);
        wRe =  BusinessManagePtr->AdjustOutputVol( pos.nPos );
    }
    
    if ( wRe!= NO_ERROR )
    {
        HANDLE_ERROR( wRe );
    }
   return NO_ERROR;
}

 


/* 静音哑音通知  
	wparam = bQuite 	是静音还是哑音.TRUE 静音， FALSE 哑音
	lparam = bOn		是开启还是关闭.开启静音使当前没有音频输出,反之是关闭静音*/
HRESULT CVolumCtrlLogic::OnMuteInd( WPARAM wparam, LPARAM lparam)
{   
    bool bVisible = UIManagePtr->IsVisible( g_stcStrVolumCtrlDlg );
    if ( !bVisible )
    {
        return NO_ERROR;
    }

    BOOL32 bQuiet = (BOOL32)wparam;
    BOOL32 bSucess = (BOOL32)lparam;
    
    if ( bQuiet && m_emVolumType == emVolumSpeaker )
    {   
        InitDlg();
    }
    else if( m_emVolumType == emVolumMic )
    {
       InitDlg();
    }
    return NO_ERROR;
}


HRESULT CVolumCtrlLogic::OnInputInd( WPARAM wparam, LPARAM lparam)
{   
    bool bVisible = UIManagePtr->IsVisible( g_stcStrVolumCtrlDlg );
    if ( !bVisible )
    {
        return NO_ERROR;
    }

    if( m_emVolumType == emVolumMic )
    {
       InitDlg();

//        u8 nVol = (u8)wparam;
//        CString msg;
//        msg.Format("\n------消息 vol=%d----- \n",nVol);
//       AfxOutputDebugString( msg );
    }
    return NO_ERROR;
}


HRESULT CVolumCtrlLogic::OnOutputInd( WPARAM wparam, LPARAM lparam)
{
    bool bVisible = UIManagePtr->IsVisible( g_stcStrVolumCtrlDlg );
    if ( !bVisible )
    {
        return NO_ERROR;
    }

    if( m_emVolumType == emVolumSpeaker )
    {
       InitDlg();
    }
    return NO_ERROR;
}

void CVolumCtrlLogic::BeforeUpdateVol( EM_VolumType emVol/* = emVolumSpeaker */) 
{
    if ( emVol == emVolumSpeaker )
    {
        BOOL bQuite = BusinessManagePtr->IsLocalCnsQuite();
        if ( bQuite )
        {
            BusinessManagePtr->SetLocalCnsQuite( FALSE );
        }
    }
    else
    {
        BOOL bMute = BusinessManagePtr->IsLocalCnsMute();
        if ( bMute )
        {
            BusinessManagePtr->SetLocalCnsMute( FALSE );
        } 
    }
   
   
}

 
