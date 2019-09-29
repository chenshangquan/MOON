// CameraLogic.cpp: implementation of the CCameraLogic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CameraLogic.h"
CCameraLogic *CCameraLogic::m_pLogic = NULL;

typedef VOID (*WINSDK_RegTouchWindow)(HWND hWnd);
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
const String CCameraLogic::m_strBtnOpenCameraSwitch = "TextCameraDlg/BtnOpenCameraSwitch";
const String CCameraLogic::m_strBtnReduce = "OrderedBackGroundDlg/OrderPositionDlg/BtnReduce";
const String CCameraLogic::m_strBtnEnlarge = "OrderedBackGroundDlg/OrderPositionDlg/BtnEnlarge";

CCameraLogic::CCameraLogic()
{   
    m_emRecallNum = emDCamRecallOne;
}

CCameraLogic::~CCameraLogic()
{
    if ( m_pLogic != NULL )
    {   
        UnRegMsg();
        UnRegFunc();
        delete m_pLogic;
        m_pLogic = NULL;
	}
}

CCameraLogic* CCameraLogic::GetLogicPtr()
{
    if ( m_pLogic == NULL )
    {
        m_pLogic = new CCameraLogic(); 
    } 
    return m_pLogic;
}

void CCameraLogic::RegMsg()
{
    REG_MSG_HANDLER( UI_CNS_DCAMSTATE_NTY, CCameraLogic::OnDCamStateNty, m_pLogic, CCameraLogic ); 
    REG_MSG_HANDLER( UI_CNS_DCAMPOWER_IND, CCameraLogic::OnDCamPowerInd, m_pLogic, CCameraLogic ); 
}

void CCameraLogic::UnRegMsg()
{
    
}


bool CCameraLogic::RegCBFun()
{   
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::InitWnd", CCameraLogic::InitWnd, m_pLogic, CCameraLogic )

    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnOpenCameraSwitch", CCameraLogic::OnBtnOpenCameraSwitch, m_pLogic, CCameraLogic );
	REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnClickOrderPosition1", CCameraLogic::OnClickOrderPosition1, m_pLogic, CCameraLogic );
    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnClickOrderPosition2", CCameraLogic::OnClickOrderPosition2, m_pLogic, CCameraLogic );
    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnClickOrderPosition3", CCameraLogic::OnClickOrderPosition3, m_pLogic, CCameraLogic );

    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBeginReduce", CCameraLogic::OnBeginReduce, m_pLogic, CCameraLogic );
    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBeginEnlarge", CCameraLogic::OnBeginEnlarge, m_pLogic, CCameraLogic );

    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnReduce", CCameraLogic::OnBtnReduce, m_pLogic, CCameraLogic );
    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnEnlarge", CCameraLogic::OnBtnEnlarge, m_pLogic, CCameraLogic );
    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnFocus", CCameraLogic::OnBtnFocus, m_pLogic, CCameraLogic );
    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnWhiteBalance", CCameraLogic::OnBtnWhiteBalance, m_pLogic, CCameraLogic );
    REG_GOBAL_MEMBER_FUNC( "CCameraLogic::OnBtnSave", CCameraLogic::OnBtnSave, m_pLogic, CCameraLogic );
    return true;
}

bool CCameraLogic::UnRegFunc()
{
    return true;
}

bool CCameraLogic::InitWnd( const IArgs & args )
{   
    CWndLogicBase::InitWnd( args );
       
    OSVERSIONINFOEX osvi;
    //利用OSVERSIONINFOEX结构调用GetVersionEx()函数
    //如果调用失败，可尝试使用OSVERSIONINFO结构
    ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    if( !GetVersionEx((OSVERSIONINFO*)&osvi) )
    {
        osvi.dwOSVersionInfoSize=sizeof(OSVERSIONINFO);
        if(!GetVersionEx((OSVERSIONINFO*)&osvi))
            return false;
    }
    //xp以上版本才有触摸事件
    if ( osvi.dwMajorVersion > 5 )
    {  
        //注册响应WM_TOUCH的窗口
        Window* pWnd = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnReduce, m_pWndTree ); 
        Window* pWnd1 = UIFACTORYMGR_PTR->GetWindowPtr( m_strBtnEnlarge, m_pWndTree ); 
        if ( pWnd->GetSafeHwnd() != NULL && pWnd1->GetSafeHwnd() != NULL )
        {
            WINSDK_RegTouchWindow _WINSDK_RegTouchWindow;
            
            HINSTANCE hInstLibrary = LoadLibrary("windowsexsdk.dll");
            if (hInstLibrary != NULL)
            {
                _WINSDK_RegTouchWindow = (WINSDK_RegTouchWindow)GetProcAddress( hInstLibrary, "WINSDK_RegTouchWindow" );
                if ( _WINSDK_RegTouchWindow != NULL )
                {
                    _WINSDK_RegTouchWindow( pWnd->GetSafeHwnd() );
                    _WINSDK_RegTouchWindow( pWnd1->GetSafeHwnd() );                  
                }
                FreeLibrary( hInstLibrary );
            }
        } 
    }

    return true;
}


bool CCameraLogic::OnBtnOpenCameraSwitch( const IArgs& args )
{
    bool bOn = false;
    UIFACTORYMGR_PTR->GetSwitchState( m_strBtnOpenCameraSwitch, bOn, m_pWndTree );

    UIFACTORYMGR_PTR->EnableWindow( m_strBtnOpenCameraSwitch, false, m_pWndTree );

    if ( bOn )
    {
        ComInterface->SetDCamPower( emDCamPowerOn );
    }
    else
    {
        ComInterface->SetDCamPower( emDCamPowerOff );
    }

    return true;
}


bool CCameraLogic::OnClickOrderPosition1( const IArgs& args )
{
    ComInterface->SetDCamRecall( emDCamRecallOne );

	return true;
}

bool CCameraLogic::OnClickOrderPosition2( const IArgs& args )
{
    ComInterface->SetDCamRecall( emDCamRecallTwo );

	return true;
}

bool CCameraLogic::OnClickOrderPosition3( const IArgs& args )
{
    ComInterface->SetDCamRecall( emDCamRecallThree );

	return true;
}

bool CCameraLogic::OnBeginReduce( const IArgs& args )
{
    ComInterface->SetDCamZoom( emDCamZoomWide, emCnStart );
    return true;
}

bool CCameraLogic::OnBeginEnlarge( const IArgs& args )
{
    ComInterface->SetDCamZoom( emDCamZoomTele, emCnStart );
    return true;
}

bool CCameraLogic::OnBtnReduce( const IArgs& args )
{
    //ComInterface->SetDCamZoom( emWide, TRUE );
    ComInterface->SetDCamZoom( emDCamZoomWide );
    return true;
}

bool CCameraLogic::OnBtnEnlarge( const IArgs& args )
{
    //ComInterface->SetDCamZoom( emTele, TRUE );
    ComInterface->SetDCamZoom( emDCamZoomTele );
    return true;
}

bool CCameraLogic::OnBtnFocus( const IArgs& args )
{
    ComInterface->SetDCamAFMode( emDCamAFOn );
    return true;
}

bool CCameraLogic::OnBtnWhiteBalance( const IArgs& args )
{
    ComInterface->SetDCamWBMode( emDcamWBAuto );
    return true;   
}

bool CCameraLogic::OnBtnSave( const IArgs& args )
{
    ComInterface->SetDCamPreset( m_emRecallNum );
    return true;   
}



HRESULT CCameraLogic::OnDCamStateNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }

    TCentreDCamCfg tDCamCfg = *(TCentreDCamCfg*)wparam;

    if ( tDCamCfg.emDCamPowerMode == emDCamPowerOn )
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmCameraOn", m_pWndTree );
        
        m_emRecallNum = tDCamCfg.emDCamRecallNum;
        if ( m_emRecallNum == emDCamRecallOne )
        {
            UIFACTORYMGR_PTR->LoadScheme( "SchmOrderPosition1Dlg", m_pWndTree );
        }
        else if ( m_emRecallNum == emDCamRecallTwo )
        {
            UIFACTORYMGR_PTR->LoadScheme( "SchmOrderPosition2Dlg", m_pWndTree );
        }
        else if ( m_emRecallNum == emDCamRecallThree )
        {
            UIFACTORYMGR_PTR->LoadScheme( "SchmOrderPosition3Dlg", m_pWndTree );
        }
    }
    else
    {
        UIFACTORYMGR_PTR->LoadScheme( "SchmCameraOff", m_pWndTree );

        if ( tDCamCfg.emDCamPowerMode == emDCamPowerDown )
        {
            UIFACTORYMGR_PTR->EnableWindow( m_strBtnOpenCameraSwitch, false, m_pWndTree );
        }
    }

    return NO_ERROR;
}

HRESULT CCameraLogic::OnDCamPowerInd( WPARAM wparam, LPARAM lparam )
{
    BOOL bOk = (BOOL)wparam;    
    //Ind回false时不会再有Nty消息，恢复按钮状态
    if ( !bOk )
    {
        EmDCamPower emPower = (EmDCamPower)lparam;
        if ( emPower == emDCamPowerOn )
        {
            UIFACTORYMGR_PTR->LoadScheme( "SchmCameraOff", m_pWndTree );
        }
        else
        {
            UIFACTORYMGR_PTR->LoadScheme( "SchmCameraOn", m_pWndTree );
        }
    }
     
    return NO_ERROR;
}

/*
HRESULT CCameraLogic::OnSchStateNty( WPARAM wparam, LPARAM lparam )
{
    if ( m_pWndTree == NULL )
    {
        return NO_ERROR;
    }
    
    TCentreSchCfg tSchCfg = *(TCentreSchCfg*)wparam;
    
    //电源
    if ( tSchCfg.emSchPower == emSchPowerOn )
    {
        UIFACTORYMGR_PTR->EnableWindow( m_strBtnOpenCameraSwitch, true, m_pWndTree );
    }
    else
    {
        UIFACTORYMGR_PTR->EnableWindow( m_strBtnOpenCameraSwitch, false, m_pWndTree );
    }
    return NO_ERROR;
}
*/

void CCameraLogic::Clear()
{   
}

